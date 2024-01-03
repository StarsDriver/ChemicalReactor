#include "choose_oport_pre.h"
#include "ui_choose_oport_pre.h"
#include "GlobalManage.h"
#include "Class_defi.h"
#include "net_show.h"
#include <QPushButton>
choose_oport_pre::choose_oport_pre(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::choose_oport_pre)
{
    ui->setupUi(this);
    for(int i=0;i<static_cast<int>(GlobalManage::AllReactor.size());i++)//这里可以展示全部反应器，不像新建反应器时选择前驱后继时，不能展示自己（不能选择自己作为自己前驱后继）
    {
        QPushButton* new_btn = new QPushButton(ui->widget);
        new_btn->setText(QString::fromStdString(GlobalManage::AllReactor[i]->cur_reactor->name));
        connect(new_btn,&QPushButton::clicked,[this, i] {
            this->chooseAreactor(i);
        });
        new_btn->resize(100,50);
        new_btn->move(100,50+50*i);

    }
}

choose_oport_pre::~choose_oport_pre()
{
    delete ui;
}
void choose_oport_pre::chooseAreactor(int i)
{
    //第i个反应器加入输出端口的前驱
    GlobalManage::all_oport.back()->addPre(GlobalManage::AllReactor[i]->cur_reactor);
    GlobalManage::all_oport.back()->name = (GlobalManage::AllReactor[i]->cur_reactor->name);
    //将端口作为第i个反应器的后继连接器
    GlobalManage::AllReactor[i]->cur_reactor->NextCon = GlobalManage::all_oport.back();//子类对象赋值给父类对象——应用了多态性
    //左侧是父类Connector,右侧是子类InputPOrt
    net_show* new_page = new net_show();
    new_page->show();
    this->close();
}
