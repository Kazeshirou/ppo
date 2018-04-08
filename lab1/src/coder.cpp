#include "coder.h"

#include <QGeoCoordinate>
#include <QtMath>

QString Coder::encode(const QList<QGeoCoordinate> &route)
{
    QGeoCoordinate lastcoordinate(0,0);
    QString polyline;
    for (int i = 0; i < route.length(); i++) {
        QGeoCoordinate delta(route[i].latitude()-lastcoordinate.latitude(),
                             route[i].longitude()-lastcoordinate.longitude());
        polyline.append(encodeCoordinate(delta));
        lastcoordinate = route[i];
    }
    return polyline;
}

QList<QGeoCoordinate> Coder::decode(const QString &polyline)
{
    QList<QGeoCoordinate> route;
    QGeoCoordinate currentcoordinate(0,0);
    QGeoCoordinate delta;
    QString currentpolyline(polyline);
    while (decodeCoordinate(currentpolyline,delta)) {
        currentcoordinate.setLatitude(currentcoordinate.latitude()+
                                      delta.latitude());
        currentcoordinate.setLongitude(currentcoordinate.longitude()+
                                       delta.longitude());
        route.append(currentcoordinate);
    }
    currentcoordinate.setLatitude(currentcoordinate.latitude()+
                                  delta.latitude());
    currentcoordinate.setLongitude(currentcoordinate.longitude()+
                                   delta.longitude());
    route.append(currentcoordinate);

    return route;
}

QString Coder::encodeCoordinate(const QGeoCoordinate &coordinate)
{
    return encodeNumber(coordinate.latitude()) + encodeNumber(coordinate.longitude());
}

QString Coder::encodeNumber(double number)
{
    unsigned int t = qRound(number*1e5);
    t <<= 1;
    if (number < 0)
        t = ~t;
    char symbols[7];
    unsigned int help = 31; // 11111b
    for (int i = 0; i < 6; i++) {
        symbols[i] = (t&help)>>i*5;
        help <<= 5;
    }
    int j = 5;
    while ((symbols[j] == 0)&&(j>0))
        j--;
    for (int i = 0; i < j; i++)
        symbols[i] = (symbols[i]^0x20)+63;
    symbols[j] = symbols[j]+63;
    symbols[j+1] = '\0';
    return QString(symbols);
}

int Coder::decodeCoordinate(QString &polyline, QGeoCoordinate &coordinate)
{
    coordinate.setLatitude(decodeNumber(polyline));
    coordinate.setLongitude(decodeNumber(polyline));
    return polyline.length();
}

double Coder::decodeNumber(QString &polyline)
{
    int i = 0;
    while ((i < polyline.length())&&(polyline[i] >= 95))
        i++;
    const char *numbersymbols = polyline.left(i+1).toStdString().c_str();
    polyline = polyline.mid(i+1);
    unsigned int number = 0;
    int j = 0;
    for (; j < i; j++)
        number ^= (((uint)numbersymbols[j]-63)&0x1f)<<5*j;
    number ^= (uint)((uint)numbersymbols[j]-63)<<5*j;
    if (number&1) {
        number = ~number;
        number = (number>>1)^0x80000000;
    }
    else
        number >>= 1;
    return double((int)number)*1.e-5;
}
