%Robert Trew - 15315527
%Assignment Week 6 - Curve Fitting
clear; close all;

%Read in Excel Data
raw_data = xlsread('muscle_data_2017.xlsx');
strain = raw_data(:,3);
stress = raw_data(:,4);

%To Note
%error = actual_stress_value - estimated_stress_value

%Part 1
figure(1);
plot1 = plot(strain, stress, 'linewidth', 3.0, 'color', 'blue');
title('Stress Vs. Strain Curve', 'fontsize', 24);
ylabel('Transverse Stress [Pa]', 'fontsize', 16);
xlabel('Transverse Strain (log(stretch))', 'fontsize', 16);
hold on;

%Part 2
M = ones(2, 1);
error_sq = zeros(2, 1);
%Stopped at 8th order, as polynomial is badly conditioned after
for N = 1 : 8 
  P1 = polyfit(strain, stress, N);
  y1 = polyval(P1, strain);
  error_loop = stress - y1;
  error_sq(N) = sum(error_loop .^ 2);
  M(N) = N;
end

figure(2);
plot2 = plot(M, error_sq, 'linewidth', 3, 'color', 'red');
title('Error squared Vs. Order', 'fontsize', 24);
xlabel('Order', 'fontsize', 16);
ylabel('Error squared', 'fontsize', 16);

%Part 3
%Using selected order: 3
figure(1);
selected_order = 3;
P2 = polyfit(strain, stress, selected_order);
y2 = polyval(P2, strain);
plot3 = plot(strain, y2, 'linewidth', 1, 'color', 'red');

%Part 4
figure(3);
error = stress - y2;
std_dev = std(error);
r = corrcoef(stress, y2);
%The example histogram appears to be set to using 10 bins, so this is why
%it has been included
% histogram1 = histogram(error, 10);
histogram1 = histogram(error);
title(['Std error = ', num2str(std_dev), ' r = ', num2str(r(2))],...
  'fontsize', 24);
xlabel('Error in Ploynomial fit', 'fontsize', 16);
ylabel('Frequency', 'fontsize', 16);
hold on;
%If it is wished to view figure(3), histogram for polynomial fit error, 
%on it's own pause here
%pause;

%Part 5
x0 = [0.3; 0.3; 0.3];
coefs = fminsearch(@(x) findingCoefficients(x, stress, strain), x0);
y_min = foundCoefficients(coefs, strain);
figure(1);
plot4 = plot(strain, y_min, 'k--', 'linewidth', 3);
legend('Original Data', 'Polynomial fit (m = 3)',...
    'Non-linear (fminsearch) fit', 'Location', 'southeast');
hold off;

%Part 6
figure(3);
error2 = stress - y_min;
std_dev2 = std(error2);
r2 = corrcoef(stress, y_min);
%Same reason as above
% histogram2 = histogram(error2, 10);
histogram2 = histogram(error2);
legend('Error 1: Polynomial Model', 'Error 2: Nonlinear Model', ...
  'location', 'northeast');
title(['Error 1 = ', num2str(std_dev), ', Error 2 = ', ...
  num2str(std_dev2), '. r1 = ', num2str(r(2)), ', r2 = ',...
  num2str(r2(2))], 'fontsize', 24);
hold off;
%If it is wished to view figure(4), histogram for non-linear fit error, on
%it's own, uncomment this:
% figure(4);
%%Same reason as above
%%histogram(error2, 10);
% histogram(error2);
% title(['Error = ', num2str(std_dev2), ' r = ', num2str(r2(2))],...
%   'fontsize', 24);
% xlabel('Error in Ploynomial fit', 'fontsize', 16);
% ylabel('Frequency', 'fontsize', 16);