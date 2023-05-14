message("--------------------------------------------------------------------")
message("EmployeeFileDaoTest")
message("--------------------------------------------------------------------")
include(../../test.pri)

QT=core testlib xml network sql
CONFIG += qt console warn_on depend_includepath testcase

TARGET=EmployeeFileDaoTest.test
TEMPLATE=app
INCLUDEPATH+=.
DEPENDPATH+=.
QMAKE_CFLAGS+=-DLINUX


HEADERS += \
    EmployeeFileDaoTest.h

SOURCES += \
    EmployeeFileDaoTest.cpp

