#include <string>
#include "product_info.h"
#include "ui_product_info.h"
#include "add_reactor_page.h"
#include "GlobalManage.h"

Product_info::Product_info(QWidget *parent,int CreateOrChange) :
    QWidget(parent),
    ui(new Ui::Product_info)
{
    ui->setupUi(this);
    this->CreateOrChange = CreateOrChange;
}

Product_info::~Product_info()
{
    delete ui;
}

void Product_info::on_pushButton_clicked()
{
    if(CreateOrChange==0)
    {
        GlobalManage::new_consumeProduct_name.push_back(ui->lineEdit->text().toStdString());//Qstring类对象转换为string类
        GlobalManage::new_consumeCount.push_back(ui->lineEdit_2->text().toFloat());
        Add_Reactor_page* new_page = new Add_Reactor_page;
        new_page->show();
        this->close();
    }else if(CreateOrChange==1)
    {
        GlobalManage::new_consumeProduct_name.push_back(ui->lineEdit->text().toStdString());//Qstring类对象转换为string类
        GlobalManage::new_consumeCount.push_back(ui->lineEdit_2->text().toFloat());
        Add_Reactor_page* new_page = new Add_Reactor_page(1);
        new_page->show();
        this->close();
    }
}

void Product_info::on_pushButton_2_clicked()
{
    if(CreateOrChange==0)
    {
        GlobalManage::new_outputProduct_name.push_back(ui->lineEdit->text().toStdString());//Qstring类对象转换为string类
        GlobalManage::new_outputCount.push_back(ui->lineEdit_2->text().toFloat());
        Add_Reactor_page* new_page = new Add_Reactor_page;
        new_page->show();
        this->close();
    }else if(CreateOrChange==1)
    {
        GlobalManage::new_outputProduct_name.push_back(ui->lineEdit->text().toStdString());//Qstring类对象转换为string类
        GlobalManage::new_outputCount.push_back(ui->lineEdit_2->text().toFloat());
        Add_Reactor_page* new_page = new Add_Reactor_page(1);
        new_page->show();
        this->close();
    }
}
