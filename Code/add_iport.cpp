#include "add_iport.h"
#include "ui_add_iport.h"
#include "GlobalManage.h"
#include "add_iport_pro.h"
#include "Class_defi.h"
#include "choose_iport_next.h"
#include<QLabel>
add_iport::add_iport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add_iport)
{
    ui->setupUi(this);
    //生成目前已添加的反应物
    int i=0;
    for(auto name:GlobalManage::new_consumeProduct_name)
    {
        //QLabel new_pro(ui->widget);
        QLabel* new_pro = new QLabel(ui->widget);
        new_pro->setText(QString::fromStdString(name));
        new_pro->resize(100,20);
        new_pro->move(100,50+50*i);
        i++;
    }
    i=0;
    for(auto coef:GlobalManage::new_consumeCount)
    {
        QLabel* new_coef = new QLabel(ui->widget);
        new_coef->setText(QString::number(coef)+"*");
        new_coef->resize(100,20);
        new_coef->move(80,50+50*i);
        i++;
    }
}

add_iport::~add_iport()
{
    delete ui;
}

void add_iport::on_pushButton_clicked()//添加反应物
{
    add_iport_pro* new_page = new add_iport_pro;
    new_page->show();
    this->close();
}

void add_iport::on_pushButton_2_clicked()//完成，下一步选择后继
{
    InputPort* new_port = new InputPort;
    for(int i=0;i<static_cast<int>(GlobalManage::new_consumeProduct_name.size());i++)
    {
        new_port->add_pro(GlobalManage::new_consumeProduct_name[i],GlobalManage::new_consumeCount[i]);
    }
    GlobalManage::all_iport.push_back(new_port);
    GlobalManage::new_consumeProduct_name.clear();
    GlobalManage::new_consumeCount.clear();

    choose_iport_next* new_page = new choose_iport_next;
    new_page->show();
    this->close();

}
