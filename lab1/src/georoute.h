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
                      const QDateTime &date = QDateTime::currentDateTime()) :
        QGeoPath(path),
        m_name(name),
        m_distance(0),
        m_date(date)
    {
        addCoordinate(QGeoCoordinate(0, 0, _nan()));
        if (path.path().length())
            setDistance();
    }

    void setName(const QString &name) { m_name = name; }
    QString getName() const { return m_name; }

    void setDistance() { m_distance = length()/1000.; }
    void setDistance(const double distance) { m_distance = distance; }
    double getDistance() const { return m_distance; }

    void setDate() { m_date = QDateTime::currentDateTime(); }
    void setDate(const QDateTime &date) { m_date = date; }
    QDateTime getDate() const { return m_date; }

    QString getPolyline() const { return Coder::encode(this->path()); }

private:
    QString m_name;
    double m_distance;
    QDateTime m_date;
};

#endif // GEOROUTE_H
