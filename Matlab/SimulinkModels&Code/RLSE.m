function [A,Bc,B,P] = RLSE(DX,XU,B,P,Nx,Nu,alpha)
    % Re calculate A and B matrices from the new data point
    I = eye(Nx+Nu);
    
    B = B + DX*XU';
    P = P*(I - XU*XU'*P/(alpha+XU'*P*XU));
    AB = B*P;
    A = AB
    A = AB(:,1:Nx);
    Bc = AB(:,Nx+1:Nu+Nx);

end
