#ifndef PRESENTER_H
#define PRESENTER_H

#include "georoute.h"
#include "commanddirector.h"

#include <QObject>

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
    void polyline(int route);
    void changeRouteName(QString newname, int index);
    void changeCoordinate(double newvalue, int route, int index, int column);
    void redo();
    void undo();
    void editRouteName(int index, QString name);
    void editCoordinate(int route, int index, int column, double newvalue);

private:
    Model *m_model;
    MainWindow *m_view;
    CommandDirector m_director;
};

#endif // PRESENTER_H
