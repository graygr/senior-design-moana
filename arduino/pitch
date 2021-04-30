
// Code for slider with the bang bang control that guides the linear slider to the position based on an angle input into the serial command.

#include <ASTCanLib.h>  

#define MESSAGE_ID        5       // Message ID
#define MESSAGE_PROTOCOL  1         // CAN protocol (0: CAN 2.0A, 1: CAN 2.0B)
#define MESSAGE_LENGTH    8         // Data length: 8 bytes
#define MESSAGE_RTR       0         // rtr bit

// CAN message object
st_cmd_t Msg;

// Transmit buffer
uint8_t Buffer[8] = {};



#define dirPin 8
#define stepPin 7

char inputBuffer[5];
int number = 0;

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 6;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

void calibrate();
// variables will change:

int buttonState = 0;         // variable for reading the pushbutton status
int velocity = 100;
int x = 1;
float stepsToX =0;
float xInput = 0; //input angle for pitch
float currentLocation = 0;
int currentDirection = 1; //direction slider is moving 0 = towards stepper, 1 is away from stepper
float addedSliderMass = 19.62;
float sliderMass = 23.58 + 4; //[Newtons] mass on top of batter + battery mass + slider weight
float totalMass = 728.125 - addedSliderMass; //[Newtons]
float separation = 1; //[inches]
float Kp = .1;  


void setup() {
 
  canInit(500000);                  // Initialise CAN port. must be before Serial.begin
  Serial.begin(1000000);             // start serial port
  Msg.pt_data = &Buffer[0];      // reference message data to transmit buffer

  // Initialise CAN packet.
  // All of these will be overwritten by a received packet
  Msg.ctrl.ide = MESSAGE_PROTOCOL;  // Set CAN protocol (0: CAN 2.0A, 1: CAN 2.0B)
  Msg.id.ext   = MESSAGE_ID;        // Set message ID
  Msg.dlc      = MESSAGE_LENGTH;    // Data length: 8 bytes
  Msg.ctrl.rtr = MESSAGE_RTR;       // Set rtr bit
 
  //Initializes the PWM Pin
  pinMode(stepPin, OUTPUT);
  //Initializes the direction Pin
  pinMode(dirPin, OUTPUT);
  //Sets an initial direction
  digitalWrite(dirPin, HIGH);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  calibrate(); // runs calibration
}

void loop() {
 
  xInput = CANin();

  Serial.println(xInput);
 
  if(xInput > -20 && xInput < 20){
    //xInput = Serial.parseFloat();
    Serial.print("I recieved the input: ");
    Serial.println(xInput); //this is the only print, so for some reason pitch angle gets reupdated to be 0 every time I input a number
    xInput = (totalMass/sliderMass)* separation * tan(xInput*3.1415926/180) + 24;
    Serial.println(xInput);
    stepsToX =  xInput/0.00125 - currentLocation;
    if(stepsToX/abs(stepsToX)>=0){
      digitalWrite(dirPin,HIGH);
    }
    else{
      digitalWrite(dirPin,LOW);
    }
    Serial.print("Steps To X: ");
    Serial.println(stepsToX);
    for (int i = 0; i < abs(stepsToX); i++) {
      currentLocation = currentLocation + stepsToX/abs(stepsToX);
     
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(300);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(300);
     
      if(Serial.available()>0){
        break;
        Serial.println(currentLocation);
      }
    }
    Serial.println(currentLocation);
  }
}



void calibrate(){
  Serial.println("Running Calibration. Please wait.");
  while(true){
    buttonState = digitalRead(buttonPin);

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState == HIGH) {
      // turn LED on:
      digitalWrite(ledPin, HIGH);
      Serial.println("Calibration Complete");
      currentLocation = 33/0.00125;
      xInput = 0;
      break;
    } else {
      // turn LED off:
      digitalWrite(ledPin, LOW);
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(400);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(400);
    }
  }
}

void feedback(){
  float pitchError = 0; //declares error for pitch
  int IMU_Pitch = 0; //Input IMU_Pitch here
  pitchError = IMU_Pitch - xInput;
 
  if(pitchError < 0){
    //Set Direction Pin
    //Set speed of movement
   
    pitchError * Kp;
  }
  else if(pitchError > 0 ){
   
  }
 
}


int CANin(){
  // Clear the message buffer
  clearBuffer(&Buffer[0]);
 
  // Send command to the CAN port controller
  Msg.cmd = CMD_RX_DATA;
 
  // Wait for the command to be accepted by the controller
  while(can_cmd(&Msg) != CAN_CMD_ACCEPTED);
  // Wait for command to finish executing
  while(can_get_status(&Msg) == CAN_STATUS_NOT_COMPLETED);
  // Data is now available in the message object

  int dir = 0, angle = 0, id = 0;
  id = Msg.pt_data[0];
 
  if(id == 5){
    dir = Msg.pt_data[1];   // 1 is pitch forward, 2 is is pitch back
    angle = Msg.pt_data[2]; //between 0 and 20 currently
  }

  if(dir == 1){
    angle = angle * -1;
  }

  return angle;  
}

