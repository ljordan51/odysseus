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

const float r = 48; // radius of stock in mm
const float mmPerRev = 1.27; // 1/4-20 screws, .05 in per revolution, 1.27 mm per revolution
const float maxCut = 3.175; // max cut depth in mm ( 1/8 in)

const int horizontalRevsPerSecond = 10; // constant horizontal revs/second
const int horizontalAccel = 2; // constant horizontal accel in revs/second/second



//
// create the stepper motor object
//
SpeedyStepper stepperY;
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
  // create the stepper object & enable them
  //
  stepperY.connectToPins(MOTOR_Y_STEP, MOTOR_Y_DIR);
  stepperX.connectToPins(MOTOR_X_STEP, MOTOR_X_DIR);
  digitalWrite(STEPPERS_ENABLE, LOW);

 
 
  Serial.begin(9600);
}


//
//
//
void loop()
{
  delay(5000);
  
  // calculate max depth of cut to make flat from cylindrical stock in mm
  float depth = r*0.29;
  float steps = depth/maxCut;

  // set the microstepping and acceleration in steps/second/second
  int xAccel = 4; // acceleration of x stepper in revs/second/second
  int yAccel = 1; // acceleration of y stepper in revs/second/second
  int xStepsPerRev = 200; // steps per revolution, 200 for no microstepping
  int yStepsPerRev = 3200; // steps per revolution, 200 for no microstepping
  stepperY.setAccelerationInRevolutionsPerSecondPerSecond(yAccel);
  stepperY.setStepsPerRevolution(yStepsPerRev);
  stepperX.setAccelerationInRevolutionsPerSecondPerSecond(xAccel);
  stepperX.setStepsPerRevolution(xStepsPerRev);

  for(int i=0;i<ceil(steps);i++){
    // calculate speeds, set speeds in steps/second
    float horizontalRevs = (i+1)*maxCut/mmPerRev;
    if(i==ceil(steps)-1){
      horizontalRevs = depth/mmPerRev;
    }
    float secondsToRun = horizontalRevs/horizontalRevsPerSecond;
    int rotationalSPEED = yStepsPerRev/8/secondsToRun; // speed of x stepper in steps/second
    int horizontalSPEED = xStepsPerRev*horizontalRevsPerSecond; // speed of y stepper in steps/second
    stepperX.setSpeedInStepsPerSecond(horizontalSPEED);
    stepperY.setSpeedInStepsPerSecond(rotationalSPEED);

    // stepperX.setAccelerationInRevolutionsPerSecondPerSecond(horizontalAccel);
    // stepperY.setAccelerationInRevolutionsPerSecondPerSecond(horizontalAccel*(rotationalSPEED/horizontalSPEED));
  
    // move in and out while turning, god I hope this shit works...
    stepperX.setupRelativeMoveInRevolutions(horizontalRevs);
    stepperY.setupRelativeMoveInRevolutions(0.125);
    while((!stepperX.motionComplete()) || (!stepperY.motionComplete())){
      stepperX.processMovement();
      stepperY.processMovement();
    }
    stepperX.setupRelativeMoveInRevolutions(-horizontalRevs);
    stepperY.setupRelativeMoveInRevolutions(0.125);
    while((!stepperX.motionComplete()) || (!stepperY.motionComplete())){
      stepperX.processMovement();
      stepperY.processMovement();
    }
    stepperY.moveRelativeInRevolutions(-.25);
  }
  
}

// -------------------------------------- End --------------------------------------
