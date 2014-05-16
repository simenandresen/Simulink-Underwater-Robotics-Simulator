function [ QDDot ] = createGenAccelerations( rob )
%% CREATEGENACCELERATIONS Create symbolic vector of second order joint generalized coordinate derivatives.
% =========================================================================
%
%   [ QDDot ] = createGenAccelerations( rob )
%
%  Input:
%    rob:       Robot definition structure.
%
%  Output:
%    QDDot:     [nx1] Symbolic vector of second order derivatives of the
%                     generalized robot coordinates.
%
%  Example:
%    createGenAccelerations( stanfordarm3 )
%
%  Known Bugs:
%    ---
%
%  TODO:
%    ---
%
%  References:
%    ---
%
%  Authors:
%    Jörn Malzahn    
%
%  See also createGenCoordinates,createGenForces,createGenVelocities.
%
%  This software may be used under the terms of CC BY-SA 3.0 license 
%          < http://creativecommons.org/licenses/by-sa/3.0/ >
%    
%          2012 RST, Technische Universität Dortmund, Germany
%               < http://www.rst.e-technik.tu-dortmund.de >
% 
% ========================================================================

nCoords = size(rob.DH,1);

evalString = [];
for iCoords = 1:nCoords
    evalString = [evalString, 'qDDot', num2str(iCoords), ' '];
end
eval(['syms ', evalString]);
QDDot = eval([ '[', evalString,']' ] );

QDDot=QDDot.';