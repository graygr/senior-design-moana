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

#define MESSAGE_ID        6        // Message ID
#define MESSAGE_PROTOCOL  1       // CAN protocol (0: CAN 2.0A, 1: CAN 2.0B)
#define MESSAGE_LENGTH    8       // Data length: 8 bytes
#define MESSAGE_RTR       0       // rtr bit

st_cmd_t Msg;

uint8_t Buffer[8] = {};

File file_out;

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
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  // NOTICE: SD requires filenames to be 8 character or less. Otherwise it won't create the file. Fuck you arduino.
  file_out = SD.open("data.txt", FILE_WRITE);

  // If file open, ok to write :)
  if(file_out) {
    Serial.println("File good");
    file_out.print("Time");file_out.print(",");file_out.print("ID");file_out.print(",");
    file_out.print("Data 0");file_out.print(",");file_out.print("Data 1");file_out.print(",");
    file_out.print("Data 2");file_out.print(",");file_out.print("Data 3");file_out.print(",");
    file_out.print("Data 4");file_out.print(",");file_out.print("Data 5");file_out.print(",");
    file_out.print("Data 6");file_out.print(",");file_out.println("Data 7");file_out.println();
    file_out.close();
    
  }
  else
  {
    Serial.println("dataLogger.txt could not be opened :(");
  }
}

void loop() {
  int id, dataArr[8];
 
  // Clear the message buffer
  clearBuffer(&Buffer[0]);
 
  // Send command to the CAN port controller
  Msg.cmd = CMD_RX_DATA;
 
  // Wait for the command to be accepted by the controller
  while(can_cmd(&Msg) != CAN_CMD_ACCEPTED);
  // Wait for command to finish executing
  while(can_get_status(&Msg) == CAN_STATUS_NOT_COMPLETED);
  // Data is now available in the message object

  id = Msg.id.ext;
  for(int i = 0;i<7;i++){
    dataArr[i] = Msg.pt_data[i];
  }
 

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  file_out = SD.open("data.txt",FILE_WRITE);

  // if the file is available, write to it:
  if (file_out) {
    curTime = millis();
    file_out.print(curTime);file_out.print(",");file_out.print(id,DEC);file_out.print(",");
    file_out.print(dataArr[0],DEC);file_out.print(",");file_out.print(dataArr[1],DEC);file_out.print(",");
    file_out.print(dataArr[2],DEC);file_out.print(",");file_out.print(dataArr[3],DEC);file_out.print(",");
    file_out.print(dataArr[4],DEC);file_out.print(",");file_out.print(dataArr[5],DEC);file_out.print(",");
    file_out.print(dataArr[5,DEC]);file_out.print(",");file_out.print(dataArr[6],DEC);file_out.print(",");
    file_out.println(dataArr[7],DEC);
   
    file_out.close();
    Serial.println("Saved");
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening dataLogger.csv");
  }
}
