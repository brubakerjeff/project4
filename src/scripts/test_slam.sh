(
    cd ../..
    source devel/setup.bash
    xterm -e "roslaunch my_robot world.launch " &
    sleep 5
    xterm -e "roslaunch ./src/my_robot/launch/gmapping.launch"  &
    sleep 5
    xterm -e "roslaunch ./src/my_robot/launch/view_navigation.launch " &
    sleep 5
    xterm -e "roslaunch ./src/my_robot/launch/keyboard.launch " &
    sleep 5
)
