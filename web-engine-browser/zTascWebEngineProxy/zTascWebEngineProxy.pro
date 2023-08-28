QT+=core network 
TEMPLATE=lib
INCLUDEPATH+=. .build widgets objects forms
DEPENDPATH+=. .build widgets objects forms resources
OBJECTS_DIR=.build
MOC_DIR=.build
QMAKE_LIBS+=-ldl
SOURCES+=zTascWebEngineProxy.cpp


