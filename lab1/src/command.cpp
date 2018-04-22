#include "command.h"
#include "model.h"

CreateRouteCommand::CreateRouteCommand(Model *model, int index, GeoRoute route) :
    m_model(model),
    m_index(index),
    m_route(route)
{

}

void CreateRouteCommand::redo()
{
    m_model->createRoute(m_index, m_route);
}

void CreateRouteCommand::undo()
{
    m_model->removeRoute(m_index);
}

