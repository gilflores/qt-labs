include(../c-labs.pri)

# the path is based in test project

LIBRARY_DIR=Library
LAB_UTILITIES=LabUtilities

LAB_UTILITIES_PATH=$$PROJECT_DIR/$$LIBRARY_DIR/$$LAB_UTILITIES/src
#The following configuration is created to use the project in Qt and console
# we are trying not depend for testing of make install and LD_LIBRARY_PATH
LIBRARY_PROJECT_LIST+= $$LAB_UTILITIES_PATH

INCLUDEPATH += $$LIBRARY_PROJECT_LIST
DEPENDPATH  += $$LIBRARY_PROJECT_LIST

# If we don't want to depend of the LD_LIBRARY_PATH
QMAKE_LIBDIR += $$LIBRARY_PROJECT_LIST
# This variable was added to include the local library to avoid make install
QMAKE_RPATHDIR += $$LIBRARY_PROJECT_LIST
QMAKE_LIBS+=-lLabUtilities

# The change in lib is done to use QTCreator for testing
LIBS += -L$$LAB_UTILITIES_PATH -lLabUtilities
LIBS += -lgcov
