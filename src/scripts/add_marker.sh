#!/bin/bash

./test_navigation.sh
# Launch the pick_objects node
cd ../../
rosrun add_markers add_markers_node
