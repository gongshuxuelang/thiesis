#include "init.h"

BPNet::BPNet(){}  //构造函数
BPNet::~BPNet() {}//析构函数

int BPNet::yuzhi(double num)
{
    return 1 > num && num > YZ ? 1 : 0;    
}
double BPNet::fnet(double net)
{
    return 1/(1+exp(-net));
}
void  BPNet::BPNetUseBpNet()
{
    double output;
    double InNum = 0;
    double temp = 0;
    std::vector<double> Input;
    std::vector<double> yg;                    //求出中间层的值
    std::vector<double> xg;                    //求出中间层的值
    while(1)
    {
        for(int i = 0; i < N_IN; ++i)
        {
            std::cin >> InNum;
            Input.push_back(InNum);
        }
        xg = Input;
        std::vector<double>().swap(Input);
        //计算中间值
        for(int i = 0; i < LayerNum; ++i)
        {
            for(int j  = 0; j < LaterNum_n[i + 1]; ++j)
            {
                temp = 0;
                for(int k = 0; k < LaterNum_n[i]; ++k)
                {
                   temp += xg[k] * V[i][k][j];                    
                }
                std::vector<double>().swap(xg);
                yg.push_back(fnet(temp));
                xg = yg;
                std::vector<double>().swap(yg);
            }
        }
        output = 0;
        temp = 0;
        for(int i = 0;i < LaterNum_n[LayerNum]; ++i)
        {   
            temp += xg[i] * w[i];        
        }
        output = yuzhi(fnet(temp));
        std::cout << "输出值为:" << output << std::endl;
    }
    return;
}

void BPNet::BPNetTrainBpNet()
{
    double e = 0;                                           //误差  
    double wh = 0;
    double temp = 0;                                  //求和数
    std::vector<double> xg;                    //提取训练数据中间变量
    std::vector<double> yg;                    //求出中间层的值
    std::vector<double>outg;                //输出矩阵
    std::vector<std::vector<double> >yout;//中间层输出值矩阵
    std::vector<std::vector<std::vector<double> > >y3out;//中间变量输出值
    std::vector<double>vyyg;                        //中间层修改值一维
    std::vector<std::vector<double> >vyg;//中间层修改值二维
    std::vector<std::vector<std::vector<double> > >vg;//修改中间层矩阵三维总体
    std::vector<double>wg;//修改输出权重矩阵
    std::vector<double>whg;//修改输出权重矩阵
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
            for(int j = 0; j < LayerNum;++j)    //求中间层输出值
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
                xg = yg;    
                yout.push_back(yg);                                              //输出转输入
                std::vector<double>().swap(yg); // 释放中间值
            }    
            temp = 0;
            for(int j = 0; j < LaterNum_n[LayerNum];++j)//求输出值
            {
                temp += xg[j] * w[j]; 
            }
            outg.push_back(yuzhi(fnet(temp)));             //记录输出值
            std::vector<double>().swap(xg); // 释放中间值
            
            
          if(outg[i] == y[i])
          {
              continue;
          }
         //以下部分反向拟合,调整参数
        //输出层调参
            for(int j = 0; j < LaterNum_n[LayerNum]; ++j)
            {
                wg.push_back(StudyRate * (fnet(temp) -  y[i]) * fnet(temp) * (1 - fnet(temp)) * yout[yout.size() - 1][j]);
            }
            //中间层参数调整
            
            for(int j = 1; j <= LayerNum; ++j)
            {                
                for(int k = 0; k < LaterNum_n[LayerNum - j]; ++k)
                {
                    for(int m = 0; m < LaterNum_n[LayerNum -j + 1]; ++m)
                    {
                        for(int q = 0; q < LaterNum_n[LayerNum - j + 1]; ++q)
                        {
                            if(m == 0)
                            {
                                wh += (fnet(temp) -  y[i]) * fnet(temp) * (1 - fnet(temp)) * w[q];
                            }else{
                                wh += (fnet(temp) -  y[i]) * fnet(temp) * (1 - fnet(temp)) * V[LayerNum - j][k][q] ;
                            }                            
                        }
                        if(LayerNum - j - 1 >= 0)
                        {
                            vyyg.push_back(StudyRate * wh * yout[yout.size() - j][m] *(1 - yout[LayerNum - j][m]) * yout[LayerNum -  j - 1][m] );
                        }else{
                            vyyg.push_back(StudyRate * wh * yout[yout.size() - j][m] *(1 - yout[yout.size() - j][m]) * x[i][m] );
                        }     
                        wh = 0;                   
                    }
                    vyg.push_back(vyyg);
                    std::vector<double>().swap(vyyg);
                }
                vg.push_back(vyg);
                std::vector<std::vector<double> >().swap(vyg);
               
            }
            //修正输出矩阵
            for(int j = 0; j < LaterNum_n[LayerNum]; ++ j)
            {
                w[j] += wg[j];
            }
            //修正中间矩阵
            for(int j = 0; j < LayerNum; ++ j)
            {
                for(int k = 0; k < LaterNum_n[LayerNum - k - 1]; ++k)
                {
                    for(int m = 0; m < LaterNum_n[LayerNum - k]; ++m)
                    {
                        V[j][k][m] += vg[LayerNum - j - 1][k][m];
                    }
                }
            }
            std::vector<double>().swap(wg);
            std::vector<std::vector<double> >().swap(yout);
            std::vector<std::vector<std::vector<double> > >().swap(vg);
        }
        std::cout << "训练" <<  num << "次"<< std::endl;
    }
    std::cout << "BP网络训练结束" << std::endl;
}

void BPNet::BPNetReaddata()
{
     double d = 0;      //读文件中间变量
    std::vector<std::vector<double> >xm(LENGTH,std::vector<double>(LINE));//中间变量存训练集数据
    std::vector<double> ym;                                                                                                     //中间变量存训练集数据
    std::ifstream ifstr_data("./data/Lable_guiyihua.txt",std::ios::in);                     //读文件,路径一定要是make文件的相对路径
    //测试用数
    //std::ifstream ifstr_data("./data/1.txt",std::ios::in);     
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
    std::cout << "请输入阈值!" << std::endl;
    std::cin >> YZ;
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