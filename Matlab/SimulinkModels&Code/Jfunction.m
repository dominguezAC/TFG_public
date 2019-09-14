function J = Jfunction(Vx,Vu,Q,R)
    J = 0;
    for i=1:length(Vx)
        x = Vx(i,:)';
        u = Vu(i,:)';
        J = J+  x'*Q*x + u'*R*u;
    end
end