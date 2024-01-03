#ifndef GLOBALMANAGE_H
#define GLOBALMANAGE_H

#include<vector>
#include<string>
#include<random>
#include<chrono>
using namespace std;
#include"extend.h"
class son_node;
class Reactor_Link//为图的邻接表表示准备的链表节点数据结构
{
    public:
        Reactor* cur_reactor;//该节点中的反应器
        son_node* next_node;//下一个结点

        Reactor_Link(Reactor* cur)
        {
            this->cur_reactor = cur;
            this->next_node = NULL;
        }
};
class son_node  //图的邻接表
{
    public:
        int val;//索引
        son_node* next;

        son_node(int val)
        {
            this->val = val;
            next = NULL;///注意置空
        }
};
class Pos_recoder//负责记录已展示反应器的坐标
{
    public:
        int val;//几号反应器
        int posx;//x坐标
        int posy;//y坐标
        int floor;//在展示图中的层级
        Pos_recoder(int val,int posx,int posy, int floor)
        {
            this->val = val;
            this->posx = posx;
            this->posy = posy;
            this->floor = floor;
        }
};

class GlobalManage
{
    public:
        static vector<Reactor_Link*> AllReactor; //记录当前所有的反应器,数组元素为上面的Reactor_Linke定义的节点，使用图的邻接表表示
        //AllReactor类主要是为了方便可视化
        static vector<Connector*> AllConnector; //记录所有的连接器
        static vector<string> new_consumeProduct_name;//储存新输入的名字，全局静态变量实现多页面通信
        static vector<float> new_consumeCount;//储存反应量
        static vector<string> new_outputProduct_name;//储存新输入的名字，全局静态变量实现多页面通信
        static vector<float> new_outputCount;//储存反应量
        static string new_reactor_name;
        static int temp_pre;//暂时的前驱后继反应器序号
        static int temp_next;//
        static int a;
        static vector<InputPort*> all_iport;//记录所有输入端口
        static vector<OutputPort*> all_oport;//记录所有输出端口
        static int changeNUM;//选择要改变的反应器
        static int deleteNum;//选择要删除的反应器

};
bool search(int i,vector<Pos_recoder> POS,int& cur_floor,int& pos);//寻找反应器是否已被添加,得到已找到的反应器所在层级,返回其在POS数组中的索引pos
//参数的自调节方法
//参数的自调节方法
//函数模板要在头文件中实现
template<class T>
void adjust(T std, T& needchange)//标准的，和需要调整的
{
    if(std<0) std=0;
    float power = 1;//功率
    T gap = abs(std-needchange);//跟标准值的差距
    if(gap>abs(std)*0.2)//差距大于20%
    {
        power = 1.5;//功率增大
        needchange += ((std-needchange)/abs(needchange))*power;
    }else if(gap<abs(std)*0.1)//差距小于10%
    {
        power = 0.5;//功率减小
        needchange += ((std-needchange)/abs(needchange))*power;
    }else//差距不大不小
    {
        power = 1;//功率正常
        needchange += ((std-needchange)/abs(needchange))*power;
    }
}




#endif // GLOBALMANAGE_H
