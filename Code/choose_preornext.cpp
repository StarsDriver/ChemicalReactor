#include "choose_preornext.h"
#include "ui_choose_preornext.h"
#include "pre_choose.h"
#include "next_choose.h"
#include "net_show.h"
#include "Class_defi.h"
#include "GlobalManage.h"
choose_preornext::choose_preornext(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::choose_preornext)
{
    ui->setupUi(this);
    //展示反应器数组末尾元素的前驱后继
    //进行连接器逻辑连接
    if(GlobalManage::temp_pre!=-1)
    {
        QLabel* label = new QLabel(ui->widget_5);
        label->setText(QString::fromStdString(GlobalManage::AllReactor[GlobalManage::temp_pre]->cur_reactor->name));
        label->resize(200,100);
        label->move(100,100);
    }
    if(GlobalManage::temp_next!=-1)
    {
        QLabel* label = new QLabel(ui->widget_6);
        label->setText(QString::fromStdString(GlobalManage::AllReactor[GlobalManage::temp_next]->cur_reactor->name));
        label->resize(200,100);
        label->move(100,100);
    }
}

choose_preornext::~choose_preornext()
{
    delete ui;
}

void choose_preornext::on_pushButton_clicked()
{
    pre_choose* new_page = new pre_choose;
    new_page->show();
    this->close();
}

void choose_preornext::on_pushButton_2_clicked()
{
    next_choose* new_page = new next_choose;
    new_page->show();
    this->close();
}

void choose_preornext::on_pushButton_3_clicked()  //完成
{
    GlobalManage::temp_pre = -1;
    GlobalManage::temp_next = -1;
    net_show* new_page = new net_show;
    new_page->show();
    this->close();
}
