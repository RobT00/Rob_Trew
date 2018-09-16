close all;
clear;



% Set up the x range and plot the true solution
x = 0 : 0.1 : 4.0;
y = -0.5 * x.^4 + 4 * x.^3 - 10 * x.^2 + 8.5 * x + 1.0;

figure(1);
plot(x, y, 'k-', 'linewidth', 3);
set(gca, 'fontsize', 16);
xlabel('x', 'fontsize', 25);
ylabel('y', 'fontsize', 25);
title('Comparing Euler''s method for different step size', 'fontsize', 25);
axis([0 4.5 0 8.0]);
hold on;

n = 1;
% Now do Eulers method at various h
for h = 0.5 : -0.05 : 0.05
  if ( h < 0.5 )
    delete(handlep);
    delete(handlet);
  end;
  % Set up all my increments in x
  x = 0 : h : 4.0;
  n = length(x);
  y = zeros(1, n);
  % Set initial condition (y = 1 when x = 0)
  y(1) = 1;
  % This is Euler
  for i = 1 : n - 1    
    slope = differential1(x(i));    
    y(i+1) = y(i) + slope * h;        
  end;
  % Plot the Euler's solution
  figure(1);
  handlep = plot(x, y, 'r-o', 'linewidth', 3);
  str = ['h = ',num2str(h)];
  handlet = text(2.0, max(y), str, 'interpreter', 'tex', 'fontsize', 20);
  pause;
  n = n + 1;
end;


    





