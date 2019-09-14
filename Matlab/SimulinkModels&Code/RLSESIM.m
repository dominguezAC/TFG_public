%==========================================================================
% TFG - Adaptative controll                                               %
% 09/08/2019                                                              %
%                                                                         %
%                        RLSE-SELF-TUNING                                 %
%                                                                         %
% Domínguez Alegre, Carlos F.                                             %
%==========================================================================

A = A_long;
B = B_long;
R = 1;
P = eye(6)*100;
%P = P_long;

clear X_long U_long dx_long xu_long ref mynorm

X_long = x_long.Data-x_trim_long;
U_long = u_long.Data-u_trim_long;

dx_long = diff(X_long)/0.02;
xu_long(:,1:4) = X_long(1:end-1,:);
xu_long(:,5:6) = U_long(1:end-1,:);


for i=1:length(dx_long)
    y = dx_long(i,:);
    x = xu_long(i,:);
    err = y' - [A B]*x';
    x = xu_long(i,:);
    [A,B,P] = RLSE_klm(A,B,err',x',P,4,2,R);
    ref(i) = B(end,1);
    myvec(i) = norm(P);
end

% Plot B(4,1) over time
plot(ref)


% Calculate new gain
%[K_long,S,e] = lqr(A,B,Q_long,R_long,N_long)
