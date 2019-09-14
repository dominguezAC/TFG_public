%==========================================================================
% TFG - Adaptative controll                                               %
% 19/08/2019                                                              %
%                                                                         %
%                        SPSA- SELF TUNING LQR                            %
%                                                                         %
% Domínguez Alegre, Carlos F.                                             %
%==========================================================================


Q = Q_long;
R = R_long;
Q_hat = Q;
R_hat = R; 

theta = [1 1 1 1];


a1 = 0.1;
a2 = 50;
alpha = 1;
c1 = 0.2;
gamma = 0.4;

Nexperiments = 10;
ng = 2;

floop = true; 

f = waitbar(l/ncases,'progress: '); % Progress bar...

for i=1:Nexperiments
    %a = a1/(i + 1 + a2)^alpha
    c = c1/(i + 1)^gamma;
    g = 0;
    for j=1:ng
        delta = Bernoulli(2);
        theta_p = theta + c*delta;
        theta_m = theta - c*delta;
       
        %Cost evaluation +
        [Q,R] = QRTheta(theta_p);
        %[K_long,S,e] = lqr(A_long,B_long,Q,R,N_long);
        [K_long,S,e] = lqr(A,B,Q,R,N_long);
        sim('model_lqr_long');
        u = u_long.Data;
        x = x_long.Data;
        J_p = J_function(x,u,Q_long,R_long);
       
        %Cost evaluation -
        [Q,R] = QRTheta(theta_m);
        %[K_long,S,e] = lqr(A_long,B_long,Q,R,N_long);
        [K_long,S,e] = lqr(A,B,Q,R,N_long);
        sim('model_lqr_long');
        u = u_long.Data;
        x = x_long.Data;
        
        J_m = J_function(x,u,Q_long,R_long);
     
        g = g + (J_p-J_m)./(2*c*delta)/ng  
       
         waitbar((i*ng + j -1)/(ng*Nexperiments),f,"Experiment: " + num2str(i) + "/" + num2str(Nexperiments) +...
             " \n iteration: " + num2str(j) + "/" + num2str(ng))
    end
    
    
    if floop
        a1 = a2*0.2/max(abs(g));
        floop = false;
    end
    a = a1/(i + 1 + a2)^alpha;
    a*g
    theta = theta - a*g
    mytheta(i,:) = theta;
    err(i) = (J_p+J_m)/2;
    
    
    
end




% FUNCTIONS
function J = J_function(Vx,Vu,Q,R)
    J = 0;
    for i=1:length(Vx)
        x = Vx(i,:)';
        u = Vu(i,:)';
        J = J+  x'*Q*x + u'*R*u;
    end
end


function B = Bernoulli(n)
%Returns an n vector with a bernoulli distribution
    for i=1:n
        B(i) =  binornd(1,0.5)*2-1; 
    end
end


function [Q,R] = QRTheta(theta)
    Q(1,1) = 10;
    Q(2,2) = 10*theta(1);
    Q(3,3) = 5;
    Q(4,4) = 5*theta(2);
    R = zeros(2);
    R(1,1) = 1000;
    R(2,2) = 100;


end


