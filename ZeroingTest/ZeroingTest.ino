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
int xRevsPerSecond = 0;
int xRead = 0;
int zRevsPerSecond = 0;
int zRead = 0;
int buttonRead = 0;

//Initialize other varaibles
boolean buttonState = 0;
int prevButtonRead = 0;
String axisState = "Roaming";
String axisState2 = "Fixed";
boolean settingOrigin = 1;

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
    Serial.println();
    Serial.println("Hit a key and press enter to start");     // signal initalization done
    while(Serial.available() == 0){}
    Serial.println("Cutting Mode Goes Here");
  }
}

void setOrigin(){
  //Read pin inputs
  xRead = analogRead(xPin);
  zRead = analogRead(zPin);
  buttonRead = digitalRead(buttonPin);

  //Toggles button states for button 1 and 2
  if (buttonRead == 1 && prevButtonRead == 0) {
    buttonState = !buttonState;
    if (buttonState == 0) {
      axisState = "Fixed";
      }
    else {
      axisState = "Roaming";
      }
    }

  //Make velocities 0. Accounts for different origins of joystick
  if (xRead > 450){
    xRevsPerSecond = defRevsPerSecond;
  } else if (xRead < 400){
    xRevsPerSecond = -defRevsPerSecond;
  } else {
    xRevsPerSecond = 0;
  }
  if (zRead > 480){
    zRevsPerSecond = defRevsPerSecond;
  } else if (zRead < 430){
    zRevsPerSecond = -defRevsPerSecond;
  } else {
    zRevsPerSecond = 0;
  }


 //Remove Velocity inputs if axis is fixed
 if (axisState.equals("Fixed")){
  xRevsPerSecond = 0;
  zRevsPerSecond = 0;
 }
    
  //Set previous button read
  prevButtonRead = buttonRead;
  
  if (axisState.equals("Fixed")){
    settingOrigin = !settingOrigin;
  }

  Serial.print("X: ");
  Serial.print(xRevsPerSecond);
  Serial.print(" | Y: ");
  Serial.print(zRevsPerSecond);
  Serial.print(" | Button: ");
  Serial.println(axisState);

  stepperX.setSpeedInRevolutionsPerSecond(xRevsPerSecond);
  stepperZ.setSpeedInRevolutionsPerSecond(zRevsPerSecond);
  stepperX.setAccelerationInRevolutionsPerSecondPerSecond(zeroingAccel);
  stepperZ.setAccelerationInRevolutionsPerSecondPerSecond(zeroingAccel);

  stepperX.setTargetPositionRelativeInRevolutions(xRevsPerSecond);
  stepperZ.setTargetPositionRelativeInRevolutions(zRevsPerSecond);
  
  stepperX.processMovement();
  stepperZ.processMovement();
  
}
