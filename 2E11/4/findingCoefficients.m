%This function is being used to calculate a value for stress based upon
%given coefficients and will return the sum of the error squared of these
%values, for use with fminsearch
function [value] = findingCoefficients(x, actual, phi)
  y_k = 1 - (x(1) * exp(x(2) * phi)) - x(3);
  error_fn = actual - y_k;
  [value] = sum(error_fn .^ 2);
end 