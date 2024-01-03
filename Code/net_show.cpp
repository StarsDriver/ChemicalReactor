#include <vector>
using namespace std;
#include "net_show.h"
#include "ui_net_show.h"
#include "add_reactor_page.h"
#include "GlobalManage.h"
#include "Class_defi.h"
#include "Painter.h"
#include "add_iport.h"
#include "choose_oport_pre.h"
#include "choose_reactor_tochange.h"
#include "delete_choose.h"
#include<QLabel>
#include<chrono>
#include<thread>
template<class T>
void adjust(T std, T& needchange);
net_show::net_show(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::net_show)
{
    ui->setupUi(this);

    this->all_oports_labs = vector<QLabel*>();
    this->is_pause = false;
    this->all_labs = vector<QLabel*>();
    this->POS = vector<Pos_recoder>();
    this->all_iports_labs = vector<QLabel*>();
    int weight=150;//按钮宽度
    int height=150;//高度
    //展示输入端口

    for(int i=0;i<GlobalManage::all_iport.size();i++)
    {
        QLabel* new_lab = new QLabel(ui->widget_3);
        all_iports_labs.push_back(new_lab);
        string text = "输入端口"+to_string(i)+"\n输入至反应器 :"+GlobalManage::all_iport[i]->name;
        text+="\n";
        for(int j=0;j<GlobalManage::all_iport[i]->productsList.size();j++)
        {
            text+=to_string(GlobalManage::all_iport[i]->productsList[j].consume)+"   "+GlobalManage::all_iport[i]->productsList[j].name;
            text+="\n";
        }
        new_lab->setText(QString::fromStdString(text));
        new_lab->resize(300,100);
        new_lab->move(20,10+100*i);
    }
    //展示输出端口
    for(int i=0;i<GlobalManage::all_oport.size();i++)
    {
        QLabel* new_lab = new QLabel(ui->widget_2);
        this->all_oports_labs.push_back(new_lab);
        string text = "输出端口"+to_string(i)+" 来自反应器"+" "+GlobalManage::all_oport[i]->name+"  输出产物:";
        text+="\n";
        for(int j=0;j<GlobalManage::all_oport[i]->productsList.size();j++)
        {
            text+=GlobalManage::all_oport[i]->productsList[j].name+"   "+to_string(GlobalManage::all_iport[i]->productsList[j].amount);
            text+="\n";
        }


        new_lab->setText(QString::fromStdString(text));
        new_lab->resize(300,100);
        new_lab->move(20,10+100*i);
    }

    //展示反应器

    /////////////////////////////
    ///在这里使用GlobalManage中的静态变量展示反应器网络
    /// 加一些额外信息的展示/////////////////////////////////////////////////////
    //展示反应器网络
    int pos;//POS数组中找到的索引
    int cur_pos;//当前节点在POS数组中的索引

    vector<int> vertical(static_cast<int>(GlobalManage::AllReactor.size()),0);//记录不同层级的y坐标
    for(int i=0;i<static_cast<int>(GlobalManage::AllReactor.size());i++)
    {
        int cur_floor=0;
        //在POS数组中查找，看是否有第i个反应器
        bool Ifsearch = search(i,POS,cur_floor,pos);
        if(Ifsearch == false)//如果没找到，新建按钮，层级为0。添加后继，但是后继有可能在，还需要找
        {
            int new_posx = (cur_floor)*200+10;
            int new_posy = vertical[cur_floor]+10;
            POS.push_back(Pos_recoder(i,new_posx,new_posy,0));
            cur_pos = POS.size()-1; //////////////////cur_pos赋值
            //绘制反应器///////////////////
            QLabel* n_rea = new QLabel(ui->widget);
            this->all_labs.push_back(n_rea);
            n_rea->setStyleSheet("border: 2px solid black");
            ////////////////////////设置显示内容
            Reactor* cur_reactor = GlobalManage::AllReactor[i]->cur_reactor;
            string text = cur_reactor->name+"\n";
            int j=0;
            if(cur_reactor->Consume.size()>0)
            {
                for(j=0;j<cur_reactor->Consume.size()-1;j++)
                {
                    text += to_string(cur_reactor->Consume[j].consume)+cur_reactor->Consume[j].name + "+";
                }
                text +=  to_string(cur_reactor->Consume[j].consume)+cur_reactor->Consume[j].name+"=";
            }
            if(cur_reactor->Output.size()>0)
            {
                for(j=0;j<cur_reactor->Output.size()-1;j++)
                {
                    text +=  to_string(cur_reactor->Output[j].consume)+cur_reactor->Output[j].name+"+";
                }
                text += to_string(cur_reactor->Output[j].consume)+cur_reactor->Output[j].name+"\n";
            }
            n_rea->setText(QString::fromStdString(text));
            ///////////////////////////////////////////////////////
       //     cout<<GlobalManage::AllReactor[i]->cur_reactor->name;
            n_rea->resize(weight,height);
            n_rea->move(new_posx,new_posy);
            vertical[cur_floor]+=200;
            son_node* cur_node = GlobalManage::AllReactor[i]->next_node;
            while(cur_node)//遍历邻接节点，添加至展示图
            {
                bool Ifsearch = search(cur_node->val,POS,cur_floor,pos);

                if(Ifsearch == false)//没找到
                {
                    int new_posx = (cur_floor+1)*200+10;
                    int new_posy = vertical[cur_floor+1]+10;
                    POS.push_back(Pos_recoder(cur_node->val,new_posx,new_posy,cur_floor+1));//注意层数要+1
                    pos = POS.size()-1;
                    QLabel* n_rea = new QLabel(ui->widget);
                    this->all_labs.push_back(n_rea);
                    n_rea->setStyleSheet("border: 2px solid black");

                    cur_reactor = GlobalManage::AllReactor[cur_node->val]->cur_reactor;
                    string text = cur_reactor->name+"\n";
                    int j=0;
                    if(cur_reactor->Consume.size()>0)
                    {
                        for(j=0;j<cur_reactor->Consume.size()-1;j++)
                        {
                            text += to_string(cur_reactor->Consume[j].consume)+cur_reactor->Consume[j].name + "+";
                        }
                        text +=  to_string(cur_reactor->Consume[j].consume)+cur_reactor->Consume[j].name+"=";
                    }
                    if(cur_reactor->Output.size()>0)
                    {
                        for(j=0;j<cur_reactor->Output.size()-1;j++)
                        {
                            text +=  to_string(cur_reactor->Output[j].consume)+cur_reactor->Output[j].name+"+";
                        }
                        text += to_string(cur_reactor->Output[j].consume)+cur_reactor->Output[j].name+"\n";
                    }
                    n_rea->setText(QString::fromStdString(text));
                    n_rea->resize(weight,height);
                    n_rea->move(new_posx,new_posy);
                    ArrowWidget *arrow = new ArrowWidget(ui->widget);
                    QPoint Start(POS[cur_pos].posx+weight,POS[cur_pos].posy+height/2);
                    QPoint End(POS[pos].posx,POS[pos].posy+height/2);
                    arrow->setStartPoint(Start);

                    arrow->setEndPoint(End);
                    arrow->show();
                    vertical[cur_floor+1]+=200;
                }else if(Ifsearch==true)//找到
                {
                    ArrowWidget *arrow = new ArrowWidget(ui->widget);
                    QPoint Start(POS[cur_pos].posx+weight,POS[cur_pos].posy+height/2);
                    QPoint End(POS[pos].posx,POS[pos].posy+height/2);
                    arrow->setStartPoint(Start);

                    arrow->setEndPoint(End);
                    arrow->show();
                   // update();
                }
                cur_node = cur_node->next;
            }
        }else if(Ifsearch==true)//已存在,但其子可能在，还需要找!!!直接用父亲的cur_floor,不要重新找
        {
            //int son_curfloor;!!错误
            int temp;//无用量
            son_node* cur_node = GlobalManage::AllReactor[i]->next_node;
            cur_pos = pos;//已存在的父节点的索引
            while(cur_node)//遍历邻接节点，添加至展示图
            {
                bool Ifsearch = search(cur_node->val,POS,temp,pos);
                if(Ifsearch == false)//没找到
                {
                    int new_posx = (cur_floor+1)*200+10;
                    int new_posy = vertical[cur_floor+1]+10;
                    POS.push_back(Pos_recoder(cur_node->val,new_posx,new_posy,cur_floor+1));
                    pos = POS.size()-1;//////////////pos赋值
                    QLabel* n_rea = new QLabel(ui->widget);
                    this->all_labs.push_back(n_rea);
                    n_rea->setStyleSheet("border: 2px solid black");

                    Reactor* cur_reactor = GlobalManage::AllReactor[cur_node->val]->cur_reactor;
                    string text = cur_reactor->name+"\n";
                    int j=0;
                    if(cur_reactor->Consume.size()>0)
                    {
                        for(j=0;j<cur_reactor->Consume.size()-1;j++)
                        {
                            text += to_string(cur_reactor->Consume[j].consume)+cur_reactor->Consume[j].name + "+";
                        }
                        text +=  to_string(cur_reactor->Consume[j].consume)+cur_reactor->Consume[j].name+"=";
                    }
                    if(cur_reactor->Output.size()>0)
                    {
                        for(j=0;j<cur_reactor->Output.size()-1;j++)
                        {
                            text +=  to_string(cur_reactor->Output[j].consume)+cur_reactor->Output[j].name+"+";
                        }
                        text += to_string(cur_reactor->Output[j].consume)+cur_reactor->Output[j].name+"\n";
                    }
                    n_rea->setText(QString::fromStdString(text));
                    n_rea->resize(weight,height);
                    n_rea->move(new_posx,new_posy);
                    ArrowWidget *arrow = new ArrowWidget(ui->widget);
                    QPoint Start(POS[cur_pos].posx+weight,POS[cur_pos].posy+height/2);
                    QPoint End(POS[pos].posx,POS[pos].posy+height/2);
                    arrow->setStartPoint(Start);

                    arrow->setEndPoint(End);
                    arrow->show();
                    vertical[cur_floor+1]+=200;
                }else if(Ifsearch==true)//找到
                {
                    ArrowWidget *arrow = new ArrowWidget(ui->widget);
                    QPoint Start(POS[cur_pos].posx+weight,POS[cur_pos].posy+height/2);
                    QPoint End(POS[pos].posx,POS[pos].posy+height/2);
                    arrow->setStartPoint(Start);
                    arrow->setEndPoint(End);
                    arrow->show();
                   // update();
                }
                cur_node = cur_node->next;
            }
        }
    }
}

