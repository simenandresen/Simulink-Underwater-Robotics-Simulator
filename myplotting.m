%-----------------------------------
%
%  plot file
%  all plots are called from here
%
%-----------------------------------
close all;
i=1;
fontsize=12;


%% commanded trajectories

% % end effector
% h(i)=figure(i);
% set(h(i),'Units','normalized');
% set(h(i),'Position',[0.1,0.3,0.4,0.4]);
% 
% subplot(2,2,1);
% plot3(ee_eta1_c(:,1),ee_eta1_c(:,2), ee_eta1_c(:,3));
% axis square;
% title('EE commanded position');
% xlabel('x'); ylabel('y');zlabel('z');
% grid on;
% 
% subplot(2,2,2);
% plot(time, ee_eta1_c(:,:));
% title('EE commanded position 2d');
% xlabel('time [s]'); ylabel('[m]');
% legend('x','y','z');
% grid on;
% 
% subplot(2,2,3);
% plot(time, r2d*[ee_eta2_c(:,1),ee_eta2_c(:,2), ee_eta2_c(:,3)]);
% title('EE commanded orientation (euler angles)');
% xlabel('time [s]'); ylabel('angle [deg]');
% leg=legend('$\phi$','$\theta$','$\psi$');
% set(leg,'Interpreter','latex');
% grid on;
% 
% subplot(2,2,4);
% plot(time, ee_vel_c(:,:));
% title('End effector commanded  velocities');
% xlabel('time [s]'); ylabel('[m/s , rad/s]');
% legend('u','v','w','p','q','r');
% grid on;
% 
% % new figure
% i=i+1;
% h(i)=figure(i);
% set(h(i),'Units','normalized');
% set(h(i),'Position',[0.1,0.3,0.4,0.4]);
% 
% subplot(2,2,1);
% plot(time, zeta_c(:,7:12));
% title('Manipulator commanded joint rates');
% xlabel('time [s]'); ylabel('[m/s]');
% leg=legend('$\dot{q}_1$','$\dot q_2$','$\dot q_3$', '$\dot q_4$', '$\dot q_5$', '$\dot q_6$');
% set(leg,'Interpreter','latex')
% grid on;
% 
% subplot(2,2,2);
% plot(time, zeta_c(:,1:6));
% title('Vehichle body commanded velocities');
% xlabel('time [s]'); ylabel('[m/s , deg/s]');
% legend('u','v','w','p','q','r');
% grid on;

% subplot(2,2,3);
% plot(time, [eta1_c(:,:), r2d*eta2_c(:,:)]);
% title('Commanded vehicle position');
% xlabel('time [s]'); ylabel('[m, deg]');
% leg=legend('x','y','z','$\phi$','$\theta$','$\psi$');
% set(leg,'Interpreter','latex');
% grid on;

% subplot(2,2,4);
% plot(time, r2d*q_c(:,:));
% title('Commanded joint angle');
% xlabel('time [s]'); ylabel('angle [deg]');
% leg=legend('$q_1$','$q_2$','$q_3$','$q_4$','$q_5$','$q_6$');
% set(leg,'Interpreter','latex');
% grid on;
% 
% 
% % new figure
% i=i+1;
% h(i)=figure(i);
% set(h(i),'Units','normalized');
% set(h(i),'Position',[0.1,0.3,0.4,0.4]);
% subplot(3,1,1);
% plot(time,x_ee_in_b);
% grid on;
% title('End effector in vehicle frame');
% 
% subplot(3,1,2);
% plot(time,H_trace(:,1:6));
% leg=legend('$x$','$y$','$z$','$\phi$','$\theta$','$\psi$');
% set(leg,'Interpreter','latex');
% grid on;
% title('Diagonal of W matrix for weighted least norm');
% 
% subplot(3,1,3);
% plot(time,H_trace(:,7:12));
% leg=legend('$q_1$','$q_2$','$q_3$','$q_4$','$q_5$','$q_6$');
% set(leg,'Interpreter','latex');
% grid on;
% title('Diagonal of W matrix for weighted least norm');

