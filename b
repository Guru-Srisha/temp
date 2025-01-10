% Dipole
clc;
clear all;
close all;

f = 2.45e9;
c = 3e8;
lambda = c/f;
L1 = 3*lambda/4;
dl = dipole('Length',L1,'Width',L1/100,'TiltAxis','Z')
figure,pattern(dl,f),title('3D Radiation of Dipole with L = 3\Lambda/4');
figure,patternElevation(dl,f),
figure,patternAzimuth(dl,f),





% Array
clc;
clear all;
close all;

freq = 1.8e9;
c = 3e8;
lambda = c/freq;
N = 9;
dx = 0.49*lambda;
dipole_L = lambda/2;
dipole_W = lambda/200;
mydipole = dipole;
mydipole.Length = dipole_L;
mydipole.Width = dipole_W;
mydipole.TiltAxis = "Z";
mydipole.Tilt = 90;
fmin = freq - .05*freq;
fmax = freq + .05*freq;
helement = figure;
show(mydipole)
axis tight
dipole_array = linearArray;
dipole_array.Element = mydipole;
dipole_array.NumElements = N;
dipole_array.ElementSpacing = dx;
hArray = figure;
show(dipole_array)
axis tight
pattern3Dfig = figure;
pattern(dipole_array,freq)
patternazfig1 = figure;
az_angle = 1:0.25:180;
pattern(dipole_array,freq,az_angle,0,CoordinateSystem="rectangular")
axis([0 180 -25 15])





% Helical
clc;
clear all;
close all;

r = 0.3e-3;
width = cylinder2strip(r);
feedheight = 3*r;
D = 56e-3;
radius = D/2;
turns = 17.5;
pitch = 11.2;
spacing = helixpitch2spacing(pitch,radius);
side = 600e-3;
radiusGP = side/2;
fc = 1.65e9;
relativeBW = 0.45;
BW = relativeBW*fc;
hx = helix(Radius=radius,Width=width,Turns=turns,...
    Spacing=spacing,GroundPlaneRadius=radiusGP,...
    FeedStubHeight=feedheight);
figure;
show(hx)
figure;
pattern(hx,fc);
Nf2 = 20;
fmin = 1.2e9;
fmax = 2.1e9;
fstep = 0.1e9;
fband1 = linspace(fmin,1.3e9,Nf2);
fband2 = linspace(fmin,fmax,Nf2);
freq = unique([fband1,fband2]);
Nf = length(freq);
D = nan(1,Nf);
f_eng = freq./1e9;
f_str = 'G';
fig1 = figure;
for i = 1:length(freq)
    D(i) = pattern(hx,freq(i),0,90);
    figure(fig1)
    plot(f_eng,D,'x-')
    grid on
    axis([f_eng(1) f_eng(end) 9 16 ])
    xlabel(["Frequency (" f_str "Hz)"]); ylabel("Directivity (dBi)");
    title("Peak Directivity Variation vs. Frequency");
    drawnow
end





% Horn
clc;
clear all;
close all;

FL = 0.0348;
FW = 0.035;
FH = 0.035;
L = 0.03;
W = 0.024;
H = 0.012;
FO = [0.01 0];
ant1 = horn(FlareLength=FL, FlareWidth=FW, FlareHeight=FH, Length=L,...
Width=W, Height=H, FeedOffset=FO);
show(ant1)
ant5 = cassegrain;
ant5.Exciter = ant1;
ant5.Exciter.Tilt = 270;
ant5.Exciter.TiltAxis = [0 1 0];
az = 0:2:360;
el = -90:1:90;
patOpt = PatternPlotOptions;
patOpt.MagnitudeScale = [-15 35];
pattern(ant5,10e9,az,el,PatternOptions=patOpt);





% Patch
clc;
clear all;
close all;

pcbThickness = 3.6e-3;
pcbLength = 250.4e-3;
pcbWidth = 200.6e-3;
pcbMaterial = 'FR4';
pcbEpsilonR = 4.4;
d = dielectric(pcbMaterial);
d.EpsilonR = pcbEpsilonR;
d.Thickness = pcbThickness;
GndPlane = antenna.Rectangle('Length',pcbLength,'Width',pcbWidth);
AntennaPlane=antenna.Rectangle('Length',5e-2,'Width',1e-2,'Center',[0,0]);
p = pcbStack;
p.Name = 'Strip-fed slot';
p.BoardShape = GndPlane;
p.BoardThickness = pcbThickness;
p.Layers = {AntennaPlane,d,GndPlane};
p.FeedLocations = [0,0,1,3];
p.Layers = {AntennaPlane,d,GndPlane};
figure(1);
figure(2);
pattern(p,1.82e9);
figure(3);
impedance(p,1.6e9:2e7:2.2e9);
freq = linspace(1.6e9, 2.2e9, 50);
s = sparameters(p,freq,50);
figure(4);
rfplot(s);
C = PCBConnectors.SMA_Cinch;
W = PCBServices.PCBWayWriter;
W.Filename = 'antenna_design_example';
gerberWrite(p,W,C);
