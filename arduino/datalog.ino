/*
  SD card datalogger

  This example shows how to log data from three analog sensors
  to an SD card using the SD library.

  The circuit:
   analog sensors on analog ins 0, 1, and 2
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 10 (for MKRZero SD: SDCARD_SS_PIN)

  created  24 Nov 2010
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

*/

#include <SPI.h>
#include <SD.h>
#include <ASTCanLib.h>

#define MESSAGE_ID        0       // Message ID
#define MESSAGE_PROTOCOL  1       // CAN protocol (0: CAN 2.0A, 1: CAN 2.0B)
#define MESSAGE_LENGTH    8       // Data length: 8 bytes
#define MESSAGE_RTR       0       // rtr bit

st_cmd_t Msg;

uint8_t Buffer[8] = {};

File data;

const int chipSelect = 10;

unsigned long curTime;

void setup() {
  canInit(500000);            // Initialise CAN port. must be before Serial.begin
  Serial.begin(1000000);       // start serial port
  Msg.pt_data = &Buffer[0];    // reference message data to buffer
 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
 
  // Initialise CAN packet.
  // All of these will be overwritten by a received packet
  Msg.ctrl.ide = MESSAGE_PROTOCOL;  // Set CAN protocol (0: CAN 2.0A, 1: CAN 2.0B)
  Msg.id.ext   = MESSAGE_ID;        // Set message ID
  Msg.dlc      = MESSAGE_LENGTH;    // Data length: 8 bytes
  Msg.ctrl.rtr = MESSAGE_RTR;       // Set rtr bit


  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");

  data = SD.open("dataLogger.csv",FILE_WRITE);
  if(data){
    Serial.println("File good");
    data.print("Time");data.print(",");data.print("ID");data.print(",");
    data.print("Data 0");data.print(",");data.print("Data 1");data.print(",");
    data.print("Data 2");data.print(",");data.print("Data 3");data.print(",");
    data.print("Data 4");data.print(",");data.print("Data 5");data.print(",");
    data.print("Data 6");data.print(",");data.println("Data 7");data.println();
  }
  data.close()
 
}

void loop() {
  int id, data[8];
 
  // Clear the message buffer
  clearBuffer(&Buffer[0]);
 
  // Send command to the CAN port controller
  Msg.cmd = CMD_RX_DATA;
 
  // Wait for the command to be accepted by the controller
  while(can_cmd(&Msg) != CAN_CMD_ACCEPTED);
  // Wait for command to finish executing
  while(can_get_status(&Msg) == CAN_STATUS_NOT_COMPLETED);
  // Data is now available in the message object

  id = msg.id.ext;
  for(int i = 0;i<7;i++){
    data[i] = msg.pt_data[i];
  }
 

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  data = SD.open

  // if the file is available, write to it:
  if (data) {
    curTime = millis();
    data.print(curTime);data.print(",");data.print(id,DEC);data.print(",");
    data.print(data[0],DEC);data.print(",");data.print(data[1],DEC);data.print(",");
    data.print(data[2],DEC);data.print(",");data.print(data[3],DEC);data.print(",");
    data.print(data[4],DEC);data.print(",");data.print(data[5],DEC);data.print(",");
    data.print(data[5,DEC]);data.print(",");data.print(data[6],DEC);data.print(",");
    data.println(data[7],DEC);
   
    data.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
}
