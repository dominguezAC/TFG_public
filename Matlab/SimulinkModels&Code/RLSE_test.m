% RLSE

A = A_long;
B = B_long;
alpha = 1;
R =50;
P = rand(6);

clear X_long U_long dx_long xu_long

X_long = x_long.Data-x_trim_long;
U_long = u_long.Data-u_trim_long;

dx_long = diff(X_long)/0.02;
xu_long(:,1:4) = X_long(1:end-1,:);
xu_long(:,5:6) = U_long(1:end-1,:);

for i=1:length(dx_long)
    y = dx_long(i,:);
    x = xu_long(i,:);
    [A,B,B_ls_long,P_long] = RLSE(y',x',B_ls_long,P_long,4,2,alpha) ;
    ref(i) = B(end,1);
end

%% KALMAN FILTER
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
    %if norm(err)>3 & P<10, P = 10e3;, end
    %if norm(err)<1, P = 0;, end
    %P = eye(6);
    [A,B,P] = RLSE_klm(A,B,err',x',P,4,2,R);
    ref(i) = B(end,1);
    mynorm(i) = norm(P);
end


plot(ref)
figure
plot(mynorm)


