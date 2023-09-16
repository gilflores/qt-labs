QT += testlib
QT -= gui

OBJECTS_DIR=.build
MOC_DIR=.build
UI_DIR=.build
RCC_DIR=.build

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  DecimalWrapper.cpp
PROJECT_LIST += ../DecimalWrapper
INCLUDEPATH += $$PROJECT_LIST

# The change in lib is done to use QTCreator for testing
LIBS += -L$$PROJECT_LIST -lDecimalWrapper
DEPENDPATH += $$PROJECT_LIST

# If we don't want to depend of the LD_LIBRARY_PATH
QMAKE_LIBDIR += $$PROJECT_LIST
# This variable was added to include the local library to avoid make install
QMAKE_RPATHDIR += $$PROJECT_LIST
QMAKE_LIBS+=-lDecimalWrapper
