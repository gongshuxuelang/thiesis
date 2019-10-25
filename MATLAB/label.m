%  lable.m代码是从online_ratings.xls表格中提取数据的，主要是对2 3 4 5列代码感兴趣
%  剔除Wheel_slice（online_ratings.xls中的一列）列为零的数据。剩下的1-8置位0，9-16置位1
%  以 1 2 3列为输入，第四列为输出，训练一个网络，实现一个分类。
% 其中1 2 3列是脑电给出的标签，并没有给出情绪，online_ratings.xls这个表格给出了脑电的标签和情绪
% 的分类。训练出这个模型就可以间接的得出情绪。
% 拿到数据还需要对数据进行清洗。剔除少数不符合条件的数据。
clc;
clear all;
A=xlsread('online_ratings.xls');%%%读取表格数据
A=A(:,[2 3 4 5]);               %%提取2 3 4 5列数据
A(A(:,4) == 0,:) = [];          %% 去掉第4列为零的数据
B = A;                          %%创建B矩阵
[length,line] = size(A);        %%读取A的行数和列数

for i = 1: length               %%把第四列大于1小于8的数置位0，其他置位1  
    if(1<=A(i,4)&&A(i,4)<=8)
       B(i,4) = 0; 
    else
        B(i,4) = 1;
    end
end

fid = fopen('Lable.txt','wb');  %%创建txt文件
fprintf(fid,[repmat('%d\t', 1, size(B,2)), '\n'], B');%%保存数据
fclose(fid);                     %%关闭文件   