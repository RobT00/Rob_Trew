close all; clear;

g = 9.81;

alpha = 0.0005 : 0.0001 : 1;

t1 = 56; v1 = 360; t2 = 69; v2 = 260;

k = exp(-alpha * t2) .* exp(alpha * t1) ...
    .* (g - alpha * v1);
error = v2 - (g ./ alpha) + (1 ./ alpha) .* k;
error = error * 100/2;

figure(1);
plot (alpha, error, 'r-', 'linewidth', 3.0);
xlabel ('\alpha', 'Interpreter', 'tex', ...
    'fontsize', 16);
ylabel ('% Error');