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

RemoveRouteCommand::RemoveRouteCommand(Model *model, int index, GeoRoute route) :
    m_model(model),
    m_index(index),
    m_route(route)
{

}

void RemoveRouteCommand::redo()
{
    m_model->removeRoute(m_index);
}

void RemoveRouteCommand::undo()
{
    m_model->createRoute(m_index, m_route);
}

CreateCoordinateCommand::CreateCoordinateCommand(Model *model, int route, int index, QGeoCoordinate coordinate) :
    m_model(model),
    m_route(route),
    m_index(index),
    m_coordinate(coordinate)
{

}

void CreateCoordinateCommand::redo()
{
    m_model->createCoordinate(m_index, m_route, m_coordinate);
}

void CreateCoordinateCommand::undo()
{
    m_model->removeCoordinate(m_route, m_index);
}

RemoveCoordinateCommand::RemoveCoordinateCommand(Model *model, int route, int index, QGeoCoordinate coordinate) :
    m_model(model),
    m_route(route),
    m_index(index),
    m_coordinate(coordinate)
{

}

void RemoveCoordinateCommand::redo()
{
    m_model->removeCoordinate(m_route, m_index);
}

void RemoveCoordinateCommand::undo()
{
    m_model->createCoordinate(m_route, m_index, m_coordinate);
}

EditRouteCommand::EditRouteCommand(Model *model, int index, QString newname, QString oldname) :
    m_model(model),
    m_index(index),
    m_name(newname),
    m_oldname(oldname)
{

}

void EditRouteCommand::redo()
{
    m_model->editRouteName(m_index, m_name);
}

void EditRouteCommand::undo()
{
    m_model->editRouteName(m_index, m_oldname);
}

EditCoordinateCommand::EditCoordinateCommand(Model *model, int route, int index, int column, double newvalue, double oldvalue) :
    m_model(model),
    m_route(route),
    m_index(index),
    m_column(column),
    m_value(newvalue),
    m_oldvalue(oldvalue)
{

}

void EditCoordinateCommand::redo()
{
    m_model->editCoordinate(m_route, m_index, m_column, m_value);
}

void EditCoordinateCommand::undo()
{
    m_model->editCoordinate(m_route, m_index, m_column, m_oldvalue);
}

