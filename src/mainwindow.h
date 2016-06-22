#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <opencv2/opencv.hpp>

#include "filehandler.h"
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

    void on_pushButton_Preview_clicked();

    void on_lineEdit_PosPrefix_editingFinished();

    void on_comboBox_PosType_currentTextChanged(const QString &arg1);

    void on_lineEdit_NegFilter_editingFinished();

    void on_pushButton_Invert_clicked();

    void on_comboBox_Mode_currentTextChanged(const QString &arg1);

private:
    QImage convertMat2QImage888(const cv::Mat &input);

    Ui::MainWindow  *ui;
    FileHandler     m_filehandler;
    InvertCore      m_inverter;
};

#endif // MAINWINDOW_H
