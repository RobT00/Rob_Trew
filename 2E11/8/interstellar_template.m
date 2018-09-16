close all
clear

h = 1;

load ('interstellar_data');

% These columns contain the pre-computed values of the ray trajectory
% Latitude
theta = data(:,3);
% Longitude
phi = data(:, 4);
% Angular momentum 
ptheta = data(:, 6);

N = length(data(:,1));

% Set up the vectors to contain the results of iterations
pr = zeros(N, 1);
r = zeros(N, 1);

% Initialise pr and r
r(1) = 20;
pr(1) = 1.0762;

% Initialise one material constant
b = -5.24284;

for k = 2 : N
  
  old_pr = pr(k - 1);
  old_r = r(k - 1);
  old_theta = theta(k - 1);
  old_ptheta = ptheta(k - 1);
  
  % Calculate dr/dt here
  drdt = ((2 * old_pr)/old_r) - old_pr;
  % and hence calculate r(k) = .... using Euler here
  r(k) = old_r + (h * drdt);
  
  % Calculate dpr/dt here
  dprdt = (b^2 * (csc(old_theta)^2) / r(k)^3) - (1/(r(k) - 2)^2) + ...
    ((r(k) * old_pr^2 - old_ptheta^2)/(r(k)^3));    
  % Calculate pr(k) = .... here using Euler
  pr(k) = old_pr + (h * dprdt);
end

% Convert from spherical to cartesian coordinates
% Using the calculated radius
% r = data(:,2); %data from .mat file
x = r.*cos(data(:,4));
y = r.*sin(data(:,4));
z = r.*sin(data(:,3));

% Render the ray in 3d
plot3(x, y, z, 'linewidth', 1.2);
hold on;
% Render the location of the black hole
plot3(0,0,0,'ko','markersize',5, 'linewidth', 3);
% Render the location of the camera
plot3(20,0,20,'bx','markersize',10, 'linewidth', 2);
% Zoom the axes
axis([-31 31 -31 31 -31 31]);
% Rotate the mesh plot to show a plan view of the ray
view([7 90]);
shg;



