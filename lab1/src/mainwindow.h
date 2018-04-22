#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class GeoRoute;
class QGeoCoordinate;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void insertRoute(const GeoRoute &route, int index = -1);
    void insertCoordinate(const QGeoCoordinate &coordinate, int route, int index = -1);

    void deleteRoute(int index = -1);
    void deleteCoordinate(int route, int index = -1);

    void changeRoute(int index, QString newname);
    void changeCoordinate(int route, int index, int column, double newvalue);

    void changePolyline(const QString &s);

signals:
    void s_fromFile(QStringList filenames);
    void s_fromPolyline(QString s);

    void s_insertRoute(int index);
    void s_insertCoordinate(int route, int index);

    void s_deleteRoute(int index);
    void s_deleteCoordinate(int route, int index);

    void s_changeRoute(int index, QString newname);
    void s_changeCoordinate(int route, int index, int column, double newvalue);

    void s_redo();
    void s_undo();

    void s_changePolyline(int route);

private slots:
    void on_insertroute_triggered();

    void on_deleteroute_triggered();

    void on_open_triggered();

    void on_pushButton_clicked();

    void on_undo_triggered();

    void on_redo_triggered();

    void selectionChanged();

private:
    Ui::MainWindow *ui;
    int currentroute;
};

#endif // MAINWINDOW_H
