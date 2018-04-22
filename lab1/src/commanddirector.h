#ifndef COMMANDDIRECTOR_H
#define COMMANDDIRECTOR_H

#include "command.h"

#include <QStack>

class CommandDirector
{
public:

    explicit CommandDirector();
    ~CommandDirector();
    void addCommand(Command *command);
    void redo();
    void undo();

private:
    QStack<Command *> undostack;
    QStack<Command *> redostack;
};

#endif // COMMANDDIRECTOR_H
