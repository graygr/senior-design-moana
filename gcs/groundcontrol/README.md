# Ground Control Station Software

## How to connect to the vehicle
1. Currently, due to implementation difficulties, the user will create a mobile hotspot on their Windows 10 laptop
2. Connect to this manually on the Jetson
3. The jetson should now autoconnect on boot!
4. ssh into the Jetson using the IP displayed in the mobile hotspot menu
5. "ssh moana@X.Y.Z.Q" - password is "root"
6. You are now connected wirelessly to the vehicle
7. Navigate to senior-design-moana and run the Toucan interface, follow instructions from there

## Issues with current approach
1. This will only work if already connected to a wifi network due to the implementation in Windows 10. The workaround is to use a cellphone hotspot as a dummy network. To fix this, future work would be to write a dedicated server that the laptop would run.

## Original Purpose
1. The goal for this software was to have a ground station track the expected movements of the vehicle and provide a better user interface
2. This was not accomplished due to time constraints and difficulty in implementing other parts of the computer system
3. Also, the wifi card that we used for the jetson has issues with Adhoc networking, and the team had only windows laptops, so it was a complicated mess to work with.
