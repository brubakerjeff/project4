# Parts of the program
# Launch Gazebo
## roslaunch my_robot world.launch &
# Launch Adaptive Monte Carlo
## roslaunch my_robot  amcl.launch &
# Launch RVIZ
## roslaunch turtlebot_rviz_launchers view_navigation.launch &
# Launch the node that instructs the robot to follow the markers
## rosrun pick_objects pick_objects_node &
# Launch the node to add the marker
## rosrun add_markers add_markers_node &
