(
    cd ../..
    echo A
    xterm -e "echo A&&cd $(pwd) && source devel/setup.bash && roslaunch turtlebot_gazebo turtlebot_world.launch;exec bash" &
    sleep 20
    echo B
    xterm -e "echo B&&cd $(pwd) && source devel/setup.bash && roslaunch turtlebot_gazebo  amcl_demo.launch;exec bash" &
    sleep 10
    echo C
    xterm -e "echo C&&cd $(pwd) && source devel/setup.bash && roslaunch turtlebot_rviz_launchers view_navigation.launch;exec bash" &
    sleep 10
)