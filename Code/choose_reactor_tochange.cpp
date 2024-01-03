#include "choose_reactor_tochange.h"
#include "ui_choose_reactor_tochange.h"
#include "GlobalManage.h"
#include"Class_defi.h"
#include "add_reactor_page.h"
#include <QPushButton>

choose_reactor_tochange::choose_reactor_tochange(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::choose_reactor_tochange)
{
    ui->setupUi(this);
    for(int i=0;i<static_cast<int>(GlobalManage::AllReactor.size());i++)//这里可以展示全部反应器
    {
        QPushButton* new_btn = new QPushButton(ui->widget);
        new_btn->setText(QString::fromStdString(GlobalManage::AllReactor[i]->cur_reactor->name));
        connect(new_btn,&QPushButton::clicked,[this, i] {
            this->chooseAreactor(i);
        });
        new_btn->resize(200,100);
        new_btn->move(100,10+100*i);

    }
}

choose_reactor_tochange::~choose_reactor_tochange()
{
    delete ui;
}
void choose_reactor_tochange::chooseAreactor(int i)
{
    //类似于新建第i个反应器
    GlobalManage::changeNUM = i;//要改第i个
    Add_Reactor_page* new_page = new Add_Reactor_page(1);
    new_page->show();
    this->close();

}
