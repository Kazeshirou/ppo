#include "commanddirector.h"

QStack<Command *> CommandDirector::undostack;
QStack<Command *> CommandDirector::redostack;

void CommandDirector::addCommand(Command *command)
{
    command->redo();
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
