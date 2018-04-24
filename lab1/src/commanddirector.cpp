#include "commanddirector.h"
#include "command.h"

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
    int l = undostack.length();
    command->redo();
    while (undostack.length() > l)
        undostack.pop_back();
    undostack.push(command);
}

void CommandDirector::undo()
{
    if (!undostack.length())
        return;
    Command *command = undostack.pop();
    int l = undostack.length();
    command->undo();
    while (undostack.length() > l)
        undostack.pop_back();
    redostack.push(command);
}

void CommandDirector::clear()
{
    while (!redostack.isEmpty())
        delete redostack.pop();
    while (!undostack.isEmpty())
        delete undostack.pop();
}

CommandDirector::~CommandDirector()
{
    clear();
}
