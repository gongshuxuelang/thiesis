#ifndef  __BPNET_H__
#define __BPNET_H__

class BPNet
{
    public:
        BPNet();
        ~BPNet();
        void BPNetInit();
    private:
        int LayerNum;			                                       //中间层数量
        int LaterNum_n;                                             //中间层节点个数
        std::vector<std::vector<double> > v;     //中间层权矩阵i,中间层节点最大数量为50
        std::vector<std::vector<double> > w;    //输出层权矩阵
        double StudyRate;		                                 //学习率
        double Accuracy;		                                  //精度控制参数
        int MaxLoop;			                                      //最大循环次数
};

#endif