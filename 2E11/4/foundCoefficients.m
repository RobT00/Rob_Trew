%This function simply calculates the values of estimated stress based on
%the input coefficients, and returns this matrix of values
function [value] = foundCoefficients(x, phi) 
  [value] = 1 - (x(1) * exp(x(2) * phi)) - x(3);
end