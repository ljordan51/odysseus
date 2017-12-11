#include <EEPROM.h>
#include "FlexyStepper.h"

// Stepper pin assignments
const int LED_PIN = 13;
const int MOTOR_X_STEP = 2;
const int MOTOR_Y_STEP = 3;
const int MOTOR_Z_STEP = 4;
const int MOTOR_X_DIR = 5;
const int MOTOR_Y_DIR = 6;
const int MOTOR_Z_DIR = 7;
const int STEPPERS_ENABLE = 8;
const int LIMIT_SWITCH_X = 9; // limit switches have not been enabled yet
const int LIMIT_SWITCH_Y = 10;
const int LIMIT_SWITCH_Z = 11;
const int SPINDLE_ENABLE = 12; // not sure what pins 12 and 13 do
const int SPINDLE_DIRECTION = 13;

// set microstepping for each motor
const int microX = 1;
const int microY = 1;
const int microZ = 1;

// set up other vars related to stepper movement
const int standardStepsPerRev = 200; // default number of steps per revolution without microstepping
const int setOrigSpeed = 1; // default stepper motor speed in revolutions per second for setting the origin
const int setOrigAccel = 5; // default stepper motor acceleration in revolutions per second per second for setting the origin
const int speedyDecel = 200; // changed acceleration to real fast so we get rid of bouncing on switching
int dir = 0; // default direction of stepper motor movement for setting the origin (0 so there is no movement by default

// set some constants for machining
const int mmCutPerRotation = 1.5; // 1/8 in in each revolution
const float mmPerRevHor = 1.5875; // 1/4-20 screws, .05 in per revolution, 1.27 mm per revolution
const float maxXSpeed = 15; // maximum x speed in mm/sec
const float mmPerRevVert = 8; // pitch 16 screws, .0625 in per rev, 1.5875 mm per rev
const float maxYSpeed = 35; // maximum y speed in mm/sec
const float sphereDiam = 74; // sphere diameter in mm
const float bitSize = 0.313*25.4; // bit size inches * mm/in
const float feedRate = 6; // vertical feed rate in mm/sec
const int zAccel = 10;

// create the stepper motor objects
FlexyStepper stepperX;
FlexyStepper stepperY;
FlexyStepper stepperZ;

// Initialize joystick pins
const int xPin = A2; // left right motion output
const int zPin = A1; // up down motion output
const int buttonPin = A0; // click output

// Initialize variables for reading output values from joystick
int xRead = 0;
int zRead = 0;
int buttonRead = 1;

bool once = true;

