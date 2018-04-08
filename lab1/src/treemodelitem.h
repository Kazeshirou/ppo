#ifndef TREEMODELITEM_H
#define TREEMODELITEM_H

#include <QList>

class TreeModelItem
{
public:
    explicit TreeModelItem(const QList<QVariant> &data, TreeModelItem *parent = nullptr);
    ~TreeModelItem();

    void appendChild(TreeModelItem *child);

    TreeModelItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    TreeModelItem *parent();
    int number() const;
    bool insertChildren(int position, int count, int columns);
    bool removeChildren(int position, int count);
    int setData(const QVariant &value, int column);

private:
    QList<TreeModelItem *> m_childItems;
    QList<QVariant> m_itemData;
    TreeModelItem *m_parent;
};

#endif // TREEMODELITEM_H
