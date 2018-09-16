function y = functDerived(c, g, m, t)

y = (g*m) * (-((1-exp(-(c*t)/m))/c^2) + (exp(-(c*t)/m)*transpose(t))/(m*c));