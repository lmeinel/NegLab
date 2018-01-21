#ifndef IMAGEPREVIEWWINDOW_H
#define IMAGEPREVIEWWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QScrollBar>

#include <opencv2/opencv.hpp>

namespace Ui {
class ImagePreviewWindow;
}

class ImagePreviewWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImagePreviewWindow(QWidget *parent = 0);
    ~ImagePreviewWindow();

    void setImage(const cv::Mat &mat);
    //void open();
    //void saveAs();
    //void print();
    //void copy();
    //void paste();
    void zoomIn();
    void zoomOut();
    void normalSize();
    void fitToWindow();
    //void about();

private:
    QImage convertMat2QImage(const cv::Mat &mat);

    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    Ui::ImagePreviewWindow *ui;

    QImage image;
    //QLabel *imageLabel;
    //QScrollArea *scrollArea;
    double scaleFactor;
};

#endif // IMAGEPREVIEWWINDOW_H
