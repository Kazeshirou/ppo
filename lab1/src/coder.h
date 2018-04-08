#ifndef CODER_H
#define CODER_H

#include <QList>

class QString;
class QGeoCoordinate;

class Coder
{

public:
    explicit Coder() = default;

    QString encode(const QList<QGeoCoordinate> &route);
    QList<QGeoCoordinate> decode(const QString &polyline);

protected:
    QString encodeCoordinate(const QGeoCoordinate &coordinate);
    QString encodeNumber(double number);
    int decodeCoordinate(QString &polyline, QGeoCoordinate &coordinate);
    double decodeNumber(QString &polyline);
};

#endif // CODER_H
