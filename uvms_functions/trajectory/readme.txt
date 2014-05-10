N-Dimensional Cardinal(Catmull-Rom) Spline Interpolation
========================================================

evalcrdnd.m
------------
Evaluate (interpolate) cardinal spline for given four control points and
tesion at given parameter value of u (a single value)

crdatnplusoneval.m
-------------------------------------
Evaluate (interpolate) cardinal spline for given four control points and
tesion at n+1 values of u (parameter u varies b/w 0 and 1). 
Uniform parameterization is used.

main.m
------------------------------------------
A Simple Test program to perform  1D, 2D, 3D Cardinal Spline interpolation
of given data with Tension=0 (Catmull-Rom)


MotionTweeningbyCardinalSpline.pdf
------------------------------------------
Research paper about Cardinal spline and its application in
motion tweening.



% % --------------------------------
% % This program or any other program(s) supplied with it does not provide any
% % warranty direct or implied.
% % This program is free to use/share for non-commerical purpose only. 
% % Kindly reference the author.
% % Author: Dr. Murtaza Khan
% % Author Reference : http://www.linkedin.com/pub/dr-murtaza-khan/19/680/3b3
% % Research Reference: http://dx.doi.org/10.1007/978-3-642-25483-3_14
% % --------------------------------
