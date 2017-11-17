//Initialize pins
int xPin = A1;
int yPin = A0;
int buttonPin = A2;
int zPin = A3;
int extraPin = A4;
int buttonPin2 = A5;

//Initialize variables for pins
int xvelocity = 0;
int yvelocity = 0;
int zvelocity = 0;
int blankvelocity = 0;
int buttonRead = 0;
int buttonRead2 = 0;

//Initialize other varaibles
boolean buttonState = 0;
boolean buttonState2 = 0;
int prevButtonRead = 0;
int prevButtonRead2 = 0;
String axisState = "Roaming";
String axisState2 = "Fixed";
boolean settingOrigin = 1;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  
  //Joystick 1
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  
  //Joystick 2
  pinMode(zPin, INPUT);
  pinMode(extraPin, INPUT);
  pinMode(buttonPin2, INPUT_PULLUP);
  
  // For versions prior to Arduino 1.0.1
  // pinMode(buttonPin, INPUT);
  // digitalWrite(buttonPin, HIGH);
  
}

void loop() {
  if (settingOrigin){
    setOrigin();
  }
  else {
    Serial.println("Cutting Mode Goes Here");
  }
}

void setOrigin(){
  //Read pin inputs
  xvelocity = analogRead(xPin);
  yvelocity = analogRead(yPin);
  buttonRead = digitalRead(buttonPin);
  zvelocity = analogRead(zPin);
  blankvelocity = analogRead(extraPin);
  buttonRead2 = digitalRead(buttonPin2);

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

  if (buttonRead2 == 1 && prevButtonRead2 == 0) {
    buttonState2 = !buttonState2;
    if (buttonState2 == 0) {
      axisState2 = "Fixed";
      }
    else {
      axisState2 = "Roaming";
      }
    }

  //Make velocities 0. Accounts for different origins of joystick
  if (xvelocity < 516 && xvelocity > 505){
    xvelocity = 512;
    }
  if (yvelocity < 516 && yvelocity > 505){
  yvelocity = 512;
  }
  if (zvelocity < 485 && zvelocity > 460){
  zvelocity = 512;
  }
  if (blankvelocity < 525 && blankvelocity > 520) {
  blankvelocity = 512;  
    }

  //Map velocities
  xvelocity = map(xvelocity, 0, 1023, -10, 10);
  yvelocity = map(yvelocity, 0, 1023, -10, 10);
  zvelocity = map(zvelocity, 0, 1023, -10, 10);
  blankvelocity = map (blankvelocity, 0, 1023, -10, 10);

 //Remove Velocity inputs if axis is fixed
 if (axisState.equals("Fixed")){
  xvelocity = 0;
  yvelocity = 0;
 }
 if (axisState2.equals("Fixed")){
  zvelocity = 0;
  blankvelocity = 0;
 }

  //Some print statements
  Serial.print("X: ");
  Serial.print(xvelocity);
  Serial.print(" | Y: ");
  Serial.print(yvelocity);
  Serial.print(" | Button: ");
  Serial.print(axisState);
  Serial.print(" | Z: ");
  Serial.print(zvelocity);
  Serial.print(" | Useless: ");
  Serial.print(blankvelocity);
  Serial.print(" | Z Origin: ");
  Serial.println(axisState2);
    
  //Set previous button read
  prevButtonRead = buttonRead;
  prevButtonRead2 = buttonRead2;
  
  //Delay
  delay(100);
  
  if (axisState.equals("Fixed") && axisState2.equals("Fixed")){
    settingOrigin = !settingOrigin;
  }
  
}
