#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
 
// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

double pickup[2] = {0.0,0.0};
double dropOff[2] = {0.4,0.4};

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal start;

  // set up the frame parameters
  start.target_pose.header.frame_id = "map";
  start.target_pose.header.stamp = ros::Time::now();
  
  // Define a position and orientation for the robot to reach
  start.target_pose.pose.position.x = pickup[0];
  start.target_pose.pose.position.y = pickup[1];
  start.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal");
  ac.sendGoal(start);
  
  // Wait an infinite time for the results
  ac.waitForResult();
  
  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Reached pickup zone");
  else
    ROS_INFO("The robot failed to move for some reason.");
  
  move_base_msgs::MoveBaseGoal goal2;

  // set up the frame parameters
  goal2.target_pose.header.frame_id = "map";
  goal2.target_pose.header.stamp = ros::Time::now();
  
  // Define a position and orientation for the robot to reach
  goal2.target_pose.pose.position.x = dropOff[0];
  goal2.target_pose.pose.position.y = dropOff[1];
  goal2.target_pose.pose.orientation.w = 1.0;
   // Send the goal position and orientation for the robot to reach

  ROS_INFO("Sending goal");
  ac.sendGoal(goal2);
  ac.waitForResult();
  
  ROS_INFO("Display messages to track if robot suceessfully reached both zones");
  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Reached Drop-Off Zone");
  else
    ROS_INFO("The robot failed to move for some reason.");


  return 0;
}