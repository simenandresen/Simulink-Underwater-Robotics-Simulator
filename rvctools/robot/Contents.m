% Robotics Toolbox.
% Version 9.8.0  2013-02-12
%
%
% Homogeneous transformations
%    angvec2r                   - angle/vector to RM
%    angvec2tr                  - angle/vector to HT
%    eul2r                      - Euler angles to RM
%    eul2tr                     - Euler angles to HT
%    oa2r                       - orientation and approach vector to RM
%    oa2tr                      - orientation and approach vector to HT
%    r2t                        - RM to HT
%    rt2tr                      - (R,t) to HT
%    rotx                       - RM for rotation about X-axis
%    roty                       - RM for rotation about Y-axis
%    rotz                       - RM for rotation about Z-axis
%    rpy2r                      - roll/pitch/yaw angles to RM
%    rpy2tr                     - roll/pitch/yaw angles to HT
%    se2                        - HT in SE(2)
%    t2r                        - HT to RM
%    tr2angvec                  - HT/RM to angle/vector form
%    tr2eul                     - HT/RM to Euler angles
%    tr2rpy                     - HT/RM to roll/pitch/yaw angles
%    tr2rt                      - HT to (R,t)
%    tranimate                  - animate a coordinate frame
%    transl                     - set or extract the translational component of HT
%    trnorm                     - normalize HT
%    trplot                     - plot HT as a coordinate frame
%    trplot2                    - plot HT, SE(2), as a coordinate frame
%    trprint                    - print an HT
%    trotx                      - HT for rotation about X-axis
%    troty                      - HT for rotation about Y-axis
%    trotz                      - HT for rotation about Z-axis
%
% Homogeneous points and lines
%    e2h                        - Euclidean coordinates to homogeneous
%    h2e                        - homogeneous coordinates to Euclidean
%    homline                    - create line from 2 points
%    homtrans                   - transform points
%
%  * HT = homogeneous transformation, a 4x4 matrix, belongs to the group SE(3).
%  * RM = RM, an orthonormal 3x3 matrix, belongs to the group SO(3).
%  * Functions of the form <b>tr2XX</b> will also accept a RM as the argument.
%
% Differential motion
%    delta2tr                   - differential motion vector to HT
%    eul2jac                    - Euler angles to Jacobian
%    rpy2jac                    - RPY angles to Jacobian
%    skew                       - vector to skew symmetric matrix
%    tr2delta                   - HT to differential motion vector
%    tr2jac                     - HT to Jacobian
%    vex                        - skew symmetric matrix to vector
%    wtrans                     - transform wrench between frames
%
% Trajectory generation
%    ctraj                      - Cartesian trajectory
%    jtraj                      - joint space trajectory
%    lspb                       - 1D trapezoidal trajectory
%    mtraj                      - multi-axis trajectory for arbitrary function
%    mstraj                     - multi-axis multi-segment trajectory
%    tpoly                      - 1D polynomial trajectory
%    trinterp                   - interpolate HT s
%
% Quaternion
%    Quaternion                 - constructor
%    /                          - divide quaternion by quaternion or scalar
%    *                          - multiply quaternion by a quaternion or vector
%    inv                        - invert a quaternion
%    norm                       - norm of a quaternion
%    plot                       - display a quaternion as a 3D rotation
%    unit                       - unitize a quaternion
%    interp                     - interpolate a quaternion
%
% Serial-link manipulator
%    SerialLink                 - construct a serial-link robot object
%    Link                       - construct a robot link object
%    Revolute                   - construct a revolute robot link object
%    Prismatic                  - construct a prismatic robot link object
%    *                          - compound two robots
%    friction                   - return joint friction torques
%    nofriction                 - return a robot object with no friction
%    perturb                    - return a robot object with perturbed parameters
%    plot                       - plot/animate robot
%    teach                      - drive a graphical  robot
%    CodeGenerator              - create efficient run-time kinematic and dynamics code
%
%     Models
%        mdl_ball               - high order ball shaped mechanism
%        mdl_coil               - high order coil shaped mechanism
%        mdl_Fanuc10L           - Fanuc 10L (DH, kine)
%        mdl_MotomanHP6         - Motoman HP6 (DH, kine)
%        mdl_phantomx           - Trossen Robotics PhantomX pincher
%        mdl_puma560            - Puma 560 data (DH, kine, dyn)
%        mdl_puma560_3          - Puma 560, first 3 joints, kine only
%        mdl_puma560_3_sym      - Puma 560, first 3 joints, symbolic, kine only
%        mdl_puma560akb         - Puma 560 data (MDH, kine, dyn)
%        mdl_p8                 - Puma 6-axis robot on a 2-axis XY base
%        mdl_S4ABB2p8           - ABB S4 2.8 (DH, kine)
%        mdl_stanford           - Stanford arm data (DH, kine, dyn)
%        mdl_twolink            - simple 2-link example (DH, kine)
%        DHFactor               - convert elementary transformations to DH form
%
%     Kinematic
%        DHFactor               - transform sequence to DH description
%        fkine                  - forward kinematics
%        ikine                  - inverse kinematics (numeric)
%        ikine6s                - inverse kinematics for 6-axis arm with sph.wrist
%        jacob0                 - Jacobian in base coordinate frame
%        jacobn                 - Jacobian in end-effector coordinate frame
%        maniplty               - compute manipulability
%
%     Dynamics
%        accel                  - forward dynamics
%        cinertia               - Cartesian manipulator inertia matrix
%        coriolis               - centripetal/coriolis torque
%        fdyn                   - forward dynamics
%        wtrans                 - transform a force/moment
%        gravload               - gravity loading
%        inertia                - manipulator inertia matrix
%        itorque                - inertia torque
%        rne                    - inverse dynamics
%
% Mobile robot
%    Map                        - point feature map object
%    RandomPath                 - driver for Vehicle object
%    RangeBearingSensor         - "laser scanner" object
%    Vehicle                    - construct a mobile robot object
%    sl_bicycle                 - Simulink "bicycle model" of non-holonomic wheeled vehicle
%    Navigation                 - Navigation superclass
%    Sensor                     - robot sensor superclass
%    plot_vehicle               - plot vehicle
%    makemap                    - make a map, occupancy grid
%    mdl_quadcopter             - simple quadcopter model
%    sl_quadrotor               - Simulink model of a flying quadrotor
%
%     Localization
%        EKF                    - extended Kalman filter object
%        ParticleFilter         - Monte Carlo estimator
%
%     Path planning
%        Bug2                   - bug navigation
%        DXform                 - distance transform from map
%        Dstar                  - D* planner
%        PRM                    - probabilistic roadmap planner
%        RRT                    - rapidly exploring random tree
%
% Graphics
%    plot2                      - plot trajectory
%    plotp                      - plot points
%    plot_arrow                 - draw an arrow
%    plot_box                   - draw a box
%    plot_circle                - draw a circle
%    plot_ellipse               - draw an ellipse
%    plot_homline               - plot homogeneous line
%    plot_point                 - plot points
%    plot_poly                  - plot polygon
%    plot_sphere                - draw a sphere
%    qplot                      - plot joint angle trajectories
%    plot2                      - Plot trajectories
%    plotp                      - Plot trajectories
%    xaxis                      - set x-axis scaling
%    yaxis                      - set y-axis scaling
%    xyzlabel                   - label axes x, y and z
%
% Utility
%    about                      - summary of object size and type
%    angdiff                    - subtract 2 angles modulo 2pi
%    bresenham                  - Bresenhan line drawing
%    circle                     - compute/draw points on a circle
%    colnorm                    - columnwise norm of matrix
%    diff2                      - elementwise diff
%    distancexform              - compute distance transform
%    edgelist                   - list of edge pixels
%    gauss2d                    - Gaussian distribution in 2D
%    ishomog                    - true if argument is a 4x4 matrix
%    ismatrix                   - true if non scalar
%    isrot                      - true if argument is a 3x3 matrix
%    isvec                      - true if argument is a 3-vector
%    numcols                    - number of columns in matrix
%    numrows                    - number of rows in matrix
%    peak                       - find peak in 1D signal
%    peak2                      - find peak in 2D signal
%    PGraph                     - general purpose graph class
%    polydiff                   - derivative of polynomial
%    Polygon                    - general purpose polygon class
%    randinit                   - initialize random number generator
%    ramp                       - create linear ramp
%    runscript                  - interactively run a script or demo
%    unit                       - unitize a vector
%    tb_optparse                - toolbox argument parser
%
%     CodeGen support
%        distributeblocks       - distribute blocks in a Simulink library
%        doesblockexist         - checks if a Simulink block exists
%        multidfprintf          - fprintf to multiple files
%        symexpr2slblock        - embedded Matlab symbolic functions
%        simulinkext            - determine extension of Simulink files
%
% Demonstrations
%    rtbdemo                    - Serial-link manipulator demonstration
%    tripleangle                - GUI to demonsrate triple angle rotations
%
% Examples
%    sl_quadcopter              - Simulink model of a flying quadcopter
%    sl_braitenberg             - Simulink model a Braitenberg vehicle
%    movepoint                  - non-holonomic vehicle moving to a point
%    moveline                   - non-holonomic vehicle moving to a line
%    movepose                   - non-holonomic vehicle moving to a pose
%    walking                    - example of 4-legged walking robot
%    eg_inertia                 - joint 1 inertia I(q1,q2)
%    eg_inertia22               - joint 2 inertia I(q3)
%    eg_grav                    - joint 2 gravity load g(q2,q3)
%
%  *  located in the examples folder
%
% Copyright (C) 2011 Peter Corke
