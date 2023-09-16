QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_decimalptest.cpp
PROJECT_LIST += ../DecimalP
INCLUDEPATH += $$PROJECT_LIST

# The change in lib is done to use QTCreator for testing
LIBS += -L$$PROJECT_LIST -lDecimalP
DEPENDPATH += $$PROJECT_LIST

# If we don't want to depend of the LD_LIBRARY_PATH
QMAKE_LIBDIR += $$PROJECT_LIST
# This variable was added to include the local library to avoid make install
QMAKE_RPATHDIR += $$PROJECT_LIST
QMAKE_LIBS+=-lDecimalP
