function [value] = differential(a, x, xmax)
  [value] = a * (1 - (x / xmax)) * x;
end