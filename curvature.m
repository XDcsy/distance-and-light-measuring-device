clc 
clear 
close all
A=xlsread('data1.xls');
B=165;
t=A(3:length(A)-B,1);
x=log10(t);
[M,N]=size(A);
KK(:,1)=x;
%%%%%%%%%%%%
for ii=2:N    
y=A(3:length(A)-B,ii);
figure()
plot(x,y)
c=16;
P=polyfit(x,y,c);
%Y=polyval(P,x);
syms x
yy=0;
for n=1:length(P)
    yy0=P(n)*x.^(length(P)-n)%log10(t)
    yy=yy+yy0
end
yy;
%t=A(3:length(A)-B,1);
x=log10(t); 
yy0=eval(yy);
dy1=diff(yy)%一阶导数
dy2=diff(yy,2)%二阶导数
dy11=eval(dy1);%一阶导数的值
dy22=eval(dy2);%二阶导数的值
% for i=1:length(t)
%     k1(i)=abs(dy22(i));
%     k2(i)=sqrt((1+dy11(i)^2)^3);
%     k(i)=k1(i)/k2(i);
% end
%  K=log(k');
%  KK(:,ii)=K;
KK(:,ii)=log(dy22);
end
xlswrite('曲率.xls',KK);
%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%




