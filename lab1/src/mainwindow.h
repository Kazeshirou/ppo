#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "treemodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:

private slots:
    void on_insertroute_triggered();

    void on_deleteroute_triggered();

    void routeWasSelected(int i);

    void on_open_triggered();

    void on_pushButton_clicked();

    void on_undo_triggered();

    void on_redo_triggered();

private:
    Ui::MainWindow *ui;
    TreeModel *m_routes;
};

#endif // MAINWINDOW_H
