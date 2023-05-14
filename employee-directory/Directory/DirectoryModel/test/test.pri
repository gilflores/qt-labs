include(../../../test-common.pri)
#The following configuration is created to use the project in Qt and console
# we are trying not depend for testing of make install and LD_LIBRARY_PATH
UNIT_TEST_BASE_FOLDER=../..
DIRECTORY_MODEL_SRC=$$UNIT_TEST_BASE_FOLDER/../src

DIRECTORY_PROJECT_LIST+= $$DIRECTORY_MODEL_SRC

INCLUDEPATH += $$DIRECTORY_PROJECT_LIST
DEPENDPATH  += $$DIRECTORY_PROJECT_LIST

# The change in lib is done to use QTCreator for testing
LIBS += -L$$DIRECTORY_MODEL_SRC -lDirectoryModel

# If we don't want to depend of the LD_LIBRARY_PATH
QMAKE_LIBDIR += $$DIRECTORY_PROJECT_LIST
# This variable was added to include the local library to avoid make install
QMAKE_RPATHDIR += $$DIRECTORY_PROJECT_LIST
QMAKE_LIBS+=-lDirectoryModel

message("----------------------------------------------------------------")
message(Project dir for src: $$PROJECT_DIR)
message(INCLUDEPATH:  $$INCLUDEPATH)
message(DEPENDPATH:   $$DEPENDPATH)
message(QMAKE_LIBDIR: $$QMAKE_LIBDIR)
message(LIBS for src: $$LIBS)
message("----------------------------------------------------------------")
