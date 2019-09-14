clear vec

for i=1:length(B_sim.data)
    vec(i) = B_sim.data(4,1,i);
end

plot(vec)

%%
clear theta_old theta_new q_old q_new
P = 0;
sim('model_rlseLQR');



for i=1:length(x_long.data)
    theta_old(i) = x_long.data(i,3);
    q_old(i) = x_long.data(i,4);
    t(i) = x_long.time(i);
end

J_old = Jfunction(x_long.data,u_long.data,Q_long,R_long)

P = 100;
sim('model_rlseLQR');

for i=1:length(x_long.data)
    theta_new(i) = x_long.data(i,3);
    q_new(i) = x_long.data(i,4);
    t(i) = x_long.time(i);
end

J_new = Jfunction(x_long.data,u_long.data,Q_long,R_long)

plot(t,rad2deg(theta_old))
hold on
plot(t,rad2deg(theta_new))
legend('No adaptation','online RLSE, P_0 = 100')
xlabel('t')

ylabel('\theta')
grid on
title('Adaptación recursiva en línea - wind gust enabled')


figure

plot(t,q_old)
hold on
grid on
plot(t,q_new)
legend('No adaptation','online RLSE, P_0 = 100')
xlabel('t')
ylabel('q')
title('Adaptación recursiva en línea - wind gust enabled')


