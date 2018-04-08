#include "routemodel.h"

#include<QDebug>

RouteModel::RouteModel(const QList<QGeoRoute> &routes, QObject *parent) :
    QAbstractItemModel(parent),
    _routes(routes)
{

}

QVariant RouteModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    if (index.internalPointer() == nullptr)
        return QVariant();
    else if (index.internalPointer() == &_routes) {
        if (index.column() == 0)
            return _routes[index.row()].routeId();
        else if (index.column() == 1)
            return _routes[index.row()].distance();
        else if (index.column() == 2)
            return _routes[index.row()].travelTime();
        else
            return QVariant();
    }
    else {
        QGeoRoute *t = (QGeoRoute *)index.internalPointer();
        QList<QGeoCoordinate> l = t->path();
        if (index.column() == 0)
            return l[index.row()].latitude();
        else if (index.column() == 1)
            return l[index.row()].longitude();
        else
            return QVariant();
    }

    return QVariant();
}

QModelIndex RouteModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!parent.isValid())
        return createIndex(0,0);
    else if (parent.internalPointer() == nullptr)
        return createIndex(row, column, (void *)&_routes);
    else if (parent.internalPointer() == (void *)&_routes)
        return createIndex(row, column, (void *)&_routes[row]);
    return QModelIndex();
}

QModelIndex RouteModel::parent(const QModelIndex &child) const
{
    return child.parent();
}

int RouteModel::rowCount(const QModelIndex &parent) const
{
    qDebug() << _routes.length();
    return _routes.length();
}

int RouteModel::columnCount(const QModelIndex &parent) const
{
   return 6;
}
