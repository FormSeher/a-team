#-------------------------------------------------
#
# Project created by QtCreator 2014-04-08T09:34:01
#
#-------------------------------------------------
include(../global.pri)
QT       -= core gui

TARGET = algorithms01
TEMPLATE = lib
VERSION = 0.1
CONFIG += staticlib
DESTDIR = $${ALG_BIN_DIR}

DEFINES += ALGORITHMS_LIBRARY

SOURCES += \
    # common
    $${ALG_SRC_DIR}/picprepare.cpp \
    $${ALG_SRC_DIR}/mathutil.cpp \
    $${ALG_SRC_DIR}/line.cpp \
    # line detection
    $${ALG_SRC_DIR}/linedetection/linedetectionalgorithm.cpp \
    $${ALG_SRC_DIR}/linedetection/edl/edl.cpp \
    $${ALG_SRC_DIR}/linedetection/edl2/edl2.cpp \
    $${ALG_SRC_DIR}/linedetection/hough/hough.cpp \
    $${ALG_SRC_DIR}/linedetection/lineutils.cpp \
    # object detection - common
    $${ALG_SRC_DIR}/objectdetection/model.cpp \
    $${ALG_SRC_DIR}/objectdetection/object.cpp \
    $${ALG_SRC_DIR}/objectdetection/objectdetectionalgorithm.cpp \
    # object detection - stub
    $${ALG_SRC_DIR}/objectdetection/stub/stub.cpp \
    # object detection - OLGA
    $${ALG_SRC_DIR}/objectdetection/olga/objectgraph.cpp \
    $${ALG_SRC_DIR}/objectdetection/olga/objectgraphnode.cpp \
    $${ALG_SRC_DIR}/objectdetection/olga/objectgraphedge.cpp \
    # object detection - HAFF
    $${ALG_SRC_DIR}/objectdetection/haff/hypothesis.cpp \
    $${ALG_SRC_DIR}/objectdetection/haff/haff.cpp \
    $${ALG_SRC_DIR}/objectdetection/haff/haffdatabase.cpp \
    # object detection - teamB
    $${ALG_SRC_DIR}/objectdetection/teamb/objectdetectionalgorithmteamb.cpp \
    $${ALG_SRC_DIR}/objectdetection/teamb/objectreader.cpp \
    # database utils
    $${ALG_SRC_DIR}/objectdetection/databaseutils.cpp

HEADERS += \
    # common
    $${ALG_INCL_DIR}/picprepare.h \
    $${ALG_INCL_DIR}/mathutil.h \
    $${ALG_INCL_DIR}/line.h \
    $${ALG_INCL_DIR}/pointercompare.h \
    # line detection
    $${ALG_INCL_DIR}/linedetection/linedetectionalgorithm.h \
    $${ALG_INCL_DIR}/linedetection/edl/edl.h \
    $${ALG_INCL_DIR}/linedetection/edl2/edl2.h \
    $${ALG_INCL_DIR}/linedetection/hough/hough.h \
    $${ALG_INCL_DIR}/linedetection/lineutils.h \
    # object detection - common
    $${ALG_INCL_DIR}/objectdetection/model.h \
    $${ALG_INCL_DIR}/objectdetection/object.h \
    $${ALG_INCL_DIR}/objectdetection/objectdetectionalgorithm.h \
    # object detection - stub
    $${ALG_INCL_DIR}/objectdetection/stub/stub.h \
    # object detection - OLGA
    $${ALG_INCL_DIR}/objectdetection/olga/objectgraph.h \
    $${ALG_INCL_DIR}/objectdetection/olga/objectgraphnode.h \
    $${ALG_INCL_DIR}/objectdetection/olga/objectgraphedge.h \
    # object detectin - HAFF
    $${ALG_INCL_DIR}/objectdetection/haff/hypothesis.h \
    $${ALG_INCL_DIR}/objectdetection/haff/haff.h \
    $${ALG_INCL_DIR}/objectdetection/haff/haffdatabase.h \
    # object detection - teamB
    $${ALG_INCL_DIR}/objectdetection/teamb/objectdetectionalgorithmteamb.h \
    $${ALG_INCL_DIR}/objectdetection/teamb/objectreader.h \
    #database utils
    $${ALG_INCL_DIR}/objectdetection/databaseutils.h \

    #utils include - fu cpp :<
    $${ALG_INCL_DIR}/utils/rapidjson/document.h


INCLUDEPATH += $${ALG_INCL_DIR}\

    $${ALG_DIR}/utils/rapidjson

#-------------------------------------------------
#               win32 specifics
#-------------------------------------------------
win32{
INCLUDEPATH += $(OPENCV_DIR_INCLUDE)
LIBS += -L$(OPENCV_DIR_LIB)
LIBS += -llibopencv_core248 -llibopencv_imgproc248 -llibopencv_highgui248
}
#-------------------------------------------------
#               Linux/Unix specifics
#-------------------------------------------------
linux{
LIBS += -lopencv_core -lopencv_imgproc
}
