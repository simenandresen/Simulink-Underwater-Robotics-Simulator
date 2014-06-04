Underwater Vehicle-Manipulator Simulator
======================================



This simulator is for simulating the dynamics of an Underwater Vehicle-Manipulator System (UVMS). 
The simulator is implemented in Matlab/Simulink and is tested for Matlab version 2013.

### Content



* initUVMS.m
>initialization script. Run this one time to set path variables.

* run_simulation.m
>Matlab script to initialize and run simulation. Entry point of simulation.

* uvms_config.ini
>Configuration file for the simulator. Holds path variables and simulation time

* uvms_functions
>Includes misc matlab scripts and functions for UVMS transformations and initialization of simulation

* data
>Directory with trajectory and polygon mesh data

* uvms_total.mdl
> Simulink diagram with the simulator of the UVMS and controllers.

* 3rdparty
>Includes the Robotics, Vision & Control toolbox for visualization 
>Includes gnc library functions



### Issues
The simulator will not work with Matlab version 2011 or below, as these versions does not support timeseries.


~~~´\/`~~~´\/`~~~´\/`~~~´\/`~~~´\/`~~~´\/`~~~~
~~~´\/`~~~´\/`~~~´\/`~~~´\/`~~~´\/`~~~´\/`~~~~


   	>=X>						>o=>
  _____________
 |\            \         ____
 | \____________\       /    \	      ___
 | |            |      /      \ _ ___|
 \ |            |_____/              |___
  \|____________|				  

						<OO<

______________________________________________



