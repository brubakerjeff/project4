#!/bin/bash


#./test_navigation.sh
# Launch the pick_objects node
cd ../../
#rosrun add_markers add_markers_node
roslaunch turtlebot_gazebo turtlebot_world.launch &
sleep 15
roslaunch turtlebot_gazebo  amcl_demo.launch &
sleep 15
roslaunch turtlebot_rviz_launchers view_navigation.launch &
sleep 45
rosrun add_markers add_markers_node


