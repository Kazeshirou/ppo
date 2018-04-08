#include "treeview.h"
#include "treemodel.h"
#include "command.h"

#include <QContextMenuEvent>
#include <QMenu>
#include <QDebug>
#include <QLineEdit>

TreeView::TreeView(QWidget *parent) :
    QTreeView(parent)
{
    connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(wasSelected(QModelIndex)));
}


void TreeView::contextMenuEvent(QContextMenuEvent *)
{
    QMenu *menu = createMenu();
    menu->exec(QCursor::pos());
}

void TreeView::insert()
{
    QModelIndex index = selectionModel()->currentIndex();
    QAbstractItemModel *m = model();

    new InsertCommand(m, index.row() + 1, index.parent());
    //m->insertRow(index.row()+1, index.parent());
}

void TreeView::remove()
{
    QModelIndexList indices = selectionModel()->selectedRows();
    TreeModel *m = dynamic_cast<TreeModel *>(model());
    new RemoveCommand(m, indices);
//    for (int i = indices.length(); --i >= 0; ) {
//        m->removeRows(indices[i].row(),1,indices[i].parent());
    //    }
}

void TreeView::commitData(QWidget *editor)
{
    if (!dynamic_cast<QLineEdit *>(editor)->text().length())
        return;
    new SetDataCommand(model(), selectionModel()->currentIndex(), dynamic_cast<QLineEdit *>(editor)->text());
    QTreeView::commitData(editor);
}

void TreeView::wasSelected(const QModelIndex &index)
{
    TreeModel *m = static_cast<TreeModel *>(model());
    emit selectedRoute(m->routeNumber(index));
}

QMenu *TreeView::createMenu()
{
    QMenu *menu = new QMenu(this);
    menu->addAction(QString("Вставить"), this, &TreeView::insert);
    menu->addAction(QString("Удалить"), this, &TreeView::remove);
    return menu;
}
