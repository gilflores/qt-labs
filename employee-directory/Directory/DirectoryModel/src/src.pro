message("----------------------------------------------------------------")
message(DirectoryModel.pro)
message("----------------------------------------------------------------")
include(../../../Library/Library.pri)

QT += sql core
QT -= gui

TARGET = DirectoryModel
TEMPLATE = lib

CONFIG += qt console warn_on depend_includepath

# -- SOURCES ---------------------------------
#SOURCES += file.cpp

# -- HEADERS -----------------------------------
#HEADERS += file.h


# -- API HEADERS --------------------------------
#API_HEADERS += file.h

apiheaders.files=$$API_HEADERS
apiheaders.path=$$(LABS_ROOT)/include/

target.path = $$(LABS_ROOT)/lib
INSTALLS += target apiheaders


QMAKE_DISTCLEAN+=.build/

HEADERS += \
    Employee.h \
    EmployeeDao.h \
    EmployeeFileDao.h \
    EmployeeService.h \
    DirectoryModel_Global.h \
    SaveEmployeeResult.h

SOURCES += \
    Employee.cpp \
    EmployeeDao.cpp \
    EmployeeFileDao.cpp \
    EmployeeService.cpp \
    SaveEmployeeResult.cpp
