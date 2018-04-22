#include "commanddirector.h"

CommandDirector::CommandDirector()
{
    redostack.clear();
    undostack.clear();
}

void CommandDirector::addCommand(Command *command)
{
    if (!command)
        return;
    undostack.push(command);
}

void CommandDirector::redo()
{
    if (!redostack.length())
        return;
    Command *command = redostack.pop();
    command->redo();
    undostack.push(command);
}

void CommandDirector::undo()
{
    if (!undostack.length())
        return;
    Command *command = undostack.pop();
    command->undo();
    redostack.push(command);
}

CommandDirector::~CommandDirector()
{
    while (!redostack.isEmpty())
        delete redostack.pop();
    while (!undostack.isEmpty())
        delete undostack.pop();
}
