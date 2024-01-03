#include "add_iport_pro.h"
#include "ui_add_iport_pro.h"
#include "GlobalManage.h"
#include "add_iport.h"
add_iport_pro::add_iport_pro(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add_iport_pro)
{
    ui->setupUi(this);
}

add_iport_pro::~add_iport_pro()
{
    delete ui;
}

void add_iport_pro::on_pushButton_clicked()
{
    GlobalManage::new_consumeProduct_name.push_back(ui->lineEdit->text().toStdString());//Qstring类对象转换为string类
    GlobalManage::new_consumeCount.push_back(ui->lineEdit_2->text().toFloat());
    add_iport* new_page = new add_iport;
    new_page->show();
    this->close();
}
