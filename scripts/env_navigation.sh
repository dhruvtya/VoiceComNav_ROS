#!/bin/sh

xterm  -e  " roslaunch turtlebot3_gazebo turtlebot3_house.launch" &
sleep 5
xterm  -e  " roslaunch turtlebot3_teleop turtlebot3_teleop_key.launch" &
sleep 5
xterm  -e  " roslaunch turtlebot3_navigation turtlebot3_navigation.launch" 


