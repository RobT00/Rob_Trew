clear;
close all;

%Redbull Data
jumpdata = csvread('RedBullJumpData.csv');
t_redbull = jumpdata(:,1);
v_redbull = jumpdata(:,2);
terminal_velocity = jumpdata(:,3);
N_timestamps = length(t_redbull);

%No Drag
%Initialising v_nodrag to a matrix of zeros
v_nodrag = zeros (N_timestamps, 1); 
g = 9.81;
v_nodrag = g*t_redbull;

%To keep v_nodrag within the graph constraints
for lim = 1:N_timestamps 
   if v_nodrag(lim) >= 400
       break
   end
end

%Plotting Graph
graph_v_redbull = plot(t_redbull(1:N_timestamps),...
    v_redbull(1:N_timestamps),'r-x');
hold on;
graph_no_drag = plot(t_redbull(1:lim), v_nodrag(1: lim), 'b--');
grid on;
set(graph_v_redbull,'linewidth', 2.0);
set(graph_no_drag,'linewidth', 2.0);
xlabel('Time (secs)', 'fontsize', 24);
ylabel('Velocity (m/s)', 'fontsize', 24);
title('Comparing Baumgartner fall Data models', 'fontsize', 24);


%When entering atmosphere
diff = abs(v_nodrag - v_redbull); 
%Matrices are of same dimensions, so difference can be found
for i = 1:N_timestamps
    error = (diff(i) / v_nodrag(i)) * 100;
    if error >= 5
        disp (['Mr. B. enters the earths atmosphere at ', ...
            num2str(t_redbull(i)), ' secs after he jumps']);
        break
    end
end
%Mr. B. enters the earths atmosphere at 35 secs after he jumps


%Numerical
v_numeric = zeros(N_timestamps, 1); 
%Initialising v_numeric to ma trix of zeros
drag = 3/60;
v_numeric(1:15) = v_redbull(1:15); 
%Seting v_numeric andv_redbull to have the same velocity...
%for the first 15 values (t = 52s)

%Iteration
for i = 16:N_timestamps %Calculating v_numeric
    v_numeric(i) = v_numeric(i-1) + ...
        (g - (drag * v_numeric(i-1)))*(t_redbull(i) - t_redbull(i-1));
end
%Plotting
graph_v_numeric = plot(t_redbull, v_numeric, 'g--');

% Percentage diff @ 64 secs
%64 = t_redbull(20)
X = abs((v_redbull(20) - v_numeric(20)) / v_redbull(20)) * 100;

% Percentage diff @ 170 secs
%170 = t_redbull(37)
Y = abs((v_redbull(37) - v_numeric(37)) / v_redbull(37)) * 100;

disp (['The Percentage error at 64 and 170 secs is ', num2str(X),...
    ' and ', num2str(Y), ' respectively']);
%The Percentage error at 64 and 170 secs is 1.3701 and 143.0678 respectively


%Modelling
%64 = t_redbull(20)
%69 = t_redbull(22)
model = zeros(N_timestamps); 
%Initialising model to a matrix of zeros
low = 2/60; %Setting the lower limit of drag
high = 5/60; %Setting the upper limit of drag
%Creating a matrix, stepped at 0.000001 of drag coefficients
new_drag = low : 0.000001 : high; 
%Setting model to be equal to v_redbull until t = 64s
model(1:20) = v_redbull(1:20); 

z = 22;
%Iterating through numeric solution to find new drag coefficient
for i = 1:length(new_drag) 
    %Computing modeled velocity at t = 65s
    model (z-1) = model (z-2) +...
        (g - (new_drag(i) * model(z-2))) * ...
        (t_redbull(z-1) - t_redbull(z-2)); 
    %Computing modelled velocity at t = 69s
    model(z) = model(z-1) +...
        (g - (new_drag(i) * model(z-1))) * ...
        (t_redbull(z) - t_redbull(z-1)); 
    %Finding difference between modelled and measured velocity at t = 69s
    diff = abs(model(z) - v_redbull(z));
    error = (diff / v_redbull(z)) * 100;
        if error <= 0.1
            model_drag = new_drag(i);
            break
        end
 end 

% Iteration using new drag coefficient
for i = (z+1):N_timestamps
    model(i) = model(i-1) + (g - (model(i-1) * model_drag)) * ...
        (t_redbull(i) - t_redbull(i-1));
end
%Plotting
graph_model = plot (t_redbull(20:N_timestamps), ...
    model(20:N_timestamps), 'k--');

c = model_drag * 60;

disp (['New Drag "c" value = ', num2str(c)]);
%New Drag "c" value = 3.3172
disp (['New Drag coefficient = ', num2str(model_drag)]);
%New Drag coefficient = 0.055287

disp (['Error at t = 69s is ', num2str(error), '%']);
%Error at t = 69s is 0.099866%
axis([0 180 0 400]); %Locking axis of graph
shg; %Showing the graph