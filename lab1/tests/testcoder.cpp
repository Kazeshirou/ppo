#include "testcoder.h"
#include "../src/coder.h"

#include <QTest>
#include <QGeoCoordinate>
#include <QList>
#include <QString>
#include <QDebug>

void TestCoder::encode()
{
    QList<QGeoCoordinate> route1 = {
        QGeoCoordinate(41.85903,-87.63220),
        QGeoCoordinate(41.83909,-87.63838),
        QGeoCoordinate(41.83499,-87.66241)
    };

    Coder coder;
    QCOMPARE(coder.encode(route1), QString("}qn~FftzuOr{Bre@rXduC"));
}

void TestCoder::decode()
{
    QList<QGeoCoordinate> route1 = {
        QGeoCoordinate(41.85903,-87.63220),
        QGeoCoordinate(41.83909,-87.63838),
        QGeoCoordinate(41.83499,-87.66241)
    };

    Coder coder;
    QCOMPARE(coder.decode(QString("}qn~FftzuOr{Bre@rXduC")), route1);
}
