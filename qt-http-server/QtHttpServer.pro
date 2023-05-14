TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += QtHttpServer 
SUBDIRS += QtHttpServerUi
SUBDIRS += test


QtHttpServerUi.depends = QtHttpServer
test.depends = QtHttpServer

