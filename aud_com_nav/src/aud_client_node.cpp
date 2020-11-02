#include <ros/ros.h>
#include <std_msgs/String.h>
#include "aud_com_nav/GoalFromAudio.h"
#include <string>

ros::ServiceClient aud_client;

void audio_callback(const std_msgs::String::ConstPtr& aud_msg){
  ROS_INFO("Audio command heard : %s", aud_msg->data.c_str());
  aud_com_nav::GoalFromAudio aud_srv;
  const std::string aud_msg_str = aud_msg->data.c_str();
//  ROS_INFO("Audio command heard : %s", aud_msg_str); 

  if(aud_msg_str=="kitchen")
     {aud_srv.request.audio_goal = 1;}
  else if(aud_msg_str=="hall")
     {aud_srv.request.audio_goal = 2;}
  else if(aud_msg_str=="room")
     {aud_srv.request.audio_goal = 3;}
  else if(aud_msg_str=="empty")
     {aud_srv.request.audio_goal = 6;}
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
