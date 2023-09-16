QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

TEMPLATE=lib

OBJECTS_DIR=.build
MOC_DIR=.build
UI_DIR=.build
RCC_DIR=.build

LIBRARY_DIR=Library
LABS_ROOT=./bin

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        DecimalWrapper.cpp \
        main.cpp

# Default rules for deployment.

TARGET=DecimalWrapper
target.path = ./lib
INSTALLS += target apiheaders




HEADERS += \
    DecimalWrapper.h
