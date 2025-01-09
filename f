clc;
clear all;
close all;

f1=input("Enter pass band edge:");
f2=input("Enter stop band edge:");
fs=input("Enter sampling frequency:");

wp=2*pi*f1*1/fs;
ws=2*pi*f2*1/fs;
N=(2*pi*2)./(ws-wp);
N=ceil(N)
r=rem(N,2);
if(r==0)
    N=N+1
end
fc=wp./pi;
alpha=(N-1)/2;
n=[0:1:(N-1)];
m=n-alpha;
hd=fc*sinc(fc*m)
w=rectwin(N)'
h=hd.*w

stem(n,hd); title("Ideal impulse response");
xlabel("n"); ylabel("hd(n)");
stem(n,w); title("Window function");
xlabel("n"); ylabel("w(n)");
stem(n,h); title("Actual impulse response");
xlabel("n"); ylabel("h(n)");
freqz(h);
