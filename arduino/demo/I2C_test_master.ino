#include <Wire.h>

void setup() {
  // put your setup code here, to run once:
  
  // No parameters, so implied master
  Wire.begin();
  
  Serial.begin(9600);
}

/*
  PORT TABLE
  1:
  2:
  3:
  4: Thruster
  5: Rudder
  6: Pitch
  7: Emergency Recovery

*/
int i = 0;
void loop() {
  // put your main code here, to run repeatedly:

// 10DOF request
// TODO: Fill this out and integrate
// TODO: Use data from 10DOF to affect other signals to actuators

// 
// Thruster Control Signals
// 
// Speed scales between 0 - 180
// Format: XXX YYYYY
// XXX is 3 digit speed
// YYYYY is 5 digit time in S * 10^-2
  if(i % 2)
  {
    Wire.beginTransmission(4);
    // Spin at 90/180 speed for 5 seconds
    // Can only send 7 bytes at a time
    Wire.write("0910500");
    Wire.endTransmission();
  } 
  else
  {
    Wire.beginTransmission(4);
    // Spin at 0/180 speed for 5 seconds
    Wire.write("0000500");
    Wire.endTransmission();
  }

// 
// Rudder Servo Control Signals
// 
// (applies to all servos below as well)
// Position rotates between 0 - 180
// Time sent is time held in that position before listening for a new position
// Format: XXX YYYYY
// XXX is 3 digit position
// YYYYY is 5 digit time in S * 10^-2

// TODO: Tune servo signals for the right position for demo
  if(i % 2)
  {
    Wire.beginTransmission(5);
    // Rotate to 90/180 for 5 seconds
    Wire.write("1800040");
    Wire.endTransmission();
  }
  else
  {

    Wire.beginTransmission(5);
    // Spin at 0/180 speed for 5 seconds
    Wire.write("0000040");
    Wire.endTransmission();
  }


// 
// Pitch Servo Control Signals
// 
// (applies to all servos below as well)
// Position rotates between 0 - 180
// Time sent is time held in that position before listening for a new position
// Format: XXX YYYYY
// XXX is 3 digit position
// YYYYY is 5 digit time in S * 10^-2

// TODO: Tune servo signals for the right position for demo

  if(i % 2)
  {
    Wire.beginTransmission(5);
    // Rotate to 90/180 for 5 seconds
    Wire.write("1800040");
    Wire.endTransmission();
  }
  else
  {

    Wire.beginTransmission(5);
    // Spin at 0/180 speed for 5 seconds
    Wire.write("0000040");
    Wire.endTransmission();
  }

// 
// Emergency Recovery Servo Control Signals
// 
// (applies to all servos below as well)
// Position rotates between 0 - 180
// Time sent is time held in that position before listening for a new position
// Format: XXX YYYYY
// XXX is 3 digit position
// YYYYY is 5 digit time in S * 10^-2

// TODO: Tune servo signals for the right position for demo

if(i % 2)
  {
    Wire.beginTransmission(5);
    // Rotate to 90/180 for 5 seconds
    Wire.write("1800040");
    Wire.endTransmission();
  }
  else
  {

    Wire.beginTransmission(5);
    // Spin at 0/180 speed for 5 seconds
    Wire.write("0000040");
    Wire.endTransmission();
  }

  // Delay for 5.5 second cycles between instruction sets
  ++i;
  delay(5500);
}
