#ifndef  __BPNET_H__
#define __BPNET_H__



class BPNet
{
    public:
        BPNet();                                                                                             //构造函数
        ~BPNet();                                                                                        //析构函数
        void BPNetReaddata();                                                               //BP网络读数据
        void BPNetInit();                                                                           //BP网络初始化函数
        void BPNetprint(int n);                                                              //BP网络打印函数 
        void BPNetTrainBpNet();                                                         //BP网络训练函数
        void  BPNetUseBpNet();                                                          //测验函数
    private:
        int LayerNum;			                                                                    //中间层数量
        std::vector<int> LaterNum_n;                                                //中间层节点个数
        std::vector<std::vector<double> > v;                                    //中间层权重矩阵
        std::vector<double> w;                                                              //输出层权重
        std::vector<std::vector<std::vector<double> > > V;        //全部的权重矩阵3维数据       
        double StudyRate;		                                                                 //学习率
        double Accuracy;		                                                                   //精度控制参数
        int MaxLoop;			                                                                       //最大循环次数
        
        std::vector<std::vector<double> >x;                                     //训练数据
        std::vector<double> y;                                                                 //结果
};

#endif