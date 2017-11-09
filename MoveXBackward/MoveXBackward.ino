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
SpeedyStepper stepperX;
SpeedyStepper stepperY;
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
  // create the stepper object & enable it
  //
  stepperX.connectToPins(MOTOR_X_STEP, MOTOR_X_DIR);
  stepperY.connectToPins(MOTOR_Y_STEP, MOTOR_Y_DIR);
  stepperZ.connectToPins(MOTOR_Z_STEP, MOTOR_Z_DIR);
  digitalWrite(STEPPERS_ENABLE, LOW);

 
 
  Serial.begin(9600);
  Serial.println ("Hit a key to start");     // signal initalization done
  while(Serial.available() == 0){}
}
//
//
//
void loop()
{
  stepperX.setStepsPerRevolution(200);
  stepperX.setSpeedInRevolutionsPerSecond(1);
  stepperX.setAccelerationInRevolutionsPerSecondPerSecond(10);

  stepperX.moveRelativeInRevolutions(-100); 
  
}

// -------------------------------------- End --------------------------------------
