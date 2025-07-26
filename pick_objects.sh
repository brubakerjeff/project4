#!/bin/bash

# Launch the robot simulation
roslaunch turtlebot_gazebo turtlebot_world.launch &

# Launch the AMCL node for localization
roslaunch turtlebot_navigation amcl.launch map_file:=/path/to/your/map.yaml &

# Launch RViz for visualization
roslaunch turtlebot_rviz_launchers view_navigation.launch &

# Launch the pick_objects node
rosrun pick_objects_node pick_objects_node

