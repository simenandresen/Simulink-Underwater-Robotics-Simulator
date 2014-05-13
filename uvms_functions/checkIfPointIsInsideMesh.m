%------------------------------------------------------------------------------------------------------------------
% check if end effector is inside Ws mesh
function isInside = checkIfPointIsInsideMesh (indices, XYZ, point)
    X = XYZ(1,:)';
    Y = XYZ(2,:)';
    Z = XYZ(3,:)';
    idx = indices;
    intersections = 0;
    for i=1:size(indices,1)
        v1 = [ X(idx(i,1)) ; Y(idx(i,1)); Z(idx(i,1)) ]; 
        v2 = [ X(idx(i,2)) ; Y(idx(i,2)); Z(idx(i,2)) ]; 
        v3 = [ X(idx(i,3)) ; Y(idx(i,3)); Z(idx(i,3)) ];
        %intersections = intersections + rayIntersectsTriangle(v1,v2,v3 , point);
        [flag, u, v, t, ray] = rayTriangleIntersection (point,  v1, v2, v3);
        if flag == 1
            intersections = intersections + 1;
        end
    end
    if mod(intersections , 2 ) == 0
       isInside = 0;
    else
       isInside = 1;
    end
end

%------------------------------------------------------------------------------------------------------------------
% Ray/triangle intersection using the algorithm proposed by Möller and Trumbore (1997).
function [flag, u, v, t, ray] = rayTriangleIntersection (o, p0, p1, p2)
    % direction of the ray from the point o
    d = [7,1,0]';
    epsilon = 0.000001;
    e1 = p1-p0;
    e2 = p2-p0;
    q  = cross(d,e2);
    a  = dot(e1,q); % determinant of the matrix M
    if (a>-epsilon && a<epsilon) 
        % the vector is parallel to the plane (the intersection is at infinity)
        [flag, u, v, t,ray] = deal(0,0,0,0,0);
        return;
    end;
    f = 1/a;
    s = o-p0;
    u = f*dot(s,q);
    if (u<0.0)
        % the intersection is outside of the triangle
        [flag, u, v, t, ray] = deal(0,0,0,0,0);
        return;          
    end;
    r = cross(s,e1);
    v = f*dot(d,r);
    if (v<0.0 || u+v>1.0)
        % the intersection is outside of the triangle
        [flag, u, v, t, ray] = deal(0,0,0,0,0);
        return;
    end;
    t = f*dot(e2,r); % verified! 
    if t > epsilon
        flag = 1;
        ray = d;
        return;
    else
        [flag, u, v, t, ray] = deal(0,0,0,0,0);
        return
    end
end

