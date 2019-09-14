%==========================================================================
% TFG - Adaptative controll                                               %
% 07/08/2019                                                              %
%                                                                         %
%                           TRIM SYSTEM                                   %
%                                                                         %
% Domínguez Alegre, Carlos F.                                             %
%==========================================================================
% Find triming points on simulink model using classical controller instead
% of an optimization algorithm. This enables us to use the 6dof integrator
% from simulink with initial conditions, otherwise a model should be made
% without initial conditions and using directly a vector state x, this
% coudl be done getting rid of the 6 DOF module and minimizing the forces
% and moments. 

% this simulation also proofs the ability of the classical controler to
% return the plane to a stable state and find triming points. 

w = [1,0,-1,-2]; % vertical speeds
TAS = [8,10,12,14]; % absolute air speeds
phi = [-20,-15,-10,-5,0,5,10,15,20]; % bank angles
ncases = length(w)*length(TAS)*length(phi); % number of trim points
l = 0;

Vb_0 = [11 0.5 0.5]; %IC should be choosen wisely to avoid simulink lock out

f = waitbar(l/ncases,'progress: '); % Progress bar...

for i=1:length(w)               % Loop in vertical speeds
    for j=1:length(TAS)         % Loop in TAS
        for k=1:length(phi)     % Loop in bank angle
            
            %Find triming point around this state:  
            sim('model_trim');
            % Store input to system at the end of simulation
            u_trim(i,j,k,:) = u_out.Data(end,:);
            l = l+1;
            waitbar(l/ncases,f,"progress: "+num2str(l) + " of "+num2str(ncases))
            clear u_out x_out tout logsout
        end %phi
    end %TAS
end %w

% SAVE DATA TO WORKSPACE
save u_trim;
w_trim = w;
TRIM.TAS = TAS;
TRIM.phi = phi;

for i=1:length(w)
    for j=1:length(TAS) 
        for k=1:length(phi)
            m = length(w)+1-i;
            TRIM.u_a(i,j,k) = u_trim(m,j,k,1);
            TRIM.u_e(i,j,k) = u_trim(m,j,k,2);
            TRIM.u_r(i,j,k) = u_trim(m,j,k,3);
            TRIM.u_p(i,j,k) = u_trim(m,j,k,4);
            TRIM.w(i) = w(m);
        end
    end
end

%==========================================================================
% PLOT GRAPHS

% u_p as a function of w and TAS at 0 bank

for i=1:length(w)
    for j=1:length(TAS)
        u_p_wTAS(i,j)=u_trim(i,j,5,4);
    end
end
surf(w,TAS,u_p_wTAS)
xlabel('vertical speed (m/s)')
ylabel('TAS (m/s)')
zlabel('Throttle')
title('Throttle vs TAS and w (h=0)')

% u_p as a function of TAS and bank at w=0

for j=1:length(TAS)
    for k=1:length(phi)
        u_p_TASphi(j,k) = u_trim(2,j,k,4);
    end
end

surf(phi,TAS,u_p_TASphi)



% elevator as a function of bank at w = 0 and TAS
for j=1:length(TAS)
    for k=1:length(phi)
        u_e_TASphi(j,k) = u_trim(2,j,k,2);
    end
end
surf(phi,TAS,u_e_TASphi)
xlabel('\phi - bank angle (deg)')
ylabel('TAS (m/s)')
zlabel('u_e')
title('elevator vs TAS and \phi at w=0 (h=0)')

figure
plot(TAS,u_e_TASphi(:,1),'-x')
xlabel('TAS (m/s)')
ylabel('u_e')
title('u_e vs TAS for a level flight (w=0, h=0)')
grid on
hold on
plot(TAS,u_e_TASphi(:,2),'-x')
plot(TAS,u_e_TASphi(:,5),'-x')
legend("\phi=20", "\phi=15", "\phi=0")


% u_a vs TAS OJO! explicación posible -> cl_beta aumenta al aumentar alpha
% debido al efecto del timón de cola
% Efectivamente, es devido a que el avión realizaba un skid -> angulo de
% inclinación positivo y beta negativo a altos ángulos de ataque debido a
% la simplificación de cos(theta)?1 del controlador de viraje coordinado,
% se soluciona añadiendo el términino cos(theta) tanto a r como a q,
% posiblemente también sea necesario añadir sen(theta) en p. Ocurre
% solamente para ángulos de asiento grandes (20 grados en este caso) 


for j=1:length(TAS)
    for k=1:length(phi)
        u_a_TASphi(j,k) = u_trim(4,j,k,1);
    end
end
figure 
hold on
grid on
plot(TAS,u_a_TASphi(:,1))
plot(TAS,u_a_TASphi(:,3))
plot(TAS,u_a_TASphi(:,5))
plot(TAS,u_a_TASphi(:,7))
plot(TAS,u_a_TASphi(:,9))

xlabel('TAS (m/s)')
ylabel('u_a')
legend('\phi=-20','\phi=-10','\phi=0','\phi=10','\phi=20')

title('Ailerons vs TAS for different bank angles, (w=-2 m/s h=0)')

