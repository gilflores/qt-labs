include(../test.pri)

QT=core
QT+= testlib
CONFIG += qt console warn_on depend_includepath testcase

# Validate with David when to use QMAKE

QMAKE_CXXFLAGS+=-g

TEMPLATE = app


SOURCES += SiteRepositoryTest.cpp
HEADERS += SiteRepositoryTest.h
