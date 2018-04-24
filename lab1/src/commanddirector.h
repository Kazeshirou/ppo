#ifndef COMMANDDIRECTOR_H
#define COMMANDDIRECTOR_H

#include <QStack>

class Command;

class CommandDirector
{
public:

    explicit CommandDirector();
    ~CommandDirector();
    void addCommand(Command *command);
    void redo();
    void undo();
    void clear();

private:
    QStack<Command *> undostack;
    QStack<Command *> redostack;
};

#endif // COMMANDDIRECTOR_H
