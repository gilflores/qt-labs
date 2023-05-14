include (../QtHttpServer.pri)


QTLAB_ROOT_TEST=$$PWD/../dist/test

ENV_QTLAB_ROOT=$$(QTLAB_ROOT)

!isEmpty(ENV_QTLAB_ROOT):{
    message(QTLAB_ROOT is empty assigning Default value)
    QTLAB_ROOT_TEST=$(ENV_QTLAB_ROOT)/test
}
message(--- QTLAB_ROOT_TEST=$$QTLAB_ROOT_TEST)


INCLUDEPATH+=$(INSTALL_ROOT)/$$QTLAB_ROOT/include
DEPENDPATH +=$(INSTALL_ROOT)/$$QTLAB_ROOT/lib
QMAKE_LIBDIR+=$(INSTALL_ROOT)/$$QTLAB_ROOT/lib

LIBS += -lQtHttpServer

target.path=$$QTLAB_ROOT_TEST
INSTALLS += target

