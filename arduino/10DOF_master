
#include <Wire.h>
#define I2CAddress 8


String text;

void getText(){
  if(Serial.available()) // check if we send a message
  {
    while(Serial.available())
    {
      char c = Serial.read(); // read the next character.
      text += c;
      delay(10);
    } 
  }
}

void sendText() {
  Wire.beginTransmission(I2CAddress); // transmit to device #9
  for(int i=0; i<(text.length()); i++){
    Wire.write(text[i]);
  }             
  Wire.endTransmission();    // stop transmitting
}

void requestOrient(){
  
}

void setup() {
  Serial.begin(115200);
  Serial.println("Master here");
 
  // Start the I2C Bus as Master
  Wire.begin();
}

void loop() {
  text = "";
  while(text.length() == 0) { // Until we send text in the serial monitor
    getText();
    }
  if(text.length() > 0) {
     Serial.print("Send: " + text);
     sendText();
  }
  delay(500);
} 
