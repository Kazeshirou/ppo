#include "treemodel.h"
#include "treemodelitem.h"
#include "georoute.h"

#include <QDebug>

TreeModel::TreeModel(const QList<GeoRoute> &data, QObject *parent) :
    QAbstractItemModel(parent),
    m_data(data)
{
    QList<QVariant> rootData( {"Название", "Длина", "Дата создания"} );
    m_root = new TreeModelItem(rootData);
    setupModelData();
}

TreeModel::~TreeModel()
{
    delete m_root;
}

bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || role != Qt::EditRole) {
        qDebug() << "not valid";
        return false;
    }

    TreeModelItem *item = static_cast<TreeModelItem *>(index.internalPointer());
    if (item->columnCount() == 3) {
        if ((index.column() == 1) || (index.column() == 2))
            return false;
        else {
            if (item->setData(value, index.column())) {
                qDebug() << value;
                m_data[item->number()].setName(value.toString());      
                emit dataChanged(index, index, (QVector<int>() << Qt::DisplayRole << Qt::EditRole));
                return true;
            }
            else
                return false;
        }
    }
    else if (item->data(0) == "Широта")
        return false;
    else {
        if (item->setData(value.toString().replace(",", ".").toDouble(), index.column())) {
            qDebug() << value;
            TreeModelItem *parent = item->parent();
            int i = parent->number();
            int j = item->number()-1;
            m_data[i].replaceCoordinate(j, QGeoCoordinate(item->data(0).toDouble(), item->data(1).toDouble()));
            m_data[i].setDistance();
            parent->setData(m_data[i].getDistance(), 1);
            emit dataChanged(index, index, (QVector<int>() << Qt::DisplayRole << Qt::EditRole));
            return true;
        }
        else
            return false;
    }

}

bool TreeModel::insertRows(int position, int count, const QModelIndex &parent)
{
    TreeModelItem *parentItem = getItem(parent);
    bool success;
    beginInsertRows(parent, position, position + count - 1);
    if (parentItem == m_root) {
        success = parentItem->insertChildren(position, count, 3);
        for (int k = position; k < position + count; k++) {
            TreeModelItem *item = parentItem->child(k);
            item->insertChildren(0, 1, 2);
            item->setData("route", 0);
            item->setData(0, 1);
            m_data.insert(k, GeoRoute());
            item->setData(m_data.at(k).getDate(), 2);
            item = parentItem->child(0);
            item->setData("Широта", 0);
            item->setData("Долгота", 1);
        }
    }
    else {
        success = parentItem->insertChildren(position, count, 2);
        for (int k = position; k < position + count; k++) {
            int i = parentItem->number();
            m_data[i].insertCoordinate(k ? k-1 : 0, QGeoCoordinate(0, 0));
            m_data[i].setDistance();
            parentItem->setData(m_data[i].getDistance(), 1);
            TreeModelItem *item = parentItem->child(k);
            item->setData(0, 0);
            item->setData(0, 1);
        }
    }
    endInsertRows();

    return success;
}

bool TreeModel::removeRows(int position, int count, const QModelIndex &parent)
{
    TreeModelItem *parentItem = getItem(parent);
    if ((!parentItem) || !count)
        return false;
    bool success = true;

    if (parentItem->child(position)->data(0) == "Широта") {
        position++;
        count--;
    }
    if (parentItem == m_root)
        for (int k = position+count-1; k >= position; k--) {
            QModelIndex route = index(k, 0, QModelIndex());
            beginRemoveRows(route, 0, m_data.at(k).path().length());
            endRemoveRows();
            m_data.removeAt(k);
        }
    else {
        int i = parentItem->number();
        for (int k = position+count-1; k >= position; k--)
            m_data[i].removeCoordinate(k-1);
        m_data[i].setDistance();
        parentItem->setData(m_data[i].getDistance(), 1);

    }
    beginRemoveRows(parent, position, position + count - 1);
    success = parentItem->removeChildren(position, count);
    endRemoveRows();

    return success;
}

GeoRoute TreeModel::getData(int i)
{
    if (i >= 0)
        return m_data[i];
    else
        return GeoRoute();
}

