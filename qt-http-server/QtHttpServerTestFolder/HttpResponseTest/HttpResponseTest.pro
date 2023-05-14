QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

OBJECTS_DIR=.build
MOC_DIR=.build
UI_DIR=.build
RCC_DIR=.build

SOURCES += \ 
    HttpResponseTest.cpp

LIBS += -L$$OUT_PWD/../../QtHttpServer/ -lQtHttpServer

INCLUDEPATH += $$PWD/../../QtHttpServer
DEPENDPATH += $$PWD/../../QtHttpServer

HEADERS += \
    HttpResponseTest.h
