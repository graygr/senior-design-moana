#include <Servo.h>
#include <Wire.h>

Servo pitch;

void setup() {
  // put your setup code here, to run once:

  // Treat ESC like a servo 

  // Assign PIN 6 to servo, with range between 1000ms and 2000ms
  pitch.attach(6, 1000, 2000);  

  // Open I2C on port 6
  Wire.begin(6);
  // Listen to I2C call to this port, call receiveEvent() on receive
  Wire.onReceive(receiveEvent);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
}

void receiveEvent(int howMany) {
  // Store received serial data into character array
  char cmd[7];
  int i = 0;
  while(0 < Wire.available())
  {    
    cmd[i] = Wire.read();
    Serial.print(cmd[i]);
    i++;
  }
  Serial.println(" ");

  // Translate characters to integers by subtracting '0' character
  for(int q = 0; q < 7; ++q)
    cmd[q] = cmd[q] - '0';
  
  // TODO: transmit in numbers, not characters. More efficient data transmission for final project
  char servo_pos[3];
  for(int j = 0; j < 3; ++j)
    servo_pos[j] = cmd[j];
  char duration[4];
  for(int k = 0; k < 4; ++k)
    duration[k] = cmd[k+3];

  // Translate characters to values
  int pos = servo_pos[2] + 10 * servo_pos[1] + 100 * servo_pos[0];
  int dur = 10 * duration[3] + 100 * duration[2] + 1000 * duration[1] + 10000 * duration[0];

  Serial.print("Position is ");
  Serial.println(pos);
  Serial.print("Duration is ");
  Serial.println(dur);

  // Write position  
  pitch.write(pos);
  // Wait until next command
  delay(dur);
}
