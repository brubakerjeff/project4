#!/bin/bash


#./test_navigation.sh
# Launch the pick_objects node
cd ../../
source devel/setup.bash
xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 15
xterm -e "roslaunch turtlebot_gazebo  amcl_demo.launch" &
sleep 15
xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 15
xterm -e "rosrun add_markers add_markers_node"


