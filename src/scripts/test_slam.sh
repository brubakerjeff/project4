(
    cd ../..
    source devel/setup.bash
    xterm -e "roslaunch my_robot world.launch " &
    sleep 5
    xterm -e "roslaunch ./src/my_robot/launch/gmapping.launch"  &
    sleep 5
    xterm -e "roslaunch ./src/turtlebot_interactions/turtlebot_rviz_launchers/launch/view_navigation.launch " &
    sleep 5
    xterm -e "roslaunch ./src/turtlebot/turtlebot_teleop/launch/keyboard_teleop.launch " &
    sleep 5
)
