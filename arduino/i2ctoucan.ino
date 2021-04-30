
/*
 * CAN port receiver example
 * Repeatedly transmits an array of test data to the CAN port
 
  * Creates 8 integer array to send as CAN command
 */

#include <ASTCanLib.h>  

#define MESSAGE_ID        256       // Message ID
#define MESSAGE_PROTOCOL  1         // CAN protocol (0: CAN 2.0A, 1: CAN 2.0B)
#define MESSAGE_LENGTH    8         // Data length: 8 bytes
#define MESSAGE_RTR       0         // rtr bit

// CAN message object
st_cmd_t txMsg;

// Array of test data to send
// TODO: Pull test data from the i2c port
const uint8_t sendData[8] = {0,10,20,40,80,100,120,127};
// Transmit buffer
uint8_t txBuffer[8] = {};

void setup() {
 
  canInit(500000);                  // Initialise CAN port. must be before Serial.begin
  Serial.begin(1000000);             // start serial port
  txMsg.pt_data = &txBuffer[0];      // reference message data to transmit buffer
}

void loop() {
  //  load data into tx buffer
  uint8_t n[8];
  func(8,n);

 
  for(int i =0;i<8;i++){
    txBuffer[i] = n[i];
  }
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
  // Transmit is now complete. Wait a bit and loop
  delay(500);
}

void func(int count, uint8_t n[8]){
  uint8_t num =0;
  char c;

  for(int j =0;j<count;j++){
    Serial.print("Input ");Serial.print(j+1);Serial.print(": ");
    do{
      c = Serial.read();
      if(c>=0x30&&c<=0x39){
       num = (num*10)+(c-0x30);
      }
   }while(c!='\r');
   n[j] = num;
   Serial.println(num);
   num = 0;
  }
}
