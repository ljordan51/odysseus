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

const int mmMaxCutDepth = 1.5; // 1/8 in in each revolution
const float mmPerRevHor = 1.5875; // 1/4-20 screws, .05 in per revolution, 1.27 mm per revolution
const float mmPerRevVert = 8; // pitch 16 screws, .0625 in per rev, 1.5875 mm per rev
const float coneHeight = 40; // part height in mm
const float coneRadius = 20; // mm distance to move in overall during entire operation
const float bitSize = 0.313*25.4; // bit size inches * mm/in
const float feedRate = 2.5; // vertical feed rate in mm/sec
const int microX = 4;
const int microY = 1;
const int microZ = 4;
const int yAccel = 10;
const int zAccel = 10;
const int standardStepsPerRev = 200;

bool notDone = true;

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
  Serial.println();
  Serial.println("Hit a key and press enter to start");     // signal initalization done
  while(Serial.available() == 0){}
}


//
//
//
void loop()
{

  float rotationsPerSec = feedRate/(0.17*bitSize);
  int numCuts = ceil(coneRadius/mmMaxCutDepth);
  
  stepperX.setStepsPerMillimeter(standardStepsPerRev*microX/mmPerRevHor);
  stepperY.setStepsPerRevolution(standardStepsPerRev*microY);
  stepperZ.setStepsPerMillimeter(standardStepsPerRev*microZ/mmPerRevVert);
  // stepperX.setSpeedInMillimetersPerSecond(feedRate);
  stepperY.setSpeedInRevolutionsPerSecond(rotationsPerSec);
  // stepperZ.setSpeedInMillimetersPerSecond(feedRate);
  // stepperX.setAccelerationInRevolutionsPerSecondPerSecond(10);
  stepperY.setAccelerationInRevolutionsPerSecondPerSecond(yAccel);
  stepperZ.setAccelerationInRevolutionsPerSecondPerSecond(zAccel);

  float numRotations = (coneHeight/feedRate)*rotationsPerSec;

  while(notDone){
    for(int i=0;i<numCuts;i++){
      float cutDepth = (i+1)*mmMaxCutDepth;
      if(i==numCuts-1){
        cutDepth = coneRadius;
      }

      stepperZ.setSpeedInMillimetersPerSecond(feedRate);

      stepperX.setSpeedInMillimetersPerSecond(feedRate);
      stepperX.setAccelerationInRevolutionsPerSecondPerSecond(5);
      stepperX.moveRelativeInMillimeters(cutDepth);

      stepperX.setSpeedInMillimetersPerSecond(feedRate*(cutDepth/coneHeight));
      stepperX.setAccelerationInRevolutionsPerSecondPerSecond(zAccel*(cutDepth/coneHeight));

      stepperX.setupRelativeMoveInMillimeters(-cutDepth);
      stepperY.setupRelativeMoveInRevolutions(numRotations);
      stepperZ.setupRelativeMoveInMillimeters(coneHeight);
  
      while((!stepperX.motionComplete()) || (!stepperY.motionComplete()) || (!stepperZ.motionComplete())){
        stepperX.processMovement();
        stepperY.processMovement();
        stepperZ.processMovement();
      }
  
      stepperZ.setSpeedInMillimetersPerSecond(3*feedRate);
      stepperZ.moveRelativeInMillimeters(-coneHeight);
    }
    notDone = false;
  }

  Serial.println("Odysseus...");
  
}

// -------------------------------------- End --------------------------------------
