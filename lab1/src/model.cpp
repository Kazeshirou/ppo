#include "model.h"
#include "gpxparser.h"
#include "coder.h"
#include "command.h"

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

    m_director.addCommand(new CreateRouteCommand(this, index, route));
    emit s_routeCreated(m_routes[index], index);
}

void Model::removeRoute(int index)
{
    GeoRoute route;
    int i = m_routes.length();
    if (!i)
        return;
    if ((index < 0) || (index >= i))
    {
        route = m_routes.at(i);
        m_routes.pop_back();
        index = i;
    }
    else
    {
        route = m_routes.at(index);
        m_routes.removeAt(index);
    }

    m_director.addCommand(new RemoveRouteCommand(this, index, route));
    emit s_routeRemoved(index);

}

void Model::editRouteName(int index, QString name)
{
    if ((index < 0) || (index >= m_routes.length()))
        return;
    QString oldname = m_routes.at(index).getName();
    m_routes[index].setName(name);
    m_director.addCommand(new EditRouteCommand(this, index, name, oldname));
    emit s_nameChanged(name, index);
}

void Model::createCoordinate(int route, int index, const QGeoCoordinate &coordinate)
{
    if ((route < 0) || (route >= m_routes.length()))
        return;
    int i = m_routes.at(route).path().length();
    if ((index < 0) || (index >= i))
    {
        m_routes[route].addCoordinate(coordinate);
        index = i;
    }
    else
        m_routes[route].insertCoordinate(index, coordinate);

    m_director.addCommand(new CreateCoordinateCommand(this, route, index, coordinate));
    emit s_coordinateCreated(coordinate, route, index);
    emit s_polylineChanged(m_routes.at(route).getPolyline());
}

void Model::removeCoordinate(int route, int index)
{
    if ((route < 0) || (route >= m_routes.length()))
        return;
    int i = m_routes.at(route).path().length();
    if ((index < 0) || (index >= i))
        return;
    QGeoCoordinate coord = m_routes[route].coordinateAt(index);
    if (m_routes.at(route).path().length() - 1)
    {
        m_routes[route].removeCoordinate(index);
        m_director.addCommand(new RemoveCoordinateCommand(this, route, index, coord));
        emit s_coordinateRemoved(route, index);
        emit s_polylineChanged(m_routes.at(route).getPolyline());
    }
    else
    {
        m_director.addCommand(new RemoveRouteCommand(this, route, m_routes.at(route)));
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
    double oldvalue;
    switch (column) {
    case 0:
        oldvalue = m_routes.at(route).coordinateAt(index).latitude();
        m_routes[route].changeLatitude(index, newvalue);
        emit s_polylineChanged(m_routes.at(route).getPolyline());
        break;
    case 1:
        oldvalue = m_routes.at(route).coordinateAt(index).longitude();
        m_routes[route].changeLongitude(index, newvalue);
        emit s_polylineChanged(m_routes.at(route).getPolyline());
        break;
    case 2:
        oldvalue = m_routes.at(route).coordinateAt(index).altitude();
        m_routes[route].changeAltitude(index, newvalue);
        break;
    default:
        return;
    }

    m_director.addCommand(new EditCoordinateCommand(this, route, index, column, newvalue, oldvalue));
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
    m_director.clear();
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

void Model::redo()
{
    m_director.redo();
}

void Model::undo()
{
    m_director.undo();
}
