close all; clc;

t = -5:dt:5;

y = zeros(length(t), 1);


y(1) = 1;


for i=1:length(t)
    y(i) = atan(t(i)); %0.9*y(i-1);
end

plot(t, y);