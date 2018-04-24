#ifndef PRESENTER_H
#define PRESENTER_H

#include "georoute.h"

#include <QObject>
#include <QtCharts/QLineSeries>

QT_CHARTS_USE_NAMESPACE

class Model;
class MainWindow;

class Presenter : public QObject
{
    Q_OBJECT

public:
    explicit Presenter(Model *model = nullptr, MainWindow *view = nullptr, QObject *parent = nullptr);

public slots:    
    void addRoutesFromFile(const QStringList files);
    void addRouteFromPolyline(const QString polyline);
    void insertRoute(const GeoRoute route, int index);
    void removeRoute(int index);
    void deleteRoute(int index);
    void createRoute(int index);
    void createCoordinate(int route, int index);
    void insertCoordinate(const QGeoCoordinate coordinate, int route, int index);
    void removeCoordinate(int route, int index);
    void deleteCoordinate(int route, int index);
    void changePolyline(QString s);
    void changeChart(QLineSeries *s);
    void changeRouteLength(int index, double l);
    void routeChanged(int route);
    void changeRouteName(QString newname, int index);
    void changeCoordinate(double newvalue, int route, int index, int column);
    void editRouteName(int index, QString name);
    void editCoordinate(int route, int index, int column, double newvalue);
    void redo();
    void undo();

private:
    Model *m_model;
    MainWindow *m_view;
};

#endif // PRESENTER_H
