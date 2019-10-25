//BP神经网络算法,c语言版本VS2010下，无语法错误，可直接运行添加了简单注释欢迎学习交流
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#define N_Out 2     //输出向量维数
#define N_In 3		//输入向量维数
#define N_Sample 6  //样本数量
//BP人工神经网络
typedef struct
{      
	int LayerNum;			//中间层数量
	double v[N_In][50];		//中间层权矩阵i,中间层节点最大数量为50
	double w[50][N_Out];	//输出层权矩阵
	double StudyRate;		//学习率
	double Accuracy;		//精度控制参数
	int MaxLoop;			//最大循环次数
} BPNet;

//Sigmoid函数
double fnet(double net)
{ 
	return 1/(1+exp(-net));
}

//初始化
int InitBpNet(BPNet *BP);

//训练BP网络，样本为x，理想输出为y
int TrainBpNet(BPNet *BP, double x[N_Sample][N_In], int y[N_Sample][N_Out]) ;

//使用BP网络
int UseBpNet(BPNet *BP);

//主函数
int main()
{
	//训练样本
	double x[N_Sample][N_In] = {
		{0.8,0.5,0}, 
		{0.9,0.7,0.3},
		{1,0.8,0.5},
		{0,0.2,0.3},
		{0.2,0.1,1.3},
		{0.2,0.7,0.8}}; 

		//理想输出
		int y[N_Sample][N_Out] = {
			{0,1},
		{0,1},
		{0,1},
		{1,1},
		{1,0},
		{1,0}};  

		BPNet BP;
		InitBpNet(&BP);        //初始化BP网络结构
		TrainBpNet(&BP, x, y); //训练BP神经网络
		UseBpNet(&BP);         //测试BP神经网络

		return 1;
} 

//使用BP网络
int UseBpNet(BPNet *BP)
{    
	double Input[N_In];
	double Out1[50]; 
	double Out2[N_Out]; //Out1为中间层输出,Out2为输出层输出

	//持续执行，除非中断程序
	while (1) 
	{           
		printf("请输入3个数：\n");
		int i, j;
		for (i = 0; i < N_In; i++)
			scanf("%f", &Input[i]);
		double Tmp;
		for (i = 0; i < (*BP).LayerNum; i++) 
		{
			Tmp = 0;
			for (j = 0; j < N_In; j++)
				Tmp += Input[j] * (*BP).v[j][i];
			Out1[i] = fnet(Tmp);
		}
		for (i = 0; i < N_Out; i++) 
		{
			Tmp = 0;
			for (j = 0; j < (*BP).LayerNum; j++)
				Tmp += Out1[j] * (*BP).w[j][i];
			Out2[i] = fnet(Tmp);
		}
		printf("结果：   ");
		for (i = 0; i < N_Out; i++)
			printf("%.3f ", Out2[i]);
		printf("\n");
	}
	return 1;
}

