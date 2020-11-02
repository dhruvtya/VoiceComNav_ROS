#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include "aud_com_nav/GoalFromAudio.h"

const float kitchen[2]={3.64,0.9};    //1
const float hall[2]={-3.0,1.0};       //2
const float room1[2]={6.1,-1.4};      //3
const float room2[2]={-6.0,3.4};      //4
const float empty1[2]={1.45,4.14};    //5

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

bool audgoalhandle(aud_com_nav::GoalFromAudio::Request& req, aud_com_nav::GoalFromAudio::Response& res){

  ROS_INFO("Goal request received :");

  MoveBaseClient ac("move_base", true);

  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  float goalCoords[2]={0.0,0.0};
  
  switch(req.audio_goal){
  
    case 1:
      ROS_INFO("Kitchen");
      goalCoords[0] = kitchen[0];
      goalCoords[1] = kitchen[1];
    break;

    case 2:
      ROS_INFO("Hall");
      goalCoords[0] = hall[0];
      goalCoords[1] = hall[1];
    break;

    case 3:
      ROS_INFO("Room 1");
      goalCoords[0] = room1[0];
      goalCoords[1] = room1[1];
    break;

    case 4:
      ROS_INFO("Room 2");
      goalCoords[0] = room2[0];
      goalCoords[1] = room2[1];
    break;

    case 5:
      ROS_INFO("Empty Area");
      goalCoords[0] = empty1[0];
      goalCoords[1] = empty1[1];
    break;

    default:
      ROS_INFO("Invalid Goal, going to home position (Hall)");
      goalCoords[0] = hall[0];
      goalCoords[1] = hall[1];
  }

  goal.target_pose.pose.position.x = goalCoords[0];
  goal.target_pose.pose.position.y = goalCoords[1];
  goal.target_pose.pose.orientation.w = 1.0;
 
  ac.sendGoal(goal);
  ac.waitForResult();

  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("Reached goal");
    ros::spinOnce();
  }
  else
    ROS_INFO("Failed to reach the goal");

  return true;

}


int main(int argc, char** argv){
  
  ros::init(argc, argv, "aud_com_nav");

  ros::NodeHandle n;

  ros::ServiceServer aud_goal_service = n.advertiseService("/aud_com_nav/goal_service", audgoalhandle);

  ros::spin();

  return 0;

}
