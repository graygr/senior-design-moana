Hi there!

To communicate with the rest of the vehicle from the navigation computer, first check that the wiring is complete from the Jetson to the communication arduino board. 

The I2C SCL and SDA ports should be plugged in accordingly, using the Jetson's PORT 0 (pins 27&28) and the arduino's SCL and SDA (pins 2 & 3)

To test the connection, if you run "i2cdetect -y -r 0", you should see something show up on port 40. If you don't you did something wrong, and double check your wiring.

In the current test version, it works by sending individual commands in a debug mode. To run this, just type "python comms.py", and follow the prompts. This is to debug individual subsystems as we begin to integrate them into the vehicle.

In a future version (which will hopefully be implemented before we test next week), we will have several preplanned missions to pick from, which the python script will send autonomously from the vehicle to the subsystem for independent movement. 

In a final version, there should be a gui to plan out missions and generate commands automatically (future work?)
