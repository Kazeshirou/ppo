#include "treewidget.h"
#include "georoute.h"

#include <QLabel>
#include <QLineEdit>

TreeWidget::TreeWidget(QWidget *parent) :
    QTreeWidget(parent)
{

}

void TreeWidget::insertRoute(const GeoRoute &route, int index)
{
    QTreeWidgetItem *routeitem = new QTreeWidgetItem((QTreeWidget *)0,
                                                QStringList() << route.getName() <<
                                                QString::number(route.getDistance()) <<
                                                route.getDate().toString(Qt::SystemLocaleLongDate));
    routeitem->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    foreach (QGeoCoordinate coord, route.path())
    {
        QTreeWidgetItem *coorditem = new QTreeWidgetItem((QTreeWidget *)0,
                                                QStringList() << QString::number(coord.latitude()) <<
                                                QString::number(coord.longitude()) <<
                                                QString::number(coord.altitude()));
        coorditem->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        routeitem->addChild(coorditem);
    }
    if ((index < 0) || (index >= topLevelItemCount()))
        addTopLevelItem(routeitem);
    else
        insertTopLevelItem(index, routeitem);

    foreach (QTreeWidgetItem *item, selectedItems())
        setItemSelected(item, false);
    setItemSelected(routeitem, true);
}

void TreeWidget::removeRoute(const int index)
{
    if (!topLevelItemCount())
        return;
    int count = topLevelItemCount() - 1;
    if ((index < 0) || (index > count))
        takeTopLevelItem(count);
    else
        takeTopLevelItem(index);
}

void TreeWidget::insertCoordinate(const QGeoCoordinate &coordinate, const int route, const int index)
{
    QTreeWidgetItem *t = topLevelItem(route);
    if (t)
    {
        int count = t->childCount() - 1;
        QTreeWidgetItem *coorditem = new QTreeWidgetItem((QTreeWidget *)0,
                                                QStringList() << QString::number(coordinate.latitude()) <<
                                                QString::number(coordinate.longitude()) <<
                                                QString::number(coordinate.altitude()));
        coorditem->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        if ((index < 0) || (index > count))
            t->insertChild(count, coorditem);
        else
            t->insertChild(index, coorditem);
    }

}

void TreeWidget::removeCoordinate(const int route, const int index)
{
    QTreeWidgetItem *t = topLevelItem(route);
    if (t)
    {
        int count = t->childCount() - 1;
        if ((index < 0) || (index > count))
            t->removeChild(t->child(count));
        else
            t->removeChild(t->child(index));
    }
    if (!t->childCount())
        takeTopLevelItem(route);
}

int TreeWidget::currentRoute()
{
    QTreeWidgetItem *t = currentItem();
    if (!t)
        return 0;
    int index = indexOfTopLevelItem(t);
    if (index < 0)
        index = indexOfTopLevelItem(t->parent());
    if (index < 0)
        index = topLevelItemCount() - 1;
    return index;
}

int TreeWidget::currentCoordinate()
{
    QTreeWidgetItem *t = topLevelItem(currentRoute());
    int index = t->indexOfChild(currentItem());
    if (index < 0)
        index = t->childCount() - 1;
    return index;
}

bool TreeWidget::currentIsRoute()
{
    return (!topLevelItemCount() || !currentItem() || (indexOfTopLevelItem(currentItem()) >= 0));
}

bool TreeWidget::edit(const QModelIndex &index, QAbstractItemView::EditTrigger trigger, QEvent *event)
{
    if ((trigger == QAbstractItemView::DoubleClicked) && currentIsRoute() && (index.column() > 0))
            return false;
    else
        return QTreeWidget::edit(index, trigger, event);
}

void TreeWidget::commitData(QWidget *editor)
{
    QString s = dynamic_cast<QLineEdit *>(editor)->text();
    if (!s.length())
        return;
    else
    {
        if (!currentIsRoute()) {
            s.replace(',', '.');
            dynamic_cast<QLineEdit *>(editor)->setText(QString::number(s.toDouble()));
            emit coordinateWasChanged(currentRoute(), currentCoordinate(), currentIndex().column(),  s.toDouble());
        }
        else
            emit routeWasChanged(currentRoute(), s);
        QTreeWidget::commitData(editor);
    }
}



