#!/bin/sh

xterm  -e  " roslaunch turtlebot3_gazebo turtlebot3_house.launch" &
sleep 5
xterm  -e  " roslaunch turtlebot3_navigation turtlebot3_navigation.launch" &
sleep 5
xterm  -e  " roslaunch pocketsphinx pocketsphinx.launch" &
sleep 5
xterm  -e  " roslaunch aud_com_nav VoiceComNav.launch" &
sleep 5
xterm  -e  " roslaunch cluster_counter ClusterCounter.launch" 
