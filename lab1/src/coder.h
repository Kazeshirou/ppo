#ifndef CODER_H
#define CODER_H

#include <QList>

class QString;
class QGeoCoordinate;

class Coder
{

    Coder() = default;
public:

    static QString encode(const QList<QGeoCoordinate> &route);
    static QList<QGeoCoordinate> decode(const QString &polyline);

protected:
    static QString encodeCoordinate(const QGeoCoordinate &coordinate);
    static QString encodeNumber(double number);
    static int decodeCoordinate(QString &polyline, QGeoCoordinate &coordinate);
    static double decodeNumber(QString &polyline);
};

#endif // CODER_H
