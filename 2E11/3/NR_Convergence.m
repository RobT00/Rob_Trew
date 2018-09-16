clear;
close all;

%Initial setup
g = 9.81;
t = 0 : 0.1 : 20;
m = 68.1;
%Around 14.9
%c = 14.9;
c = 5;
v = ((g*m)/c)*(1-(exp((-c*t)/m)));

figure(1);
fig1 = plot(t, v, 'r-', 'linewidth', 2.0);
title('Velocity vs Time', 'fontsize', 24);
xlabel('Time (s)', 'fontsize', 16);
ylabel('Velocity (m/s)', 'fontsize', 16);
axis([0 12 0 40]);
shg;

%N-R method
v = zeros(length(t));
goal = 40;
i = 1;
max_its = 200;
% cn = zeros(20,1);
% while abs(v(101) - goal) > 0.5 && iterations < 20 
%     v = ((g*m)/c)*(1-(exp((-c*t)/m)));
%     cn(iterations) = c;
%     c = c + 1;
%     iterations = iterations + 1;
%     disp (abs(v(101) - goal));
% end
disp (['Iterations: ', num2str(i)]);
disp (['C value: ', num2str(c)]);
disp (['V: ', num2str(v(101))]);
% cn = zeros (length(t));
cn = 5;
rel_error = 5;
lim = 1;
while ((rel_error > lim) && (i <= max_its))
   %cn(i+1) = cn(i) - funct(cn(i), g, m, t)/functDerived(cn(i), g, m, t);
   cn(i+1) = cn(i) + (40 - funct(cn(i), g, m, t))/functDerived(cn(i), g, m, t);
   disp(['c(n+1): ', num2str(cn(i+1))]);
   %rel_error = abs((cn(i+1)-cn(i))/(cn(i)));
   v1 = ((g*m)/cn(i+1))*(1-(exp((-cn(i+1)*t(101))/m)));
%    v2 = ((g*m)/cn(i+1))*(1-(exp((-cn(i+1)*t(101))/m)));
   %rel_error = abs((v2-v1)/(v1));
   rel_error = abs(40 - v1);
%    disp (['C value: ', num2str(cn(i+1))]);
   i = i+1;
%    disp (['Iterations: ', num2str(i)]);
%    
    disp (['V: ', num2str(v1)]);
    disp (['Error: ', num2str(rel_error)]);
end
disp (['Iterations: ', num2str(i)]);
disp (['C value: ', num2str(cn(end))]);
disp (['V: ', num2str(v(101))]);

%plot
new_c = cn(end);
v1 = ((g*m)/new_c)*(1-(exp((-new_c*t)/m)));
figure(2);
fig1 = plot(t, v1, 'r-', 'linewidth', 2.0);
title('Velocity vs Time', 'fontsize', 24);
xlabel('Time (s)', 'fontsize', 16);
ylabel('Velocity (m/s)', 'fontsize', 16);
axis([0 12 0 40]);
shg;

pause;

figure(3);
fig2 = plot((1 : i-1), cn(1 : i-1), 'r-x', 'linewidth', 3.0);
title('Guesses', 'fontsize', 24);
xlabel('Iterations', 'fontsize', 16);
ylabel('Estimated c', 'fontsize', 16);
axis([0 12 5 15]);
shg;

%ct = fzero(((g*m)/c)*(1-(exp((-c*t)/m))), 40);
% x = 0.05; 
% x_old = 100;
% x_true = 0.0623776;
% iter = 0;
% while abs(x_old-x) > 10^-3 && x ~= 0
%     x_old = x;
%     x = x - (x^3 - 0.165*x^2 + 3.993*10^-4)/(3*x^2 - 0.33*x);
%     iter = iter + 1;
%     fprintf('Iteration %d: x=%.20f, err=%.20f\n', iter, x, x_true-x);
%     pause;
% end
% x = -10:0.01:10;
% f = x.^3 - 0.165*x.^2 + 3.993*10^-4;
% figure;
% plot(f)
% grid on
% shg;
% x = fzero(@(x)x.^3 - 0.165*x.^2 + 3.993*10.^-4,0.05);