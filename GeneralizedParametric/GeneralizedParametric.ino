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
const float partHeight = 74; // sphere diameter in mm
const float bitSize = 0.313*25.4; // bit size inches * mm/in
const float feedRate = 6; // vertical feed rate in mm/sec
const float feedRateFacing = 2.5; // horizontal feed rate in mm/sec
const int maximum_travel = 60; // maximum travel of x-axis backward from origin in mm

// create the stepper motor objects
FlexyStepper stepperX;
FlexyStepper stepperY;
FlexyStepper stepperZ;

// Initialize joystick pins
const int xPin = A2; // left right motion output
const int zPin = A1; // up down motion output
const int buttonPin = A0; // click output

// Initialize variables for reading output values from joystick
int Read = 0;
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

  // set steps per millimeter
  stepperX.setStepsPerMillimeter(standardStepsPerRev*microX/mmPerRevHor);
  stepperZ.setStepsPerMillimeter(standardStepsPerRev*microZ/mmPerRevVert);

  // set the origin
  setOrigin();

  // wait for user input to move on to main loop
  Serial.println();
  Serial.println("Please press any key and then enter to start machining.");
  while(Serial.available() == 0){}
}

void loop() {
  while(1){
    Serial.println("Odysseus...");
  }
}

float equation(float y){
  float x = sqrt(pow(partHeight/2, 2) - pow(y-partHeight/2,2));
  return x;
}

void face(float facing_depth){
  
  stepperX.setAccelerationInRevolutionsPerSecondPerSecond(speedyDecel);
  stepperZ.setSpeedInMillimetersPerSecond(1);
  stepperZ.setAccelerationInRevolutionsPerSecondPerSecond(speedyDecel);
  float facing_bit_length = 10; // facing bit length in mm
  float rotationsPerSec = feedRateFacing/(0.17*facing_bit_length);
  stepperY.setSpeedInRevolutionsPerSecond(rotationsPerSec);
  stepperY.setAccelerationInRevolutionsPerSecondPerSecond(10);

  float start = stepperX.getCurrentPositionInMillimeters();
  float numRotations = (start/feedRateFacing)*rotationsPerSec + 2;

  int numCuts = ceil(facing_depth/mmCutPerRotation);

  for (int i = 0; i < numCuts; i++){
    stepperX.setSpeedInMillimetersPerSecond(feedRateFacing);
    float cutDepth = mmCutPerRotation;
    if(i==(numCuts-1)){
      cutDepth = (facing_depth/mmCutPerRotation-floor(facing_depth/mmCutPerRotation))*mmCutPerRotation;
    }
    stepperZ.moveRelativeInMillimeters(cutDepth);

    stepperY.setTargetPositionRelativeInRevolutions(numRotations);
    stepperX.setTargetPositionInMillimeters(0);

    while((!stepperY.motionComplete()) || (!stepperX.motionComplete())){
        stepperY.processMovement();
        stepperX.processMovement();
    }
    stepperX.setSpeedInMillimetersPerSecond(8);
    stepperX.moveToPositionInMillimeters(start);
  }
}

void joystickControl(FlexyStepper stepper, int pin, int max_val, int min_val){
  stepper.setSpeedInRevolutionsPerSecond(setOrigSpeed);
  stepper.setAccelerationInRevolutionsPerSecondPerSecond(speedyDecel);

  while ( buttonRead ) {
      Read = analogRead(pin); // zero is around 460
      // set direction based on value of joystick
      if (Read > max_val) {
        dir = 1;
      } else if (Read < min_val) {
        dir = -1;
      } else {
        dir = 0;
      }
      // set target position (either negative, positive, or 0)
      stepper.setTargetPositionRelativeInRevolutions(dir*150); // the number of revolutions is arbitrary (150 for now)
      if(abs(dir)){
        stepper.processMovement();
      }
      buttonRead = digitalRead(buttonPin); // check if button is clicked
  }

  // reset values to defaults so next while loop behaves properly
  buttonRead = 1;
  dir = 0;
}

void setOrigin(){
    Serial.println("Raise the Z-Axis above the maximum height of the stock. Click the joystick when you are done.");

    // allow user to manipulate z-axis until button is clicked
    joystickControl(stepperZ, zPin, 550, 500);

    delay(1000);
    Serial.println("Now zero the X-Axis by moving the joystick so the tape on the dremel is flush with the face of the front plate. Click the joystick when you are done.");

    // allow user to manipulate x-axis until button is clicked
    joystickControl(stepperX, xPin, 500, 450);

    stepperX.setCurrentPositionInMillimeters(0.01);

    Serial.println("Now enter the maximum radius of your stock (mm) from the center of the chuck.");
    float r = 0;
    while(r == 0){
      r = Serial.parseFloat();
    }
    while(r > maximum_travel || r == 0){
      Serial.println("My maximum travel is 60 mm. Please enter a maximum radius smaller than that or change your stock to a smaller size.");
      while(r > maximum_travel || r == 0){
        r = Serial.parseFloat();
      }
    }

    stepperX.moveToPositionInMillimeters(r);

    Serial.println("Now lower the Z-Axis until the bottom of the cutting bit is flush with the top of the stock. Click the joystick when you are done.");
    // allow user to manipulate x-axis until button is clicked
    joystickControl(stepperZ, zPin, 550, 500);

    Serial.println("Now enter a value (mm) to face off the top of your stock.");
    float facing_depth = 0;
    while(facing_depth == 0){
      facing_depth = Serial.parseFloat();
    }
    face(facing_depth);

    stepperZ.setCurrentPositionInMillimeters(0.01);
}

