#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QTreeView>

class TreeView : public QTreeView
{
    Q_OBJECT

public:
    explicit TreeView(QWidget *parent = nullptr);
    ~TreeView() = default;

    void contextMenuEvent(QContextMenuEvent *);

public slots:
    void insert();
    void remove();
protected slots:
    void commitData(QWidget *editor);
signals:
    void selectedRoute(int i);
private slots:
    void wasSelected(const QModelIndex &index);
private:
    QMenu *createMenu();
};

#endif // TREEVIEW_H
