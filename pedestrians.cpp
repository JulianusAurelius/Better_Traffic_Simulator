#include "pedestrians.h"
#include "ui_pedestrians.h"

Pedestrians::Pedestrians(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Pedestrians)
{
    ui->setupUi(this);
}

Pedestrians::~Pedestrians()
{
    delete ui;
}
