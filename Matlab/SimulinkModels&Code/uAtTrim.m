function [u_trim] = uAtTrim(TRIM,TAS,w,phi)
% Returns trim controls for a given flight condition
u_trim(1) = interp3(TRIM.TAS,TRIM.w,TRIM.phi,TRIM.u_a,TAS,w,phi);
u_trim(2) = interp3(TRIM.TAS,TRIM.w,TRIM.phi,TRIM.u_e,TAS,w,phi);
u_trim(3) = interp3(TRIM.TAS,TRIM.w,TRIM.phi,TRIM.u_r,TAS,w,phi);
u_trim(4) = interp3(TRIM.TAS,TRIM.w,TRIM.phi,TRIM.u_p,TAS,w,phi);
end

