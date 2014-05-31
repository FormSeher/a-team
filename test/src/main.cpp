#include <QtTest>

#include "linetest.h"
#include "pointercomparetest.h"

#include "linedetection/edl/edltest.h"

#include "objectdetection/olga/objectgraphedgetest.h"
#include "objectdetection/olga/objectgraphnodetest.h"
#include "objectdetection/olga/objectgraphtest.h"

#include "objectdetection/modeltest.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    LineTest lineTest;
    PointerCompareTest pointerCompareTest;

    EDLTest edlTest;

    ObjectGraphEdgeTest objectGraphEdgeTest;
    ObjectGraphNodeTest objectGraphNodeTest;
    ObjectGraphTest objectGraphTest;

    ModelTest objectTest;

    return   QTest::qExec(&lineTest, argc, argv)
           | QTest::qExec(&pointerCompareTest, argc, argv)
           | QTest::qExec(&edlTest, argc, argv)
           | QTest::qExec(&objectGraphEdgeTest, argc, argv)
           | QTest::qExec(&objectGraphTest, argc, argv)
           | QTest::qExec(&objectGraphNodeTest, argc, argv)
           | QTest::qExec(&objectTest, argc, argv);
}

