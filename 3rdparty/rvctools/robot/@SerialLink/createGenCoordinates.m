function [ Q phie dPhiedx] = createGenCoordinates( rob )
%% CREATEGENCOORDINATES Create symbolic vector of generalized robot joint coordinates.
% =========================================================================
%
%   [ Q ] = createGenCoordinates( rob )
%
%  Input:
%    rob:       Robot definition structure.
%
%  Output:
%    Q:     [nx1] Symbolic vector of the generalized robot coordinates.
%
%  Example:
%    createGenCoordinates( stanfordarm3 )
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
%  See also createGenForces,createGenVelocities,createGenAccelerations.
%
%  This software may be used under the terms of CC BY-SA 3.0 license 
%          < http://creativecommons.org/licenses/by-sa/3.0/ >
%    
%          2012 RST, Technische Universität Dortmund, Germany
%               < http://www.rst.e-technik.tu-dortmund.de >
% 
% ========================================================================

nCoords = rob.n;

evalString = [];

phie = sym([]);
dPhiedx = sym([]);
indOffset = 0;

for iCoords = 1:nCoords
    % Generalized coordinates: Joint values...
    evalString = [evalString, 'q', num2str(iCoords), ' '];
    
    if isfield(rob, 'links')    % If there is no link definition field, the robot must be rigid
        if rob.links(iCoords) == 'f'
            % ... and flexible time dependent mode amplitudes
            evalString = [evalString, 'del', num2str(iCoords), '1 '];
            evalString = [evalString, 'del', num2str(iCoords), '2 '];
            
            % Additionally store symbolic variables for the mode shape
            % functions at the link ends in separate containers
            tmpEvalString = ['syms phie', num2str(iCoords),'1; phie(', num2str(iCoords+indOffset+1),') = phie', num2str(iCoords),'1;'];
            eval(tmpEvalString);
            tmpEvalString = ['syms phie', num2str(iCoords),'2; phie(', num2str(iCoords+indOffset+2),') = phie', num2str(iCoords),'2;'];
            eval(tmpEvalString);
            tmpEvalString = ['syms dPhiedx', num2str(iCoords),'1; dPhiedx(', num2str(iCoords+indOffset+1),') = dPhiedx', num2str(iCoords),'1;'];
            eval(tmpEvalString);
            tmpEvalString = ['syms dPhiedx', num2str(iCoords),'2; dPhiedx(', num2str(iCoords+indOffset+2),') = dPhiedx', num2str(iCoords),'2;'];
            eval(tmpEvalString);
            indOffset = indOffset +2;
        else
            
        end
    else
    end
        
end
eval(['syms ', evalString]);
Q = eval([ '[', evalString,']' ] );

Q = Q.';
