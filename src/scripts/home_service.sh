cd ../../
source devel/setup.bash
xterm -e "roslaunch my_robot world.launch" &
sleep 15
xterm -e "roslaunch my_robot  amcl.launch" &
sleep 15
xterm -e "roslaunch my_robot view_navigation.launch;pause;" &
sleep 15
xterm -e "rosrun add_markers add_markers_node;pause;" &
sleep 15
rosparam /set /use_sim_time true
xterm -e "rosrun pick_objects pick_objects_node;pause;" &
sleep 15
