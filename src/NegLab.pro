#-------------------------------------------------
#
# Project created by QtCreator 2016-06-19T14:10:57
#
#-------------------------------------------------

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = NegLab
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
        invertcore.cpp \
        filehandler.cpp \
        qcustomplot.cpp

HEADERS  += mainwindow.h \
            invertcore.h \
            filehandler.h \
            qcustomplot.h

FORMS    += mainwindow.ui

INCLUDEPATH += $$PWD/OpenCV/include
INCLUDEPATH += $$PWD/OpenCV/include/opencv

LIBS += -L$$PWD/OpenCV/x64/vc12/lib
LIBS += -lopencv_core2413d -lopencv_highgui2413d -lopencv_imgproc2413d

# copy other files to build dir
CONFIG(debug, debug|release) {
    DESTDIR = $$OUT_PWD/debug
} else {
    DESTDIR = $$OUT_PWD/release
}

install_it.path = $$DESTDIR
install_it.files += $$PWD/ExifTool/exiftool.exe \
                    $$PWD/OpenCV/x64/vc12/bin/opencv_core2413d.dll \
                    $$PWD/OpenCV/x64/vc12/bin/opencv_highgui2413d.dll \
                    $$PWD/OpenCV/x64/vc12/bin/opencv_imgproc2413d.dll

INSTALLS += install_it
