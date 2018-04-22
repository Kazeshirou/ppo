#ifndef CODER_H
#define CODER_H

#include <QList>

class QString;
class QGeoCoordinate;

class Coder
{

    Coder() = default;
public:

    static QList<QList<QString>> encode(const QList<QGeoCoordinate> &route);
    static QList<QString> encodeCoordinate(const QGeoCoordinate &coordinate);
    static QList<QGeoCoordinate> decode(const QString &polyline);

protected:
    static QString encodeNumber(double number);
    static int decodeCoordinate(QString &polyline, QGeoCoordinate &coordinate);
    static double decodeNumber(QString &polyline);
};

#endif // CODER_H
