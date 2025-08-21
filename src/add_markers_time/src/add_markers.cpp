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
double pickup[2] = {1.25218,-4.156599};
double dropOff[2] = {3.431139,-1.530365};
// %Tag(INIT)%
enum State {
  HELLO,
  PICK,
  CARRYING,
  DROP,
  END
} state = HELLO;
int main( int argc, char** argv )
{
    ros::init(argc, argv, "add_markers_time");
    ros::NodeHandle nh;
    ros::Publisher marker_pub = nh.advertise<visualization_msgs::Marker>("visualization_marker", 1);

    ros::Rate r(1);  // 1 Hz rate just to not hammer the system

    visualization_msgs::Marker marker;
    marker.header.frame_id = "base_link";
    marker.header.stamp = ros::Time::now();
    marker.ns = "toggle_marker";
    marker.id = 0;
    marker.type = visualization_msgs::Marker::CUBE;
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

    marker.lifetime = ros::Duration();  // Forever
    marker.pose.position.x = pickup[0];
    marker.pose.position.y = pickup[1];
    marker_pub.publish(marker);  
    bool visible = true;
    ros::Time last_toggle_time = ros::Time::now();

    while (ros::ok())
    {
        ros::Time current_time = ros::Time::now();
        if ((current_time - last_toggle_time).toSec() >= 5.0) {
            if(state == HELLO) {
                //Show the marker at the drop off zone since the robot just arrived at the pick up zone
                ROS_INFO("Publishing marker at pickup zone");
                marker.action = visualization_msgs::Marker::ADD;
                marker.pose.position.x = pickup[0];
                marker.pose.position.y = pickup[1];
                marker_pub.publish(marker);  
                state = PICK;
            } else if(state==PICK) {
                ROS_INFO("Switching to carrying");
                sleep(5);
                state = CARRYING;
                marker.action = visualization_msgs::Marker::DELETE;   
                marker.pose.position.x = pickup[0];
                marker.pose.position.y = pickup[1]; 
                marker_pub.publish(marker);   
                ROS_INFO("Cube removed from pickup zone.");
            } else if (state == CARRYING) {
                    ROS_INFO("Switching to drop off");
                    sleep(5);
                    state = DROP;
            }
            else if (state == DROP) {
                ROS_INFO("Cube placed at drop off zone.");
                marker.action = visualization_msgs::Marker::ADD;   
                marker.pose.position.x = dropOff[0];
                marker.pose.position.y = dropOff[1]; 
                marker_pub.publish(marker);  
                state = END;
            }

            last_toggle_time = current_time;
        }

        marker.header.stamp = ros::Time::now();  // Update timestamp
        marker_pub.publish(marker);

        ros::spinOnce();
        r.sleep();
    }

    return 0;

}


