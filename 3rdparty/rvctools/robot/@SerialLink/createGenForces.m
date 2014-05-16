function [ tau ] = createGenForces( rob )
%% CREATEGENFORCES Create symbolic vector of generalized robot joint forces.
% =========================================================================
%
%   [ tau ] = createGenForces( rob )
%
%  Input:
%    rob:       Robot definition structure.
%
%  Output:
%    tau:     [nx1] Symbolic vector of the generalized robot joint forces.
%
%  Example:
%    createGenForces( stanfordarm3 )
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
%  See also createGenCoordinates,createGenVelocities,createGenAccelerations.
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
    evalString = [evalString, 'tau', num2str(iCoords), ' '];
end
eval(['syms ', evalString]);
tau = eval([ '[', evalString,']' ] );

tau=tau.';