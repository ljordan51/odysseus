#include <EEPROM.h>
#include "SpeedyStepper.h"


//
// pin assignments
//
const int LED_PIN = 13;
const int MOTOR_X_STEP = 2;
const int MOTOR_X_DIR = 5;
const int STEPPERS_ENABLE = 8;
const int LIMIT_SWITCH_X = 9;
const int SPINDLE_ENABLE = 12;
const int SPINDLE_DIRECTION = 13;

//
// create the stepper motor object
//
SpeedyStepper stepperX;


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
  digitalWrite(STEPPERS_ENABLE, LOW);

 
 
  Serial.begin(9600);
}


//
//
//
void loop()
{
  stepperX.setStepsPerRevolution(200);
  stepperX.setSpeedInRevolutionsPerSecond(0.5);
  stepperX.setAccelerationInRevolutionsPerSecondPerSecond(1);

  stepperX.moveRelativeInRevolutions(-50); 
  
}

// -------------------------------------- End --------------------------------------
