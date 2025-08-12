cd ../../
source devel/setup.bash
roslaunch my_robot world.launch &
sleep 15
roslaunch my_robot  amcl.launch &
sleep 15
roslaunch my_robot view_navigation.launch &
sleep 15
rosrun pick_objects pick_objects_node &
sleep 15
rosrun add_markers add_markers_node &
sleep 15
