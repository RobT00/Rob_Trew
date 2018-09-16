% Solution for assignment in week 8
% Population density calculation
% Robert Trew - 15315527
clear;
close all;

% Define constants
pmax = 12000;
k = 0.026;

% Define step size
h = 1;

% Define the ground truth from the table given
truth = [1950 1960 1970 1980 1990 2000 2011;...
         2555 3040 3708 4454 5276 6079 7000];
     
% Define time interval
t = 1950 : h : 2016;

% Work out number of time steps
N = length(t);

% Set up output variables for euler and heun estimates
p_euler = zeros(1, N);
p_heun = zeros(1, N);

% Set initial values
p_euler(1) = 2555;
p_heun(1) = 2555;

for i = 2 : N
  slope = differential(k, p_euler(i - 1), pmax);
  slope_left = differential(k, p_heun(i - 1), pmax);
  %Euler
  p_euler(i) = p_euler(i - 1) + slope * h;
  %Heun
  slope_right = differential(k, p_euler(i), pmax);
  p_heun(i) = p_heun(i - 1) + 0.5 * h * (slope_left + slope_right);
end

figure(1);
hold on;
% Plot the euler and heun estimates as well as the truth here
truth_plot = plot(truth(1,:), truth(2,:), 'r-d', 'MarkerFaceColor', 'r'...
  , 'linewidth', 2.0);
euler_plot = plot(t, p_euler, 'b-o');
heun_plot = plot(t, p_heun, 'gx-');
hold off;

% Now for the various labels.
ylabel('World Population (Millions)', 'fontsize', 20);
xlabel('Year', 'fontsize', 20);
set(gca, 'fontsize', 20);
title('Modeling the world population 1950-2017')
% Turn on grid
grid on;

% *****************************

% Insert the legend on the plot
legend('Truth', 'Euler', 'Heun', 'location', 'southeast'); 

% *****************************

% Calculate the std error at the points in the table
% *****************************
matches = zeros(length(truth(1, :)), 1);

for i = 1 : length(truth(1,:))
  matches(i) = find(t == truth(1, i));
end

std_euler = std(truth(2,:) - p_euler(matches));
std_heun = std(truth(2,:) - p_heun(matches));
% *****************************

fprintf('Standard Error: Euler = %2.0f, Heun = %2.0f Million People.\n',...
  std_euler, std_heun);
fprintf('At 2017 Euler World Population = %4.0f \n', p_euler(end));
fprintf('At 2017 Heun World Population = %4.0f \n', p_heun(end));

