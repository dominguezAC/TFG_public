%==========================================================================
% TFG - Adaptative controll                                               %
% 10/08/2019                                                              %
%                                                                         %
%                           LINEARIZE SYSTEM                              %
%                                                                         %
% Domínguez Alegre, Carlos F.                                             %
%==========================================================================
% Obtain a linear ss system from simulation values

clear XU_long x_long u_long
clear XU_lat x_lat u_lat

% INITIAL CONDITIONS
% must be chosen out of trim condition in order to capture de dynamic of
% the system
omega_0 = [0,0,0];
euler_0 = deg2rad([5,5,0]);
Vb_0 = [13    1   -0.15];
X_0 = [0 0 -100];

% DESIRED FLIGHT CONDITION
w_cmd = 0;
TAS_cmd = 12;
phi_cmd = 0;
theta_cmd = 0;

%%
%--------------------------------------------------------------------------
% RUN THE SIMULATION
% the random perturbation on imputs must be enhabled
%sim('model_lqr_long');
sim('model_rlseLQR');


%--------------------------------------------------------------------------
% LONGITUDINAL MODEL ESTIMATION

% TRIMING POINT FOR FLIGHT CONDITION
u_trim = uAtTrim(TRIM,TAS_cmd,w_cmd,phi_cmd);
x_trim_long = [TAS_cmd w_cmd 0 0];
u_trim_long = u_trim([2 4]);

% LONGITUDINAL VECTOR STATE AND DERIVATE
X_long = x_long.Data-x_trim_long;
U_long = u_long.Data-u_trim_long;
DX_long = diff(X_long)/0.02;
XU_long(:,1:4) = X_long(1:end-1,:);
XU_long(:,5:6) = U_long(1:end-1,:);

%Longitudinal model: 
[A_long,B_long,cond,P_long,B_ls_long] = LSE(DX_long',XU_long',4,2);

%LQR lateral-directional weights and controller synthesis
Q_long = diag([10 10 5 5]);
R_long(1,1) = 1000;
R_long(2,2) = 100;
N_long = zeros(4,2);
[K_long,S,e] = lqr(A_long,B_long,Q_long,R_long,N_long)


%--------------------------------------------------------------------------
% LATERAL-DIRECTIONAL MODEL ESTIMATION

u_trim_lat = u_trim([1 3]);
x_trim_lat = [phi_cmd,0,0,0];

%LATERAL VECTOR STATE AND DERIVATE
X_lat = x_lat.Data - x_trim_lat;
X_lat = X_lat(:,[1 3 4]);
U_lat = u_lat.Data - u_trim_lat;
DX_lat = diff(X_lat)/0.02;
XU_lat(:,1:3)=X_lat(1:end-1,:);
XU_lat(:,4:5)=U_lat(1:end-1,:);

%Lateral-directional model
[A_lat,B_lat,cond] = LSE(DX_lat',XU_lat',3,2)

%LQR lateral-directional weights and controller synthesis
Q_lat = eye(3); 
Q_lat(1,1)=1000; 
Q_lat(2,2)=10;
Q_lat(3,3)=10;
R_lat = eye(2); R_lat = R_lat*10; 
N_lat = zeros(3,2);
[K_lat,S,e] = lqr(A_lat,B_lat,Q_lat,R_lat,N_lat)

