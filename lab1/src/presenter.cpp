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

    connect(m_view, SIGNAL(Open(QStringList)), this, SLOT(addRoutesFromFile(QStringList)));
    connect(m_model, SIGNAL(RouteWasCreated(GeoRoute)), this, SLOT(showRoute(GeoRoute)));

    m_model->loadFromSave();
}

void Presenter::addRoutesFromFile(QStringList l)
{
    m_model->addRoutesFromFiles(l);
}

void Presenter::showRoute(const GeoRoute &route)
{
    m_view->showRoute(route);
}
