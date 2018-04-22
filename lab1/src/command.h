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

#endif // COMMAND_H
