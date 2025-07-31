#!/bin/bash

./test_navigation.sh
# Launch the pick_objects node
cd ../../
rosrun pick_objects pick_objects_node

