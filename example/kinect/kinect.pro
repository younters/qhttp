QT          += core network
QT          -= gui
CONFIG      += console
osx:CONFIG  -= app_bundle

TARGET       = kinect
TEMPLATE     = app
CONFIG      += c++11

PRJDIR       = ../..
include($$PRJDIR/commondir.pri)

HEADERS   +=


#INCLUDEPATH += /usr/local/include
#macx: LIBS += -L$$PWD/../../../../../../../../../usr/local/Cellar/opencv/2.4.12_2/lib/ -lopencv_core.2.4.12

INCLUDEPATH += $$PWD/../../../../../../../../../usr/local/Cellar/opencv/2.4.12_2/include
#DEPENDPATH += $$PWD/../../../../../../../../../usr/local/Cellar/opencv/2.4.12_2/include
LIBS += -L/usr/local/lib \
     -lopencv_core \
     -lopencv_imgproc \
     -lopencv_features2d \
     -lopencv_highgui


SOURCES   += main.cpp


LIBS      += -lqhttp

#osx:LIBS += -L"../../libfreenect"
#osx:LIBS += -L"../../libusb-1.0"

#macx: LIBS += -L$$PWD/../../../../../../../../../usr/local/Cellar/libfreenect/0.5.1/lib/ -lfreenect.0.5.0
#
#INCLUDEPATH += $$PWD/../../../../../../../../../usr/local/Cellar/libfreenect/0.5.1/include
#DEPENDPATH += $$PWD/../../../../../../../../../usr/local/Cellar/libfreenect/0.5.1/include
#
#macx: LIBS += -L$$PWD/../../../../../../../../../usr/local/Cellar/libusb-compat/0.1.5/lib/ -lusb-0.1.4
#
#INCLUDEPATH += $$PWD/../../../../../../../../../usr/local/Cellar/libusb-compat/0.1.5/include
#DEPENDPATH += $$PWD/../../../../../../../../../usr/local/Cellar/libusb-compat/0.1.5/include

#macx: LIBS += -lusb-0.1
#macx: LIBS += -lfreenect.0.5.0

