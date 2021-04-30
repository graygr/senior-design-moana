
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

// CAN message object
st_cmd_t txMsg;

// Array of test data to send
const uint8_t sendData[8] = {0,10,20,40,80,100,120,127};
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
	if(txBuffer[0] == -1)
	{	
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

		// Send copy of the buffer back
		msgBuffer = txBuffer;
		sendData(&msgBuffer[0]);
		
		txBuffer[0] = -1;
	}
	// Transmit is now complete. Wait a bit and loop
	delay(500);
}

// This is called when we send a command over I2C to the CAN network
// ***This could cause issues with reading all 8 on a single receive
void receiveEvent(int bytes) {
  for(int i = 0; i < 8; ++i)
  {
  	txBuffer[i] = Wire.read();    // read one character from the I2C
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
