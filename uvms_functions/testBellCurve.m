close all; clc
a=4;
b=6;
c=3;

c = CircleProps.innerCircleRadius + (CircleProps.middleCircleRadius - CircleProps.innerCircleRadius)./2; % middle of bell curve
    b = 2.5;
    a = c/2-0.17;
    x = norm(Vehicle_Velocity_States.Circle2EEVec);

f=@(x)[1./(1+abs((x-c)./a).^(2*b))];

x = -0.3:0.001:1.2;
y = zeros(length(x),1);
triangle = zeros(length(x),1);

ir = CircleProps.innerCircleRadius;
mr = CircleProps.middleCircleRadius;
slope =1000;

for i = 1:length(x);
  if x(i) < ir || x(i) > mr
       triangle(i) = 0;
   elseif x(i) >= ir && x(i) <= c
       triangle(i) = slope*(x(i))-ir*slope;
   elseif x(i) > c 
        triangle(i) = (-slope*x(i) + (-mr*(-slope)));
  end
  if triangle(i) >= 1
      triangle(i) =1;
  end
    y(i) = f(x(i))*triangle(i);
end



plot(x,y);
hold on
plot(CircleProps.middleCircleRadius, 0 , 'or');
plot(CircleProps.innerCircleRadius, 0 ,'or');
%plot(x,triangle, '-g');
grid on;