//训练BP网络，样本为x，理想输出为y
int TrainBpNet(BPNet *BP, double x[N_Sample][N_In], int y[N_Sample][N_Out]) 
{

	double f = (*BP).Accuracy;          //精度控制参数
	double a = (*BP).StudyRate;          //学习率
	int LayerNum = (*BP).LayerNum; //中间层节点数
	double v[N_In][50], w[50][N_Out]; //权矩阵
	double ChgH[50], ChgO[N_Out];         //修改量矩阵
	double Out1[50], Out2[N_Out]; //中间层和输出层输出量

	int MaxLoop = (*BP).MaxLoop;           //最大循环次数
	int i, j, k, n;
	double Tmp;
	for (i = 0; i < N_In; i++)// 复制结构体中的权矩阵 
		for (j = 0; j < LayerNum; j++)
			v[i][j] = (*BP).v[i][j];

	for (i = 0; i < LayerNum; i++)
		for (j = 0; j < N_Out; j++)
			w[i][j] = (*BP).w[i][j];

	double e = f + 1;

	//对每个样本训练网络
	for (n = 0; e > f && n < MaxLoop; n++) 
	{ 
		e = 0;
		for (i= 0; i < N_Sample; i++) 
		{ 
			//计算中间层输出向量
			for (k= 0; k < LayerNum; k++)
			{          
				Tmp = 0;
				for (j = 0; j < N_In; j++)
					Tmp = Tmp + x[i][j] * v[j][k];    
				Out1[k] = fnet(Tmp);
			}
			//计算输出层输出向量
			for (k = 0; k < N_Out; k++) 
			{ 
				Tmp = 0;
				for (j = 0; j < LayerNum; j++)
					Tmp = Tmp + Out1[j] * w[j][k];
				Out2[k] = fnet(Tmp);
			}
			//计算输出层的权修改量    
			for (j = 0; j < N_Out; j++)   
				ChgO[j] = Out2[j] * (1 - Out2[j]) * (y[i][j] - Out2[j]);
			//计算输出误差
			for (j = 0; j < N_Out ; j++)   
				e = e + (y[i][j] - Out2[j]) * (y[i][j] - Out2[j]);
			//计算中间层权修改量
			for (j = 0; j < LayerNum; j++) 
			{         
				Tmp = 0;
				for (k = 0; k < N_Out; k++)
					Tmp = Tmp + w[j][k] * ChgO[k];
				ChgH[j] = Tmp * Out1[j] * (1 - Out1[j]);
			}
			//修改输出层权矩阵
			for (j = 0; j < LayerNum; j++)           
				for (k = 0; k < N_Out; k++)
					w[j][k] = w[j][k] + a * Out1[j] * ChgO[k]; 
			for (j = 0; j < N_In; j++)
				for (k = 0; k < LayerNum; k++)
					v[j][k] = v[j][k] + a * x[i][j] * ChgH[k]; 
		}
		if (n % 10 == 0)
			printf("误差 : %f\n", e);
	}
	printf("总共循环次数：%d\n", n);
	printf("调整后的中间层权矩阵：\n");
	for (i = 0; i < N_In; i++)
	{    
		for (j = 0; j < LayerNum; j++)
			printf("%f    ", v[i][j]);    
		printf("\n");
	}
	printf("调整后的输出层权矩阵：\n");
	for (i = 0; i < LayerNum; i++) {
		for (j = 0; j < N_Out; j++)
			printf("%f    ", w[i][j]);    
		printf("\n");
	}
	//把结果复制回结构体 
	for (i = 0; i < N_In; i++) 
		for (j = 0; j < LayerNum; j++)
			(*BP).v[i][j] = v[i][j];
	for (i = 0; i < LayerNum; i++)
		for (j = 0; j < N_Out; j++)
			(*BP).w[i][j] = w[i][j];
	printf("BP网络训练结束！\n");

	return 1;
}

//初始化
int InitBpNet(BPNet *BP)
{ 
	printf("请输入中间层节点数，最大数为100：\n");    
	scanf("%d", &(*BP).LayerNum);

	printf("请输入学习率：\n");
	scanf("%lf", &(*BP).StudyRate);    //(*BP).StudyRate为double型数据，所以必须是lf

	printf("请输入精度控制参数：\n");
	scanf("%lf", &(*BP).Accuracy);

	printf("请输入最大循环次数：\n");
	scanf("%d", &(*BP).MaxLoop);

	int i, j;
	srand((unsigned)time(NULL));
	for (i = 0; i < N_In; i++) 
		for (j = 0; j < (*BP).LayerNum; j++)
			(*BP).v[i][j] = rand() / (double)(RAND_MAX);    

	for (i = 0; i < (*BP).LayerNum; i++) 
		for (j = 0; j < N_Out; j++)
			(*BP).w[i][j] = rand() / (double)(RAND_MAX);    

	return 1;
}
