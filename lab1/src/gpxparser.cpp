#include "gpxparser.h"

#include <QXmlStreamReader>
#include <QFile>

#include <QDebug>

QGeoCoordinate GpxParser::readCoordinate(QXmlStreamReader &inputStream)
{
    QGeoCoordinate coordinate;
    coordinate.setLongitude(inputStream.attributes().value("lon").toDouble());
    coordinate.setLatitude(inputStream.attributes().value("lat").toDouble());
    return coordinate;
}

GeoRoute GpxParser::parseFile(QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "File " << filename << " open error: " << file.errorString();
        return GeoRoute();
    }
    QList<QGeoCoordinate> wpt;
    QList<QGeoCoordinate> trkseg;
    bool trk = false;
    GeoRoute route;
    QXmlStreamReader inputStream(&file);
    while (!inputStream.atEnd() && !inputStream.hasError()) {
        inputStream.readNext();
        if (inputStream.isStartElement()) {
            QString name = inputStream.name().toString();
            if (name == "wpt") {
                QGeoCoordinate coordinate = readCoordinate(inputStream);
                if (inputStream.hasError())
                    continue;
                wpt.append(coordinate);
            }
            else if (name == "trk")
                trk = true;
            else if (name == "trkpt") {
                QGeoCoordinate coordinate = readCoordinate(inputStream);
                if (inputStream.hasError())
                    continue;
                trkseg.append(coordinate);
            }
            else if (trk && (name == "name"))
                route.setName(inputStream.readElementText());
            else if (trk && (name == "desc")){
                QStringList text = inputStream.readElementText().split(" km, ");
                route.setDistance((text[0]).toFloat());
            }
        }
        else if (inputStream.isEndElement()) {
            QString name = inputStream.name().toString();
            if (name == "trk")
                trk = false;
        }
    }
    trkseg.push_front(wpt[0]);
    trkseg.push_back(wpt[1]);
    route.setPath(trkseg);
    route.setDate();
    return route;
}

QList<GeoRoute> GpxParser::parse(QStringList &filenames)
{
    QList<GeoRoute> routes;
    for (int i = 0; i < filenames.length(); i++) {
        GeoRoute route = parseFile(filenames[i]);
        if (route.path().length())
            routes.append(route);
    }
    return routes;
}
