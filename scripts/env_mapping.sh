#!/bin/sh

xterm  -e  " roslaunch turtlebot3_gazebo turtlebot3_house.launch" &
sleep 5
xterm  -e  " roslaunch turtlebot3_bringup turtlebot3_lidar.launch" &
sleep 5
xterm  -e  " rosrun gmapping slam_gmapping scan:=base_scan _base_frame:=base_footprint" &
sleep 5
#xterm  -e  " roslaunch turtlebot3_teleop turtlebot3_teleop_key.launch" &
#sleep 5
xterm  -e  " roslaunch rvizconfig rviz_config.launch" 

