#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QApplication>
#include <QProgressBar>
//#include <QDebug>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // init file handler
    m_filehandler.setInputPath("");
    m_filehandler.setNameFilter(ui->lineEdit_NegFilter->text());
    m_filehandler.setOutputPath("");
    m_filehandler.setOutputPrefix(ui->lineEdit_PosPrefix->text());
    m_filehandler.setOutputType(ui->comboBox_PosType->currentText());

    // init inverter
    on_comboBox_Mode_currentTextChanged(ui->comboBox_Mode->currentText());
    on_spinBox_NegHdVal_valueChanged(ui->spinBox_NegHdVal->value());
    on_spinBox_NegLdVal_valueChanged(ui->spinBox_NegLdVal->value());
    on_spinBox_PosBlackVal_valueChanged(ui->spinBox_PosBlackVal->value());
    on_spinBox_PosWhiteVal_valueChanged(ui->spinBox_PosWhiteVal->value());
    m_inverter.setType(CV_16UC1);

    // init Tone Curve widget
    updateToneCurve();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_BrowseNeg_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Negatives Path"));
    ui->lineEdit_NegPath->setText(path);

    m_filehandler.setInputPath(path);
    m_filehandler.analyzeDirectory();
    m_filehandler.setOutputPath();

    ui->lineEdit_PosPath->setText(m_filehandler.getOutputPath());
}

void MainWindow::on_pushButton_BrowsePos_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Positives Path"));
    ui->lineEdit_PosPath->setText(path);

    m_filehandler.setOutputPath(path);
}

void MainWindow::on_pushButton_Preview_clicked()
{
    // disable button
    ui->pushButton_Preview->setEnabled(false);

    // clear list widget
    ui->listWidget_NegPreview->clear();
    qApp->processEvents();

    // init file path
    QStringList files = m_filehandler.getFileList();
    QString dirPath = m_filehandler.getInputPath();

    // update statusBar
    QProgressBar *progressBar = new QProgressBar;
    progressBar->setMaximum(files.length());
    ui->statusBar->addPermanentWidget(progressBar, 0);
    ui->statusBar->showMessage(QString("Loading Previews..."));
    progressBar->setValue(0);
    qApp->processEvents();

    // load previews
    for(int i=0; i<files.length(); i++)
    {
        // load image
        QString file = files.at(i);
        QString path = QDir(dirPath).filePath(file);
        QImage image;
        image.load(path);
        QImage thumb = image.scaled(100, 100, Qt::KeepAspectRatio, Qt::FastTransformation);

        // add thumb to preview list
        QListWidgetItem *itm = new QListWidgetItem(file);
        //itm->setIcon(QIcon(path));
        itm->setIcon(QPixmap::fromImage(thumb));
        ui->listWidget_NegPreview->addItem(itm);

        progressBar->setValue(i+1);
        qApp->processEvents();
    }

    // clear statusBar
    ui->statusBar->clearMessage();
    ui->statusBar->removeWidget(progressBar);

    ui->pushButton_Preview->setEnabled(true);
}

void MainWindow::on_lineEdit_PosPrefix_editingFinished()
{
    if(ui->lineEdit_PosPrefix->text() != m_filehandler.getOutputPrefix())
    {
        ui->statusBar->showMessage(tr("Changed output prefix to \"") + ui->lineEdit_PosPrefix->text() + tr("\"."),1000);
        m_filehandler.setOutputPrefix(ui->lineEdit_PosPrefix->text());
    }
}

void MainWindow::on_comboBox_PosType_currentTextChanged(const QString &arg1)
{
    ui->statusBar->showMessage(tr("Changed output type to \"") + arg1 + tr("\"."), 1000);
    m_filehandler.setOutputType(arg1);
}

void MainWindow::on_lineEdit_NegFilter_editingFinished()
{
    if(ui->lineEdit_NegFilter->text() != m_filehandler.getNameFilter())
    {
        ui->statusBar->showMessage(tr("Changed input filter to \"") + ui->lineEdit_NegFilter->text() + tr("\"."), 1000);
        m_filehandler.setNameFilter(ui->lineEdit_NegFilter->text());
    }
}

void MainWindow::on_pushButton_Invert_clicked()
{
    ui->pushButton_Invert->setEnabled(false);

    // clear list widget
    ui->listWidget_NegPreview->clear();
    ui->listWidget_PosPreview->clear();
    qApp->processEvents();

    // init file path
    QStringList files = m_filehandler.getFileList();
    QString dirPath = m_filehandler.getInputPath();

    // update statusBar
    QProgressBar *progressBar = new QProgressBar;
    progressBar->setMaximum(files.length());
    ui->statusBar->addPermanentWidget(progressBar, 0);
    ui->statusBar->showMessage(QString("Inverting..."));
    progressBar->setValue(0);
    qApp->processEvents();

    // init inverter
    m_inverter.setType(CV_16UC1);
    m_inverter.updateLut();

    // INVERT
    for(int i=0; i<files.length(); i++)
    {
        // load image
        QString fileNeg = files.at(i);
        QString pathNeg = QDir(dirPath).filePath(fileNeg);
        cv::Mat matNegFull = cv::imread(pathNeg.toUtf8().data(), CV_LOAD_IMAGE_ANYDEPTH);

        // create negative thumb
        cv::Mat matNegScaled; double scale = matNegFull.rows / 100.0;
        cv::resize(matNegFull, matNegScaled, cv::Size(matNegFull.cols / scale , 100), 0, 0, cv::INTER_NEAREST);

        // convert to Qimage
        QImage thumbNeg = convertMat2QImage(matNegScaled);

        // add thumb to preview list
        QListWidgetItem *itmNeg = new QListWidgetItem(fileNeg);
        itmNeg->setIcon(QPixmap::fromImage(thumbNeg));
        ui->listWidget_NegPreview->addItem(itmNeg);
        qApp->processEvents();

        // invert
        cv::Mat matPosFull = m_inverter.invert(matNegFull);

        // create negative thumb
        cv::Mat matPosScaled;
        cv::resize(matPosFull, matPosScaled, cv::Size(matPosFull.cols / scale , 100), 0, 0, cv::INTER_NEAREST);

        // convert to Qimage
        QImage thumbPos = convertMat2QImage(matPosScaled);


        // add thumb to preview list
        // load image
        QString filePos = m_filehandler.getOutputPrefix() + fileNeg;
        QListWidgetItem *itmPos = new QListWidgetItem(filePos);
        itmPos->setIcon(QPixmap::fromImage(thumbPos));
        ui->listWidget_PosPreview->addItem(itmPos);
        qApp->processEvents();

        progressBar->setValue(i+1);
        qApp->processEvents();
    }

    // clear statusBar
    ui->statusBar->clearMessage();
    ui->statusBar->removeWidget(progressBar);

    ui->pushButton_Invert->setEnabled(true);

    }

