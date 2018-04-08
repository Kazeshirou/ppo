#ifndef ROUTEMODEL_H
#define ROUTEMODEL_H

#include <QAbstractItemModel>
#include <QVector>
#include <QGeoRoute>

class RouteModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit RouteModel(const QList<QGeoRoute> &routes, QObject *parent = nullptr);
    ~RouteModel() = default;

    QVariant data(const QModelIndex &index, int role) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

private:
    QList<QGeoRoute> _routes;
};

#endif // ROUTEMODEL_H
