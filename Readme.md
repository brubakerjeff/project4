# Home Service
 
The robot will use the generted map and localize itself with the amcl. It will navigate to a virtual amrker, which will then disappear and re-appear at the drop off zone. The robot will then follow to the drop off zone

## Mapping
 Mapping is done with the SLAM algorithm. This map was saved previosuly and made available for this proect

``` rosrun map_server map_saver -f map ```

## Navigation 
Navigation is done by running add markers and pick objects. Pick Objects instructs the robot to move to the pick up and then the drop off zone.
The add markers node adds a marker which switches to the drop off zone when the robot is within the distance.

## Localization
Localization is done with adapative monte carlo. A particle filter is used
to represent the distribution of possible robot poses and converges to the correct location.


#Map generation
# roslaunch slam_gmapping slam_gmapping_pr2.launch



```  position: 
      x: 0.350057935449
      y: 1.49084831962
      z: 0.0
    orientation: 
      x: 0.0
      y: 0.0
      z: 0.885590982595
      w: 0.464465942289
  covariance: [0.017787210032198145, -0.005299161666603602, 0.0, 0.0, 0.0, 0.0, -0.005299161666603602, 0.05017600822859336, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.018377276653829912]


      x: -1.69675752388
      y: 6.08354368243
      z: 0.0
    orientation: 
      x: 0.0
      y: 0.0
      z: 0.775023203557
      w: 0.631932776447
  covariance: [0.021876915366100924, -0.008264800343214418, 0.0, 0.0, 0.0, 0.0, -0.008264800343212642, 0.03845569156518991, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0```