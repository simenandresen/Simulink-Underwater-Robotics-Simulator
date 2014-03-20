%-----------------------------------
%
%  plot file
%  all plots are called from here
%
%-----------------------------------
close all;
i=0;
fontsize=12;


%% ---------- commanded zeta and xi --------------------------------
i=i+1;
h(i)=figure(i);
set(h(i),'Units','normalized');
set(h(i),'Position',[0.1,0.3,0.4,0.4]);
set(h(i), 'name', 'Fig: Commanded xi and zeta','NumberTitle','off');


subplot(2,2,1);
plot(time, zeta_com(7:12, :));
title('Manipulator commanded joint rates');
xlabel('time [s]'); ylabel('[m/s]');
leg=legend('$\dot{q}_1$','$\dot q_2$','$\dot q_3$', '$\dot q_4$', '$\dot q_5$', '$\dot q_6$');
set(leg,'Interpreter','latex')
grid on;

subplot(2,2,2);
plot(time, zeta_com(1:6, :));
title('Vehichle body commanded velocities');
xlabel('time [s]'); ylabel('[m/s , deg/s]');
legend('u','v','w','p','q','r');
grid on;

subplot(2,2,3);
plot(time, [eta1_com(:,:), r2d*eta2_com(:,:)]);
title('Commanded vehicle position');
xlabel('time [s]'); ylabel('[m, deg]');
leg=legend('x','y','z','$\phi$','$\theta$','$\psi$');
set(leg,'Interpreter','latex');
grid on;

subplot(2,2,4);
plot(time, r2d*q_com(:,:));
title('Commanded joint angle');
xlabel('time [s]'); ylabel('angle [deg]');
leg=legend('$q_1$','$q_2$','$q_3$','$q_4$','$q_5$','$q_6$');
set(leg,'Interpreter','latex');
grid on;

%% -------------- measured xi and zeta ---------------
i=i+1;
h(i)=figure(i);
set(h(i), 'name', 'Fig: Measured xi and zeta','NumberTitle','off');
set(h(i),'Units','normalized');
set(h(i),'Position',[0.1,0.3,0.4,0.4]);

subplot(2,2,2);
plot(time, zeta_mes(7:12, :));
title('Measured manipulator joint rates');
xlabel('time [s]'); ylabel('[m/s]');
leg=legend('$\dot{q}_1$','$\dot q_2$','$\dot q_3$', '$\dot q_4$', '$\dot q_5$', '$\dot q_6$');
set(leg,'Interpreter','latex')
grid on;

subplot(2,2,1);
plot(time, zeta_mes(1:6, :));
title('Measured vehichle body velocities');
xlabel('time [s]'); ylabel('[m/s , deg/s]');
legend('u','v','w','p','q','r');
grid on;

subplot(2,2,3);
plot(time, [eta1_mes(:,:), r2d*eta2_mes(:,:)]);
title('Measured vehicle position');
xlabel('time [s]'); ylabel('[m, deg]');
leg=legend('x','y','z','$\phi$','$\theta$','$\psi$');
set(leg,'Interpreter','latex');
grid on;


subplot(2,2,4);
plot(time, r2d*q_mes(:,:));
title('Measured joint angle');
xlabel('time [s]'); ylabel('angle [deg]');
leg=legend('$q_1$','$q_2$','$q_3$','$q_4$','$q_5$','$q_6$');
set(leg,'Interpreter','latex');
grid on;



%% --------------- commanded torque ---------------------
i=i+1;
h(i)=figure(i);
set(h(i), 'name', 'Fig: Commanded torque','NumberTitle','off');
set(h(i),'Units','normalized');
set(h(i),'Position',[0.1,0.3,0.4,0.4]);

subplot(2,1,1);
plot(time, tau(1:6,:));
title('Commanded torque to vehicle (output from controller)');
xlabel('time [s]'); ylabel('[m/s]');
leg=legend('$\tau_1$','$\tau_2$','$\tau_3$', '$\tau_4$', '$\tau_5$', '$\tau_6$');
set(leg,'Interpreter','latex')
grid on;

subplot(2,1,2);
plot(time, tau(7:12,:));
title('Commanded torque to manipulator (output from controller)');
xlabel('time [s]'); ylabel('[m/s]');
leg=legend('$\tau_7$','$\tau_8$','$\tau_9$', '$\tau_{10}$', '$\tau_{11}$', '$\tau_{12}$');
set(leg,'Interpreter','latex')
grid on;


%% ------------- error states (tilde)-------------------
i=i+1;
h(i)=figure(i);
set(h(i),'Units','normalized');
set(h(i),'Position',[0.1,0.3,0.4,0.4]);
set(h(i), 'name', 'Fig: Error States','NumberTitle','off');


subplot(2,2,1);
plot(time, zeta_tilde(1:6,:));
title('Error vehicle velocity');
xlabel('time [s]'); ylabel('[m/s]');
legend('u','v','w','p','q','r');
grid on;


subplot(2,2,2);
plot(time, zeta_tilde(7:12,:));
title('Error Manipulator velocity');
xlabel('time [s]'); ylabel('[m/s]');
leg=legend('$\dot{q}_1$','$\dot q_2$','$\dot q_3$', '$\dot q_4$', '$\dot q_5$', '$\dot q_6$');
set(leg,'Interpreter','latex')
grid on;


subplot(2,2,3);
plot(time, [xi_tilde(1:3,:); r2d*xi_tilde(4:6,:)]);
title('Error vehicle position');
xlabel('time [s]'); ylabel('[m, deg]');
leg=legend('x','y','z','$\phi$','$\theta$','$\psi$');
set(leg,'Interpreter','latex');
grid on;


subplot(2,2,4);
plot(time, r2d*xi_tilde(7:12,:));
title('Error joint angle');
xlabel('time [s]'); ylabel('angle [deg]');
leg=legend('$q_1$','$q_2$','$q_3$','$q_4$','$q_5$','$q_6$');
set(leg,'Interpreter','latex');
grid on;

%% --------------- specific forces  ---------------------
i=i+1;
h(i)=figure(i);
set(h(i), 'name', 'Fig: Specific Forces','NumberTitle','off');
set(h(i),'Units','normalized');

subplot(2,1,1);
plot(time, specific_forces(1:6,:));
title('Specific forces vehicle )');
xlabel('time [s]'); ylabel('[m/s]');
leg=legend('$\tau_1$','$\tau_2$','$\tau_3$', '$\tau_4$', '$\tau_5$', '$\tau_6$');
set(leg,'Interpreter','latex')
grid on;

subplot(2,1,2);
plot(time, specific_forces(7:12,:));
title('Specific forces - Manipulator');
xlabel('time [s]'); ylabel('[m/s]');
leg=legend('$\tau_7$','$\tau_8$','$\tau_9$', '$\tau_{10}$', '$\tau_{11}$', '$\tau_{12}$');
set(leg,'Interpreter','latex')
grid on;



%%
%figHandles = get(0,'Children');
%# make all text in the figure to size 14 and bold
%set(findall(figHandles,'type','text'),'fontSize',13,'fontWeight','bold')








