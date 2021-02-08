%% ��ɫԤ�� 
clc 
clear 
count = xlsread('C:\Users\Lenovo\Desktop\extreme.xlsx','Sheet1','C2:C71');
%�������ű���a(��չϵ��)��b(��������) 
syms a b; 
c = [a b]'; 

%ԭʼ���� A 
A = count';    %��������
n = length(A); 

%��ԭʼ���� A ���ۼӵõ����� B 
B = cumsum(A); 
%������ B �����ھ�ֵ���� 
for i = 2:n 
C(i) = (B(i) + B(i - 1))/2; 
end 
C(1) = []; 
%�������ݾ��� 
B = [-C;ones(1,n-1)]; 
Y = A; Y(1) = []; Y = Y'; 
%ʹ����С���˷�������� a(��չϵ��)��b(��������) 
c = inv(B*B')*B*Y; 
c = c'; 
a = c(1); b = c(2); 
%Ԥ��������� 
F = []; F(1) = A(1); 
for i = 2:(n+10) 
F(i) = (A(1)-b/a)/exp(a*(i-1))+ b/a; 
end 
%������ F �ۼ���ԭ,�õ�Ԥ��������� 
G = []; G(1) = A(1); 
for i = 2:(n+10) 
G(i) = F(i) - F(i-1); %�õ�Ԥ����������� 
end 
disp('Ԥ������Ϊ��'); 
G
%% ģ�ͼ��� 
H = G(1:70); 
%����в����� 
epsilon = A - H; 
%%��һ����Բв�Q���� 
%�������������� 
delta = abs(epsilon./A); 
%����������Q 
disp('��Բв�Q���飺') 
Q = mean(delta) 
%% �����������C���� 
disp('�����C���飺') 
C = std(epsilon, 1)/std(A, 1) 
%% ������С������P���� 
S1 = std(A, 1); 
tmp = find(abs(epsilon - mean(epsilon))< 0.6745 * S1); 
disp('С������P���飺') 
P = length(tmp)/n 
%% ��������ͼ 
t1 = 1951:2020;  %ʵ�����е����������ʼ
t2 = 1951:2030;  %Ԥ������ݵ�������
plot(t1, A,'ro','LineWidth',3); hold on; 
plot(t2, G,'b-','LineWidth',2); 
set(gca,'FontSize',15); 
xlabel('Year'); ylabel('Frequency'); 
legend('Truth','Predict'); 
title('Forecast of the frequency of extreme fires in the next decade'); 
grid on