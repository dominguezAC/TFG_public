%==========================================================================
% TFG - Adaptative control for UAVs                                       %
% 10/08/2019                                                              %
%                                                                         %
%                CG, INERTIAS AND WEIGHTS ESTIMATIONS                     %
%                                                                         %
% Domínguez Alegre, Carlos F.                                            %
%==========================================================================
% SI units
% Domínguez Alegre, Carlos F.
% 2019

Wwing = 0.47;       % wing mass
Wfus = 0.650;       % fuselage and tail mass 
Wtail = Wfus*0.20;  % tail mass (from tail mass fraction)
Wbat = 0.18;        % batery mass
Wplane = Wbat+Wfus+Wwing;

lt = 0.70;          % tail-cg_fuselage length
B = 2;              % wingspan
c = 0.23;           % MAC
e = 0.02;           % profile thickness


% Lengths referenced to a body axis attached to the nose of the plane, x
% positive forward, z positive down

xcgBat = [-0.17,0,0];   
xcgWing= [-0.31,0,-0.05];
xcgFus = [-0.34,0,0];

l1Bat = 0.1;        % batery length
l2Bat = 0.035;      % batery height
l3Bat = 0.025;      % batery width


Bfus = 0.06;        % characteristic fuselage width
Lfus = 1.1;         % characteristic fuselage length


% WING MOMENT OF INERTIA ESTIMATION
% Approximated by a prism of the same thickness and length. The width will
% be taken as 50% of the chord. The CDG of the wing is located at 1/3 of 
% the chord.
Iw = zeros(3,3);
Iw(1,1) = (1/12)*Wwing*(e^2+B^2);
Iw(2,2) = (1/12)*Wwing*(e^2+(0.5*c)^2);
Iw(3,3) = (1/12)*Wwing*(B^2+(0.5*c)^2);



% BATERY MOMENT OF INERTIA ESTIMATION
Ib = zeros(3,3);
Ib(1,1) = (1/12)*Wbat*(l2Bat^2+l3Bat^2);
Ib(2,2) = (1/12)*Wbat*(l1Bat^2+l2Bat^2);
Ib(3,3) = (1/12)*Wbat*(l1Bat^2+l3Bat^2);



% FUSELAGE MOMENT OF INERTIA ESTIMATION
% For the Iyy and Izz moments of inertia the fuselage is considered as two
% different solids, first a stretch of fuselage of length xcgFus(1) and
% another representing the tail. The moment of inertia of the tail section
% within the body axis of the tail will be dispise. Ixx moment of inertia
% wil be estimated as a homogeneous prism.

If = zeros(3,3);
If(1,1) = (1/6)*Wfus*Bfus^2;


It = zeros(3,3);
It(2,2) = Wtail*lt^2;
It(3,3) = Wtail*lt^2;


Wff = Wfus-Wtail; 
Iff_cg = zeros(3,3);
Iff_cg(2,2) = (1/12)*Wff*(Bfus^2+xcgFus(1)^2);
Iff_cg(3,3) = Iff_cg(2,2);

lff = lt*Wtail/Wff;

Iff = zeros(3,3);
Iff(2,2) = Iff_cg(2,2) + Wff*lff^2; %steiner
Iff(3,3) = Iff_cg(3,3) + Wff*lff^2;

If = Iff + It +If;



% COG AND MOMENTS OF INERTIA ESTIMATION OF THE FUSELAGE

XCG = (xcgBat*Wbat + xcgFus*Wfus + xcgWing*Wwing)/Wplane;

%Fuselage
OG = xcgFus-XCG;
If_cg = If + Wfus*(norm(OG)^2*eye(3,3) - kron(OG,OG'))

%Batery
OG = xcgBat-XCG;
Ib_cg = Ib + Wbat*(norm(OG)^2*eye(3,3) - kron(OG,OG'))

%Wing
OG = xcgWing-XCG;
Iw_cg = Iw + Wwing*(norm(OG)^2*eye(3,3) - kron(OG,OG'))


% TOTAL
Icg = zeros(3,3);
Icg = If_cg + Ib_cg + Iw_cg;


%--------------------------------------------------------------------------
% Data out
display("Cálculo de pesos y tensor de inercia del UAV")
display(Icg);
display(Wplane);
display(XCG);


myfile = fopen("UAV_Icg.txt",'w')
fmt = '%1.4f %1.4f %1.4f\n'; fprintf(myfile,fmt,Icg); fclose(myfile);

myfile = fopen("UAV_mass.txt",'w'); 
fmt = '%1.4f\n'; fprintf(myfile,fmt,Wplane);fclose(myfile);


myfile = fopen("UAV_Xcg.txt",'w'); 
fmt = '%1.4f\n'; fprintf(myfile,fmt,XCG);fclose(myfile);

