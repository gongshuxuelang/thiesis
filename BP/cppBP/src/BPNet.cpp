#include "init.h"
/*
        int LayerNum;			                                       //中间层数量
        int LaterNum_n;                                             //中间层节点个数
        std::vector<std::vector<double> > v;     //中间层权矩阵i,中间层节点最大数量为50
        std::vector<std::vector<double> > w;    //输出层权矩阵
        double StudyRate;		                                 //学习率
        double Accuracy;		                                  //精度控制参数
        int MaxLoop;			                                      //最大循环次数
*/
BPNet::BPNet()  //构造函数
{
    BPNetInit();
}


BPNet::~BPNet() {}//析构函数

void BPNet::BPNetInit()
{
    std::cout << "请输入中间层数量!" << std::endl;
    std::cin >> LayerNum;
    std::cout << "请输入中间层节点个数!" << std::endl;
    std::cin >> LaterNum_n;
    std::cout << "请输入学习率!" << std::endl;
    std::cin >> StudyRate;
    std::cout << "请输入精度控制!" << std::endl;
    std::cin >> Accuracy;
    std::cout << "最大循环次数!" << std::endl;
    std::cin >> MaxLoop;

    
}