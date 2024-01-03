
#include<vector>
#include<string>
#include<iostream>
#include<string>
using namespace std;
#include "add_reactor_page.h"
#include "ui_add_reactor_page.h"
#include "net_show.h"
#include "product_info.h"
#include "Class_defi.h"  //所有类的声明
#include "GlobalManage.h"
#include "choose_preornext.h"
//静态成员初始化
//vector<Reactor_Link*> GlobalManage::AllReactor = vector<Reactor_Link*>();
//vector<string> GlobalManage::new_consumeProduct_name = vector<string>();
//vector<float> GlobalManage::new_consumeCount = vector<float>();
//vector<string> GlobalManage::new_outputProduct_name = vector<string>();
//vector<float> GlobalManage::new_outputCount = vector<float>();
Add_Reactor_page::Add_Reactor_page(int createORchange,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Add_Reactor_page)
{
    int i=0;
    this->createORchange = createORchange;
    ui->setupUi(this);
    //生成目前已添加的反应物
    for(auto name:GlobalManage::new_consumeProduct_name)
    {
        //QLabel new_pro(ui->widget);
        QLabel* new_pro = new QLabel(ui->widget_2);
        /*当你使用new来分配内存时，QLabel对象是在堆上创建的。这意味着，即使离开了当前作用域，QLabel对象仍然存在，直到你显式地删除它。

如果你直接使用QLabel label(this)来创建QLabel对象，那么这个对象是在栈上创建的。当离开当前作用域时，这个对象会被自动销毁。因此，如果你希望QLabel在页面上持续显示，那么你应该使用new来分配内存。

*/
        new_pro->setText(QString::fromStdString(name));
        new_pro->resize(100,20);
        new_pro->move(100,50+50*i);
        i++;
    }
    i=0;
    for(auto coef:GlobalManage::new_consumeCount)
    {
        QLabel* new_coef = new QLabel(ui->widget_2);
        new_coef->setText(QString::number(coef)+"*");
        new_coef->resize(100,20);
        new_coef->move(80,50+50*i);
        i++;
    }
    //生成目前已添加的生成物
    i =0;
    for(auto name:GlobalManage::new_outputProduct_name)
    {
        QLabel* new_pro = new QLabel(ui->widget);
        new_pro->setText(QString::fromStdString(name));
        new_pro->resize(100,20);
        new_pro->move(100,50+50*i);
        i++;
    }
    i=0;
    for(auto coef:GlobalManage::new_outputCount)
    {
        QLabel* new_coef = new QLabel(ui->widget);
        new_coef->setText(QString::number(coef)+"*");
        new_coef->resize(100,20);
        new_coef->move(80,50+50*i);
        i++;
    }

}

Add_Reactor_page::~Add_Reactor_page()
{
    delete ui;
}

void Add_Reactor_page::on_pushButton_3_clicked()//完成，下一步,createORchange==0,选择后继，createORchange==1,完成修改
{
    if(createORchange==0)
    {
        GlobalManage::new_reactor_name = ui->name_input->text().toStdString();//记录新名字
        ////////////////
        /// 用全局变量构建反应器类至GlobalManage
        Reactor* new_reactor = new Reactor(GlobalManage::new_reactor_name);
        GlobalManage::new_reactor_name = "";
        for(int i=0;i<static_cast<int>(GlobalManage::new_consumeProduct_name.size());i++)
        {
            new_reactor->add_consume(GlobalManage::new_consumeProduct_name[i],GlobalManage::new_consumeCount[i]);
        }
        for(int i=0;i<static_cast<int>(GlobalManage::new_outputProduct_name.size());i++)
        {
            new_reactor->add_output(GlobalManage::new_outputProduct_name[i],GlobalManage::new_outputCount[i]);
        }
        Reactor_Link* new_node = new Reactor_Link(new_reactor);
        GlobalManage::AllReactor.push_back(new_node);

        ///同时清空GlobalManage储存临时量的数组
        GlobalManage::new_consumeProduct_name.clear();
        GlobalManage::new_consumeCount.clear();
        GlobalManage::new_outputProduct_name.clear();
        GlobalManage::new_outputCount.clear();
        choose_preornext* new_page = new choose_preornext;
        new_page->show();
        this->close();
    }else if(createORchange==1)
    {
        GlobalManage::new_reactor_name = ui->name_input->text().toStdString();//记录新名字
        ////////////////
        /// 用全局变量构建反应器类至GlobalManage
        //Reactor* new_reactor = new Reactor(GlobalManage::new_reactor_name);
        Reactor* new_reactor = GlobalManage::AllReactor[GlobalManage::changeNUM]->cur_reactor;
        new_reactor->name = GlobalManage::new_reactor_name;
        new_reactor->Consume.clear();
        new_reactor->Output.clear();
        GlobalManage::new_reactor_name = "";
        for(int i=0;i<static_cast<int>(GlobalManage::new_consumeProduct_name.size());i++)
        {
            new_reactor->add_consume(GlobalManage::new_consumeProduct_name[i],GlobalManage::new_consumeCount[i]);
        }
        for(int i=0;i<static_cast<int>(GlobalManage::new_outputProduct_name.size());i++)
        {
            new_reactor->add_output(GlobalManage::new_outputProduct_name[i],GlobalManage::new_outputCount[i]);
        }
       // GlobalManage::AllReactor[GlobalManage::changeNUM]->cur_reactor = new_reactor;

        ///同时清空GlobalManage储存临时量的数组
        GlobalManage::new_consumeProduct_name.clear();
        GlobalManage::new_consumeCount.clear();
        GlobalManage::new_outputProduct_name.clear();
        GlobalManage::new_outputCount.clear();
        net_show* new_page = new net_show;
        new_page->show();
        this->close();
    }

}

void Add_Reactor_page::on_pushButton_clicked()//添加反应物
{
    if(this->createORchange==0)
    {
        Product_info* new_page = new Product_info(nullptr);
        new_page->show();
        this->close();
    }else if(this->createORchange==1)
    {
        Product_info* new_page = new Product_info(nullptr,1);
        new_page->show();
        this->close();
    }

}
