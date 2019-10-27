#include "init.h"

BPNet::BPNet()  //构造函数
{
   BPNetInit();//初始化BP网络
   std::cout << "读文件"<<std::endl;
   BPNetReaddata();
   std::cout << "打印函数"<< std::endl;
   BPNetprint(0);
   BPNetprint(1);
   BPNetTrainBpNet();
}

BPNet::~BPNet() {}//析构函数
double BPNet::fnet(double net)
{
    return 1/(1+exp(-net));
}
void  BPNet::BPNetUseBpNet()
{

}

void BPNet::BPNetTrainBpNet()
{
    double e = 0;                                           //误差
    double temp = 0;                                  //求和数
    std::vector<double> xg;                    //提取训练数据中间变量
    std::vector<double> yg;                    //求出中间层的值
    std::vector<double>outg;                //输出矩阵
    std::vector<std::vector<std::vector<double> > >vg;//修改中间层矩阵
    std::vector<double>wg;//修改输出权重矩阵
    std::vector<std::vector<double> >yout;//中间层输出值矩阵
    //训练过程
    for(int num = 0; Accuracy > e && num < MaxLoop; ++num)//拟合次数和精度控制
    {
        e = 0;
        for(int i = 0; i < N_SAMPLE; ++i)   //训练样本数量
        {
            for(int ix = 0; ix < LINE; ++ix)    //提取训练数据
            {
                xg.push_back(x[i][ix]); 
            }            
            for(int j = 0; j < LayerNum;++j)    //中间层
            {
                for(int k = 0; k < LaterNum_n[j + 1]; ++k)//中间层节点个数
                {
                    temp = 0; //求和
                    for(int m = 0; m < LaterNum_n[j]; ++m)  //计算每一层的输出值
                    {
                        temp += xg[m] * V[j][m][k];
                    }
                   yg.push_back(fnet(temp));
                }
                std::vector<double>().swap(xg); // 释放中间值
                xg = yg;                                                    //输出转输入
                std::vector<double>().swap(yg); // 释放中间值
            }
            temp = 0;
            for(int j = 0; j < LaterNum_n[LayerNum];++j)//求输出值
            {
                temp += xg[j] * w[j]; 
            }
            outg.push_back(fnet(temp));             //记录输出值
            std::vector<double>().swap(xg); // 释放中间值
            std::vector<double>().swap(yg); // 释放中间值
            //以下部分反向拟合,调整参数
        }
        //测试BP网络输出
        for(int i = 0;i < N_SAMPLE; ++ i)
        {
            std::cout << outg[i] << "  ";
        }
        std::cout << std::endl;
    }
}

void BPNet::BPNetReaddata()
{
     double d = 0;      //读文件中间变量
    std::vector<std::vector<double> >xm(LENGTH,std::vector<double>(LINE));//中间变量存训练集数据
    std::vector<double> ym;                                                                                                     //中间变量存训练集数据
    //std::ifstream ifstr_data("./data/Lable_guiyihua.txt",std::ios::in);                     //读文件,路径一定要是make文件的相对路径
    //测试用数
    std::ifstream ifstr_data("./data/1.txt",std::ios::in);     
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
    //LaterNum_n.push_back(1);    
    std::cout << "请输入学习率!" << std::endl;
    std::cin >> StudyRate;
    std::cout << "请输入精度控制!" << std::endl;
    std::cin >> Accuracy;
    std::cout << "最大循环次数!" << std::endl;
    std::cin >> MaxLoop;

    srand(time(NULL));

    //初始化中间层矩阵
    for(int i = 0; i < LayerNum; ++i)//中间层循环
    {       
        for(int j  = 0; j < LaterNum_n[i] ; ++j)//中间层节点个数循环
        {
            std::vector<double> vm;
            for(int k = 0; k < LaterNum_n[i + 1]; ++k)//初始化各个节点的权重
            {
                vm.push_back( rand() / (double)(RAND_MAX));
            }
            v.push_back(vm);
            std::vector<double>().swap(vm);//清空元素            
        }
        V.push_back(v);
        std::vector<std::vector<double> >().swap(v);
    }
    //初始化输出权重
    for(int i = 0; i < LaterNum_n[LayerNum]; ++i)
    {
        w.push_back(rand() / (double)(RAND_MAX));        
    }
    return ;
}

void BPNet::BPNetprint(int n)
{
    switch (n)
    {
    case 0:
         //打印权重
        std::cout << "中间层权重"<<std::endl;
        for(int i = 0; i < LayerNum; ++i)
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
        std::cout << "输出层权重"<<std::endl;
        for(int i = 0; i < LaterNum_n[LayerNum];++i)
        {
            std::cout << w[i] << "     ";
        }
        std::cout << std::endl;

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