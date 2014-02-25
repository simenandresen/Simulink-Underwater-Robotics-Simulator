%% Init Dynamics



%% init structures

I=zeros(6,6,n+1);
for i=1:(n+1)
   I(:,:,i) = eye(6); 
end

Dynamics_Parameters = struct('Inertia',I);