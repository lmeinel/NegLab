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
        imagepreviewwindow.cpp \
        imagecache.cpp \
        qcustomplot.h

HEADERS  += mainwindow.h \
            invertcore.h \
            filehandler.h \
            imagepreviewwindow.h \
            imagecache.h \
            qcustomplot.h

FORMS    += mainwindow.ui \
            imagepreviewwindow.ui

THIRDPARTY = $$clean_path($$PWD/../third_party)
			
INCLUDEPATH += $$THIRDPARTY/OpenCV/include
INCLUDEPATH += $$THIRDPARTY/OpenCV/include/opencv

message($$clean_path($$THIRDPARTY/OpenCV/include))
message($$clean_path($$THIRDPARTY/OpenCV/include/opencv))

RC_ICONS = icon.ico

CONFIG(debug, debug|release){
    message("Compiling in Debug mode")

    # set output directory
    DESTDIR = $$OUT_PWD/debug

    # detect compiler using platform scopes
    win32-msvc* {
        MSVC_VER = $$(VisualStudioVersion)
        message("Microsoft Visual Studio Compiler $$MSVC_VER")

        equals(MSVC_VER, 15.0){
            LIBS += $$THIRDPARTY/OpenCV/x64/vc15/lib/opencv_core340d.lib
            LIBS += $$THIRDPARTY/OpenCV/x64/vc15/lib/opencv_highgui340d.lib
            LIBS += $$THIRDPARTY/OpenCV/x64/vc15/lib/opencv_imgcodecs340d.lib
            LIBS += $$THIRDPARTY/OpenCV/x64/vc15/lib/opencv_imgproc340d.lib
            #LIBS += $$THIRDPARTY/OpenCV/x64/vc15/lib/opencv_features2d340d.lib
            #LIBS += $$THIRDPARTY/OpenCV/x64/vc15/lib/opencv_calib3d340d.lib

            install_opencv.path   = $$DESTDIR
            install_opencv.files  = $$THIRDPARTY/OpenCV/x64/vc15/bin/opencv_core340d.dll \
                                    $$THIRDPARTY/OpenCV/x64/vc15/bin/opencv_highgui340d.dll \
                                    $$THIRDPARTY/OpenCV/x64/vc15/bin/opencv_imgcodecs340d.dll \
                                    $$THIRDPARTY/OpenCV/x64/vc15/bin/opencv_imgproc340d.dll
        }
    }

    win32-g++{
            LIBS += $$THIRDPARTY/OpenCV/x86/mingw/bin/libopencv_core340d.dll
            LIBS += $$THIRDPARTY/OpenCV/x86/mingw/bin/libopencv_highgui340d.dll
            LIBS += $$THIRDPARTY/OpenCV/x86/mingw/bin/libopencv_imgcodecs340d.dll
            LIBS += $$THIRDPARTY/OpenCV/x86/mingw/bin/libopencv_imgproc340d.dll
            #LIBS += $$THIRDPARTY/OpenCV/x86/mingw/bin/libopencv_features2d340d.dll
            #LIBS += $$THIRDPARTY/OpenCV/x86/mingw/bin/libopencv_calib3d340d.dll

            install_opencv.path   = $$DESTDIR
            install_opencv.files  = $$THIRDPARTY/OpenCV/x86/mingw/bin/libopencv_core340d.dll \
                                    $$THIRDPARTY/OpenCV/x86/mingw/bin/libopencv_highgui340d.dll \
                                    $$THIRDPARTY/OpenCV/x86/mingw/bin/libopencv_imgcodecs340d.dll \
                                    $$THIRDPARTY/OpenCV/x86/mingw/bin/libopencv_imgproc340d.dll
    }


    install_exiftool.path   = $$DESTDIR
    install_exiftool.files  = $$THIRDPARTY/ExifTool/exiftool.exe

    install_qtlibs.path =   $$DESTDIR
    install_qtlibs.files =  $$[QT_INSTALL_BINS]/Qt5Cored.dll \
                            $$[QT_INSTALL_BINS]/Qt5Guid.dll \
                            $$[QT_INSTALL_BINS]/Qt5Widgetsd.dll \
                            $$[QT_INSTALL_BINS]/Qt5PrintSupportd.dll
}
else{
    message("Compiling in Release mode")

    # set output directory
    DESTDIR = $$OUT_PWD/release

    # detect compiler using platform scopes
    win32-msvc*{
        MSVC_VER = $$(VisualStudioVersion)
        message("Microsoft Visual Studio Compiler $$MSVC_VER")

        equals(MSVC_VER, 15.0){
            LIBS += $$THIRDPARTY/OpenCV/x64/vc15/lib/opencv_core340.lib
            LIBS += $$THIRDPARTY/OpenCV/x64/vc15/lib/opencv_highgui340.lib
            LIBS += $$THIRDPARTY/OpenCV/x64/vc15/lib/opencv_imgcodecs340.lib
            LIBS += $$THIRDPARTY/OpenCV/x64/vc15/lib/opencv_imgproc340.lib
            #LIBS += $$THIRDPARTY/OpenCV/x64/vc15/lib/opencv_features2d340.lib
            #LIBS += $$THIRDPARTY/OpenCV/x64/vc15/lib/opencv_calib3d340.lib

            install_opencv.path   = $$DESTDIR
            install_opencv.files  = $$THIRDPARTY/OpenCV/x64/vc15/bin/opencv_core340.dll \
                                    $$THIRDPARTY/OpenCV/x64/vc15/bin/opencv_highgui340.dll \
                                    $$THIRDPARTY/OpenCV/x64/vc15/bin/opencv_imgcodecs340.dll \
                                    $$THIRDPARTY/OpenCV/x64/vc15/bin/opencv_imgproc340.dll
        }
    }

    win32-g++{
            LIBS += $$THIRDPARTY/OpenCV/x86/mingw/bin/libopencv_core340.dll
            LIBS += $$THIRDPARTY/OpenCV/x86/mingw/bin/libopencv_highgui340.dll
            LIBS += $$THIRDPARTY/OpenCV/x86/mingw/bin/libopencv_imgcodecs340.dll
            LIBS += $$THIRDPARTY/OpenCV/x86/mingw/bin/libopencv_imgproc340.dll
            #LIBS += $$THIRDPARTY/OpenCV/x86/mingw/bin/libopencv_features2d340.dll
            #LIBS += $$THIRDPARTY/OpenCV/x86/mingw/bin/libopencv_calib3d340.dll

            install_opencv.path   = $$DESTDIR
            install_opencv.files  = $$THIRDPARTY/OpenCV/x86/mingw/bin/libopencv_core340.dll \
                                    $$THIRDPARTY/OpenCV/x86/mingw/bin/libopencv_highgui340.dll \
                                    $$THIRDPARTY/OpenCV/x86/mingw/bin/libopencv_imgcodecs340.dll \
                                    $$THIRDPARTY/OpenCV/x86/mingw/bin/libopencv_imgproc340.dll
    }

    install_exiftool.path   = $$DESTDIR
    install_exiftool.files  = $$THIRDPARTY/ExifTool/exiftool.exe

    install_qtlibs.path =   $$DESTDIR
    install_qtlibs.files =  $$[QT_INSTALL_BINS]/Qt5Core.dll \
                            $$[QT_INSTALL_BINS]/Qt5Gui.dll \
                            $$[QT_INSTALL_BINS]/Qt5Widgets.dll \
                            $$[QT_INSTALL_BINS]/Qt5PrintSupport.dll
}

INSTALLS += install_exiftool \
            install_opencv \
            install_qtlibs
