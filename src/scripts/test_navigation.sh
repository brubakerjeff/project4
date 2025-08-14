cd ../../
source devel/setup.bash
roslaunch my_robot world.launch &
sleep 15
roslaunch my_robot  amcl.launch &
sleep 15
roslaunch my_robot view_navigation.launch &