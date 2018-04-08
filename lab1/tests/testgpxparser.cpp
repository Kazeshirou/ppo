#include "testgpxparser.h"
#include "../src/gpxparser.h"

#include <QTest>
#include <QStringList>
#include <QFileDialog>
#include <QDebug>

void TestGPXParser::parse()
{
    QStringList files;
    files.append("C:/temp/ppo/lab1/route1.gpx");
    GpxParser parser;
    QList<GeoRoute> routes = parser.parse(files);
    QList<QGeoCoordinate> path = routes.first().path();
    QCOMPARE(routes.first().path().length(),1338);
    //QCOMPARE(routes.first().routeId(),QString("ул. Ленина - МКАД"));
    QCOMPARE(path.first(), QGeoCoordinate(55.8236739,37.3163428));
    QCOMPARE(path.last(), QGeoCoordinate(55.6876623,37.8295531));
}
