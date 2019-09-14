theta1 = linspace(5,20,10);
theta2 = linspace(2,10,10);

clear J


for i = 1:length(theta1)
    i
    for j=1:length(theta2)   
        j
        theta = [theta1(i) theta2(j)];
        [Q,R] = QRTheta(theta);
        [K_long,S,e] = lqr(A_long,B_long,Q,R,N_long);
        sim('model_lqr_long');
        u = u_long.Data;
        x = x_long.Data;
        J(i,j) = J_function(x,u,Q_long,R_long);   
    end
end

%Plot
surf(theta2,theta1,J)
zlabel('J')
ylabel('Q(3,3) - \theta')
xlabel('Q(4,4) - w')
title('J = J(Q(3,3)- \theta y Q(4,4) [q]),\n Q(1,1)=Q(2,2)=50')


% FUNCTIONS
function J = J_function(Vx,Vu,Q,R)
    J = 0;
    for i=1:length(Vx)
        x = Vx(i,:)';
        u = Vu(i,:)';
        J = J+  x'*Q*x + u'*R*u;
    end
end


function [Q,R] = QRTheta(theta)
    Q = diag([10 theta(1) 5 theta(2)]);
    R = zeros(2);
    R(1,1) = 1000;
    R(2,2) = 100;
end