%==========================================================================
% TFG - Control Adaptativo                                                %
% 07/08/2019                                                              %
%                                                                         %
%                        LOAD SIM VARIABLES                               %
%                                                                         %
% Domínguez Alegre, Carlos F.                                             %
%==========================================================================
%Loads all the derivatives obtained from the datcom model to the UAV struct
%in order for the symulink model to use it. 

clear all
close all

raw = datcomimport("CFDA_UAV.out");
UAV = raw{1,1};

%cleaning data
n = UAV.nalpha;
UAV.cyb = UAV.cyb(1)*ones(1,n);
UAV.cnb = UAV.cnb(1)*ones(1,n);
UAV.clq = UAV.clq(1)*ones(1,n);
UAV.cmq = UAV.cmq(1)*ones(1,n);


%Add data from the second case (symetric deflection of flaps -> elevator)
UAV.dcl_sym = raw{1,2}.dcl_sym;
UAV.dcm_sym = raw{1,2}.dcm_sym;
UAV.dcdi_sym = raw{1,2}.dcdi_sym;
UAV.delta = raw{1,2}.delta;



% Add rudder information
UAV.srudder = 0.01;
UAV.lrudder =0.835;
UAV.hrudder =0.08;
UAV.delta_rud_max = 10; 

UAV.srudder_a = UAV.srudder/UAV.sref;
UAV.lrudder_a = UAV.lrudder/UAV.cbar;

alpha = deg2rad(UAV.alpha); 
h = UAV.hrudder;
l = UAV.lrudder; 

UAV.hrudder_a = -(h*cos(alpha)-l*sin(alpha))/UAV.blref;

clear raw
clear n

%--------------------------------------------------------------------------
% LOAD MASS PROPERTIES

UAV.Icg = load("UAV_Icg.txt");
UAV.mass = load("UAV_mass.txt");
UAV.xcg = load("UAV_Xcg.txt");


%--------------------------------------------------------------------------
% ADD ENGINE PROPERTIES

UAV.power = 150; %Nominal power 150 watts, efficiency 0,7 aprox
UAV.eng_eff = 0.7;
UAV.rpm_max = 10000;
