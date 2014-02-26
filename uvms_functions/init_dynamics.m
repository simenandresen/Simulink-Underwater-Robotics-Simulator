%% Init Dynamics



%% inertia
I=zeros(6,6,n+1);
for i=1:(n+1)
   I(:,:,i) = eye(6); 
end

%% persistent forces
rho = 1000;
nabla=ones(n+1,1);
m=zeros(n+1,1);
g=9.81;
rig=zeros(n+1,3);   % vector from frame i to CG
rib=zeros(n+1,3);   % vector from frame i to CB
Persistent=struct('rho',rho,'nabla', nabla, 'g', g, 'rig', rig, 'rib',rib, 'm',m );





Kinetics_Parameters = struct('Inertia',I, 'Persistent', Persistent);
