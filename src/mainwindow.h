#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

#include <opencv2/opencv.hpp>

#include "imagepreviewwindow.h"
#include "filehandler.h"
#include "imagecache.h"
#include "invertcore.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_BrowseNeg_clicked();
    void on_pushButton_BrowsePos_clicked();
    void on_lineEdit_NegPath_editingFinished();
    void on_lineEdit_PosPath_editingFinished();
    void on_pushButton_Preview_clicked();
    void on_lineEdit_PosPrefix_editingFinished();
    void on_comboBox_PosType_currentTextChanged(const QString &arg1);
    void on_lineEdit_NegFilter_editingFinished();
    void on_pushButton_Invert_clicked();
    void on_comboBox_Mode_currentTextChanged(const QString &arg1);
    void on_spinBox_NegHdVal_valueChanged(int arg1);
    void on_spinBox_NegLdVal_valueChanged(int arg1);
    void on_spinBox_PosWhiteVal_valueChanged(int arg1);
    void on_spinBox_PosBlackVal_valueChanged(int arg1);
    void on_checkBox_syncPrevScrollbar_clicked(bool checked);
    void on_listWidget_NegPreview_itemDoubleClicked(QListWidgetItem *item);
    void on_listWidget_PosPreview_itemDoubleClicked(QListWidgetItem *item);

private:
    QImage convertMat2QImage(const cv::Mat &input);
    void updateToneCurve();

    Ui::MainWindow      *ui;
    ImagePreviewWindow  *ipwindow;
    FileHandler         m_filehandler;
    ImageCache          m_imagecache;
    InvertCore          m_inverter;

    bool                m_negativesReady;
};

#endif // MAINWINDOW_H
