#ifndef PRESENTER_H
#define PRESENTER_H

#include <QObject>

class Model;
class MainWindow;
class GeoRoute;

class Presenter : public QObject
{
    Q_OBJECT
public:
    explicit Presenter(Model *model = nullptr, MainWindow *view = nullptr, QObject *parent = nullptr);
public slots:
    void addRoutesFromFile(QStringList l);
    void showRoute(const GeoRoute &route);
private:
    Model *m_model;
    MainWindow *m_view;
};

#endif // PRESENTER_H
