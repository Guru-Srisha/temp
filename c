clc;
clear all;
close all;

f1=input("Enter passband edge:");
f2=input("Enter stopband edge:");
k1=input("Enter passband attenuation:");
k2=input("Enter stopband attenuation:");
fs=input("Enter sampling rate:");

w1=2*pi*f1*1/fs;
w2=2*pi*f2*1/fs;
o1=2*fs*tan(w1/2);
o2=2*fs*tan(w2/2);

[N,wn]=cheb1ord(o1,o2,k1,k2,'s');
[num,den]=cheby1(N,k1,wn,'s');

[numz,denz]=bilinear(num,den,fs)
w=0:pi/100:pi;
freqz(numz,denz,w);

t=0:1/fs:1;
f_sg=1000;
f_ns=3500;

signal=sin(2*pi*f_sg*t);
noise=sin(2*pi*f_ns*t);
noisy_signal=signal+noise;
filter_op=filter(numz,denz,noisy_signal);

n=2*length(signal);
signal_dft=abs(fft(signal,n));
noise_dft=abs(fft(noise,n));
noisy_signal_dft=abs(fft(noisy_signal,n));
filter_op_dft=abs(fft(filter_op,n));

w=0:pi/((n/2)-1):pi;
freq=w*fs/(2*pi);
plot(freq,signal_dft(1:n/2));
plot(freq,noise_dft(1:n/2));
plot(freq,noisy_signal_dft(1:n/2));
plot(freq,filter_op_dft(1:n/2));
