#include "add_iportoroport.h"
#include "ui_add_iportoroport.h"

add_iportoroport::add_iportoroport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add_iportoroport)
{
    ui->setupUi(this);
}

add_iportoroport::~add_iportoroport()
{
    delete ui;
}
