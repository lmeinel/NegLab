#include <QtWidgets>
#include <QDebug>

#include "imagepreviewwindow.h"
#include "ui_imagepreviewwindow.h"

ImagePreviewWindow::ImagePreviewWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImagePreviewWindow),
    m_imageLabel(new QLabel),
    m_scaleFactor(1.0),
    m_fitToWindow(true)
{
    ui->setupUi(this);

    // setup image area
    m_imageLabel->setBackgroundRole(QPalette::Base);
    m_imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    m_imageLabel->setScaledContents(true);

    ui->scrollArea->setBackgroundRole(QPalette::Dark);
    ui->scrollArea->setWidget(m_imageLabel);
    ui->scrollArea->setVisible(false);
    ui->scrollArea->setWidgetResizable(false);
    //setCentralWidget(ui->scrollArea);
}

ImagePreviewWindow::~ImagePreviewWindow()
{
    delete ui;
}

void ImagePreviewWindow::setImage(const cv::Mat &mat, std::string filename)
{
    // update image
    m_image = convertMat2QImage(mat);
    m_imageLabel->setPixmap(QPixmap::fromImage(m_image));
    m_scaleFactor = 1.0; //reset scale factor

    ui->scrollArea->setVisible(true);
    fitToWindow();

    // update histogram
    updateHistogram(mat);

    // update image information
    ui->label_fileName->setText(QString(filename.c_str()));

    int bitDepth;
    int channels = 1;
    switch (mat.type()) {
    case CV_8UC1:
        bitDepth = 8;
        ui->label_bitDepth->setText("8");
        break;
    case CV_16UC1:
        bitDepth = 16;
        ui->label_bitDepth->setText("16");
        break;
    default:
        bitDepth = 1;
        ui->label_bitDepth->setText("unknown");
        break;
    }
    double range = pow(2, bitDepth) - 1.0;
    ui->label_range->setText("[ 0 ; " + QString::number(range) + " ]");

    double minVal, maxVal;
    cv::minMaxLoc(mat, &minVal, &maxVal);
    ui->label_minValue->setText(QString::number(minVal));
    ui->label_maxValue->setText(QString::number(maxVal));

    double spread = (maxVal - minVal) / range;
    ui->label_spread->setText(QString::number(spread * 100, 'f', 2) + "%");

    ui->label_width->setText(QString::number(mat.cols) + " px");
    ui->label_height->setText(QString::number(mat.rows) + " px");

    double rmp = static_cast<double>(mat.cols*mat.rows) / 1000000;
    ui->label_resolution->setText(QString::number(rmp) + " MP");

    double smb = static_cast<double>(mat.cols * mat.rows * bitDepth * channels) / (8.0*1000000);
    ui->label_size->setText(QString::number(smb) + " MB");

    // update window title
    std::string windowTitle = "Image Preview - " + filename;
    setWindowTitle(QString(windowTitle.c_str()));

}

void ImagePreviewWindow::resizeEvent(QResizeEvent *e)
{
    if(!m_image.isNull() && m_fitToWindow)
        fitToWindow();

    QWidget::resizeEvent(e);
}

QImage ImagePreviewWindow::convertMat2QImage(const cv::Mat &mat)
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

