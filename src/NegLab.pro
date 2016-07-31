#-------------------------------------------------
#
# Project created by QtCreator 2016-06-19T14:10:57
#
#-------------------------------------------------

QT       += core gui

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

CONFIG(debug, debug|release) {
    message("debug mode")

    LIBS += -L$$PWD/OpenCV/x64/vc12/lib
    LIBS += -lopencv_core2413d -lopencv_highgui2413d -lopencv_imgproc2413d

    DESTDIR = $$OUT_PWD/debug

    install_exiftool.path   = $$DESTDIR
    install_exiftool.files  = $$PWD/ExifTool/exiftool.exe

    install_opencv.path   = $$DESTDIR
    install_opencv.files += $$PWD/OpenCV/x64/vc12/bin/opencv_core2413d.dll \
                            $$PWD/OpenCV/x64/vc12/bin/opencv_highgui2413d.dll \
                            $$PWD/OpenCV/x64/vc12/bin/opencv_imgproc2413d.dll

    install_qtlibs.path =   $$DESTDIR
    install_qtlibs.files =  $$[QT_INSTALL_BINS]/Qt5Cored.dll \
                            $$[QT_INSTALL_BINS]/Qt5Guid.dll \
                            $$[QT_INSTALL_BINS]/Qt5Widgetsd.dll \
                            $$[QT_INSTALL_BINS]/Qt5PrintSupportd.dll
}
else {
    message("release mode")

    LIBS += -L$$PWD/OpenCV/x64/vc12/lib
    LIBS += -lopencv_core2413 -lopencv_highgui2413 -lopencv_imgproc2413

    DESTDIR = $$OUT_PWD/release

    install_exiftool.path   = $$DESTDIR
    install_exiftool.files  = $$PWD/ExifTool/exiftool.exe

    install_opencv.path   = $$DESTDIR
    install_opencv.files += $$PWD/OpenCV/x64/vc12/bin/opencv_core2413.dll \
                            $$PWD/OpenCV/x64/vc12/bin/opencv_highgui2413.dll \
                            $$PWD/OpenCV/x64/vc12/bin/opencv_imgproc2413.dll

    install_qtlibs.path =   $$DESTDIR
    install_qtlibs.files =  $$[QT_INSTALL_BINS]/Qt5Core.dll \
                            $$[QT_INSTALL_BINS]/Qt5Gui.dll \
                            $$[QT_INSTALL_BINS]/Qt5Widgets.dll \
                            $$[QT_INSTALL_BINS]/Qt5PrintSupport.dll
}

INSTALLS += install_exiftool \
            install_opencv \
            install_qtlibs
