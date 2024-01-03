#include "next_choose.h"
#include "ui_next_choose.h"
#include "GlobalManage.h"
#include "Class_defi.h"
#include "choose_preornext.h"
next_choose::next_choose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::next_choose)
{
    ui->setupUi(this);
    ///展示所有反应器
    /// 当前新建反应器在数组末尾，不展示
    for(int i=0;i<static_cast<int>(GlobalManage::AllReactor.size())-1;i++)
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

next_choose::~next_choose()
{
    delete ui;
}

void next_choose::chooseAreactor(int i)//选择第i个反应器作为后继
{
    GlobalManage::temp_next = i;
    //写入连接的部分//
    //当前连接器位于连接器数组的末尾
    //被选择的后继反应器若有前驱连接器，则将该新反应器的接入其前驱连接器，否则为该后继反应器构建前驱连接器，并接入本反应器
    //将被选择的后继反应器的前驱连接器作为新建反应器的后继连接器
    if(GlobalManage::AllReactor[i]->cur_reactor->PreCon)//若不为空
    {
        GlobalManage::AllReactor[i]->cur_reactor->PreCon->addPre(GlobalManage::AllReactor.back()->cur_reactor);
        GlobalManage::AllReactor.back()->cur_reactor->NextCon = GlobalManage::AllReactor[i]->cur_reactor->PreCon;//将后继反应器的前驱连接器作为新建反应器的后继连接器
    }else if(!(GlobalManage::AllReactor[i]->cur_reactor->PreCon))      //前驱连接器为空
    {
        GlobalManage::AllReactor[i]->cur_reactor->PreCon = new Connector;//为后继新建前驱连接器
        GlobalManage::AllReactor[i]->cur_reactor->PreCon->addNext(GlobalManage::AllReactor[i]->cur_reactor);//将后继加入为前驱连接器的后继
        GlobalManage::AllReactor[i]->cur_reactor->PreCon->addPre(GlobalManage::AllReactor.back()->cur_reactor);//将新建反应器加入至连接器前驱
        GlobalManage::AllReactor.back()->cur_reactor->NextCon = GlobalManage::AllReactor[i]->cur_reactor->PreCon;//将后继反应器的前驱连接器作为新建反应器的后继连接器
    }
    //加入图的邻接表
    son_node* cur_node = new son_node(i);
    //将被选择的反应器加入至新建反应器的邻接链表
    GlobalManage::AllReactor.back()->next_node = cur_node;


    choose_preornext* new_page = new choose_preornext;
    new_page->show();
    this->close();
}

void next_choose::on_pushButton_clicked()
{
    choose_preornext* new_page = new choose_preornext;
    new_page->show();
    this->close();
}
