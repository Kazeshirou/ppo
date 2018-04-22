#include "gpxparser.h"
#include "georoute.h"

#include <QGeoCoordinate>
#include <QXmlStreamReader>
#include <QFile>
#include <iostream>
#include <QStandardPaths>


QGeoCoordinate GpxParser::readCoordinate(QXmlStreamReader &inputStream)
{
    QGeoCoordinate coordinate;
    coordinate.setLongitude(inputStream.attributes().value("lon").toDouble());
    coordinate.setLatitude(inputStream.attributes().value("lat").toDouble());
    coordinate.setAltitude(nan(""));
    inputStream.readNext();
    while (!inputStream.atEnd() && !inputStream.hasError() && (inputStream.name().toString() != "wpt") && (inputStream.name().toString() != "trkpt"))
    {
        if (inputStream.isStartElement())
        {
            QString name = inputStream.name().toString();
            if (name == "ele")
                coordinate.setAltitude(inputStream.readElementText().toDouble());
        }
        inputStream.readNext();
    }
    return coordinate;
}

GeoRoute GpxParser::parseFile(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return GeoRoute();
    QList<QGeoCoordinate> wpt;
    QList<QGeoCoordinate> trkseg;
    bool trk = false;
    GeoRoute route;
    QXmlStreamReader inputStream(&file);
    while (!inputStream.atEnd() && !inputStream.hasError())
    {
        inputStream.readNext();
        if (inputStream.isStartElement())
        {
            QString name = inputStream.name().toString();
            if (name == "wpt")
            {
                QGeoCoordinate coordinate = readCoordinate(inputStream);
                if (inputStream.hasError())
                    continue;
                wpt.append(coordinate);
            }
            else if (name == "trk")
                trk = true;
            else if (name == "trkpt")
            {
                QGeoCoordinate coordinate = readCoordinate(inputStream);
                if (inputStream.hasError())
                    continue;
                trkseg.append(coordinate);
            }
            else if (trk && (name == "name"))
                route.setName(inputStream.readElementText());
            else if (trk && (name == "desc"))
            {
                QStringList text = inputStream.readElementText().split(" km, ");
                route.setDistance((text[0]).toFloat());
            }
        }
        else if (inputStream.isEndElement())
        {
            QString name = inputStream.name().toString();
            if (name == "trk")
                trk = false;
        }
    }
    if (!route.getName().length())
    {
        QStringList l = filename.split('/');
        route.setName(l.last());
    }
    trkseg.push_front(wpt[0]);
    trkseg.push_back(wpt[1]);
    route.setPath(trkseg);
    route.setDate();
    file.close();
    return route;
}

QList<GeoRoute> GpxParser::parse(const QStringList &filenames)
{
    QList<GeoRoute> routes;
    for (int i = 0; i < filenames.length(); i++)
    {
        GeoRoute route = parseFile(filenames[i]);
        if (route.path().length())
            routes.append(route);
    }
    return routes;
}

SaveParser::SaveParser() :
    filename(QStandardPaths::standardLocations(
                 QStandardPaths::AppDataLocation).at(0))
{

}

QList<GeoRoute> SaveParser::parse() const
{
    QList<GeoRoute> routes;
    FILE *file = fopen(filename.toStdString().c_str(), "r");
    if (!file)
        return routes;
    int n;
    fscanf(file, "%d", &n);
    for (int i = 0; i < n; i++)
    {
        char c[10];
        fgets(c, 10, file);
        QList<QGeoCoordinate> path;
        char name[1000], date[40];
        int k;
        fgets(name, 1000, file);
        fgets(date, 40, file);
        fscanf(file, "%d", &k);
        for (int j = 0; j < k; j++)
        {
            double lat, lon, ele;
            int p = fscanf(file, "%lf %lf %lf", &lat, &lon, &ele);
            if (p == 3)
                path.append(QGeoCoordinate(lat, lon, ele));
            else if (p == 2)
                path.append(QGeoCoordinate(lat,lon));
        }
        routes.append(GeoRoute(path, QString(name).remove("\n"), QDateTime::fromString(QString(date))));
    }
    fclose(file);
    return routes;
}

void SaveParser::save(const QList<GeoRoute> &routes) const
{
    FILE *file = fopen(filename.toStdString().c_str(), "w");
    fprintf(file, "%d\n", routes.length());
    foreach (GeoRoute route, routes)
    {
        fprintf(file, "%s\n%s\n%d\n",
                route.getName().toStdString().c_str(),
                route.getDate().toString().toStdString().c_str(),
                route.path().length());
        foreach (QGeoCoordinate c, route.path())
            fprintf(file, "%lf %lf %lf\n",
                    c.latitude(),
                    c.longitude(),
                    c.altitude());
    }
    fclose(file);
}