void setup() {

  Serial.begin(9600);
  
  //Joystick 1
  pinMode(xPin, INPUT);
  pinMode(zPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  byte contrastValue;

  // configure IO pins
  pinMode(LED_PIN, OUTPUT);   
  pinMode(STEPPERS_ENABLE, OUTPUT);   

  // create the stepper objects & enable them
  stepperY.connectToPins(MOTOR_Y_STEP, MOTOR_Y_DIR);
  stepperX.connectToPins(MOTOR_X_STEP, MOTOR_X_DIR);
  stepperZ.connectToPins(MOTOR_Z_STEP, MOTOR_Z_DIR);
  digitalWrite(STEPPERS_ENABLE, LOW);

  // set steps per revolution for each motor based on microstepping multiplier
  stepperX.setStepsPerRevolution(standardStepsPerRev*microX);
  stepperY.setStepsPerRevolution(standardStepsPerRev*microY);
  stepperZ.setStepsPerRevolution(standardStepsPerRev*microZ);

  // set the origin
  // setOrigin();

  // wait for user input to move on to main loop
  Serial.println();
  Serial.println("Please press any key and then enter to start machining.");
  while(Serial.available() == 0){}
}

void loop() {
  stepperX.setCurrentPositionInMillimeters(0.01);
  stepperZ.setCurrentPositionInMillimeters(0.01);
  stepperX.setStepsPerMillimeter(standardStepsPerRev*microX/mmPerRevHor);
  stepperZ.setStepsPerMillimeter(standardStepsPerRev*microZ/mmPerRevVert);
  stepperZ.setTargetPositionInMillimeters(sphereDiam);
  stepperX.setSpeedInMillimetersPerSecond(feedRate);
  stepperZ.setSpeedInMillimetersPerSecond(feedRate);
  stepperZ.setAccelerationInMillimetersPerSecondPerSecond(speedyDecel);
  stepperX.setTargetPositionInMillimeters(sphereDiam/2);
  while((!stepperX.motionComplete()) || (!stepperZ.motionComplete())){ 
    
    float zVel = stepperZ.getCurrentVelocityInMillimetersPerSecond();
    float zPos = stepperZ.getCurrentPositionInMillimeters();
    float zSpeed = sin(zPos*3.14/sphereDiam)*feedRate;
    stepperZ.setSpeedInMillimetersPerSecond(zSpeed);
    if(zPos > (sphereDiam/2)){
      stepperX.setTargetPositionInMillimeters(0);
    }
    float xPos = stepperX.getCurrentPositionInMillimeters();
    float xVel = stepperX.getCurrentVelocityInMillimetersPerSecond();
    float xSpeed = abs(((zPos-sphereDiam/2)/xPos)*zVel);
    if(xSpeed > maxXSpeed){
      xSpeed = maxXSpeed;
    }
    stepperX.setSpeedInMillimetersPerSecond(xSpeed);
    stepperX.setAccelerationInMillimetersPerSecondPerSecond(speedyDecel);
    stepperX.processMovement();
    stepperZ.processMovement();
  }
  while(1){
    Serial.println("Odysseus...");
  }
}

void setOrigin(){
    // set stepper Z speed and acceleration
    stepperZ.setSpeedInMillimetersPerSecond(setOrigSpeed);
    stepperZ.setAccelerationInRevolutionsPerSecondPerSecond(speedyDecel);

    Serial.println("Now zero the Z-Axis by moving the joystick up and down. Click the joystick when you are done to zero the X-Axis.");

    // allow user to manipulate z-axis until button is clicked
    while ( buttonRead ) {
      zRead = analogRead(zPin); // zero is around 460
      // set direction based on value of joystick
      if (zRead > 550) {
        dir = 1;
      } else if (zRead < 500) {
        dir = -1;
      } else {
        dir = 0;
      }
      // set target position (either negative, positive, or 0)
      stepperZ.setTargetPositionRelativeInRevolutions(dir*150); // the number of revolutions is arbitrary (150 for now)
      if(abs(dir)){
        stepperZ.processMovement();
      }
      buttonRead = digitalRead(buttonPin); // check if button is clicked
    }

    // reset values to defaults so next while loop behaves properly
    buttonRead = 1;
    dir = 0;

    // set stepper X speed and acceleration
    stepperX.setSpeedInRevolutionsPerSecond(setOrigSpeed);
    stepperX.setAccelerationInRevolutionsPerSecondPerSecond(speedyDecel);

    delay(1000);
    Serial.println("Now zero the X-Axis by moving the joystick left and right. Click the joystick when you are done.");

    // allow user to manipulate x-axis until button is clicked
    while ( buttonRead ) {
      xRead = analogRead(xPin); // zero is around 430
      // set direction based on value of joystick
      if (xRead > 500) {
        dir = 1;
      } else if (xRead < 450) {
        dir = -1;
      } else {
        dir = 0;
      }
      // set target position (either negative, positive, or 0)
      stepperX.setTargetPositionRelativeInRevolutions(dir*150); // the number of revolutions is arbitrary (150 for now)
      if(abs(dir)){
        stepperX.processMovement();
      }
      buttonRead = digitalRead(buttonPin); // check if button is clicked
    }
    Serial.println("Great job zeroing the cutter!");
}

