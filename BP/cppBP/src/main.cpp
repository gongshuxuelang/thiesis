#include "init.h"

int main()
{    
    BPNet BP;
    BP.BPNetInit();//初始化BP网络
   std::cout << "读文件"<<std::endl;
   BP.BPNetReaddata();
   std::cout << "打印函数"<< std::endl;
   BP.BPNetprint(0);
   //BP.BPNetprint(1);
   BP.BPNetTrainBpNet();
   BP.BPNetprint(0);
   BP.BPNetUseBpNet();
    return 0;
}