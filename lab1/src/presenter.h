#ifndef PRESENTER_H
#define PRESENTER_H

#include <QObject>

class Model;
class MainWindow;

class Presenter
{
    Q_OBJECT
public:
    explicit Presenter(Model *model = nullptr, MainWindow *view = nullptr);

private:
    Model *m_model;
    MainWindow *m_view;
};

#endif // PRESENTER_H
