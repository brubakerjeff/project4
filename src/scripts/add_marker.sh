#!/bin/bash


#./test_navigation.sh
# Launch the pick_objects node
cd ../../
source devel/setup.bash
xterm -e "roslaunch my_robot world.launch" &
sleep 15
xterm -e "roslaunch my_robot  amcl.launch" &
sleep 15
xterm -e "roslaunch my_robot view_navigation.launch" &
sleep 15
xterm -e "rosrun add_markers add_markers_node"


