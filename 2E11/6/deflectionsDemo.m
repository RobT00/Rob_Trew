% Beam deflection demo
close all
clear all

I = 6.67e-9; % units m^4
L = 6; % units m
w = 2; % units N/m
h = L/5; % units m
E = 20e9; % units N/m^2

% Nodal solution with 4 nodes
K = [-2 1 0 0;1 -2 1 0;0 1 -2 1;0 0 1 -2];
c = -w * (h * h) / (2 * E * I);
f = c * [L * h - h^2; L * (2 * h) - (2 * h)^2; L * (3 * h) - (3 * h)^2;...
         L * (4 * h) - (4 * h)^2];

u = K \ f;
xu = [0 : h : L];
u_nodal = [0 u' 0];

% Analytic solution
x = (0 : h/4 : L);
u_analytic = (-w / (12 * E * I)) * ((L * x.^3) - (x.^4 / 2)...
           - (L.^3 * x / 2) );
        
% Colocation solution
cc = w / (2 * E * I);
% Can change the node points here
xc = [L / 3; 2 * L / 3]; %, 2 * L / 4, 5 * L / 8];
%xc = [1, 2] * L / 3;
f = - cc * (L - xc) .* xc;
k1 = -2 * ones(2, 1);
k2 = 2 * L - 6 * xc;
% These are for 3rd and 4th order
% k3 = 6 * xc * L - 12 * xc.^2;
% k4 = 12 * L * xc.^2 - 20 * xc.^3;

K = [k1 k2];

a = K \ f;

u_colo = a(1) * x .* (L - x) + a(2) * (x.^2) .* (L - x); %...
       %+ a(3) * (x.^3) .* (L - x) + a(4) * (x.^4) .* (L - x);

% Plot results
figure(1);
plot(x, u_analytic, 'k-', xu, u_nodal, 'r--x', 'linewidth', 3);
% plot(x, u_analytic, 'k-', xu, u_nodal, 'r-x', x, u_colo, 'b-',...
%      'linewidth', 3);
xlabel('x', 'fontsize', 20);
ylabel('Deflection $u$', 'fontsize', 20, 'interpreter', 'latex');
