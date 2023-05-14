message("----------------------------------------------------------------")
message(LabUtilities.pro)
message("----------------------------------------------------------------")
include(../../../c-labs.pri)

QT += sql core
QT -= gui

TARGET = LabUtilities
TEMPLATE = lib

CONFIG += qt console warn_on depend_includepath

# -- SOURCES ---------------------------------
SOURCES += FileUtil.cpp
SOURCES += Message.cpp 
SOURCES += MessageList.cpp 
SOURCES += TestLogger.cpp
SOURCES += StringUtil.cpp


# -- HEADERS -----------------------------------
HEADERS += FileUtil.h
HEADERS += Message.h 
HEADERS += MessageList.h 
HEADERS += TestLogger.h
HEADERS += FileUtil.h
HEADERS += StringUtil.h


# -- API HEADERS --------------------------------
API_HEADERS += StringUtil.h
API_HEADERS += FileUtil.h
API_HEADERS += TestLogger.h
API_HEADERS += Message.h
API_HEADERS += MessageList.h


apiheaders.files=$$API_HEADERS
apiheaders.path=$$(LABS_ROOT)/include/

target.path = $$(LABS_ROOT)/lib
INSTALLS += target apiheaders


QMAKE_DISTCLEAN+=.build/
