QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    brightdialog.cpp \
    hlsdialog.cpp \
    imgedit.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    brightdialog.h \
    hlsdialog.h \
    imgedit.h \
    mainwindow.h

FORMS += \
    HLSdialog.ui \
    brightdialog.ui \
    hlsdialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource.qrc
@QMAKE_LFLAGS += /OPT:NOREF@

LIBS += -LD:\SDK\cvBuild\install\x64\vc16\lib -lopencv_core440 -lopencv_imgproc440 -lopencv_highgui440 -lopencv_imgcodecs440 -lopencv_videoio440 -lopencv_video440 -lopencv_calib3d440 -lopencv_photo440 -lopencv_xphoto440 -lopencv_features2d440
INCLUDEPATH += D:\SDK\cvBuild\install\include
DEPENDPATH += D:\SDK\cvBuild\install\include
