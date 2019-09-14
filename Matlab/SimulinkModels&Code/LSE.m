function [A,Bc,condition,P,B] = LSE(DX,XU,Nx,Nu)
% Takes the data to be fitted into a linear model and returns the A and Bc
% system matrices

M = XU*XU';
P = M^(-1);
B = DX*XU';

AB = B*P;

A = AB(:,1:Nx);
Bc = AB(:,Nx+1:Nu+Nx);
condition = cond(M);

end

