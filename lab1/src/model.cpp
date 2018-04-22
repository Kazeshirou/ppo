#include "model.h"
#include "gpxparser.h"
#include "coder.h"

Model::Model(QObject *parent) :
    QObject(parent)
{

}

Model::~Model()
{
    save();
}

void Model::createRoute(int index, const GeoRoute &route)
{
    int i = m_routes.length();
    if ((index < 0) || (index >= i))
    {
        m_routes.append(route);
        index = i;
    }
    else
        m_routes.insert(index, route);

    emit s_routeCreated(m_routes[index], index);
}

void Model::removeRoute(int index)
{
    int i = m_routes.length();
    if (!i)
        return;
    if ((index < 0) || (index >= i))
    {
        m_routes.pop_back();
        index = i;
    }
    else
        m_routes.removeAt(index);
    emit s_routeRemoved(index);

}

void Model::editRouteName(int index, QString name)
{
    if ((index < 0) || (index >= m_routes.length()))
        return;
    m_routes[index].setName(name);
    emit s_nameChanged(name, index);
}

void Model::createCoordinate(int route, int index)
{
    if ((route < 0) || (route >= m_routes.length()))
        return;
    int i = m_routes.at(route).path().length();
    if ((index < 0) || (index >= i))
    {
        m_routes[route].addCoordinate(QGeoCoordinate(0, 0, nan("")));
        index = i;
    }
    else
        m_routes[route].insertCoordinate(index, QGeoCoordinate(0, 0, nan("")));
    emit s_coordinateCreated(QGeoCoordinate(0, 0, nan("")), route, index);
    emit s_polylineChanged(m_routes.at(route).getPolyline());
}

void Model::removeCoordinate(int route, int index)
{
    if ((route < 0) || (route >= m_routes.length()))
        return;
    int i = m_routes.at(route).path().length();
    if ((index < 0) || (index >= i))
        return;
    m_routes[route].removeCoordinate(index);
    if (m_routes.at(route).path().length())
    {
        emit s_coordinateRemoved(route, index);
        emit s_polylineChanged(m_routes.at(route).getPolyline());
    }
    else
    {
        m_routes.removeAt(route);
        emit s_routeRemoved(route);
    }
}

void Model::editCoordinate(int route, int index, int column, double newvalue)
{
    if ((route < 0) || (route >= m_routes.length()))
        return;
    int i = m_routes.at(route).path().length();
    if ((index < 0) || (index >= i))
        return;

    switch (column) {
    case 0:
        m_routes[route].changeLatitude(index, newvalue);
        emit s_polylineChanged(m_routes.at(route).getPolyline());
        break;
    case 1:
        m_routes[route].changeLongitude(index, newvalue);
        emit s_polylineChanged(m_routes.at(route).getPolyline());
        break;
    case 2:
        m_routes[route].changeAltitude(index, newvalue);
        break;
    default:
        return;
    }
    emit s_coordinateChanged(newvalue, route, index, column);
}

void Model::addRoutesFromFiles(const QStringList filenames)
{
    GpxParser parser;
    QList<GeoRoute> routes = parser.parse(filenames);
    for (int i = 0; i < routes.length(); i++)
        createRoute(-1, routes[i]);
}

void Model::addRouteFromPolyline(const QString polyline)
{
    createRoute(-1, GeoRoute(Coder::decode(polyline)));
}

void Model::loadFromSave()
{
    SaveParser p;
    QList<GeoRoute> routes = p.parse();
    foreach (GeoRoute route, routes)
        createRoute(-1, route);
}

void Model::save()
{
    SaveParser p;
    p.save(m_routes);
}

QString Model::getPolyline(int route)
{
    if ((route >= 0) && (route < m_routes.length()))
        return m_routes.at(route).getPolyline();
    return QString();
}
