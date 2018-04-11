#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include "georoute.h"

class Model : public QObject
{
    Q_OBJECT

public:

    explicit Model(QObject *parent = nullptr);
    ~Model();

    int createRoute(int index = -1, GeoRoute route = GeoRoute());
    void removeRoute(int index);

    void editRouteName(int index, QString name);
    void editRouteDate(int index, QDateTime date);

    void createCoordinate(int index = -1);
    void removeCoordinate(int index);

    void editCoordinateLatitude(int route, int index, double latitude);
    void editCoordinateLongitude(int route, int index, double longitude);
    void editCoordinateAltitude(int route, int index, double altitude);

    void addRoutesFromFiles(QStringList filenames);
    void addRouteFromPolyline(QString polyline);

    void loadFromSave();

signals:
    void RouteWasCreated(const GeoRoute &route);
private:
    QList<GeoRoute> m_routes;
    GeoRoute *curroute;
    QString *polyline;
};

#endif // MODEL_H
