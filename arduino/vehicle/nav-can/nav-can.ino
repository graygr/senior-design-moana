/* This sketch waits for incoming serial data to be present
   and then sends a message serially.
   
   After Serial.println() is a call to Serial.read() to remove
   the received byte from the input queue. If you send more than 
   one byte to the Arduino, you'll get more than one response sent
   back at you.
*/

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available() > 0)
  {
    Serial.println("Hello");
    Serial.read();
  }
}
