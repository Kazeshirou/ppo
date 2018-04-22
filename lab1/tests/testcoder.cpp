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

    QList<QList<QString>> polyline(Coder::encode(route1));
    QString s;
    foreach (QList<QString> coord, polyline)
    {
        s += coord.at(0) + coord.at(1);
    }
    QCOMPARE(s, QString("}qn~FftzuOr{Bre@rXduC"));
}

void TestCoder::decode()
{
    QList<QGeoCoordinate> route1 = {
        QGeoCoordinate(41.85903,-87.63220),
        QGeoCoordinate(41.83909,-87.63838),
        QGeoCoordinate(41.83499,-87.66241)
    };


    QCOMPARE(Coder::decode(QString("}qn~FftzuOr{Bre@rXduC")), route1);
}
