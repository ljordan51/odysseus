#include <EEPROM.h>
#include "SpeedyStepper.h"


//
// pin assignments
//
const int LED_PIN = 13;
const int MOTOR_X_STEP = 2;
const int MOTOR_Y_STEP = 3;
const int MOTOR_Z_STEP = 4;
const int MOTOR_X_DIR = 5;
const int MOTOR_Y_DIR = 6;
const int MOTOR_Z_DIR = 7;
const int STEPPERS_ENABLE = 8;
const int LIMIT_SWITCH_X = 9;
const int LIMIT_SWITCH_Y = 10;
const int LIMIT_SWITCH_Z = 11;
const int SPINDLE_ENABLE = 12;
const int SPINDLE_DIRECTION = 13;



//
// create the stepper motor object
//
SpeedyStepper stepperY;
SpeedyStepper stepperX;
SpeedyStepper stepperZ;


//
// local vars
//


// ---------------------------------------------------------------------------------
//                              Hardware and software setup
// ---------------------------------------------------------------------------------

//
// top level setup function
//

int incomingByte = 0; // for serial read

void setup()
{ 
  byte contrastValue;

  //
  // configure IO pins
  //
  pinMode(LED_PIN, OUTPUT);   
  pinMode(STEPPERS_ENABLE, OUTPUT);   


  //
  // create the stepper object & enable them
  //
  stepperY.connectToPins(MOTOR_Y_STEP, MOTOR_Y_DIR);
  stepperX.connectToPins(MOTOR_X_STEP, MOTOR_X_DIR);
  stepperZ.connectToPins(MOTOR_Z_STEP, MOTOR_Z_DIR);
  digitalWrite(STEPPERS_ENABLE, LOW);

 
 
  Serial.begin(9600);
}


//
//
//
void loop()
{
  //
  // set the speed in steps/second and acceleration in steps/second/second
  //
  int SPEED = 200;
  stepperY.setSpeedInStepsPerSecond(50);
  stepperY.setAccelerationInStepsPerSecondPerSecond(800);
  stepperY.setStepsPerRevolution(200);            // 200 for no microstepping
  stepperX.setSpeedInStepsPerSecond(SPEED);
  stepperX.setAccelerationInStepsPerSecondPerSecond(800);
  stepperX.setStepsPerRevolution(200);            // 200 for no microstepping
  stepperZ.setSpeedInStepsPerSecond(SPEED);
  stepperZ.setAccelerationInStepsPerSecondPerSecond(800);
  stepperZ.setStepsPerRevolution(200);            // 200 for no microstepping

  //
  // move motor continuously
  //
  stepperY.setupRelativeMoveInRevolutions(40);
  stepperX.setupRelativeMoveInRevolutions(40);
  stepperZ.setupRelativeMoveInRevolutions(-40);
  while(1){
    stepperY.processMovement();
    stepperX.processMovement();
    stepperZ.processMovement();
  }
  
}

// -------------------------------------- End --------------------------------------
