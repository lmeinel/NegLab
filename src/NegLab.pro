#-------------------------------------------------
#
# Project created by QtCreator 2016-06-19T14:10:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NegLab
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    invertcore.cpp \
    filehandler.cpp

HEADERS  += mainwindow.h \
    invertcore.h \
    filehandler.h

FORMS    += mainwindow.ui

INCLUDEPATH += $$PWD/OpenCV/include
INCLUDEPATH += $$PWD/OpenCV/include/opencv

LIBS += -L$$PWD/OpenCV/x64/vc12/lib
LIBS += -lopencv_core2413d -lopencv_highgui2413d -lopencv_imgproc2413d

