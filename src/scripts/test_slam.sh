(
    cd ../..
    source devel/setup.bash
    xterm -e "roslaunch my_robot world.launch " &
    sleep 5
    xterm -e "roslaunch my_robot gmapping.launch"  &
    sleep 5
    xterm -e "roslaunch my_robot view_navigation.launch " &
    sleep 5
    xterm -e "rosrun teleop_twist_keyboard teleop_twist_keyboard.py" &
    sleep 5
)
