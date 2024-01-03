#ifndef EXTREND_H
#define EXTREND_H

#endif // EXTREND_H
#include<iostream>
#include<vector>
#include<string>
/////头文件中给出类定义，别的文件才可调用
using namespace std;
//前置类声明，解决相互调用问题
class Reactor; //反应器类
class Connector; //连接器类
class Product; //产品类,表示该产品在某一阶段的总数
class ReaProduct;
class GlobalManage;
class InputPort;
class OutputPort;

