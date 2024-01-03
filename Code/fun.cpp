#include<vector>
using namespace std;
#include "GlobalManage.h"
#include"extend.h"
bool search(int i,vector<Pos_recoder> POS,int& cur_floor,int& pos)//寻找反应器是否已被添加,得到已找到的反应器所在层级
{

   //在POS数组中查找，看是否有第i个反应器
   cur_floor = 0;
   bool Ifsearch = false;
   int j=0;
   for(auto x:POS)
   {
        if(x.val==i)
        {
            Ifsearch = true;//找到
            cur_floor = x.floor;
            pos =j;
            break;
        }
        j++;
   }
   return Ifsearch;

}
