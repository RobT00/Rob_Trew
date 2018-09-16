%Simultaneous ODEs
clear
close all

t_start = 0;
t_end = 30;
x_initial = 2;
y_initial = 1;
initial_conditions = [x_initial, y_initial];
[tout, yout] = ode45(@dxdtdydt, [t_start, t_end],...
  initial_conditions);

figure(1);
plot1 = plot(tout, yout(:, 1), 'r-',...
  tout, yout(:, 2), 'b-', 'linewidth', 2.0);
set(gca, 'fontsize', 14);
xlabel('Time (t)');
ylabel('Predators and Prey');
title('Graph of P&P against Time', 'fontsize', 16);
legend('Prey', 'Predators', 'location', 'northeast');

figure(2);
plot2 = plot(yout(:, 1), yout(:, 2), 'k-', 'linewidth', 3.0);
title('Phase Plot', 'fontsize', 16);
xlabel('Prey');
ylabel('Predators');

figure(1);
shg;

fprintf('Maximum number of Predators that can be supported: ~%d \n', ...
  floor(max(yout(:, 2))));
%3.6
fprintf('Prey when Predators at maximum: ~%d \n', ...
  floor(yout(yout(:, 2) == max(yout(:, 2)), 1)));
