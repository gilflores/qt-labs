#-------------------------------------------------
#
# Project created by QtCreator 2019-02-01T10:28:39
#
#-------------------------------------------------

QT+=core
QT+=gui
QT+=network
QT+=sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtHttpServer
TEMPLATE = lib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_CXXFLAGS += -std=c++0x

OBJECTS_DIR=.build
MOC_DIR=.build
UI_DIR=.build
RCC_DIR=.build

#CONFIG += c++11

SOURCES += \
    SiteRepository.cpp \
    HttpRequest.cpp \
    HttpServer.cpp \
    HttpSocket.cpp \
    HttpServerSocket.cpp \
    FileUtil.cpp \
    HttpResponse.cpp \
    RequestHandler.cpp \
    SiteConfiguration.cpp

API_HEADERS += \
    SiteRepository.h \
   HttpRequest.h \
#    HttpServer.h \
    HttpSocket.h \
    HttpServerSocket.h

HEADERS += \
    SiteRepository.h \
    HttpRequest.h \
    HttpServer.h \
    HttpSocket.h \
    HttpServerSocket.h \
    FileUtil.h \
    HttpResponse.h \
    RequestHandler.h \
    SiteConfiguration.h




apiheaders.files=$$API_HEADERS
apiheaders.path=$$(QTLAB_ROOT)/include/

target.path = $$(QTLAB_ROOT)/lib
INSTALLS += target apiheaders

