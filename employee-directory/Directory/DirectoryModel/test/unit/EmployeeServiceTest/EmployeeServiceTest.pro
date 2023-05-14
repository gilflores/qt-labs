message("--------------------------------------------------------------------")
message("EmployeeServiceTest")
message("--------------------------------------------------------------------")
include(../../test.pri)

QT=core testlib xml network sql
CONFIG += qt console warn_on depend_includepath testcase

TARGET=EmployeeServiceTest.test
TEMPLATE=app
INCLUDEPATH+=.
DEPENDPATH+=.
QMAKE_CFLAGS+=-DLINUX


HEADERS += \
    EmployeeServiceTest.h
    

SOURCES += \
    EmployeeServiceTest.cpp
    

