#ifndef  __INIT_H__
#define __INIT_H__

/***全局变量********/
#define N_IN 3                         //输入层的节点个数  
#define N_OUT 1                     //输出层的节点个数

//#define N_SAMPLE 435        //样本数量
//测试使用样本
#define N_SAMPLE 4        //样本数量

#define LINE 3                             //训练集列数
//#define LENGTH 435                //训练集行数
//测试使用样本
#define LENGTH 4        //样本数量

/*****系统头文件****/
#include  <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iomanip>//cout输出控制精度
#include <fstream>  //读文件头文件
#include <string>

/*****项目头哦文件***/
#include "BPNet.h"

#endif