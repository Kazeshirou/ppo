#include "model.h"
#include "gpxparser.h"

Model::Model(QObject *parent) :
    QObject(parent)
{

}

Model::~Model()
{
    SaveParser p;
    p.save(m_routes);
}

int Model::createRoute(int index, GeoRoute route)
{
    int i = m_routes.length();
    if ((index < 0) || (index >= i))
    {
        m_routes.append(route);
        index = i;
    }
    else
        m_routes.insert(index, route);

    emit RouteWasCreated(m_routes[index]);

    return index;
}

void Model::addRoutesFromFiles(QStringList filenames)
{
    GpxParser parser;
    QList<GeoRoute> routes = parser.parse(filenames);
    foreach (GeoRoute route, routes)
        createRoute(-1, route);
}

void Model::loadFromSave()
{
    SaveParser p;
    QList<GeoRoute> routes = p.parse();
    foreach (GeoRoute route, routes)
        createRoute(-1, route);
}
