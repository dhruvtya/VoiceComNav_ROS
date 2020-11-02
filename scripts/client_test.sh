#!/bin/sh

xterm  -e  " roslaunch turtlebot3_gazebo turtlebot3_house.launch" &
sleep 5
xterm  -e  " roslaunch turtlebot3_navigation turtlebot3_navigation.launch" &
sleep 5
xterm  -e  " roslaunch pocketsphinx pocketsphinx.launch" &
sleep 5
xterm  -e  " rosrun aud_com_nav aud_com_nav" &
sleep 5
xterm  -e  " rosrun aud_com_nav aud_client_node" &
sleep 5
xterm  -e  " rostopic echo /output" 
