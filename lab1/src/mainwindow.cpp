#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "georoute.h"

#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{

}

void MainWindow::showRoute(const GeoRoute &route)
{
    ui->routes->insertRoute(route);
}



void MainWindow::on_insertroute_triggered()
{
    int route = ui->routes->currentRoute();
    if (ui->routes->currentIsRoute())
        ui->routes->insertRoute(GeoRoute(), route + 1);
    else
    {
        int coordinate = ui->routes->currentCoordinate();
        ui->routes->insertCoordinate(QGeoCoordinate(0, 0, _nan()), route, coordinate + 1);
    }
}

void MainWindow::on_deleteroute_triggered()
{
    int route = ui->routes->currentRoute();
    if (ui->routes->currentIsRoute())
        ui->routes->removeRoute(route);
    else
    {
        int coordinate = ui->routes->currentCoordinate();
        ui->routes->removeCoordinate(route, coordinate);
    }
}



void MainWindow::on_open_triggered()
{
   QStringList filenames = QFileDialog::getOpenFileNames(this, "Выберите файлы", QString(), "*.gpx");
   emit Open(filenames);
}


void MainWindow::on_pushButton_clicked()
{
    QString s = ui->polyline->document()->toPlainText();
    emit fromPolyline(s);
}

void MainWindow::on_undo_triggered()
{

    emit Undo();
}

void MainWindow::on_redo_triggered()
{
    emit Redo();
}
