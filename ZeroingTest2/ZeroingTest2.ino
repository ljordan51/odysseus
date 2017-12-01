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
const int microX = 4;
const int microY = 1;
const int microZ = 4;

// set up other vars related to stepper movement
const int standardStepsPerRev = 200; // default number of steps per revolution without microstepping
const int setOrigSpeed = 1; // default stepper motor speed in revolutions per second for setting the origin
const int setOrigAccel = 5; // default stepper motor acceleration in revolutions per second per second for setting the origin
int dir = 0; // default direction of stepper motor movement for setting the origin (0 so there is no movement by default


// create the stepper motor objects
FlexyStepper stepperX;
FlexyStepper stepperY;
FlexyStepper stepperZ;


// Initialize joystick pins
const int xPin = A1; // left right motion output
const int zPin = A0; // up down motion output
const int buttonPin = A2; // click output

// Initialize variables for reading output values from joystick
int xRead = 0;
int zRead = 0;
int buttonRead = 1;

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

  // set the origin
  setOrigin();

  // wait for user input to move on to main loop
  Serial.println();
  Serial.println("Please press any key and then enter to start machining.");
  while(Serial.available() == 0){}
}

void loop() {
  Serial.println("Cutting Mode Goes Here");
}

void setOrigin(){
    // set stepper Z speed and acceleration
    stepperZ.setSpeedInRevolutionsPerSecond(setOrigSpeed);
    stepperZ.setAccelerationInRevolutionsPerSecondPerSecond(setOrigAccel);

    
    Serial.println("Wait 2 seconds. Please don't click the joytstick until you are done zeroing the Z-Axis.");
    delay(2000); // delay to make sure everything has time to settle, get back to default state, and user has time to stop messing with the joystick
    Serial.println("Now zero the Z-Axis by moving the joystick up and down. Click the joystick when you are done to zero the X-Axis.");

    // allow user to manipulate z-axis until button is clicked
    while ( buttonRead ) {
      zRead = analogRead(zPin); // zero is around 460
      // set direction based on value of joystick
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
      // set target position (either negative, positive, or 0)
      stepperZ.setTargetPositionRelativeInRevolutions(dir*150); // the number of revolutions is arbitrary (150 for now)
      stepperZ.processMovement();
      buttonRead = digitalRead(buttonPin); // check if button is clicked
    }

    // reset values to defaults so next while loop behaves properly
    buttonRead = 1;
    dir = 0;
    digitalWrite(STEPPERS_ENABLE, HIGH);

    // set stepper X speed and acceleration
    stepperX.setSpeedInRevolutionsPerSecond(setOrigSpeed);
    stepperX.setAccelerationInRevolutionsPerSecondPerSecond(setOrigAccel);
    
    Serial.println("Wait 2 seconds. Please don't click the joytstick until you are done zeroing the X-Axis.");
    delay(2000); // delay to make sure everything has time to settle, get back to default state, and user has time to stop messing with the joystick
    Serial.println("Now zero the X-Axis by moving the joystick left and right. Click the joystick when you are done.");

    // allow user to manipulate x-axis until button is clicked
    while ( buttonRead ) {
      xRead = analogRead(xPin); // zero is around 430
      // set direction based on value of joystick
      if (xRead > 450) {
        dir = 1;
        digitalWrite(STEPPERS_ENABLE, LOW);
      } else if (xRead < 400) {
        dir = -1;
        digitalWrite(STEPPERS_ENABLE, LOW);
      } else {
        dir = 0;
        digitalWrite(STEPPERS_ENABLE, HIGH);
      }
      // set target position (either negative, positive, or 0)
      stepperX.setTargetPositionRelativeInRevolutions(dir*150); // the number of revolutions is arbitrary (150 for now)
      stepperX.processMovement();
      buttonRead = digitalRead(buttonPin); // check if button is clicked
    }
    digitalWrite(STEPPERS_ENABLE, LOW); // make sure steppers are enabled
    Serial.println("Great job zeroing the cutter!");
}

