function [A,B,P] = RLSE_ff(A,B,DX_err,XU,P,Nx,Nu,alpha,R)
    % Re calculate A and B matrices from the new data point
    I = eye(Nx+Nu);
    
    AB = [A B];
    AB = AB';
    
    
    P = alpha^2*P*(I - XU*XU'*P/(R/alpha^2+XU'*P*XU));
    K = P*XU/(XU'*P*XU + R/alpha^2);
    %K = -1*[0.01 0.01 0.01 0.01 0.01 0.01];
    
    AB = AB + (K.*(DX_err))';
    
    AB = AB';
    A = AB(:,1:Nx);
    B = AB(:,Nx+1:end);
end