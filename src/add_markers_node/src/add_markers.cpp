/*
 * Copyright (c) 2010, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

// %Tag(FULLTEXT)%
// %Tag(INCLUDES)%
#include "nav_msgs/Odometry.h"
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
// %EndTag(INCLUDES)%
double pose[2] = {0,0};
uint8_t robotState = 0;
long counter=0;
long counter2=0;
void poseCallBack(const nav_msgs::Odometry::ConstPtr& msg) {
  pose[0] =msg->pose.pose.position.x;
  pose[1] =msg->pose.pose.position.y;
  if(counter%5000==0)
  {
    ROS_INFO("Robot State %f %f" ,pose[0],pose[1] );
  }
  counter=counter+1; 
}



double pickup[2] = {0.546197,2.317277};
double dropOff[2] = {-0.546197,-5.826971};

double getdistance(double goal[2])
{
  double dx = goal[0]-pose[0];
  double dy = goal[1]-pose[1];
  if(counter2%5000==0)
  {  
    ROS_INFO("Distance  %0.2f" ,sqrt(dx*dx + dy*dy) );
    
  }
  counter2=counter2+1;
  return sqrt(dx*dx + dy*dy);
}

bool atPickUpZone() {
  return getdistance(pickup) < 0.2;
}

bool atDropOff() {
  return getdistance(dropOff) < 0.2;
}

enum State {
  HELLO,
  PICK,
  CARRYING,
  DROP
} state = HELLO;
// %Tag(INIT)%
int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
// %EndTag(INIT)%
  ros::Subscriber pose_sub = n.subscribe("/odom",10,poseCallBack);
  // Set our initial shape type to be a cube
// %Tag(SHAPE_INIT)%
  uint32_t shape = visualization_msgs::Marker::CUBE;
// %EndTag(SHAPE_INIT)%

// %Tag(MARKER_INIT)%
  while (ros::ok())
  {
    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "/map";
    marker.header.stamp = ros::Time::now();
// %EndTag(MARKER_INIT)%

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
// %Tag(NS_ID)%
    marker.ns = "add_markers";
    marker.id = 0;
// %EndTag(NS_ID)%

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
// %Tag(TYPE)%
    marker.type = shape;
    marker.action = visualization_msgs::Marker::ADD;
    marker.pose.position.x = pickup[0];
    marker.pose.position.y = pickup[1];
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
// %Tag(SCALE)%
    marker.scale.x = 0.2;
    marker.scale.y = 0.2;
    marker.scale.z = 0.2;
// %EndTag(SCALE)%

    // Set the color -- be sure to set alpha to something non-zero!
// %Tag(COLOR)%
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN("Please create a subscriber to the marker");
      sleep(1);
    }
    
    ros::spinOnce();
    // Going to pick up zone. There is nodependency on ODM for the first state
    if(state == HELLO) {
      //Show the marker at the drop off zone since the robot just arrived at the pick up zone
      ROS_INFO("Publishing marker at pickup zone");
      marker.action = visualization_msgs::Marker::ADD;
      marker.pose.position.x = pickup[0];
      marker.pose.position.y = pickup[1];
      marker_pub.publish(marker);  
      state = PICK;
    } else if(state==PICK) {
        if(atPickUpZone()) {
          ROS_INFO("Switching to carrying");
          sleep(5);
          state = CARRYING;
          marker.action = visualization_msgs::Marker::DELETE;   
          marker.pose.position.x = pickup[0];
          marker.pose.position.y = pickup[1]; 
          marker_pub.publish(marker);   
          ROS_INFO("Cube removed from pickup zone.");
       
      }
    } else if (state == CARRYING) {

      if(atDropOff()) {
        ROS_INFO("Switching to drop off");
        sleep(5);
        state = DROP;
      }
    }
    else if (state == DROP) {
      ROS_INFO("Cube placed at drop off zone.");
      marker.action = visualization_msgs::Marker::ADD;   
      marker.pose.position.x = dropOff[0];
      marker.pose.position.y = dropOff[1]; 
      marker_pub.publish(marker);  
    }
  }

}


