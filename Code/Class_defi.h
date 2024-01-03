#ifndef CLASS_DEFI_H
#define CLASS_DEFI_H


#include<iostream>
#include<vector>
#include<string>
#include<random>
#include <cstdlib>
#include<chrono>
#include"GlobalManage.h"
/////头文件中给出类定义，别的文件才可调用
using namespace std;
//前置类声明，解决相互调用问题
class Reactor; //反应器类
class Connector; //连接器类
class Product; //产品类,表示该产品在某一阶段的总数
//产物类
class Product
{
    public:
        string name;
        float amount;
        float consume;
        Product(string name,float amount = 0,int consume =0)  // amount总量
        {
            this->name = name;
            this->amount = amount;
            this->consume = consume;//大部分情况不需要
        }
};
class ReaProduct : public Product //用于在反应器中，不止记录产物总量，
{                                  //还需记录每单位反应所产生的产物数量
    public:
        int consume = 0;
        ReaProduct(string name,int consume,float amount =0):Product(name,amount)
        {
            this->consume = consume;
        }

};
//连接器类
class Connector
{
    public:
        Connector()
        {
            this->PreRea = vector<Reactor>();
            this->NextRea = vector<Reactor>();
        }
        vector<Product> productsList; //反应器中所有暂存产物
        //virtual void GetInput() = 0; //
        //virtual void GetOutput() = 0;//
        void addPre(Reactor* input) //加入前驱反应器//不用指针会出现定义不完整报错
        {
            PreRea.push_back(*input);
        }
        void addNext(Reactor* output) //加入后继反应器
        {
            NextRea.push_back(*output);
        }
        vector<Reactor> PreRea;
        vector<Reactor> NextRea; //前驱、后继反应器列表

};
class InputPort:public Connector//输入端口
{
     public:
      //  vector<Product> productsList;//需要系数
        string name;//后继端口的名字
        vector<int> next_record;
        InputPort():Connector()
        {
            this->productsList = vector<Product>();
            this->name = "";
        }
        void update_input(float coef)//更新输入
        {
            for(int i=0;i<productsList.size();i++)
            {
                productsList[i].amount+=productsList[i].consume*coef;
            }
        }
        void add_pro(string name,float coef)//加入产品
        {
            productsList.push_back(Product(name,0,coef));
        }
        void addNext(Reactor* output,int i) //加入后继反应器,传入后继索引
        {
            this->next_record.push_back(i);
            NextRea.push_back(*output);
        }
};
class OutputPort:public Connector//输出端口
{
public:
    string name;
    OutputPort():Connector()
    {
        this->productsList = vector<Product>();
        this->name = "";
    }
};

//反应器类
class Reactor
{
    public:
        string name; //反应器名字
        vector<vector<ReaProduct>> allProducts; //记录反应器中所有产品,包含反应物数组与生成物数组
        vector<ReaProduct> Consume; //反应方程式消耗产品——方程式左侧
        vector<ReaProduct> Output;//反应方程式输出——方程式右侧
        vector<Product> OutputProducts;//用于向后继连接器输出的产物
        Connector* PreCon = NULL; //前驱连接器           目前只声明了该类，没有给出类定义，此时若不用指针类型定义会报错
        Connector* NextCon = NULL; //后继连接器
        float tempture;//记录温度
        float preesure;//记录压强
        Reactor()
        {

        }
        Reactor(string name)
        {
            this->name = name;
            allProducts.push_back(Consume);
            allProducts.push_back(Output);//这两步不能写在构造函数外

        }
        void add_consume(string name, float coef)
        {
            Consume.push_back(ReaProduct(name,coef));
        }
        void add_output(string name,float coef)
        {
            Output.push_back(ReaProduct(name,coef));
        }
        void GetInput()//.h中只能内联定义
        {

                for(int i=0;i<(this->Consume).size();i++)// 该反应需要的反应物
                {//用auto遍历无法更新值。。
                    bool IsFound = false;
                    for(int j=0;j<(this->PreCon)->productsList.size();j++)//前置连接器存在的反应物
                    {
                        if(IsFound == true)
                        {
                            break;
                        }

                        if(this->Consume[i].name == (this->PreCon)->productsList[j].name)
                        {
                           // cout<<(this->PreCon)->productsList[i].amount<<endl;
                            this->Consume[i].amount +=(this->PreCon)->productsList[j].amount;
                           // cout<<this->Consume[i].amount<<endl;
                            (this->PreCon)->productsList[j].amount = 0;
                            IsFound = true;
                        }

                    }
                 }


        }
        /////////////////////////自检方法，有没有反应物为0了
        void GoOutPut()// 将输出产物输出至后继连接器
        {
            for(int i=0;i<this->Output.size();i++)// 该反应可提供的产物！！要输出产物
            {
                bool IsFound = false;
                for(int j=0;j<(this->NextCon)->productsList.size();j++)//后继连接器存在的反应物,若有重名就补充量，若不存在则新建实例
                {
                    if(IsFound == true)
                    {
                        continue;
                    }
                    if(this->Output[i].name == this->NextCon->productsList[j].name)
                    {
                        this->NextCon->productsList[j].amount += this->Output[i].amount;
                        this->Output[i].amount = 0;
                        IsFound = true;
                    }

                }
                if(IsFound == false) //如果没找到，则在后继连接器中新建产物名
                {
                    //后继连接器不需要记录一单位方程式所消耗或生成的量，所以用普通的产物类就可以
                    Product new_product(this->Output[i].name,this->Output[i].amount);
                    this->Output[i].amount = 0;
                    (this->NextCon)->productsList.push_back(new_product);
                }
            }
        }


        void Reacting()//该反应器进行反应
        {
            //获取前驱连接器的产物
            this->GetInput();
         //   cout<<this->Consume[0].amount<<endl;
            bool ok = true;
            //消耗产物
            /////////////////////////////需要有自检,自检后可进行反应,可以设置一个反应物下限,可以设置反应速度，在反应时乘系数
            for(int i=0;i<this->Consume.size();i++)
            {
               // cout<<need.amount<<"  "<<need.consume;
                this->Consume[i].amount -= this->Consume[i].consume;
               // cout<<need.amount<<endl;
                if(this->Consume[i].amount<0)//小于0不反应
                {
                    this->Consume[i].amount = 0;
                    ok = false;
                    //warning!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                }
            }
            //此处如果warning,反应终止
            if(ok==true)
            {
                for(int i=0;i<this->Output.size();i++)
                {
                    this->Output[i].amount +=this->Output[i].consume;
                }
            }
            this->GoOutPut();//产物输出至后继连接器

            std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());
            std::uniform_real_distribution<double> dist(160.0, 240.0); // 生成0.0到1.0之间的浮点数
            double random_num = dist(rng);
            this->tempture = random_num;

            std::mt19937 rng2(std::chrono::high_resolution_clock::now().time_since_epoch().count());
            std::uniform_real_distribution<double> dist2(2.0, 6.0);
            double random_num2 = dist(rng2);


            this->preesure = random_num2;


            //实例化函数模板，调用调节方法
            adjust<float>(200,this->tempture);
            adjust<float>(4,this->preesure);
        }




};



#endif // CLASS_DEFI_H
