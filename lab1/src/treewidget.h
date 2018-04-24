#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QTreeWidget>

class GeoRoute;
class QGeoCoordinate;

class TreeWidget: public QTreeWidget
{
    Q_OBJECT

public:
    explicit TreeWidget(QWidget *parent = nullptr);
    ~TreeWidget() = default;

    void insertRoute(const GeoRoute &route, const int index = -1);
    void removeRoute(const int index = -1);

    void insertCoordinate(const QGeoCoordinate &coordinate, const int route, const int index = -1);
    void removeCoordinate(const int route, const int index = -1);

    int currentRoute();
    int currentCoordinate();
    bool currentIsRoute();

    void changeRoute(int index, QString newname);
    void changeRouteLength(int index, double newlength);
    void changeCoordinate(int route, int index, int column, double newvalue);

signals:
    void s_changeRoute(int index, QString newname);
    void s_changeCoordinate(int route, int index, int column, double newvalue);

protected:
    bool edit(const QModelIndex &index, EditTrigger trigger, QEvent *event);

protected slots:
    void commitData(QWidget *editor);

};

#endif // TREEWIDGET_H
