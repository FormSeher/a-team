#-------------------------------------------------
#
# Project created by QtCreator 2014-04-06T15:29:53
#
#-------------------------------------------------

#-------------------------------------------------
#                General Qmake settings
#-------------------------------------------------
include(global.pri)
TEMPLATE = subdirs

SUBDIRS += algorithms app haffdbtool TeamBdbTool test
CONFIG += ordered
OTHER_FILES += .gitignore


