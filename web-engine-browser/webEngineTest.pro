QT+=core sql network gui widgets webenginewidgets
INCLUDEPATH+=. .build widgets objects forms
DEPENDPATH+=. .build widgets objects forms resources
OBJECTS_DIR=.build
MOC_DIR=.build
FORMS_DIR=.build
UI_DIR=.build
CONFIG+=debug

SOURCES+=main.cpp

HEADERS+=objects/webEngineTestApp.h
SOURCES+=objects/webEngineTestApp.cpp


FORMS+=forms/webEngineTestMW.ui
HEADERS+=widgets/webEngineTestMW.h
SOURCES+=widgets/webEngineTestMW.cpp

HEADERS+=objects/testProfile.h
SOURCES+=objects/testProfile.cpp
HEADERS+=widgets/wePage.h
SOURCES+=widgets/wePage.cpp

TARGET=webEngine.x