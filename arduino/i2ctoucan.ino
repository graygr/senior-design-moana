
/*
 * CAN port receiver example
 * Repeatedly transmits an array of test data to the CAN port
 
  * Creates 8 integer array to send as CAN command
 */

#include <ASTCanLib.h>
#include <Wire.h>

#define MESSAGE_ID        256       // Message ID
#define MESSAGE_PROTOCOL  1         // CAN protocol (0: CAN 2.0A, 1: CAN 2.0B)
#define MESSAGE_LENGTH    8         // Data length: 8 bytes
#define MESSAGE_RTR       0         // rtr bit

int i2cAddress = 0x40;
int i2c_read = 0;
int counter = 0;

// @ANDREW use this
uint8_t conv_arr[3] = {};

// CAN message object
st_cmd_t txMsg;

// Transmit buffer
uint8_t txBuffer[8] = {};
// Message buffer for writing
uint8_t msgBuffer[8] = {};

void setup() 
{ 
  canInit(500000);                  // Initialise CAN port. must be before Serial.begin
  Serial.begin(1000000);             // start serial port
  txMsg.pt_data = &txBuffer[0];      // reference message data to transmit buffer
 
  // Init I2C line
  Wire.begin(i2cAddress);                // join i2c bus with address #0x40
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(sendData);
}

void loop() 
{
  // If first byte is negative, then no new message
  if(txBuffer[0] != 255)
  { 
    Serial.print("Sending message");
    // Setup CAN packet.
    txMsg.ctrl.ide = MESSAGE_PROTOCOL;  // Set CAN protocol (0: CAN 2.0A, 1: CAN 2.0B)
    txMsg.id.ext   = MESSAGE_ID;        // Set message ID
    txMsg.dlc      = MESSAGE_LENGTH;    // Data length: 8 bytes
    txMsg.ctrl.rtr = MESSAGE_RTR;       // Set rtr bit

    // Send command to the CAN port controller
    txMsg.cmd = CMD_TX_DATA;       // send message
    // Wait for the command to be accepted by the controller
    while(can_cmd(&txMsg) != CAN_CMD_ACCEPTED);
    // Wait for command to finish executing
    while(can_get_status(&txMsg) == CAN_STATUS_NOT_COMPLETED);

    // Print out msg info to serial just in case
    Serial.print("CAN Message sent: \n");
    serialPrintData(&txMsg);
      
    // Send copy of the buffer back
    // TODO: This
    //sendData(&msgBuffer[0]);
    
    txBuffer[0] = 255;
  }
  // Transmit is now complete. Wait a bit and loop
//  for(int i = 0; i < 8; ++i)
//  {
//    Serial.print(txBuffer[i]);
//    Serial.print(" ");
//  }
  delay(500);
}

// This is called when we send a command over I2C to the CAN network
void receiveEvent(int bytes) {
  txBuffer[counter] = Wire.read();    // read one character from the I2C
  Serial.print(txBuffer[counter]);
  Serial.print("\n");
  ++counter;
  if(counter > 7)
  {
    counter = 0;
  }
}

// This is called when we need to send data back to the jetson from the CAN network over I2C
// Currently dumps all messages sent back to the jetson
// TODO: Dump whenever receives a CAN message
void sendData(uint8_t *msg)
{
  for(int i = 0; i < 8; ++i)
  {
    Wire.write(msg[i]);
  }
}

void serialPrintData(st_cmd_t *msg){
  char textBuffer[50] = {0};
  if (msg->ctrl.ide>0){
    sprintf(textBuffer,"id %d ",msg->id.ext);
  }
  else
  {
    sprintf(textBuffer,"id %04x ",msg->id.std);
  }
  Serial.print(textBuffer);
 
  //  IDE
  sprintf(textBuffer,"ide %d ",msg->ctrl.ide);
  Serial.print(textBuffer);
  //  RTR
  sprintf(textBuffer,"rtr %d ",msg->ctrl.rtr);
  Serial.print(textBuffer);
  //  DLC
  sprintf(textBuffer,"dlc %d ",msg->dlc);
  Serial.print(textBuffer);
  //  Data
  sprintf(textBuffer,"data ");
  Serial.print(textBuffer);
 
  for (int i =0; i<msg->dlc; i++){
    sprintf(textBuffer,"%02X ",msg->pt_data[i]);
    Serial.print(textBuffer);
  }
  Serial.print("\r\n");
}

// The input is a 3 byte array
// First byte is sign. 1 is neg, 2 is positive
// Second byte is rounded whole
// Third byte is fraction, calc by (val * 100) - (whole * 100)
// To undo, reverse process
float three_byte_arr_to_float()
{
	int sign;
	
	if(conv_arr[0] == 0)
	{
		return 0;
	}
	else if(conv_arr[0] == 1)
	{
		sign = -1;
	}
	else if(conv_arr[0] == 2)
	{
		sign = 1;
	}
	
	return (conv_arr[1] + (conv_arr[2] / 100)) * sign;
}
