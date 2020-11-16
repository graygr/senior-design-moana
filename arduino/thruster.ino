#include <Servo.h>
#include <Wire.h>

Servo thrustESC;

void setup() {
  // put your setup code here, to run once:

  // Treat ESC like a servo 
  // Map to pin 6 with signals between 1000 and 2000 ms
  thrustESC.attach(6, 1000, 2000);  
  Wire.begin(4);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);

  // Arm ESC manually with low - high - low signals
  thrustESC.write(0);
  delay(500);
  thrustESC.write(180);
  delay(500);
  thrustESC.write(0);
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:

  delay(100);
}

void receiveEvent(int howMany) {
  
  // Receive serial data and store in character array
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
  
  // TODO: transmit in numbers, not characters
  char esc_speed[3];
  for(int j = 0; j < 3; ++j)
    esc_speed[j] = cmd[j];
  char duration[4];
  for(int k = 0; k < 4; ++k)
    duration[k] = cmd[k+3];

  // Translate characters to values
  
  int spd = esc_speed[2] + 10 * esc_speed[1] + 100 * esc_speed[0];
  int dur = 10 * duration[3] + 100 * duration[2] + 1000 * duration[1] + 10000 * duration[0];

  Serial.print("Speed is ");
  Serial.println(spd);
  Serial.print("Duration is");
  Serial.println(dur);

  // Write out desired speed to the ESC  
  thrustESC.write(spd);
  delay(dur);
}
