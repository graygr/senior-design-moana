# Ground Control Station Software

## Purpose
1. Allow the user to issue commands from the boat / laptop
2. Provide a GUI for the user to input commands to
3. Provide interface to create a script for autonomous AUV operation
4. Provide modelling interface to estimate AUV capabilities and error check a script that should fail
5. Communicate with the NAV via wifi network

## Implementation
### Networking
1. The network will be run adhoc from the ground control station using a shell script
2. This shell script will create an adhoc network and launch the GCS software
3. The NAVComms software will search for this network and connect to it on bootup to receive initial commands

### Server Software
1. A server will run on the ground control station with a client on the AUV