void ImagePreviewWindow::updateHistogram(const cv::Mat &mat)
{
    // calculate histogram
    cv::Mat hist;
    int histSize = 256;
    float range[] = { 0, 65535 };
    const float *ranges[] = { range };

    cv::calcHist( &mat, 1, 0, cv::Mat(),  hist, 1, &histSize, ranges, true, false );

    double minVal, maxVal;
    cv::minMaxIdx(hist, &minVal, &maxVal);
    //qDebug() << minVal;
    //qDebug() << maxVal;

    //int type = hist.type();

    // update plot
    QVector<double> x0(256), y0(256);
    for (int i=0; i<256; i++)
    {
      x0[i] = (65536.0 / 255.0) * i;
      y0[i] = static_cast<double>(hist.at<float>(i));
    }

    // create graph and assign data to it:
    ui->widget_Histogram->addGraph(ui->widget_Histogram->xAxis, ui->widget_Histogram->yAxis);
    ui->widget_Histogram->graph(0)->setData(x0, y0);
    ui->widget_Histogram->graph(0)->setPen(QPen(QColor(200, 200, 200), 2));
    ui->widget_Histogram->graph(0)->setBrush(QBrush(QColor(200, 200, 200, 160)));

    //configure axis ticks
    QVector<double> xticks;
    xticks << 0 << 65535;
    ui->widget_Histogram->xAxis->setAutoTicks(false);
    ui->widget_Histogram->xAxis->setTickVector(xticks);

    //QVector<double> yticks;
    //yticks << 0 << maxVal;
    //ui->widget_Histogram->yAxis->setAutoTicks(false);
    //ui->widget_Histogram->yAxis->setTickVector(yticks);

    ui->widget_Histogram->xAxis->setTickLabelFont(QFont(QFont().family(), 6));
    ui->widget_Histogram->yAxis->setTickLabelFont(QFont(QFont().family(), 6));
    //ui->widget_Histogram->xAxis->setTickLabelRotation(-45.0);
    //ui->widget_Histogram->yAxis->setTickLabelRotation(-45.0);

    // set axes ranges, so we see all data:
    ui->widget_Histogram->xAxis->setRange(0, 65536);
    ui->widget_Histogram->yAxis->setRange(0, maxVal);

    // set some pens, brushes and backgrounds:
    ui->widget_Histogram->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->widget_Histogram->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->widget_Histogram->xAxis->setTickPen(QPen(Qt::white, 1));
    ui->widget_Histogram->yAxis->setTickPen(QPen(Qt::white, 1));
    ui->widget_Histogram->xAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->widget_Histogram->yAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->widget_Histogram->xAxis->setTickLabelColor(Qt::white);
    ui->widget_Histogram->yAxis->setTickLabelColor(Qt::white);
    ui->widget_Histogram->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->widget_Histogram->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->widget_Histogram->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->widget_Histogram->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->widget_Histogram->xAxis->grid()->setSubGridVisible(true);
    ui->widget_Histogram->yAxis->grid()->setSubGridVisible(true);
    ui->widget_Histogram->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->widget_Histogram->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->widget_Histogram->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    ui->widget_Histogram->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    plotGradient.setColorAt(1, QColor(50, 50, 50));
    ui->widget_Histogram->setBackground(plotGradient);

    ui->widget_Histogram->replot();
}

void ImagePreviewWindow::zoomIn()
{
    scaleImage(1.25);
}

void ImagePreviewWindow::zoomOut()
{
    scaleImage(0.8);
}

void ImagePreviewWindow::scaleImage(double factor)
{
    Q_ASSERT(m_imageLabel->pixmap());
    m_scaleFactor *= factor;
    m_imageLabel->resize(m_scaleFactor * m_imageLabel->pixmap()->size());

    adjustScrollBar(ui->scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(ui->scrollArea->verticalScrollBar(), factor);
}

void ImagePreviewWindow::fitToWindow()
{
    //bool fitToWindow = false;//fitToWindowAct->isChecked();
    //ui->scrollArea->setWidgetResizable(m_fitToWindow);
    //ui->scrollArea->setWidgetResizable(false);

    // calculate scale
    int hwin = ui->scrollArea->geometry().height()-2;
    int wwin = ui->scrollArea->geometry().width()-2;
    int himg = m_image.height();
    int wimg = m_image.width();

    double hscale = static_cast<double>(hwin) / static_cast<double>(himg);
    double wscale = static_cast<double>(wwin) / static_cast<double>(wimg);
    double scale = std::min(hscale, wscale);

    // set scale
    m_scaleFactor = 1.0;
    scaleImage(scale);

    //if (!m_fitToWindow)
    //    normalSize();
}

void ImagePreviewWindow::normalSize()
{
    m_imageLabel->adjustSize();
    m_scaleFactor = 1.0;
}

void ImagePreviewWindow::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}

void ImagePreviewWindow::on_pushButton_zoomIn_clicked()
{
    m_fitToWindow = false;
    zoomIn();
}

void ImagePreviewWindow::on_pushButton_zoomOut_clicked()
{
    m_fitToWindow = false;
    zoomOut();
}

void ImagePreviewWindow::on_pushButton_zoomFit_clicked()
{
    m_fitToWindow = true;
    fitToWindow();
}

void ImagePreviewWindow::on_pushButton_zoomOrig_clicked()
{
    m_fitToWindow = false;
    normalSize();
}
