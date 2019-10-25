clc;
clear all;
A = importdata('Lable_qucong.txt');
AA = A(:,1:3);
xmin = min(min(AA));
xmax = max(max(AA));
[length,line] = size(AA);            
for i = 1: length
   for j = 1:line
       A(i,j) = (A(i,j)-xmin)*(1-0) / (xmax-xmin);    
   end
end
fid = fopen('Lable_guiyihua.txt','wb');  %%创建txt文件
fprintf(fid,[repmat('%f\t', 1, size(A,2)), '\n'], A');%%保存数据
fclose(fid);    