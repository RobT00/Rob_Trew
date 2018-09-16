%Robert Trew - 15315527
%PDEs for Fixing Bad Pictures
%Assignment Week 10

clear;
close all;

%Function definitions are at the bottom

%Assumption for problem
%h = 1;

%Setting a to 1, 2 or 3 will process the image with different alpha values
%as can be seen below
a = 1;

if a == 1
  alpha = 1; %Value of alpha given in assignment
elseif a == 2
  step = 0.01;
  alpha = 1.7 : step : 1.8; %This can take a while to run through
elseif a == 3
  alpha = 1.743; %Found to be the optimal value of alpha (from a == 2)
end

times = 2000; %The number of iterations on the picture

load('forcing.mat'); %"f" forcing matrix
load('badpicture.mat');%corrupted picture

figure(1); %Original.tif
pic_org = double(imread('greece.tif'));
image(pic_org);
colormap(gray(256));
title('Original');

figure(2); %Badpicture.mat
image(badpic);
colormap(gray(256));
title('Corrupted Picture');

mask = imread('badpixels.tif'); %used to find corrupted pixels

%Setting up variables to be used
%"nof" refers to the data not using the forcing matrix
%"f" means the forcing matrix is used
nof = zeros(length(f)); %Using a forcing matrix of 0s in function
new_pic = badpic; %To keep the corrupted picture unchanged
new_pic_nof = new_pic;
new_pic_f = new_pic;
pic_nof = new_pic_nof;
pic_f  = new_pic_f;

[m, n] = find(mask == 1); %Finding locations of corruption

error_standard1 = zeros(length(m), 1); %To store differences between 
%original and changed pixel values
error_standard2 = error_standard1;
e_nof = error_standard1; %To store errors from SOR method formula
e_f = e_nof;
new_error1 = zeros(length(times), 1); %Will store the standard errors
new_error2 = new_error1;

min = 0.0; %To record the minimum error, to calculate optimal alpha
opt = min; %Will point to the optimal value of alpha

%Iterating through image to fix
for val = 1 : length(alpha)
   for iterations = 1 : times
    [e_nof, new_pic_nof, error_standard1] = ...
      pictureFixing(e_nof, error_standard1, new_pic_nof, m, n, ...
      alpha(val), nof, pic_org);
    [e_f, new_pic_f, error_standard2] = ...
      pictureFixing(e_f, error_standard2, new_pic_f, m, n, ...
      alpha(val), f, pic_org);
    new_error1(iterations) = std(error_standard1);
    new_error2(iterations) = std(error_standard2);
   end
   
  %This bit is used to find the optimal value of alpha
  if a == 2
    e_sum = abs(mean(e_nof));
    if isnan(e_sum) && min == 0.0
      %Do nothing
    elseif min == 0.0 || e_sum <= min
      min = e_sum;
    else 
      %Current error is greater, previous alpha is best
      opt = val - 1;
    end
  else
    opt = val;
  end
  %Current images are stored and then reset
  [pic_nof, new_pic_nof, error1] = clearSwap(new_pic_nof, badpic, ...
    new_error1);
  [pic_f, new_pic_f, error2] = clearSwap(new_pic_f, badpic, new_error2);
  %If search for optimal alpha in given range is over
  if opt ~= 0.0
    break
  end
end

figure(3);
image(pic_nof);
colormap(gray(256));
title('Restored Picture');

figure(4);
image(pic_f);
colormap(gray(256));
title('Restored Picture (with F)');

disp(['Using value of alpha: ', num2str(alpha(opt))]);

%Plotting Standard Error vs iterations for fixing corrupted pixels
figure(5);
plot_nof = plot(1 : iterations, error1, 'linewidth', 3, 'color', 'red');
hold on;
plot_f = plot(1 : iterations, error2, 'linewidth', 3, 'color', 'blue');
title('Error', 'fontsize', 20);
xlabel('Iteration');
ylabel('Std Error');
legend('No forcing function', 'With forcing function', 'location', 'ne');
hold off;

%Function Definitions

%The function uses the Successive Overrelaxation (SOR) method to fix the
%corrupted image. The error from the method, the updated pixel value and 
%the difference between the original and changed pixel values are stored
function [error, picture, diff] = pictureFixing(error, diff, ...
  picture, m, n, coeff, forcing, original)
  for i = 1 : length(m)  
    error(i) = picture(m(i) - 1, n(i)) + ...
      picture(m(i) + 1, n(i)) + ...
      picture(m(i), n(i) - 1) + ...
      picture(m(i), n(i) + 1) - ...
      4 * picture(m(i), n(i))- forcing(m(i), n(i));
    picture(m(i), n(i)) = picture(m(i), n(i)) + ...
      coeff * (error(i) / 4);
    diff(i) = picture(m(i), n(i)) - original(m(i),n(i));
  end
end


%This function is used to swap processed images and unprocessed ones, in
%order to have a clean slate to test each alpha, but also save the previous
%data for comparison
function [previous, current, error] = clearSwap(current, original, diff)
  previous = current;
  current = original;
  error = diff;
end