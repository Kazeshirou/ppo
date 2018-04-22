#ifndef MODEL_H
#define MODEL_H

#include "georoute.h"

#include <QObject>

class Model : public QObject
{
    Q_OBJECT

public:

    explicit Model(QObject *parent = nullptr);
    ~Model();

    void createRoute(int index = -1, const GeoRoute &route = GeoRoute());
    void removeRoute(int index);

    void createCoordinate(int route, int index = -1);
    void removeCoordinate(int route, int index = -1);

    void editRouteName(int index, QString name);
    void editCoordinate(int route, int index, int column, double newvalue);

    void addRoutesFromFiles(const QStringList filenames);
    void addRouteFromPolyline(QString polyline);

    void loadFromSave();
    void save();

    QString getPolyline(int route);

signals:
    void s_routeCreated(const GeoRoute &route, int index);
    void s_routeRemoved(int index);
    void s_nameChanged(QString name, int index);
    void s_coordinateCreated(QGeoCoordinate coord, int route, int index);
    void s_coordinateRemoved(int route, int index);
    void s_coordinateChanged(double newvalue, int route, int index, int column);
    void s_polylineChanged(QString s);

private:
    QList<GeoRoute> m_routes;

};

#endif // MODEL_H
