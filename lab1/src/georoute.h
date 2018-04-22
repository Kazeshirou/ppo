#ifndef GEOROUTE_H
#define GEOROUTE_H

#include <QGeoPath>
#include <QDateTime>

#include "coder.h"

class GeoRoute : public QGeoPath
{
public:
    explicit GeoRoute(const QGeoPath &path = QGeoPath(),
                      const QString &name = QString("route"),
                      const QDateTime &date = QDateTime::currentDateTime());

    void insertCoordinate(int index, const QGeoCoordinate &coordinate);
    void removeCoordinate(int index);
    void setPath(const QList<QGeoCoordinate> &path);

    void changeLatitude(int index, double newvalue);
    void changeLongitude(int index, double newvalue);
    void changeAltitude(int index, double newvalue);

    void changePolyline(int index);

    void setName(const QString &name);
    QString getName() const;

    void setDistance();
    void setDistance(float d);
    double getDistance() const;

    void setDate();
    void setDate(const QDateTime &date);
    QDateTime getDate() const;

    QString getPolyline() const;

private:
    QString m_name;
    double m_distance;
    QDateTime m_date;
    QList<QList<QString>> m_polyline;
};

#endif // GEOROUTE_H
