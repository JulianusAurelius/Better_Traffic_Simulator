#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "qgraphicsscene.h"
#include "vehicles.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsScene scene;
    QGraphicsScene view(&scene);
    Vehicles *vehicle = new Vehicles;
    vehicle->setPos(200, 200);
    scene.addItem(vehicle);
}

MainWindow::~MainWindow()
{
    delete ui;
}

