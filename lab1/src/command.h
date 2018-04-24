#ifndef COMMAND_H
#define COMMAND_H2

#include <georoute.h>

class Model;

class Command
{
public:
    Command() = default;
    virtual ~Command() = default;

    virtual void redo() = 0;
    virtual void undo() = 0;
};

class CreateRouteCommand : public Command
{
public:
    CreateRouteCommand(Model *model, int index, GeoRoute route);
    ~CreateRouteCommand() = default;

    void redo();
    void undo();

private:
    Model *m_model;
    int m_index;
    GeoRoute m_route;

};

class RemoveRouteCommand : public Command
{
public:
    RemoveRouteCommand(Model *model, int index, GeoRoute route);
    ~RemoveRouteCommand() = default;

    void redo();
    void undo();

private:
    Model *m_model;
    int m_index;
    GeoRoute m_route;

};

class CreateCoordinateCommand : public Command
{
public:
    CreateCoordinateCommand(Model *model, int route, int index, QGeoCoordinate coordinate);
    ~CreateCoordinateCommand() = default;

    void redo();
    void undo();

private:
    Model *m_model;
    int m_route;
    int m_index;
    QGeoCoordinate m_coordinate;

};

class RemoveCoordinateCommand : public Command
{
public:
    RemoveCoordinateCommand(Model *model, int route, int index, QGeoCoordinate coordinate);
    ~RemoveCoordinateCommand() = default;

    void redo();
    void undo();

private:
    Model *m_model;
    int m_route;
    int m_index;
    QGeoCoordinate m_coordinate;

};

class EditRouteCommand : public Command
{
public:
    EditRouteCommand(Model *model, int index, QString newname, QString oldname);
    ~EditRouteCommand() = default;

    void redo();
    void undo();

private:
    Model *m_model;
    int m_index;
    QString m_name;
    QString m_oldname;

};

class EditCoordinateCommand : public Command
{
public:
    EditCoordinateCommand(Model *model, int route, int index, int column, double newvalue, double oldvalue);
    ~EditCoordinateCommand() = default;

    void redo();
    void undo();

private:
    Model *m_model;
    int m_route;
    int m_index;
    int m_column;
    double m_value;
    double m_oldvalue;

};
#endif // COMMAND_H
