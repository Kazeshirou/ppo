#include "presenter.h"
#include "model.h"
#include "mainwindow.h"

Presenter::Presenter(Model *model, MainWindow *view, QObject *parent) :
    QObject(parent),
    m_model(model),
    m_view(view)
{
    if (!model)
        m_model = new Model(this);
    if (!view)
        m_view = new MainWindow();
    m_view->show();

    connect(m_view, SIGNAL(s_fromFile(QStringList)), this, SLOT(addRoutesFromFile(QStringList)));
    connect(m_view, SIGNAL(s_fromPolyline(QString)), this, SLOT(addRouteFromPolyline(QString)));
    connect(m_view, SIGNAL(s_insertRoute(int)), this, SLOT(createRoute(int)));
    connect(m_view, SIGNAL(s_deleteRoute(int)), this, SLOT(removeRoute(int)));
    connect(m_view, SIGNAL(s_insertCoordinate(int, int)), this, SLOT(createCoordinate(int, int)));
    connect(m_view, SIGNAL(s_deleteCoordinate(int, int)), this, SLOT(removeCoordinate(int, int)));
    connect(m_view, SIGNAL(s_changeCurrentRoute(int)), this, SLOT(routeChanged(int)));
    connect(m_view, SIGNAL(s_changeRoute(int, QString)), this, SLOT(editRouteName(int, QString)));
    connect(m_view, SIGNAL(s_changeCoordinate(int, int, int, double)), this, SLOT(editCoordinate(int, int, int, double)));

    connect(m_view, SIGNAL(s_redo()), this, SLOT(redo()));
    connect(m_view, SIGNAL(s_undo()), this, SLOT(undo()));

    connect(m_model, SIGNAL(s_routeCreated(GeoRoute, int)), this, SLOT(insertRoute(GeoRoute, int)));
    connect(m_model, SIGNAL(s_routeRemoved(int)), this, SLOT(deleteRoute(int)));
    connect(m_model, SIGNAL(s_coordinateCreated(QGeoCoordinate, int, int)), this, SLOT(insertCoordinate(QGeoCoordinate, int, int)));
    connect(m_model, SIGNAL(s_coordinateRemoved(int, int)), this, SLOT(deleteCoordinate(int, int)));
    connect(m_model, SIGNAL(s_polylineChanged(QString)), this, SLOT(changePolyline(QString)));
    connect(m_model, SIGNAL(s_chartChanged(QLineSeries*)), this, SLOT(changeChart(QLineSeries*)));
    connect(m_model, SIGNAL(s_nameChanged(QString, int)), this, SLOT(changeRouteName(QString, int)));
    connect(m_model, SIGNAL(s_coordinateChanged(double, int, int, int)), this, SLOT(changeCoordinate(double, int, int, int)));
    connect(m_model, SIGNAL(s_lengthChanged(int, double)), this, SLOT(changeRouteLength(int, double)));

    m_model->loadFromSave();
}

void Presenter::addRoutesFromFile(const QStringList files)
{
    if (files.length())
        m_model->addRoutesFromFiles(files);
}

void Presenter::addRouteFromPolyline(const QString polyline)
{
    if (polyline.length())
        m_model->addRouteFromPolyline(polyline);
}

void Presenter::createRoute(int index)
{
    m_model->createRoute(index, GeoRoute());
}

void Presenter::createCoordinate(int route, int index)
{
    m_model->createCoordinate(route, index);
}

void Presenter::removeCoordinate(int route, int index)
{
    m_model->removeCoordinate(route, index);
}

void Presenter::removeRoute(int index)
{
    m_model->removeRoute(index);
}

void Presenter::editRouteName(int index, QString name)
{
    m_model->editRouteName(index, name);
}

void Presenter::editCoordinate(int route, int index, int column, double newvalue)
{
    m_model->editCoordinate(route, index, column, newvalue);
}

void Presenter::insertRoute(const GeoRoute route, int index)
{
    m_view->insertRoute(route, index);
}

void Presenter::deleteRoute(int index)
{
    m_view->deleteRoute(index);
}

void Presenter::insertCoordinate(const QGeoCoordinate coordinate, int route, int index)
{
    m_view->insertCoordinate(coordinate, route, index);
}

void Presenter::deleteCoordinate(int route, int index)
{
    m_view->deleteCoordinate(route, index);
}

void Presenter::changePolyline(QString s)
{
    m_view->changePolyline(s);
}

void Presenter::changeChart(QLineSeries *s)
{
    m_view->changeChart(s);
}

void Presenter::changeRouteLength(int index, double l)
{
    m_view->changeRouteLength(index, l);
}

void Presenter::routeChanged(int route)
{
    changePolyline(m_model->getPolyline(route));
    QLineSeries *s = m_model->createSeries(route);
    changeChart(s);
}

void Presenter::changeRouteName(QString newname, int index)
{
    m_view->changeRoute(index, newname);
}

void Presenter::changeCoordinate(double newvalue, int route, int index, int column)
{
    m_view->changeCoordinate(route, index, column, newvalue);
}

void Presenter::redo()
{
    m_model->redo();
}

void Presenter::undo()
{
    m_model->undo();
}
