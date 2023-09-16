QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

LIBRARY_DIR=Library
LABS_ROOT=./bin

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        DecimalWrapper.cpp \
        main.cpp

# Default rules for deployment.

TARGET=DecimailWrapper.x
target.path = ./bin
INSTALLS += target apiheaders




HEADERS += \
    DecimalWrapper.h
