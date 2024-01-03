#include "reactor.h"
#include "ui_reactor.h"

Reactor::Reactor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Reactor)
{
    ui->setupUi(this);
}

Reactor::~Reactor()
{
    delete ui;
}

