message("----------------------------------------------------------------")
message(MessageListTest.pro)
message("----------------------------------------------------------------")
include(../../test.pri)

TEMPLATE = app
QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TARGET = MessageListTest.test

SOURCES += MessageListTest.cpp
HEADERS += MessageListTest.h
