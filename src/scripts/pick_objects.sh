#!/bin/bash

./test_navigation.sh
# Launch the pick_objects node
cd ../../
roslaunch turtlebot_gazebo turtlebot_world.launch
roslaunch turtlebot_gazebo  amcl_demo.launch
roslaunch turtlebot_rviz_launchers view_navigation.launch
rosrun pick_objects pick_objects_node

