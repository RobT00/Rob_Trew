function [ddt] = dxdtdydt(t, f)
  ddt = zeros(2, 1);
  a = 1.2;
  b = 0.6;
  c = 0.8;
  d = 0.3;
  x = f(1);
  y = f(2);
  ddt(1) = (a * x) - (b * x * y);
  ddt(2) = -(c * y) + (d * x * y);
end