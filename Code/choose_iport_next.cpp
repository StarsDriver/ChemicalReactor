#include "choose_iport_next.h"
#include "ui_choose_iport_next.h"
#include "GlobalManage.h"
#include "Class_defi.h"
#include "net_show.h"
#include<QPushButton>
choose_iport_next::choose_iport_next(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::choose_iport_next)
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

choose_iport_next::~choose_iport_next()
{
    delete ui;
}
void choose_iport_next::chooseAreactor(int i)//选择第i个反应器作为后继
{
    //第i个反应器加入输入端口的后继
    GlobalManage::all_iport.back()->addNext(GlobalManage::AllReactor[i]->cur_reactor,i);
    GlobalManage::all_iport.back()->name = GlobalManage::AllReactor[i]->cur_reactor->name;
    //将端口作为第i个反应器的前驱连接器
    GlobalManage::AllReactor[i]->cur_reactor->PreCon = GlobalManage::all_iport.back();//子类对象赋值给父类对象——应用了多态性
    net_show* new_page = new net_show();
    new_page->show();
    this->close();
}
