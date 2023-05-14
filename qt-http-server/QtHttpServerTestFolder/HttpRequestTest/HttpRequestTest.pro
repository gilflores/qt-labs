QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

OBJECTS_DIR=.build
MOC_DIR=.build
UI_DIR=.build
RCC_DIR=.build

TEMPLATE = app

SOURCES += HttpRequestTest.cpp

LIBS += -L$$OUT_PWD/../../QtHttpServer/ -lQtHttpServer

INCLUDEPATH += $$PWD/../../QtHttpServer
DEPENDPATH += $$PWD/../../QtHttpServer

HEADERS += HttpRequestTest.h
