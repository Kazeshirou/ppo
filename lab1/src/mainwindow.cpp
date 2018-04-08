#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gpxparser.h"
#include "coder.h"
#include "commanddirector.h"

#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_routes(nullptr)
{
    ui->setupUi(this);
    GpxParser parser;
//    QList<GeoRoute> routes = parser.parse(QStringList() << "/home/ntl/Desktop/temp/ppo/lab1/route1.gpx"
//            << "/home/ntl/Desktop/temp/ppo/lab1/lissabon_vladivostok.gpx");
    QList<GeoRoute> routes = parser.parse(QStringList() <<  "C:/temp/ppo/lab1/route1.gpx"
            << "C:/temp/ppo/lab1/lissabon_vladivostok.gpx");
    m_routes = new TreeModel(routes);
    ui->routes->setModel(m_routes);
    for (int i = 0; i < m_routes->columnCount(QModelIndex()); i++)
        ui->routes->resizeColumnToContents(i);

    connect(ui->routes, SIGNAL(selectedRoute(int)), this, SLOT(routeWasSelected(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_routes;
}



void MainWindow::on_insertroute_triggered()
{
    ui->routes->insert();
}

void MainWindow::on_deleteroute_triggered()
{
    ui->routes->remove();
}

void MainWindow::routeWasSelected(int i)
{
    static int t = -1;

    if (t == i)
        return;
    t = i;
    Coder coder;
    QString polyline = coder.encode(m_routes->getData(i).path());
    ui->polyline->setText(polyline);
}

void MainWindow::on_open_triggered()
{
    GpxParser parser;
    QStringList files = QFileDialog::getOpenFileNames(this, QString("Выберите файлы"),QString(),"*.gpx");
    if (!files.length())
        return;
    QList<GeoRoute> routes = parser.parse(files);  
    new AddDataCommand(m_routes, routes);
}


void MainWindow::on_pushButton_clicked()
{
    Coder coder;
    QString polyline = ui->import_2->toPlainText();
    GeoRoute route = GeoRoute(QGeoPath(coder.decode(polyline)));
    if (!route.length()) {
        QMessageBox msg;
        msg.setWindowTitle("Некорректный полилайн");
        msg.setText("Введите корректный полилайн.");
        msg.exec();
        return;
    }
    QList<GeoRoute> routes;
    routes << route;
    new AddDataCommand(m_routes, routes);
}

void MainWindow::on_undo_triggered()
{
    CommandDirector::undo();
}

void MainWindow::on_redo_triggered()
{
    CommandDirector::redo();
}
