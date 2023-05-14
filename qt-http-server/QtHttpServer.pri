message("--------------------------------------------------------------------")
QTLAB_ROOT=$$PWD/dist

ENV_QTLAB_ROOT=$$(QTLAB_ROOT)

!isEmpty(ENV_QTLAB_ROOT):{
    message(QTLAB_ROOT is empty assigning Default value)
    QTLAB_ROOT=$(ENV_QTLAB_ROOT)
}
message(--- QTLAB_ROOT=$$QTLAB_ROOT)



OBJECTS_DIR=.build
MOC_DIR=.build
UI_DIR=.build
RCC_DIR=.build


INCLUDEPATH+=$(INSTALL_ROOT)/$$QTLAB_ROOT/include
DEPENDPATH +=$(INSTALL_ROOT)/$$QTLAB_ROOT/lib
QMAKE_LIBDIR+=$(INSTALL_ROOT)/$$QTLAB_ROOT/lib

LIBS += -L$$QTLAB_ROOT/lib

target.path = $$QTLAB_ROOT
INSTALLS += target


