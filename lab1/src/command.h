#ifndef COMMAND_H
#define COMMAND_H

class TreeModel;

#include "georoute.h"

#include <QList>
#include <QModelIndex>

class Command
{
public:
    Command() = default;
    virtual void redo() = 0;
    virtual void undo() = 0;
};

class SetDataCommand : public Command
{
public:
    explicit SetDataCommand(QAbstractItemModel *model, QModelIndex index, QVariant data);


    void redo() override;
    void undo() override;
private:
    QAbstractItemModel *_model;
    QModelIndex _index;
    QVariant _newdata;
    QVariant _olddata;
};


class InsertCommand : public Command
{
public:
    explicit InsertCommand(QAbstractItemModel *model, int row, QModelIndex index);


    void redo() override;
    void undo() override;
private:
    QAbstractItemModel *_model;
    int _row;
    QModelIndex _index;
};

class RemoveCommand : public Command
{
public:
    explicit RemoveCommand(TreeModel *model, QModelIndexList indices);


    void redo() override;
    void undo() override;
private:
    TreeModel *_model;
    QModelIndexList _indices;
    QList<GeoRoute> _data;
    QList<GeoRoute> _data1;
};

class AddDataCommand : public Command
{
public:
    explicit AddDataCommand(TreeModel *model, const QList<GeoRoute> &routes);

    void redo() override;
    void undo() override;
private:
    TreeModel *_model;
    QList<GeoRoute> _routes;

};

class GroupCommand : public Command
{
public:
    explicit GroupCommand(const QList<Command *> &commands) : _commands(commands)
    { }

    void redo();
    void undo();

private:
    QList<Command *> _commands;
};
#endif // COMMAND_H
