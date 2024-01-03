#include "delete_choose.h"
#include "ui_delete_choose.h"
#include "GlobalManage.h"
#include "Class_defi.h"
#include "net_show.h"
#include <QPushButton>

delete_choose::delete_choose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::delete_choose)
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

delete_choose::~delete_choose()
{
    delete ui;
}
void delete_choose::chooseAreactor(int i)//选择第i个反应器删除
{
    GlobalManage::AllReactor.erase(GlobalManage::AllReactor.begin()+i);
    for(int j=0;j<GlobalManage::AllReactor.size();j++)
    {
        son_node* cur_node = GlobalManage::AllReactor[j]->next_node;
        son_node* pre;
        if(cur_node==NULL) continue;
        if(GlobalManage::AllReactor[j]->next_node->next==NULL)//只有一个后继
        {
            if(cur_node->val==i)
            {
                GlobalManage::AllReactor[j]->next_node=NULL;
                continue;
            }
        }
        while(cur_node)
        {
            if(cur_node->val==i)
            {
                pre->next = cur_node->next;
            }
            pre = cur_node;
            cur_node = cur_node->next;
        }

    }

    net_show* new_page = new net_show();
    new_page->show();
    this->close();
}
