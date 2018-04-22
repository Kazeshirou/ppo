#include "georoute.h"

GeoRoute::GeoRoute(const QGeoPath &p, const QString &name, const QDateTime &date) :
    QGeoPath(p),
    m_name(name),
    m_distance(0),
    m_date(date)
{
    if (path().length())
    {
        setDistance();
    }
    else
        addCoordinate(QGeoCoordinate(0, 0, nan("")));

    m_polyline = Coder::encode(path());

}

void GeoRoute::insertCoordinate(int index, const QGeoCoordinate &coordinate)
{
    QGeoPath::insertCoordinate(index, coordinate);
    m_polyline.insert(index, QList<QString>() << QString() << QString());
    changePolyline(index);
}

void GeoRoute::removeCoordinate(int index)
{
    QGeoPath::removeCoordinate(index);
    m_polyline.removeAt(index);
    changePolyline(index);
}

void GeoRoute::setPath(const QList<QGeoCoordinate> &path)
{
    QGeoPath::setPath(path);
    m_polyline.clear();
    m_polyline =  Coder::encode(path);
}

void GeoRoute::changeLatitude(int index, double newvalue)
{
    QGeoCoordinate c = coordinateAt(index);
    c.setLatitude(newvalue);
    replaceCoordinate(index, c);
    changePolyline(index);
}

void GeoRoute::changeLongitude(int index, double newvalue)
{
    QGeoCoordinate c = coordinateAt(index);
    c.setLongitude(newvalue);
    replaceCoordinate(index, c);
    changePolyline(index);
}

void GeoRoute::changeAltitude(int index, double newvalue)
{
    QGeoCoordinate c = coordinateAt(index);
    c.setAltitude(newvalue);
    replaceCoordinate(index, c);
}

void GeoRoute::changePolyline(int index)
{
    QList<QGeoCoordinate> p(path());
    int n = p.length();
    if ((index >= 0) && (index < n))
    {
        if (index == 0)
        {
            m_polyline[index] = Coder::encodeCoordinate(p.at(index));
        }
        if (index > 0)
        {
            QGeoCoordinate delta(p.at(index).latitude() - p.at(index - 1).latitude(),
                                 p.at(index).longitude() - p.at(index - 1).longitude());
            m_polyline[index] = Coder::encodeCoordinate(delta);
        }
        if (index < n-1)
        {
            QGeoCoordinate delta1(p.at(index + 1).latitude() - p.at(index).latitude(),
                                 p.at(index + 1).longitude() - p.at(index).longitude());
            m_polyline[index + 1] = Coder::encodeCoordinate(delta1);
        }
    }
}

void GeoRoute::setName(const QString &name)
{
    m_name = name;
}

QString GeoRoute::getName() const
{
    return m_name;
}

void GeoRoute::setDistance()
{
    m_distance = length()/1000.;
}

void GeoRoute::setDistance(float d)
{
    m_distance = d;
}

double GeoRoute::getDistance() const
{
    return m_distance;
}

void GeoRoute::setDate()
{
    m_date = QDateTime::currentDateTime();
}

void GeoRoute::setDate(const QDateTime &date)
{
    m_date = date;
}

QDateTime GeoRoute::getDate() const
{
    return m_date;
}

QString GeoRoute::getPolyline() const
{
    QString polyline;

    foreach (QList<QString> coord, m_polyline)
    {
        polyline += coord.at(0) + coord.at(1);
    }

    return polyline;
}
