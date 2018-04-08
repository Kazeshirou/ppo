#ifndef COMMANDDIRECTOR_H
#define COMMANDDIRECTOR_H

#include "command.h"

#include "QStack"

template <class T>
class QStack;

class CommandDirector
{
public:
    static void addCommand(Command *command);
    static void redo();
    static void undo();

private:
    explicit CommandDirector() = default;
    static QStack<Command *> undostack;
    static QStack<Command *> redostack;

};

#endif // COMMANDDIRECTOR_H
