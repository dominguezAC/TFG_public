function [A,B,P] = RLSE_klm(A,B,DX_err,XU,P,Nx,Nu,R)
    % Re calculate A and B matrices from the new data point
    I = eye(Nx+Nu);
    
    AB = [A B];
    AB = AB';
   
    K = P*XU/(XU'*P*XU + R);
    P = (I-K*XU')*P;
    
    AB = AB + K*(DX_err);
    
    AB = AB';
    A = AB(:,1:Nx);
    B = AB(:,Nx+1:end);
end