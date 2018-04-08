#include "presenter.h"

Presenter::Presenter(Model *model, MainWindow *view, QObject *parent) :
    QObject(parent),
    m_model(model),
    m_view(view)
{

}
