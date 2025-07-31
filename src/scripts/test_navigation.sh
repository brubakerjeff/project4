(
    cd ../..
    source devel/setup.bash
    roslaunch ./src/turtlebot_simulator/turtlebot_gazebo/launch/turtlebot_world.launch &
    roslaunch ./src/turtlebot_simulator/turtlebot_gazebo/launch/amcl_demo.launch &
    roslaunch ./src/turtlebot_simulator/turtlebot_gazebo/view_navigation.launch &
)