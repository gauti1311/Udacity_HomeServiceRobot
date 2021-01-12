# UD_Home_Service_Robot
An Udacity Nano-degree project for Home Service Autonomous robot navigating in a simulated environment performing SLAM and Path planning using ROS and Gazebo packages.

## Installation and Build

```
$ mkdir -p catkin_ws/src
$ cd catkin_ws/src
$ catkin_init_workspace
$ git clone https://github.com/gauti1311/UD_Home_Service_Robot.git
$ cd ..
$ catkin_make
```

Install all packages dependencies with 
```
$ rosdep install [package_name]
```

## Run 
```
$ cd catkin_ws/src/scripts
$ chmod +x home_service.sh
$ ./home_service.sh
```

A Gazebo world and RViz will open with turtlebot in simulated environment the robot will navigate autonomously to pick an object (virtual marker) from pickup location then drop it at desitnation and marker appears again.

![UD_Home_Service_Robot](demo.gif) 
