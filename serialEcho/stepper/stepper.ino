/*Example sketch to control a stepper motor with A4988/DRV8825 stepper motor driver and Arduino without a library. More info: https://www.makerguides.com */

// Define stepper motor connections and steps per revolution:
#define dirPin 2
#define stepPin 3
#define stepsPerRevolution 6400
int speedo = 1;
void setup() {
  // Declare pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  digitalWrite(dirPin, HIGH);
  accelerate();
}

void loop() {
  // Set the spinning direction clockwise:
  
  
  // Spin the stepper motor 1 revolution slowly:
  for (int i = 0; i < stepsPerRevolution; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(speedo);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(speedo);
  }
  //speedo --;
  
}
void accelerate(){

  for(int x = 0; x < 20; x++){
    int del = (20-x)*1;
    for (int i = 0; i < 1600; i++) {
      
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(del);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(del);
    }
  }
}
