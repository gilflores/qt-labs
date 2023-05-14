#-------------------------------------------------
#
# Project created by QtCreator 2019-02-01T10:28:39
#
#-------------------------------------------------
include(../QtHttpServer.pri)

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

#CONFIG += c++11

INCLUDEPATH+= .
INCLUDEPATH+= utils/.
INCLUDEPATH+= http/.
INCLUDEPATH+= http/server/.


SOURCES += utils/FileUtil.cpp

SOURCES += http/HttpResponse.cpp
SOURCES += http/RequestHandler.cpp
SOURCES += http/HttpRequest.cpp


SOURCES += http/server/SiteRepository.cpp
SOURCES += http/server/HttpSocket.cpp
SOURCES += http/server/HttpServerSocket.cpp
SOURCES += http/server/SiteConfiguration.cpp
SOURCES += http/server/HttpServer.cpp

HEADERS += utils/FileUtil.h

HEADERS += http/HttpRequest.h
HEADERS += http/HttpResponse.h
HEADERS += http/RequestHandler.h

HEADERS += http/server/SiteRepository.h
HEADERS += http/server/HttpServer.h
HEADERS += http/server/HttpSocket.h
HEADERS += http/server/HttpServerSocket.h
HEADERS += http/server/SiteConfiguration.h

API_HEADERS += utils/FileUtil.h
API_HEADERS += http/HttpRequest.h 
API_HEADERS += http/HttpResponse.h

API_HEADERS += http/server/SiteRepository.h 
API_HEADERS += http/server/HttpServer.h 
API_HEADERS += http/server/HttpSocket.h 
API_HEADERS += http/server/HttpServerSocket.h
API_HEADERS += http/server/SiteConfiguration.h


apiheaders.files=$$API_HEADERS
apiheaders.path=$$QTLAB_ROOT/include/

target.path = $$QTLAB_ROOT/lib
INSTALLS += target apiheaders