net_show::~net_show()///////////////之前把代码写在析构函数里了！！！啥也没有
{
    delete ui;

}

void net_show::on_Add_clicked()
{
    Add_Reactor_page* new_page = new Add_Reactor_page;//要用new分配堆空间
    new_page->show();
    this->close();
}

void net_show::on_pushButton_2_clicked()//加输入端口
{
    add_iport* new_page = new add_iport;
    new_page->show();
    this->close();
}

void net_show::on_pushButton_clicked()//加输出端口,直接新建输出端口并，选输出端口前驱
{
    OutputPort* new_port = new OutputPort;
    GlobalManage::all_oport.push_back(new_port);
    choose_oport_pre* new_page = new choose_oport_pre;
    new_page->show();
    this->close();
}

void net_show::on_Go_clicked()///进行反应,使用GLOBALMANAGE中的变量运算
{
    //反应器中只展示反应物的余量
    //展示输入端口的物料和输出端口的物料
    //每1s反应一次
    //调用输入端口，自调节输入
        is_pause =false;
           //if(this->is_pause==true) break;
            for(int i=0;i<GlobalManage::all_iport.size();i++)//调用所有输入端口，获取输入，并进行自调节
            {
                GlobalManage::all_iport[i]->update_input(1);
                for(int j=0;j<GlobalManage::AllReactor[GlobalManage::all_iport[i]->next_record[i]]->cur_reactor->Consume.size();j++)//比较所有产物，调整输入
                {
                    for(int k=0;k<GlobalManage::all_iport[i]->productsList.size();k++)
                    {
                        if(GlobalManage::AllReactor[GlobalManage::all_iport[i]->next_record[i]]->cur_reactor->Consume[j].name==GlobalManage::all_iport[i]->productsList[k].name)
                        {
                            //自调节，使能稳定到10
                            adjust<float>(10-GlobalManage::AllReactor[GlobalManage::all_iport[i]->next_record[i]]->cur_reactor->Consume[j].amount,GlobalManage::all_iport[i]->productsList[k].consume);
                        }
                    }
                }
            }
            for(auto x:POS)//调用所有反应器进行反应
            {
                //更新反应器内容展示
                GlobalManage::AllReactor[x.val]->cur_reactor->Reacting();

                Reactor* cur_reactor = GlobalManage::AllReactor[x.val]->cur_reactor;
                string text = cur_reactor->name+"\n";
                text+="温度:"+to_string(cur_reactor->tempture)+"℃\n";
                text+="压力:"+to_string(cur_reactor->preesure)+"kPa\n";
                int j=0;
                if(cur_reactor->Consume.size()>0)
                {
                    for(j=0;j<cur_reactor->Consume.size()-1;j++)
                    {
                        text += to_string(cur_reactor->Consume[j].consume)+cur_reactor->Consume[j].name + "+";
                    }
                    text +=  to_string(cur_reactor->Consume[j].consume)+cur_reactor->Consume[j].name+"=";
                }
                if(cur_reactor->Output.size()>0)
                {
                    for(j=0;j<cur_reactor->Output.size()-1;j++)
                    {
                        text +=  to_string(cur_reactor->Output[j].consume)+cur_reactor->Output[j].name+"+";
                    }
                    text += to_string(cur_reactor->Output[j].consume)+cur_reactor->Output[j].name+"\n";
                }
                text+="\n";
                for(auto pro:cur_reactor->Consume)
                {
                    text+=pro.name+"  "+to_string(pro.amount)+"\n";
                }
                all_labs[x.val]->setText(QString::fromStdString(text));
            }
            //更新画面展示
            //更新输入端口展示
            for(int i=0;i<GlobalManage::all_iport.size();i++)
            {

                string text = "输入端口"+to_string(i)+"\n输入至反应器 :"+GlobalManage::all_iport[i]->name;
                text+="\n";
                for(int j=0;j<GlobalManage::all_iport[i]->productsList.size();j++)
                {
                    text+=to_string(GlobalManage::all_iport[i]->productsList[j].consume)+"   "+GlobalManage::all_iport[i]->productsList[j].name;
                    text+="\n";
                }
                all_iports_labs[i]->setText(QString::fromStdString(text));
                all_iports_labs[i]->resize(300,100);
                all_iports_labs[i]->move(20,10+100*i);
            }
            //更新输出端口展示

            //展示输出端口
            for(int i=0;i<this->all_oports_labs.size();i++)
            {
                 string text = "输出端口"+to_string(i)+" 来自反应器"+" "+GlobalManage::all_oport[i]->name+"  输出产物:";
                text+="\n";
                for(int j=0;j<GlobalManage::all_oport[i]->productsList.size();j++)
                {
                    text+=GlobalManage::all_oport[i]->productsList[j].name+"   "+to_string(GlobalManage::all_oport[i]->productsList[j].amount);
                    text+="\n";
                }
                all_oports_labs[i]->setText(QString::fromStdString(text));
                all_oports_labs[i]->resize(300,100);
                all_oports_labs[i]->move(20,10+100*i);
            }
          //  std::this_thread::sleep_for(std::chrono::seconds(1));



}

void net_show::on_Pause_clicked()
{
    this->is_pause = true;
}

void net_show::on_pushButton_3_clicked()//修改反应器
{
    choose_reactor_tochange* new_page = new choose_reactor_tochange;
    new_page->show();
    this->close();
}

void net_show::on_pushButton_4_clicked()//删除反应器
{
    delete_choose* new_page = new delete_choose;
    new_page->show();
    this->close();
}
