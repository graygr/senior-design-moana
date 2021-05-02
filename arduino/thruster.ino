#include <ASTCanLib.h>

#include <Servo.h>

Servo thrustESC;

#define MESSAGE_ID 2 // Message ID
#define MESSAGE_PROTOCOL 1 // CAN protocol (0: CAN 2.0A, 1: CAN 2.0B)
#define MESSAGE_LENGTH 8 // Data length: 8 bytes
#define MESSAGE_RTR 0 // rtr bit

// Function prototypes
void serialPrintData(st_cmd_t * msg);

// CAN message object
st_cmd_t Msg;

// Buffer for CAN data
uint8_t Buffer[8] = {};

void setup() {
    // put your setup code here, to run once:

    // Treat ESC like a servo
    // Map to pin 6 with signals between 1000 and 2000 ms
    thrustESC.attach(6, 1000, 2000);

    canInit(500000); // Initialise CAN port. must be before Serial.begin
    Serial.begin(1000000); // start serial port
    Msg.pt_data = & Buffer[0]; // reference message data to buffer

    // Initialise CAN packet.
    // All of these will be overwritten by a received packet
    Msg.ctrl.ide = MESSAGE_PROTOCOL; // Set CAN protocol (0: CAN 2.0A, 1: CAN 2.0B)
    Msg.id.ext = MESSAGE_ID; // Set message ID
    Msg.dlc = MESSAGE_LENGTH; // Data length: 8 bytes
    Msg.ctrl.rtr = MESSAGE_RTR; // Set rtr bit

    // Arm ESC manually with low - high - low signals
    thrustESC.write(1500);
    delay(3000);

}

void loop() {
    // Clear the message buffer
    clearBuffer( & Buffer[0]);

    // Send command to the CAN port controller
    Msg.cmd = CMD_RX_DATA;

    // Wait for the command to be accepted by the controller
    while (can_cmd( & Msg) != CAN_CMD_ACCEPTED);
    // Wait for command to finish executing
    while (can_get_status( & Msg) == CAN_STATUS_NOT_COMPLETED);
    // Data is now available in the message object
    // Print received data to the terminal
    serialPrintData( & Msg);

    int dir, power, id, duration;
    id = Msg.pt_data[0];
    if (id == 2) {
        dir = Msg.pt_data[1]; // 1 is negative thrust, 2 is positive thrust
        power = Msg.pt_data[2]; // Range 0 - 100 for percent power
		duration = Msg.pt_data[3]; // 255 for indefinite, 1-254 are seconds
        if (dir == 1) {
            power = power * -1;
        }
		if(dur == 255)
		{
			// Turn on thruster indefinitely
			// Call mapping function to take 0-100 scale and convert to PWM signal
			thrustESC.write(mapping(power));	
		}
		else
		{
			// Turn on thruster for a bit
			thrustESC.write(mapping(power));
			delay(duration * 1000);
			thrustESC.write(mapping(0));
		}
    }
}

int mapping(int input) { // Map input values from 0 - 100 to blue robotics thruster pwm values
    input = input * 4 + 1500;
    return input;
}

void serialPrintData(st_cmd_t * msg) {
    char textBuffer[50] = {
        0
    };
    if (msg -> ctrl.ide > 0) {
        sprintf(textBuffer, "id %d ", msg -> id.ext);
    } else {
        sprintf(textBuffer, "id %04x ", msg -> id.std);
    }
    Serial.print(textBuffer);

    //  IDE
    sprintf(textBuffer, "ide %d ", msg -> ctrl.ide);
    Serial.print(textBuffer);
    //  RTR
    sprintf(textBuffer, "rtr %d ", msg -> ctrl.rtr);
    Serial.print(textBuffer);
    //  DLC
    sprintf(textBuffer, "dlc %d ", msg -> dlc);
    Serial.print(textBuffer);
    //  Data
    sprintf(textBuffer, "data ");
    Serial.print(textBuffer);

    for (int i = 0; i < msg -> dlc; i++) {
        sprintf(textBuffer, "%02X ", msg -> pt_data[i]);
        Serial.print(textBuffer);
    }
    Serial.print("\r\n");
}