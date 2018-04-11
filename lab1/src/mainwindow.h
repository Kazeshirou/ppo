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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void showRoute(const GeoRoute &route);
protected:

private slots:
    void on_insertroute_triggered();

    void on_deleteroute_triggered();

    void on_open_triggered();

    void on_pushButton_clicked();

    void on_undo_triggered();

    void on_redo_triggered();

signals:
    void Open(QStringList filenames);
    void fromPolyline(QString s);
    void Redo();
    void Undo();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
