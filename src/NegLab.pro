#-------------------------------------------------
#
# Project created by QtCreator 2016-06-19T14:10:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = NegLab
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
        invertcore.cpp \
        filehandler.cpp \
        qcustomplot.cpp \
        imagepreviewwindow.cpp \
        imagecache.cpp

HEADERS  += mainwindow.h \
            invertcore.h \
            filehandler.h \
            qcustomplot.h \
            imagepreviewwindow.h \
            imagecache.h

FORMS    += mainwindow.ui \
            imagepreviewwindow.ui

INCLUDEPATH += $$PWD/OpenCV/include
INCLUDEPATH += $$PWD/OpenCV/include/opencv

RC_ICONS = icon.ico

CONFIG(debug, debug|release) {
    message("debug mode")

    #LIBS += -L$$PWD/OpenCV/x64/vc12/lib
    #LIBS += -lopencv_core2413d -lopencv_highgui2413d -lopencv_imgproc2413d

    LIBS += $$PWD/OpenCV/x86/mingw/bin/libopencv_core340.dll
    LIBS += $$PWD/OpenCV/x86/mingw/bin/libopencv_highgui340.dll
    LIBS += $$PWD/OpenCV/x86/mingw/bin/libopencv_imgcodecs340.dll
    LIBS += $$PWD/OpenCV/x86/mingw/bin/libopencv_imgproc340.dll
    #LIBS += $$PWD/OpenCV/x86/mingw/bin/libopencv_features2d340.dll
    #LIBS += $$PWD/OpenCV/x86/mingw/bin/libopencv_calib3d340.dll

    DESTDIR = $$OUT_PWD/debug

    #message("INSTALL TO $$DESTDIR")
    install_exiftool.path   = $$DESTDIR
    install_exiftool.files  = $$PWD/ExifTool/exiftool.exe

    install_opencv.path   = $$DESTDIR
    install_opencv.files  = $$PWD/OpenCV/x86/mingw/bin/libopencv_core340.dll \
                            $$PWD/OpenCV/x86/mingw/bin/libopencv_highgui340.dll \
                            $$PWD/OpenCV/x86/mingw/bin/libopencv_imgcodecs340.dll \
                            $$PWD/OpenCV/x86/mingw/bin/libopencv_imgproc340.dll

    install_qtlibs.path =   $$DESTDIR
    install_qtlibs.files =  $$[QT_INSTALL_BINS]/Qt5Cored.dll \
                            $$[QT_INSTALL_BINS]/Qt5Guid.dll \
                            $$[QT_INSTALL_BINS]/Qt5Widgetsd.dll \
                            $$[QT_INSTALL_BINS]/Qt5PrintSupportd.dll
}
else {
message("release mode")

    #LIBS += -L$$PWD/OpenCV/x86/mingw/lib
    #LIBS += -lopencv_core340 -lopencv_highgui340 -lopencv_imgproc340

    LIBS += $$PWD/OpenCV/x86/mingw/bin/libopencv_core340.dll
    LIBS += $$PWD/OpenCV/x86/mingw/bin/libopencv_highgui340.dll
    LIBS += $$PWD/OpenCV/x86/mingw/bin/libopencv_imgcodecs340.dll
    LIBS += $$PWD/OpenCV/x86/mingw/bin/libopencv_imgproc340.dll
    #LIBS += $$PWD/OpenCV/x86/mingw/bin/libopencv_features2d340.dll
    #LIBS += $$PWD/OpenCV/x86/mingw/bin/libopencv_calib3d340.dll

    DESTDIR = $$OUT_PWD/release


    #message("INSTALL TO $$DESTDIR")
    install_exiftool.path   = $$DESTDIR
    install_exiftool.files  = $$PWD/ExifTool/exiftool.exe

    install_opencv.path   = $$DESTDIR
    install_opencv.files  = $$PWD/OpenCV/x86/mingw/bin/libopencv_core340.dll \
                            $$PWD/OpenCV/x86/mingw/bin/libopencv_highgui340.dll \
                            $$PWD/OpenCV/x86/mingw/bin/libopencv_imgcodecs340.dll \
                            $$PWD/OpenCV/x86/mingw/bin/libopencv_imgproc340.dll

    install_qtlibs.path =   $$DESTDIR
    install_qtlibs.files =  $$[QT_INSTALL_BINS]/Qt5Core.dll \
                            $$[QT_INSTALL_BINS]/Qt5Gui.dll \
                            $$[QT_INSTALL_BINS]/Qt5Widgets.dll \
                            $$[QT_INSTALL_BINS]/Qt5PrintSupport.dll
}

INSTALLS += install_exiftool \
            install_opencv \
            install_qtlibs
