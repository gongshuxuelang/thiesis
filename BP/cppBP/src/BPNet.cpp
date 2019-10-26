#include "init.h"

BPNet::BPNet()  //构造函数
{
   // BPNetInit();//初始化BP网络
   std::cout << "读文件"<<std::endl;
   BPNetReaddata();
   std::cout << "打印函数"<< std::endl;
   BPNetprint(1);
}

BPNet::~BPNet() {}//析构函数
 void  BPNet::BPNetUseBpNet()
 {

 }

void BPNet::BPNetTrainBpNet()
{

}

void BPNet::BPNetReaddata()
{
     double d = 0;      //读文件中间变量
    std::vector<std::vector<double> >xm(LENGTH,std::vector<double>(LINE));//中间变量存训练集数据
    std::vector<double> ym;                                                                                                     //中间变量存训练集数据
    std::ifstream ifstr_data("./data/Lable_guiyihua.txt",std::ios::in);                     //读文件,路径一定要是make文件的相对路径
    if(!ifstr_data)
    {
        std::cout << "打开文件失败!" << std::endl;
        exit(-1);
    }
    for(int i = 0; i < LENGTH; ++i)
    {                
        for(int j = 0; j < LINE + 1; ++j)
        {
            ifstr_data >> d;                    
            if(j == LINE)
            {
                ym.push_back(d);
                continue;
            }                       
            xm[i][j] = d;            
        }               
    }
    ifstr_data.close();
    x = xm;
    y=ym;
    std::vector<std::vector<double> >().swap(xm);//清空元素            
    std::vector<double>().swap(ym);//清空元素            
    return ;
}

void BPNet::BPNetInit()
{
    std::cout << "请输入中间层数量!" << std::endl;
    std::cin >> LayerNum;
    std::cout << "请输入中间层节点个数!" << std::endl;
    int num = 0;
    LaterNum_n.push_back(3);
    for(int i = 0; i < LayerNum; ++i)
    {
        std::cin >> num;
        LaterNum_n.push_back(num);
    }    
    LaterNum_n.push_back(1);
    std::cout << "请输入学习率!" << std::endl;
    std::cin >> StudyRate;
    std::cout << "请输入精度控制!" << std::endl;
    std::cin >> Accuracy;
    std::cout << "最大循环次数!" << std::endl;
    std::cin >> MaxLoop;

    srand(time(NULL));

    //初始化中间层矩阵
    for(int i = 0; i < LayerNum + 1; ++i)
    {
       
        for(int j  = 0; j < LaterNum_n[i] ; ++j)
        {
            std::vector<double> vm;
            for(int k = 0; k < LaterNum_n[i+ 1]; ++k)
            {
                vm.push_back( rand() / (double)(RAND_MAX));
            }
            v.push_back(vm);
            std::vector<double>().swap(vm);//清空元素            
        }
        V.push_back(v);
        std::vector<std::vector<double> >().swap(v);
    }
    return ;
}

void BPNet::BPNetprint(int n)
{
    switch (n)
    {
    case 0:
            //打印权重
        for(int i = 0; i < LayerNum + 1; ++i)
        {
        
            for(int j  = 0; j < LaterNum_n[i]; ++j)
            {            
                for(int k = 0; k < LaterNum_n[i + 1]; ++k)
                {
                    std::cout << std::setprecision(7) << V[i][j][k] << "    ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        } 
        break;
    
    case 1:
        std::cout << "x的值:" << std::endl;
        for(int i = 0; i < LENGTH; ++i)
        {
            for(int j = 0; j < LINE ; ++j)
            {
                std::cout << x[i][j] << "    ";           
            }
            std::cout << std::endl;
        }
        std::cout << "y的值:" << std::endl;
        for(int i = 0; i < LENGTH; ++i)
        {
            std::cout << y[i]<< std::endl;
        }
        break;
    } 
}