#include "command.h"
#include "commanddirector.h"
#include "treemodel.h"

#include <QDebug>

void GroupCommand::redo()
{
    for (int i = 0; i < _commands.length(); i++)
        _commands[i]->redo();
}

void GroupCommand::undo()
{
    for (int i = _commands.length(); --i >= 0; )
        _commands[i]->undo();
}

AddDataCommand::AddDataCommand(TreeModel *model, const QList<GeoRoute> &routes) :
    _model(model),
    _routes(routes)
{
    CommandDirector::addCommand(this);
}

void AddDataCommand::redo()
{
    _model->addData(_routes);
}

void AddDataCommand::undo()
{
    _model->removeRows(_model->rowCount(QModelIndex()) - _routes.length(), _routes.length(), QModelIndex());
}

RemoveCommand::RemoveCommand(TreeModel *model, QModelIndexList indices) :
    _model(model),
    _indices(indices)
{
    _data = _model->getData();

    for (int i = _indices.length(); --i >= 0; )
        _model->removeRows(_indices[i].row(), 1, _indices[i].parent());
    _data1 = _model->getData();
    CommandDirector::addCommand(this);

}

void RemoveCommand::redo()
{
    _model->setData(_data1);
}

void RemoveCommand::undo()
{
    _model->setData(_data);
}

InsertCommand::InsertCommand(QAbstractItemModel *model, int row, QModelIndex index) :
    _model(model),
    _row(row),
    _index(index)
{
    CommandDirector::addCommand(this);
}

void InsertCommand::redo()
{
    _model->insertRows(_row, 1, _index);
}

void InsertCommand::undo()
{
    _model->removeRows(_row, 1, _index);
}

SetDataCommand::SetDataCommand(QAbstractItemModel *model, QModelIndex index, QVariant data) :
    _model(model),
    _index(index),
    _newdata(data)
{
    _olddata = _model->data(_index, Qt::DisplayRole);
    qDebug() << _olddata << _newdata;
    CommandDirector::addCommand(this);
}

void SetDataCommand::redo()
{
    qDebug() << _newdata;
    _model->setData(_index, _newdata, Qt::DisplayRole);
}

void SetDataCommand::undo()
{
    qDebug() << _olddata;
    _model->setData(_index, _olddata, Qt::DisplayRole);
}
