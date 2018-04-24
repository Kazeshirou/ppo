#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "georoute.h"

#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    currentroute(-1)
{
    ui->setupUi(this);
    setWindowTitle("Routes");
    QChart *c = new QChart();
    c->legend()->hide();
    c->createDefaultAxes();
    chart = new QChartView(c);
    chart->show();
    chart->setRenderHint(QPainter::Antialiasing);
    chart->resize(800, 600);
    connect(ui->routes, SIGNAL(itemSelectionChanged()), this, SLOT(selectionChanged()));
    connect(ui->routes, SIGNAL(s_changeCoordinate(int, int, int, double)), this, SIGNAL(s_changeCoordinate(int, int, int, double)));
    connect(ui->routes, SIGNAL(s_changeRoute(int, QString)), this, SIGNAL(s_changeRoute(int, QString)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::insertRoute(const GeoRoute &route, int index)
{
    ui->routes->insertRoute(route, index);
}

void MainWindow::insertCoordinate(const QGeoCoordinate &coordinate, int route, int index)
{
    ui->routes->insertCoordinate(coordinate, route, index);
}

void MainWindow::deleteRoute(int index)
{
    ui->routes->removeRoute(index);
}

void MainWindow::deleteCoordinate(int route, int index)
{
    ui->routes->removeCoordinate(route, index);
}

void MainWindow::changeRoute(int index, QString newname)
{
    ui->routes->changeRoute(index, newname);
}

void MainWindow::changeRouteLength(int index, double newlength)
{
    ui->routes->changeRouteLength(index, newlength);
}

void MainWindow::changeCoordinate(int route, int index, int column, double newvalue)
{
    ui->routes->changeCoordinate(route, index, column, newvalue);
}

void MainWindow::changePolyline(const QString &s)
{
    ui->polyline->setText(s);
}

void MainWindow::changeChart(QLineSeries *s)
{
    QChart *c = chart->chart();
    c->removeAllSeries();
    c->addSeries(s);
    c->createDefaultAxes();
}


void MainWindow::on_insertroute_triggered()
{
    int route = ui->routes->currentRoute();
    if (ui->routes->currentIsRoute())
        emit s_insertRoute(route + 1);
    else
    {
        int coordinate = ui->routes->currentCoordinate();
        emit s_insertCoordinate(route, coordinate);
    }
}

void MainWindow::on_deleteroute_triggered()
{
    int route = ui->routes->currentRoute();
    if (ui->routes->currentIsRoute())
        emit s_deleteRoute(route);
    else
    {
        int coordinate = ui->routes->currentCoordinate();
        emit s_deleteCoordinate(route, coordinate);
    }
}

void MainWindow::on_open_triggered()
{
   QStringList filenames = QFileDialog::getOpenFileNames(this, "Выберите файлы", QString(), "*.gpx");
   emit s_fromFile(filenames);
}


void MainWindow::on_pushButton_clicked()
{
    QString s = ui->import_2->document()->toPlainText();
    emit s_fromPolyline(s);
}

void MainWindow::on_undo_triggered()
{
    emit s_undo();
}

void MainWindow::on_redo_triggered()
{
    emit s_redo();
}

void MainWindow::selectionChanged()
{
    int r = ui->routes->currentRoute();
    if (r != currentroute)
    {
        currentroute = r;
        emit s_changeCurrentRoute(r);
    }
}
