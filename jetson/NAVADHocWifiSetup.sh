# This file contains a shell script to configure the nav computer to a wireless ad-hoc network
# for communicating with the ground control station.
# Should only need to be ran once (maybe)

# This code configures the device to run its adaptor in adhoc mode
iwconfig wlan0 mode Ad-hoc
iwconfig wlan0 essid MyWifi

# This assigns the IP address on the network so the two computers can communicate
ifconfig wlan0 192.168.1.2 netmask 255.255.255.0