void TreeModel::setData(const QList<GeoRoute> &routes)
{
    removeRows(0, m_data.length(),QModelIndex());
    addData(routes);
}

QList<GeoRoute> TreeModel::getData()
{
    return m_data;
}

bool TreeModel::addData(const QList<GeoRoute> &data)
{
    QModelIndex parent = QModelIndex();
    TreeModelItem *parentItem = getItem(parent);
    bool success;
    int position = m_data.length();
    int count = data.length();
    beginInsertRows(parent, position, position + count - 1);
    success = parentItem->insertChildren(position, count, 3);
    for (int k = position; k < position + count; k++) {
        m_data.insert(k, data[k - position]);
        TreeModelItem *item = parentItem->child(k);
        item->insertChildren(0, 1, 2);
        item->setData(m_data[k].getName(), 0);
        m_data[k].setDistance();
        item->setData(m_data[k].getDistance(), 1);
        item->setData(m_data.at(k).getDate(), 2);
        item = item->child(0);
        item->setData("Широта", 0);
        item->setData("Долгота", 1);
    }
    endInsertRows();
    for (int k = position; k < position + count; k++) {
        QModelIndex route = index(k, 0, QModelIndex());
        parentItem = getItem(route);
        QList<QGeoCoordinate> path = m_data[k].path();
        int count = path.length();
        beginInsertRows(route, 1, count);
        success = parentItem->insertChildren(1, count, 2);
        for (int i = 1; i <= count; i++) {
            TreeModelItem *item = parentItem->child(i);
            item->setData(path[i-1].latitude(), 0);
            item->setData(path[i-1].longitude(), 1);
        }
        endInsertRows();
    }


    return success;
}

int TreeModel::routeNumber(const QModelIndex &index)
{
    if (!index.isValid())
        return -1;
    TreeModelItem *item = getItem(index);
    if (item->parent() == m_root)
        return item->number();
    else
        return item->parent()->number();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    TreeModelItem *item = static_cast<TreeModelItem *>(index.internalPointer());
    return item->data(index.column());
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;
    TreeModelItem *item = static_cast<TreeModelItem *>(index.internalPointer());
    if (item->data(0) == "Широта")
        return QAbstractItemModel::flags(index);
    else
        return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return m_root->data(section);

    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeModelItem *parentItem;

    if (!parent.isValid())
        parentItem = m_root;
    else
        parentItem = static_cast<TreeModelItem *>(parent.internalPointer());

    TreeModelItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeModelItem *childItem = static_cast<TreeModelItem *>(index.internalPointer());
    TreeModelItem *parentItem = childItem->parent();

    if (parentItem == m_root)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeModelItem *parentItem;
    if(parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = m_root;
    else
        parentItem = static_cast<TreeModelItem *>(parent.internalPointer());

    return parentItem->childCount();
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeModelItem *>(parent.internalPointer())->columnCount();
    else
        return m_root->columnCount();
}

void TreeModel::setupModelData()
{
    QList<QVariant> coordinateRootData({"Широта", "Долгота"});
    for (int i = 0; i < m_data.length(); i++) {
        QList<QVariant> routeData( {m_data.at(i).getName(),
                                   m_data.at(i).getDistance(),
                                   m_data.at(i).getDate()} );
        TreeModelItem *routeItem = new TreeModelItem(routeData, m_root);
        m_root->appendChild(routeItem);
        TreeModelItem *coordinateRootItem = new TreeModelItem(coordinateRootData, routeItem);
        routeItem->appendChild(coordinateRootItem);
        for (int j = 0; j < m_data[i].path().length(); j++) {
            QList<QVariant> coordinateData;
            coordinateData << m_data[i].path().at(j).latitude() << m_data[i].path().at(j).longitude();
            TreeModelItem *coordinateItem = new TreeModelItem(coordinateData, routeItem);
            routeItem->appendChild(coordinateItem);
        }
    }
}

TreeModelItem *TreeModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        TreeModelItem *item = static_cast<TreeModelItem *>(index.internalPointer());
        if (item)
            return item;
    }
    return m_root;
}
