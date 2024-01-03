#include "pre_choose.h"
#include "ui_pre_choose.h"
#include "GlobalManage.h"
#include "Class_defi.h"
#include "choose_preornext.h"
pre_choose::pre_choose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pre_choose)
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

pre_choose::~pre_choose()
{
    delete ui;
}

void pre_choose::chooseAreactor(int i)//i表示第i选择第i个反应器，作为前驱
{
    GlobalManage::temp_pre = i;
    //写入连接的部分//
    //当前连接器位于连接器数组的末尾
    //被选择的前驱反应器若有后继连接器，则将该新反应器的接入其后继连接器，否则为该前驱反应器构建后继连接器，并接入本反应器
    //将被选择的前驱反应器的后继连接器作为新建反应器的前驱连接器
    if(GlobalManage::AllReactor[i]->cur_reactor->NextCon)//若不为空
    {
        GlobalManage::AllReactor[i]->cur_reactor->NextCon->addNext(GlobalManage::AllReactor.back()->cur_reactor);
        GlobalManage::AllReactor.back()->cur_reactor->PreCon = GlobalManage::AllReactor[i]->cur_reactor->NextCon;//将前驱反应器的后继连接器作为新建反应器的前驱连接器
    }else if(!(GlobalManage::AllReactor[i]->cur_reactor->NextCon))      //后继连接器为空
    {
        GlobalManage::AllReactor[i]->cur_reactor->NextCon = new Connector;//为前驱新建后继连接器
        GlobalManage::AllReactor[i]->cur_reactor->NextCon->addPre(GlobalManage::AllReactor[i]->cur_reactor);//将前驱加入为后继连接器的前驱
        GlobalManage::AllReactor[i]->cur_reactor->NextCon->addNext(GlobalManage::AllReactor.back()->cur_reactor);//将新建反应器加入至连接器后继
        GlobalManage::AllReactor.back()->cur_reactor->PreCon = GlobalManage::AllReactor[i]->cur_reactor->NextCon;//将前驱反应器的后继连接器作为新建反应器的前驱连接器
    }
    //加入图的邻接表
    son_node* cur_node = GlobalManage::AllReactor[i]->next_node;
    if(!cur_node)//被选择的前驱反应器还无后继
    {
        GlobalManage::AllReactor[i]->next_node =  new son_node(static_cast<int>(GlobalManage::AllReactor.size())-1);
    }else if(cur_node)
    {
        while(cur_node->next)
        {
            cur_node = cur_node->next;
        }
        cur_node->next = new son_node(static_cast<int>(GlobalManage::AllReactor.size())-1);
    }

    choose_preornext* new_page = new choose_preornext;
    new_page->show();
    this->close();
}

void pre_choose::on_pushButton_clicked()
{
    choose_preornext* new_page = new choose_preornext;
    new_page->show();
    this->close();
}
