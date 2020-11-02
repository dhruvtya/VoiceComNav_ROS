#include <ros/ros.h>
#include <std_msgs/String.h>
#include "aud_com_nav/GoalFromAudio.h"

ros::ServiceClient aud_client;

void audio_callback(const std_msgs::String aud_msg){
  ROS_INFO("Audio command heard : %s", aud_msg.data.c_str());
  aud_com_nav::GoalFromAudio aud_srv;
 
  if(aud_msg.data.c_str()=="kitchen")
     aud_srv.request.audio_goal = 1;
  else if(aud_msg.data.c_str()=="hall")
     aud_srv.request.audio_goal = 2;
  else if(aud_msg.data.c_str()=="room one")
     aud_srv.request.audio_goal = 3;
  else if(aud_msg.data.c_str()=="empty two")
     aud_srv.request.audio_goal = 5;
  else
  {
     ROS_INFO("Going to default hall position");
     aud_srv.request.audio_goal = 2;
  }

  if(!aud_client.call(aud_srv))
        ROS_ERROR("Failed to call service safe_move");

}

int main(int argc,char** argv){

  ros::init(argc, argv, "aud_client_node");

  ros::NodeHandle n;

  aud_client = n.serviceClient<aud_com_nav::GoalFromAudio>("/aud_com_nav/goal_service");

  ros::Subscriber aud_sub = n.subscribe("/output",1,audio_callback);

  ros::spin();

  return 0;
}
