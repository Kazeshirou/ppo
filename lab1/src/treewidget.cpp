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
                                                route.getDate().toString(Qt::SystemLocaleShortDate));
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
    setCurrentItem(routeitem);

    emit itemSelectionChanged();
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
    emit itemSelectionChanged();
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
}

int TreeWidget::currentRoute()
{
    if (!selectedItems().length())
        return -1;
    QTreeWidgetItem *t = selectedItems().at(0);
    if (!t)
        return -1;
    int index = indexOfTopLevelItem(t);
    if (index < 0)
        index = indexOfTopLevelItem(t->parent());
    if (index < 0)
        index = topLevelItemCount() - 1;
    return index;
}

int TreeWidget::currentCoordinate()
{
    if (!selectedItems().length())
        return -1;
    QTreeWidgetItem *t = topLevelItem(currentRoute());
    int index = t->indexOfChild(selectedItems().at(0));
    if (index < 0)
        index = t->childCount() - 1;
    return index;
}

bool TreeWidget::currentIsRoute()
{
    return (!topLevelItemCount() || !currentItem() || (indexOfTopLevelItem(currentItem()) >= 0));
}

void TreeWidget::changeRoute(int index, QString newname)
{
    QTreeWidgetItem *t = topLevelItem(index);
    if (t)
        t->setData(0, Qt::DisplayRole | Qt::EditRole, QVariant(newname));
}

void TreeWidget::changeCoordinate(int route, int index, int column, double newvalue)
{
    QTreeWidgetItem *t = topLevelItem(route);
    if (t)
    {
        t = t->child(index);
        if (t)
            t->setData(column, Qt::DisplayRole | Qt::EditRole, QVariant(newvalue));
    }
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
            emit s_changeCoordinate(currentRoute(), currentCoordinate(), currentIndex().column(),  s.toDouble());
        }
        else
            emit s_changeRoute(currentRoute(), s);
    }
}



