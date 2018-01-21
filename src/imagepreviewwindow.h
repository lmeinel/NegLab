#ifndef IMAGEPREVIEWWINDOW_H
#define IMAGEPREVIEWWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QScrollBar>
#include <QLabel>

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

    void setImage(const cv::Mat &mat, std::string filename);

protected:
    void resizeEvent(QResizeEvent *e);

private slots:
    void on_pushButton_zoomIn_clicked();
    void on_pushButton_zoomOut_clicked();
    void on_pushButton_zoomFit_clicked();
    void on_pushButton_zoomOrig_clicked();

private:
    Ui::ImagePreviewWindow *ui;

    QImage convertMat2QImage(const cv::Mat &mat);
    void updateHistogram(const cv::Mat &mat);
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    void zoomIn();
    void zoomOut();
    void normalSize();
    void fitToWindow();
    //void about();

    QImage  m_image;
    QLabel* m_imageLabel;
    double  m_scaleFactor;
    bool    m_fitToWindow = true;
};

#endif // IMAGEPREVIEWWINDOW_H
