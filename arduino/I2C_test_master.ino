#include <Wire.h>

void setup() {
  // put your setup code here, to run once:
  // No parameters, so implied master
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  // Thruster Control Signals
  Wire.beginTransmission(4);
  // Spin at 90/180 speed for 5 seconds
  // Can only send 7 bytes at a time
  Wire.write("0910500");
  Wire.endTransmission();
  delay(5000);

  Wire.beginTransmission(4);
  // Spin at 0/180 speed for 5 seconds
  Wire.write("0000500");
  Wire.endTransmission();
  delay(5000);

  Wire.beginTransmission(5);
  // Rotate to 90/180 for 5 seconds
  Wire.write("1800040");
  Wire.endTransmission();
  delay(1000);

  Wire.beginTransmission(5);
  // Spin at 0/180 speed for 5 seconds
  Wire.write("0000040");
  Wire.endTransmission();
  delay(1000);
}
