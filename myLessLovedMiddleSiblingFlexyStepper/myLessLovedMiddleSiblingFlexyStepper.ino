#include <EEPROM.h>
#include "FlexyStepper.h"


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

bool notDone = true;

//
// create the stepper motor object
//
FlexyStepper stepperX;
FlexyStepper stepperY;
FlexyStepper stepperZ;


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
  Serial.println();
  Serial.println("Hit a key and press enter to start");     // signal initalization done
  while(Serial.available() == 0){}
}


//
//
//
void loop()
{

  while(notDone){
    stepperZ.setStepsPerRevolution(800); // currently set to 4x microstepping
    stepperZ.setSpeedInRevolutionsPerSecond(5); // start slow
    stepperZ.setAccelerationInRevolutionsPerSecondPerSecond(1); // random acceleration
    stepperZ.setTargetPositionRelativeInRevolutions(10); // just run for a while idk
    unsigned long start_time = millis();

    while(!stepperZ.motionComplete()){
      unsigned long cur_time = millis()-start_time;
      if(cur_time > 3000){
        stepperZ.setTargetPositionRelativeInRevolutions(-10);
      }
      stepperZ.processMovement();
    }
  }
  
}

// -------------------------------------- End --------------------------------------
