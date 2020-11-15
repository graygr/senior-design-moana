#include <Wire.h>

void setup() {
  // put your setup code here, to run once:
  // Parameter is the address of the slave
  Wire.begin(8);
  Wire.onRequest(requestEvent);

  pinMode(6, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(6, HIGH);
//  delay(500);
//  digitalWrite(6, LOW);
//  delay(1000);
}

void requestEvent() {
  Wire.write("hello!");
}
