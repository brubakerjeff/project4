# Parts of the program
# Launch Gazebo so we have our simulation
## roslaunch my_robot world.launch &
# Launch Adaptive Monte Carlo to localize us
## roslaunch my_robot  amcl.launch &
# Launch RVIZ
## roslaunch turtlebot_rviz_launchers view_navigation.launch &
# Launch the node that instructs the robot to follow the markers
## rosrun pick_objects pick_objects_node &
# Launch the node to add the markers
## rosrun add_markers add_markers_node &
