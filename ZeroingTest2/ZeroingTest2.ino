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

const int microX = 1;
const int microY = 1;
const int microZ = 1;
const int standardStepsPerRev = 200;
int defRevsPerSecond = 50;
int zeroingAccel = 100;
int dir = 0;


// create the stepper motor object
//
FlexyStepper stepperX;
FlexyStepper stepperY;
FlexyStepper stepperZ;


//Initialize pins
int xPin = A1;
int zPin = A0;
int buttonPin = A2;

//Initialize variables for pins
int xRead = 0;
int zRead = 0;
int buttonRead = 1;
boolean settingOrigin = 1;
boolean started = 0;

void setup() {
  
  //Joystick 1
  pinMode(xPin, INPUT);
  pinMode(zPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);

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

  stepperX.setStepsPerRevolution(standardStepsPerRev*microX);
  stepperY.setStepsPerRevolution(standardStepsPerRev*microY);
  stepperZ.setStepsPerRevolution(standardStepsPerRev*microZ);
 
  Serial.begin(9600);
  
}

void loop() {
  if (settingOrigin){
    setOrigin();
  }
  else {
    if (!started) {
      Serial.println();
      Serial.println("Hit a key and press enter to start");     // signal initalization done
      while(Serial.available() == 0){}
      started = 1;
    }
    Serial.println("Cutting Mode Goes Here");
  }
}

void setOrigin(){
    stepperZ.setStepsPerRevolution(standardStepsPerRev*microY);
    stepperZ.setSpeedInRevolutionsPerSecond(1);
    stepperZ.setAccelerationInRevolutionsPerSecondPerSecond(5);
    Serial.println("Wait 5 seconds");
    delay(5000);
    Serial.println("First zero the Z-Axis");
    while ( buttonRead ) {
      zRead = analogRead(zPin);
      if (zRead > 480) {
        dir = 1;
        digitalWrite(STEPPERS_ENABLE, LOW);
      } else if (zRead < 430) {
        dir = -1;
        digitalWrite(STEPPERS_ENABLE, LOW);
      } else {
        dir = 0;
        digitalWrite(STEPPERS_ENABLE, HIGH);
      }
      stepperZ.setTargetPositionRelativeInRevolutions(dir*150); // just run for a while idk
      stepperZ.processMovement();
      buttonRead = digitalRead(buttonPin);
    }
    
    
    settingOrigin = 0;
}
