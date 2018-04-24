#ifndef MODEL_H
#define MODEL_H

#include "georoute.h"
#include "commanddirector.h"

#include <QObject>
#include <QtCharts/QLineSeries>

QT_CHARTS_USE_NAMESPACE

class Model : public QObject
{
    Q_OBJECT

public:

    explicit Model(QObject *parent = nullptr);
    ~Model();

    void createRoute(int index = -1, const GeoRoute &route = GeoRoute());
    void removeRoute(int index);

    void createCoordinate(int route, int index = -1, const QGeoCoordinate &coordinate = QGeoCoordinate(0, 0, nan("")));
    void removeCoordinate(int route, int index = -1);

    void editRouteName(int index, QString name);
    void editCoordinate(int route, int index, int column, double newvalue);

    void addRoutesFromFiles(const QStringList filenames);
    void addRouteFromPolyline(QString polyline);

    void loadFromSave();
    void save();

    QString getPolyline(int route);
    QLineSeries *createSeries(int route);


    void redo();
    void undo();

signals:
    void s_routeCreated(const GeoRoute &route, int index);
    void s_routeRemoved(int index);
    void s_nameChanged(QString name, int index);
    void s_coordinateCreated(QGeoCoordinate coord, int route, int index);
    void s_coordinateRemoved(int route, int index);
    void s_coordinateChanged(double newvalue, int route, int index, int column);
    void s_polylineChanged(QString s);
    void s_chartChanged(QLineSeries *s);
    void s_lengthChanged(int index, double l);

private:
    QList<GeoRoute> m_routes;
    CommandDirector m_director;

};

#endif // MODEL_H
