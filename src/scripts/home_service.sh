cd ../../
roslaunch turtlebot_gazebo turtlebot_world.launch &
sleep 15
roslaunch turtlebot_gazebo  amcl_demo.launch &
sleep 15
roslaunch turtlebot_rviz_launchers view_navigation.launch &
read -p "add marker in rviz"
rosrun add_markers add_markers_node
rosrun picks_objects pick_objects_node
