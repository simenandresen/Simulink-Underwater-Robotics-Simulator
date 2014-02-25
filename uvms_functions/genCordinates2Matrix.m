function [ g, R ] = genCordinates2Matrix(position, euler_angles )
% function [ g, R ] = genCordinates2Matrix(position, euler_angles )
% get the generalized coordinates and transform to matrix representation
% g is the transformation matrix, R rotation matrix and p is the position
% vector
%
% euler_angles - zyx convention

R = Rzyx(euler_angles(1),euler_angles(2),euler_angles(3));
position = [position(1),position(2),position(3)]'; % make sure its a column vector
g = [R, position; 0,0,0,1];

end

