#include<random>
#include<vector>
using namespace std;
#include "GlobalManage.h"
////在这里初始化所有的静态成员
vector<Reactor_Link*> GlobalManage::AllReactor = vector<Reactor_Link*>();
vector<string> GlobalManage::new_consumeProduct_name = vector<string>();
vector<float> GlobalManage::new_consumeCount = vector<float>();
vector<string> GlobalManage::new_outputProduct_name = vector<string>();
vector<float> GlobalManage::new_outputCount = vector<float>();
string GlobalManage::new_reactor_name = string();
int GlobalManage::temp_pre = int(-1);
int GlobalManage::temp_next = int(-1);
vector<InputPort*> GlobalManage::all_iport = vector<InputPort*>();//记录所有输入端口
vector<OutputPort*> GlobalManage::all_oport = vector<OutputPort*>();//记录所有输出端口
int GlobalManage::changeNUM;//选择要改变的反应器
int GlobalManage::deleteNum;
