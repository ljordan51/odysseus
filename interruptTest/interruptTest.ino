const byte ledPin = 13;
const byte interruptPin = 2;
volatile byte state = HIGH;
long interrupt_time = 0;
long last_interrupt_time = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);
}

void loop() {
  blinky();
  while(millis() < 30000){
    Serial.println("ooo");
  }
  Serial.println("done");
  noInterrupts();
}

void blink() {
  long interrupt_time = millis();
  Serial.println(interrupt_time);
  Serial.println(last_interrupt_time);
  Serial.println(interrupt_time - last_interrupt_time);
  if (interrupt_time - last_interrupt_time > 200){
    Serial.println("change");
    state = digitalRead(interruptPin);
  }
  last_interrupt_time = interrupt_time;
  Serial.println();
  digitalWrite(ledPin, state);
}

void blinky() {
  while (millis() < 5000){
    digitalWrite(ledPin, 0);
    delay(200);
    digitalWrite(ledPin, 1);
    delay(200);
  }
}

