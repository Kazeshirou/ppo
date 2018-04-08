#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>

class GeoRoute;
class TreeModelItem;

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit TreeModel(const QList<GeoRoute> &data, QObject *parent = nullptr);
    ~TreeModel();

    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    bool insertRows(int position, int count, const QModelIndex &parent) override;
    bool removeRows(int position, int count, const QModelIndex &parent) override;

    GeoRoute getData(int i);
    void setData(const QList<GeoRoute> &routes);
    QList<GeoRoute> getData();
    bool addData(const QList<GeoRoute> &data);
    int routeNumber(const QModelIndex &index);


private:
    void setupModelData();
    TreeModelItem *getItem(const QModelIndex &index) const;

    TreeModelItem *m_root;
    QList<GeoRoute> m_data;
};

#endif // TREEMODEL_H
