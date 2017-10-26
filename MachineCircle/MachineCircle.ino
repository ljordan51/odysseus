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

const int mmCutPerRotation = 3.175; // 1/8 in in each revolution
const float mmPerRev = 1.27; // 1/4-20 screws, .05 in per revolution, 1.27 mm per revolution

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
  stepperX.setStepsPerRevolution(200);
  stepperY.setStepsPerRevolution(200);
  stepperX.setSpeedInRevolutionsPerSecond(0.5);
  stepperY.setSpeedInRevolutionsPerSecond(0.1);
  stepperX.setAccelerationInRevolutionsPerSecondPerSecond(1);
  stepperY.setAccelerationInRevolutionsPerSecondPerSecond(1); 
  
  while(1){
    stepperY.moveRelativeInRevolutions(1);
    stepperX.moveRelativeInRevolutions(-mmCutPerRotation/mmPerRev);      
  }  
  
}

// -------------------------------------- End --------------------------------------
