#include "treemodelitem.h"

TreeModelItem::TreeModelItem(const QList<QVariant> &data, TreeModelItem *parent)
{
    m_parent    = parent;
    m_itemData = data;
}

TreeModelItem::~TreeModelItem()
{
    qDeleteAll(m_childItems);
}

void TreeModelItem::appendChild(TreeModelItem *child)
{
    m_childItems.append(child);
}

TreeModelItem *TreeModelItem::child(int row)
{
    return m_childItems.value(row);
}

int TreeModelItem::childCount() const
{
    return m_childItems.count();
}

int TreeModelItem::columnCount() const
{
    return m_itemData.count();
}

QVariant TreeModelItem::data(int column) const
{
    return m_itemData.value(column);
}

int TreeModelItem::row() const
{
    if (m_parent)
        return m_parent->m_childItems.indexOf(const_cast<TreeModelItem *>(this));

    return 0;
}

TreeModelItem *TreeModelItem::parent()
{
    return m_parent;
}

int TreeModelItem::number() const
{
    if (m_parent)
        return m_parent->m_childItems.indexOf(const_cast<TreeModelItem *>(this));

    return 0;
}

bool TreeModelItem::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > m_childItems.length())
        return false;
    for (int row = 0; row < count; row++) {
        QList<QVariant> data;
        for (int i = 0; i < columns; i++)
            data << QVariant();
        TreeModelItem *item = new TreeModelItem(data, this);
        m_childItems.insert(position, item);
    }

    return true;
}

bool TreeModelItem::removeChildren(int position, int count)
{
    if (position < 0 || position + count > m_childItems.length())
        return false;

    for (int row = 0; row < count; ++row)
        delete m_childItems.takeAt(position);
    return true;
}

int TreeModelItem::setData(const QVariant &value, int column)
{
    if (column < m_itemData.length()) {
        m_itemData[column] = value;
        return true;
    }
    else
        return false;
}
