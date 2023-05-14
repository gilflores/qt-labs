QT=core
QT+= testlib
CONFIG += qt console warn_on depend_includepath testcase

# Validate with David when to use QMAKE

QMAKE_CXXFLAGS+=-g

OBJECTS_DIR=.build
MOC_DIR=.build
UI_DIR=.build
RCC_DIR=.build

TEMPLATE = app


SOURCES += \ 
    SiteRepositoryTest.cpp

LIBS += -L$$OUT_PWD/../../QtHttpServer/ -lQtHttpServer

INCLUDEPATH += $$PWD/../../QtHttpServer
DEPENDPATH += $$PWD/../../QtHttpServer

HEADERS += \
    SiteRepositoryTest.h
