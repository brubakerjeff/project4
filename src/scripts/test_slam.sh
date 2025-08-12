(
    cd ../..
    source devel/setup.bash
    xterm -e "roslaunch my_robot world.launch " &
    sleep 5
    xterm -e "roslaunch ./src/turtlebot_simulator/turtlebot_gazebo/launch/gmapping_demo.launch " &
    sleep 5
    xterm -e "roslaunch ./src/turtlebot_interactions/turtlebot_rviz_launchers/launch/view_navigation.launch " &
    sleep 5
    xterm -e "roslaunch ./src/turtlebot/turtlebot_teleop/launch/keyboard_teleop.launch " &
    sleep 5
)
