#include "imagepreviewwindow.h"
#include "ui_imagepreviewwindow.h"

ImagePreviewWindow::ImagePreviewWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImagePreviewWindow),
    scaleFactor(1.0)
{
    ui->setupUi(this);

    // setup image area
    ui->imageLabel->setBackgroundRole(QPalette::Base);
    ui->imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->imageLabel->setScaledContents(true);

    ui->scrollArea->setBackgroundRole(QPalette::Dark);
    //ui->scrollArea->setWidget(imageLabel);
    ui->scrollArea->setVisible(false);
    setCentralWidget(ui->scrollArea);

    //createActions();
    //resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
}

ImagePreviewWindow::~ImagePreviewWindow()
{
    delete ui;
}

void ImagePreviewWindow::setImage(const cv::Mat &mat)
{
    scaleFactor = 1.0;
    ui->scrollArea->setVisible(true);
//    printAct->setEnabled(true);
//    fitToWindowAct->setEnabled(true);
//    //updateActions();

//    //if (!fitToWindowAct->isChecked())
//    //    imageLabel->adjustSize();

//    imageLabel->resize(imageLabel->pixmap()->size());
    image = convertMat2QImage(mat);
    ui->imageLabel->setPixmap(QPixmap::fromImage(image));
    ui->imageLabel->show();

    normalSize();
    ui->scrollArea->setWidgetResizable(false);
    ui->scrollArea->setVisible(true);
    //ui->printAct->setEnabled(true);
    //ui->fitToWindowAct->setEnabled(true);
    //updateActions();

    //if (!fitToWindowAct->isChecked())
    //    imageLabel->adjustSize();
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

void ImagePreviewWindow::zoomIn()
{
    scaleImage(1.25);
}

void ImagePreviewWindow::zoomOut()
{
    scaleImage(0.8);
}

void ImagePreviewWindow::normalSize()
{
    ui->imageLabel->adjustSize();
    scaleFactor = 1.0;
}

void ImagePreviewWindow::fitToWindow()
{
//    bool fitToWindow = fitToWindowAct->isChecked();
//    scrollArea->setWidgetResizable(fitToWindow);
//    if (!fitToWindow)
//        normalSize();
//    updateActions();
}

void ImagePreviewWindow::scaleImage(double factor)
{
    Q_ASSERT(ui->imageLabel->pixmap());
    scaleFactor *= factor;
    ui->imageLabel->resize(scaleFactor * ui->imageLabel->pixmap()->size());

    adjustScrollBar(ui->scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(ui->scrollArea->verticalScrollBar(), factor);

//    zoomInAct->setEnabled(scaleFactor < 3.0);
//    zoomOutAct->setEnabled(scaleFactor > 0.333);
}

void ImagePreviewWindow::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}
