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
v = (g*m/c)*(1-exp(-c*t/m));

%Settign up graph
h = plot(t, v, '-r');
set(h, 'linewidth', 2);
xlabel('Time (sec)', 'fontsize', 24);
ylabel('Velocity (m/s)', 'fontsize', 24);
grid on;
grid minor;