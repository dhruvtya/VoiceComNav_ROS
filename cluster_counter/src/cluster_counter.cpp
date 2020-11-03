#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;


const float thresh_dist = 0.2;  //Threshold Distance between 2 consecutive 'Non-infinity' points to consider them different clusters


// Callback function - subscribes to laser scan
void cluster_callback(const sensor_msgs::LaserScan::ConstPtr& lsrscan_msg){

  int numOfClusters = 0;    //Number of Clusters Counter
  vector<int> numOfPoints;  //Number of Points for Each Cluster

  int length_range = 360;   //Length of Ranges array from Laser Scan;
  ROS_INFO("Length of Array = %d",length_range);

  bool prev_inf;            //To check if previous scan point value was infinity or not

  // For First-last Concatenation (Explained Later)
  float x_first=0.0,x_last=0.0;
  float y_first=0.0,y_last=0.0;
  //

  // For x,y coordinates of each point
  float x_prev=0.0,x_curr=0.0;
  float y_prev=0.0,y_curr=0.0;
  float theta;
  float distance;
 

  // To check for and store the first point before loop is started
  if(isfinite(lsrscan_msg->ranges[0])){
    numOfClusters++;
    numOfPoints.push_back(1);

    prev_inf = false;
    theta = lsrscan_msg->angle_min;

    x_prev = lsrscan_msg->ranges[0]*cos(theta);
    y_prev = lsrscan_msg->ranges[0]*sin(theta);

    // For First-last Concatenation
    x_first = x_prev;
    y_first = y_prev;
    //

  }
  else{prev_inf = true;}


//////// Loop to check each point and find where new clusters start
  for(int i=1;i<length_range;i++){
    
     //If the point is a Finite value only then coordinates and cluster check would be done
     if(isfinite(lsrscan_msg->ranges[i])){
	theta = lsrscan_msg->angle_min + (i*lsrscan_msg->angle_increment);

	x_curr = lsrscan_msg->ranges[i]*cos(theta);
	y_curr = lsrscan_msg->ranges[i]*sin(theta);
	
	// For First-last Concatenation
	if(numOfClusters==0){
	  x_first = x_curr;
	  y_first = y_curr;
	}
	//


	if(prev_inf==false){
	    distance = sqrt(pow((x_curr-x_prev),2)+pow((y_curr-y_prev),2));
	    if(distance>thresh_dist){
		numOfClusters++;
		numOfPoints.push_back(1);
	    }
	    else{numOfPoints[numOfClusters-1]++;}
	}
	else{
	    numOfClusters++;
	    numOfPoints.push_back(1);
	}
	x_prev = x_curr;
	y_prev = y_curr;
	prev_inf = false;
    }

    //Else the point is infinity, update prev_inf to true
    else{prev_inf=true;}
  }
//////// Loop End -------------------



//////// First-last Concatenation
/*
The sweep is 360 degrees. This means that the point at the start
of the sweep and the end of the sweep CAN be of the same cluster.

The loop above will treat them aas different clusters.

Below function checks if first and last points are within the threshold distance.
If yes, they are treated as the same cluster and no. of points for both are added. 
*/

  x_last = x_prev;
  y_last = y_prev;

  distance = sqrt(pow((x_first-x_last),2)+pow((y_first-y_last),2));
  if(distance<=thresh_dist){
     numOfClusters--;
     numOfPoints.front()=numOfPoints.front()+numOfPoints.back();
     numOfPoints.pop_back();
  }
  else{}
////////



  //Print values of cluster and points
  ROS_INFO("No. of Clusters : %d", numOfClusters);
  ROS_INFO("No. of Points in ");
  for(int j=0;j<numOfPoints.size();j++){
    
    ROS_INFO("Cluster %d : %d points", j+1, numOfPoints[j]);

  }
  ROS_INFO("---------------");
  //
}




int main(int argc, char** argv){

  ros::init(argc, argv, "cluster_counter");
  ros::NodeHandle n;

  // Subscriber to the laser scan on /scan topic
  ros::Subscriber cluster_sub = n.subscribe("/scan",1,cluster_callback);

  ros::spin();
  return 0;
}