% %% measured velocities
% i=i+1;
% 
% % end effector
% h(i)=figure(i);
% set(h(i),'Units','normalized');
% set(h(i),'Position',[0.1,0.3,0.4,0.4]);
% 
% subplot(2,2,1);
% plot3(ee_eta1(:,1),ee_eta1(:,2), ee_eta1(:,3));
% title('EE position');
% axis square;
% xlabel('x'); ylabel('y');zlabel('z');
% grid on;
% 
% subplot(2,2,2);
% plot(time, ee_eta1(:,:));
% title('EE position 2d');
% xlabel('time [s]'); ylabel('[m]');
% legend('x','y','z');
% grid on;
% 
% subplot(2,2,3);
% plot(time, r2d*[ee_eta2(:,1),ee_eta2(:,2), ee_eta2(:,3)]);
% title('EE orientation (euler angles)');
% xlabel('time [s]'); ylabel('angle [deg]');
% leg=legend('$\phi$','$\theta$','$\psi$');
% set(leg,'Interpreter','latex');
% grid on;
% 
% subplot(2,2,4);
% plot(time, ee_vel(:,:));
% title('End velocities');
% xlabel('time [s]'); ylabel('[m/s , rad/s]');
% legend('u','v','w','p','q','r');
% grid on;
% 
% new figure
i=i+1;
h(i)=figure(i);
%set(h(i),'Units','normalized');
%set(h(i),'Position',[0.1,0.3,0.4,0.4]);
% 
% subplot(2,2,1);
% plot(time, zeta(:,7:12));
% title('Manipulator joint rates');
% xlabel('time [s]'); ylabel('[m/s]');
% leg=legend('$\dot{q}_1$','$\dot q_2$','$\dot q_3$', '$\dot q_4$', '$\dot q_5$', '$\dot q_6$');
% set(leg,'Interpreter','latex')
% grid on;
% 
% subplot(2,2,2);
% plot(time, zeta(:,1:6));
% title('Vehichle body velocities');
% xlabel('time [s]'); ylabel('[m/s , deg/s]');
% legend('u','v','w','p','q','r');
% grid on;
% 
subplot(2,1,1);

plot(time, [eta1(:,:), r2d*eta2(:,:)]);
title('Vehicle position');
xlabel('time [s]'); ylabel('[m, deg]');
leg=legend('x','y','z','$\phi$','$\theta$','$\psi$');
set(leg,'Interpreter','latex');
grid on;


subplot(2,1,2);
plot(time, r2d*q_log(:,:));
title('Joint angle');
xlabel('time [s]'); ylabel('angle [deg]');
leg=legend('$q_1$','$q_2$','$q_3$','$q_4$','$q_5$','$q_6$');
set(leg,'Interpreter','latex');
grid on;
% 
% %% force
% 
% 
% % new figure
% i=i+1;
% h(i)=figure(i);
% set(h(i),'Units','normalized');
% set(h(i),'Position',[0.1,0.3,0.4,0.4]);
% 
% 
% 
% subplot(2,2,1);
% plot(time, f_ee);
% title('Force in ee frame due to interaction');
% xlabel('time [s]'); ylabel('force [N]');
% legend('X','Y','Z','P','Q','R');
% grid on;
% 
% subplot(2,2,2);
% plot(time, f_config);
% title('Force configspace due to end effector interaction');
% xlabel('time [s]'); ylabel('force [N]');
% leg=legend('x','y','z','$\phi$','$\theta$','$\psi$','$q_1$','$q_2$','$q_3$','$q_4$','$q_5$','$q_6$');
% set(leg,'Interpreter','latex');
% grid on;
% 
% subplot(2,2,3);
% plot(time, tau_c);
% title('Control input \tau_c');
% xlabel('time [s]'); ylabel('force [N]');
% leg=legend('$q_1$','$q_2$','$q_3$','$q_4$','$q_5$','$q_6$');
% set(leg,'Interpreter','latex');
% grid on;
% 
% 
% % new figure
% i=i+1;
% h(i)=figure(i);
% set(h(i),'Units','normalized');
% set(h(i),'Position',[0.1,0.3,0.4,0.4]);
% 
% subplot(2,2,1);
% plot(time, pos_corr);
% title('Position correction term');
% xlabel('time [s]'); ylabel('Position correction [m]');
% legend('u','v','w','p','q','r');
% set(gca,'FontSize',fontsize);
% grid on;
% 
% subplot(2,2,2);
% plot(time, alpha);
% title('alpha');
% xlabel('time [s]'); ylabel('\alpha');
% leg=legend('$\alpha$');
% set(leg,'Interpreter','latex');
% set(gca,'FontSize',fontsize);
% grid on;
% 
% 
% subplot(2,2,3);
% plot(time, ee_pos_corrector.force_norm.Data);
% title('norm(F_{ee})');
% xlabel('time [s]'); ylabel('norm(Force_ee)');
% leg=legend('$\alpha$');
% set(leg,'Interpreter','latex');
% set(gca,'FontSize',fontsize);
% grid on;