void MainWindow::on_comboBox_Mode_currentTextChanged(const QString &arg1)
{
    if(arg1 == "Bitwise Not")
    {
        m_inverter.setMode(BITWISE_NOT);
    }
    else if(arg1 == "Tone Curve")
    {
        m_inverter.setMode(TONE_CURVE);
    }

    updateToneCurve();
}

QImage MainWindow::convertMat2QImage(const cv::Mat &mat)
{
    Q_ASSERT(mat.channels() == 1 || mat.channels() == 3);
    Q_ASSERT(mat.depth() == CV_8U || mat.depth() == CV_16U);

    if(mat.empty())
        return QImage();

    // set output format
    QImage::Format format;
    if(mat.channels() == 1)
    {
        format = QImage::Format_Grayscale8;
    }
    else
    {
        format = QImage::Format_RGB888;
    }

    cv::Mat mat8U;

    // reduce bit depth to 8-bit
    if (mat.depth() != CV_8U)
    {
        mat.convertTo(mat8U, CV_8UC(mat.channels()), mat.depth() == CV_16U ? 1/255.0 : 255.0);
    }
    else
    {
        mat8U = mat;
    }

    QImage img(mat8U.data, mat8U.cols, mat8U.rows, static_cast<int>(mat8U.step), format);
    return img.copy();
}

void MainWindow::updateToneCurve()
{
    // generate some data:
    QVector<double> x0(101), y0(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
      x0[i] = (65536.0 / 100.0) * i;
      y0[i] = static_cast<double>(m_inverter.applyToneCurve(static_cast<int>(x0[i])));
    }
    // create graph and assign data to it:
    ui->widget_ToneCurve->addGraph(ui->widget_ToneCurve->xAxis, ui->widget_ToneCurve->yAxis);
    ui->widget_ToneCurve->graph(0)->setData(x0, y0);

    // configure axis labels:
    ui->widget_ToneCurve->xAxis->setLabel("Negative");
    ui->widget_ToneCurve->yAxis->setLabel("Positive");

    //configure axis ticks
    QVector<double> ticks;
    ticks << 0  << 1*65536/4-1 << 2*65536/4-1 << 3*65536/4-1 << 65535;
    ui->widget_ToneCurve->xAxis->setAutoTicks(false);
    ui->widget_ToneCurve->xAxis->setTickVector(ticks);
    ui->widget_ToneCurve->yAxis->setAutoTicks(false);
    ui->widget_ToneCurve->yAxis->setTickVector(ticks);

    ui->widget_ToneCurve->xAxis->setTickLabelFont(QFont(QFont().family(), 6));
    ui->widget_ToneCurve->yAxis->setTickLabelFont(QFont(QFont().family(), 6));
    ui->widget_ToneCurve->xAxis->setTickLabelRotation(-45.0);
    ui->widget_ToneCurve->yAxis->setTickLabelRotation(-45.0);

    // set axes ranges, so we see all data:
    ui->widget_ToneCurve->xAxis->setRange(0, 65536);
    ui->widget_ToneCurve->yAxis->setRange(0, 65536);

    // draw anchors
    ui->widget_ToneCurve->addGraph(ui->widget_ToneCurve->xAxis, ui->widget_ToneCurve->yAxis);
    ui->widget_ToneCurve->graph(1)->setPen(QColor(255, 0, 0, 255));
    ui->widget_ToneCurve->graph(1)->setLineStyle(QCPGraph::lsNone);
    ui->widget_ToneCurve->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 8));
    QVector<double> x1(2), y1(2);
    x1[0] = ui->spinBox_NegHdVal->value();
    x1[1] = ui->spinBox_NegLdVal->value();
    y1[0] = ui->spinBox_PosWhiteVal->value();
    y1[1] = ui->spinBox_PosBlackVal->value();
    ui->widget_ToneCurve->graph(1)->setData(x1, y1);

    ui->widget_ToneCurve->replot();
}

void MainWindow::on_spinBox_NegHdVal_valueChanged(int arg1)
{
    m_inverter.setNegHighDensity(arg1);
    updateToneCurve();
}

void MainWindow::on_spinBox_NegLdVal_valueChanged(int arg1)
{
    m_inverter.setNegLowDensity(arg1);
    updateToneCurve();
}

void MainWindow::on_spinBox_PosWhiteVal_valueChanged(int arg1)
{
    m_inverter.setPosWhite(arg1);
    updateToneCurve();
}

void MainWindow::on_spinBox_PosBlackVal_valueChanged(int arg1)
{
    m_inverter.setPosBlack(arg1);
    updateToneCurve();
}
