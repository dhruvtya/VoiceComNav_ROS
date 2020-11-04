# VoiceComNav_ROS
ROS Project - Voice command navigation for turtlebot3 

### Intro :
In this project, the turtlebot3 and pocketsphinx packages are used to achieve navigation with Voice Commands.
The voice commands can be given through an audio stream with a mic or an audio (WAV) file.

Example voice command : "kitchen"
Output : The robot will navigate to a pre-defined position in the kitchen area and wait there for the next command.

### Output Screenshot :
![Kitchen](https://github.com/dhruvtya/VoiceComNav_ROS/blob/main/kitchennav.JPG)

### Point Cloud Cluster Counter :
The project also has a cluster_counter package.

It uses 2D raw data from /scan topic (LaserScan) to calculate the number of clusters and the number of points in each cluster.

### Output of Cluster Counter :
![EmptyAreaCluster](https://github.com/dhruvtya/VoiceComNav_ROS/blob/main/Empty%202%20Clusters.JPG)

## Steps to Implement :

### Version : Ubuntu 18.04 & ROS Melodic
#### Have xterm terminal installed (```sudo apt-get install xterm```)

1. Clone the repository folders directly into your catkin_ws/src folder.
2. Only aud_com_nav, cluster_counter, scripts and maps folder can be copied into your src.
3. The turtlebot3, turtlebot3_simulations, turtlebot3_msgs and pocketsphinx can be downloaded from their respective official repos.
4. Make sure all dependencies for the packages in point 3 are installed.
5. Copy the contents of maps folder to turtlebot3/turtlebot3_navigation/maps, rename both the files so that this directory should have map.pgm and map.yaml.
6. Edit ~/.bashrc and put the following code at the very end : ```export TURTLEBOT3_MODEL=burger```
7. cd back to your catkin_ws and execute ```catkin_make```
8. cd to the src/scripts/ folder in the terminal
9. Execute the command : ```./final.sh```
