#ifndef GPXPARSER_H
#define GPXPARSER_H

#include "georoute.h"

#include <QList>
#include <QGeoCoordinate>

class QStringList;
class QXmlStreamReader;

class GpxParser
{

public:
    explicit GpxParser() = default;
    QList<GeoRoute> parse(QStringList &filenames);
protected:
    QGeoCoordinate readCoordinate(QXmlStreamReader &inputStream);
    GeoRoute parseFile(QString &filename);

};

#endif // GPXPARSER_H
