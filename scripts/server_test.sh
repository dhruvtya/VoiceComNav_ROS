#!/bin/sh

xterm  -e  " roslaunch turtlebot3_gazebo turtlebot3_house.launch" &
sleep 5
xterm  -e  " roslaunch turtlebot3_navigation turtlebot3_navigation.launch" &
sleep 5
xterm  -e  " rosrun aud_com_nav aud_com_nav"  
