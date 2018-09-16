%Script for comparing Numerical and Analytic Solutions
clear vars;
close all;

%Define known variables
g = 9.81; c = 12.5; m = 70;

%Define timestep
delta_t = 0.1;

%Define time vector containing time instants starting from 0
%in increments of delta_t
t = 0 : delta_t : 10;

%Calculate the analytic velocity solution
v_analytic = (g*m/c)*(1-exp(-c*t/m));

%Calculate numerical solution
%First set up N (the number of iterations)
% and the array for the numerical results
N = length(t);
v_numerical = zeros(N,1);
%
% Numerical iteration code goes here
for i = 2 : N
    v_numerical(i) = v_numerical(i-1) + ((g - ((c/m)*v_numerical(i-1)))*(delta_t));
end

%Now plot the two solutions on the same plot
h = plot(t, v_analytic, 'g', t, v_numerical, 'r');
grid on;
grid minor;
set(h,'linewidth',2.0);
xlabel('Time (sec)', 'fontsize', 24);
ylabel('Velocity (m/s)', 'fontsize', 24);
title('Comparing Numerical and Analytic Solutions');
legend('analytical', 'numerical', 'Location','northwest');

%Getting differences
v_diff1 = abs(v_numerical(2) - v_analytic(2));
v_diff2 = abs(v_numerical(19) - v_analytic(19));

disp ('Difference at t = 0.5:');
disp (v_diff1);
disp ('Difference at t = 9:');
disp (v_diff2);
