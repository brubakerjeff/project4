# Home Service
## Navigation 
Navigation is done by running add markers an pick objects. Pick Objects instructs the robot to move to the pick up and then the drop off zone.
The add markers node adds a marker which switches to the drop off zone when the robot is within the distance.
## Mapping
 Mapping is done with slam. This map was saved previosuly and made available for this proect

## Localization
Localization is done with adapative monte carlo. A particle filter is used
to represent the distribution of possible robot poses and converges to the correct location.
