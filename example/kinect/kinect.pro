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

SOURCES   += main.cpp


LIBS      += -lqhttp
