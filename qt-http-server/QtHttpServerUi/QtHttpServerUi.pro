#-------------------------------------------------
#
# Project created by QtCreator 2019-02-04T12:45:26
#
#-------------------------------------------------

QT+= core gui
QT+=network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtHttpServerUi
TEMPLATE = app


QMAKE_CXXFLAGS += -std=c++0x

OBJECTS_DIR=.build
MOC_DIR=.build
UI_DIR=.build
RCC_DIR=.build



# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        LongTaskThread.cpp \
        main.cpp \
        MainWindow.cpp \
        WidgetPrincipal.cpp \

HEADERS += \
        LongTaskThread.h \
        MainWindow.h \
        WidgetPrincipal.h

FORMS += \
        MainWindow.ui

# Default rules for deployment.
target.path = $$(QTLAB_ROOT)/bin
INSTALLS += target

LIBS += -L$$OUT_PWD/../QtHttpServer/ -lQtHttpServer

INCLUDEPATH += $$PWD/../QtHttpServer
DEPENDPATH += $$PWD/../QtHttpServer
