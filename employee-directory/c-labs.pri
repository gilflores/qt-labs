message(Loading c-labs.pri)

PROJECT_DIR = $$PWD


isEmpty( LABS_ROOT ) {
  LABS_ROOT=$$PROJECT_DIR
} 

# Activate Debug for the workshop
CONFIG += debug
CONFIG += c++11


# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS


# -- Build folders ------
OBJECTS_DIR=.build
MOC_DIR=.build
UI_DIR=.build
RCC_DIR=.build


# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
