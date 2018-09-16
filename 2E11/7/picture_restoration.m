clear
close all
clc

original = imread('greece.tif');
figure(1);
image(original);
title('Original image');
colormap(gray(256));

load badpicture;
figure(2);
image(badpic);
title('Corrupted image');
colormap(gray(256));
badpic1 = badpic;

badpixels = imread('badpixels.tif');

forcing = load('forcing.mat');
f = (forcing.f);

[y,x] = find( badpixels == 1);
iterations = 2000;
corrupted_pixels = length(y);
iterations_xaxis = zeros(1, iterations);
error1 = zeros(1, corrupted_pixels);
error2 = zeros(1, corrupted_pixels);
error_standard1 = zeros(1, corrupted_pixels);
error_standard2 = zeros(1, corrupted_pixels);
std_error1 = zeros(1, iterations);
std_error2 = zeros(1, iterations);
alpha = 1;

for i = 1:iterations
   
    for q = 1 : corrupted_pixels
    error1(q) = badpic( y(q)-1, x(q)) + badpic( y(q)+1, x(q)) + badpic( y(q), x(q)-1) + badpic( y(q), x(q)+1) - 4*badpic(y(q), x(q) );
    badpic(y(q), x(q)) = badpic(y(q), x(q)) + alpha * ( error1(q)/4);
    error_standard1(q) = original(y(q), x(q)) - badpic(y(q), x(q));
    
    error2(q) = badpic1( y(q)-1, x(q)) + badpic1( y(q)+1, x(q)) + badpic1( y(q), x(q)-1) + badpic1( y(q), x(q)+1) - 4*badpic1(y(q), x(q) ) - f( y(q), x(q));
    badpic1(y(q), x(q)) = badpic1(y(q), x(q)) + alpha * ( error2(q)/4);
    error_standard2(q) = original(y(q), x(q)) - badpic1(y(q), x(q));
    end

    iterations_xaxis(i) = i;
    std_error1(i) = std(error_standard1);
    std_error2(i) = std(error_standard2);
    disp(i);
    
end

figure(3);
image(badpic);
title('Restored image with f[m,n] = 0');
colormap(gray(256));

figure(4);
image(badpic1);
title('Restored image with f[ y(q), x(q) ] = formating array');
colormap(gray(256));

figure(5);
x = plot(iterations_xaxis, std_error1,'r', iterations_xaxis, std_error2,'b', 'LineWidth', 3);
title('Decline of error between original and corrupted images with iterations');
xlabel('Iterations');
ylabel('Standard error');
legend('Without forcing','With forcing');
