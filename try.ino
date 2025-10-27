#include <Stepper.h>

const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

// DC Moter
int moterA1 = 2;
int moterA2 = 3;
int moterB1 = 0;
int moterB2 = 1;

int moterC1 = 6;
int moterC2 = 7;
int moterD1 = 4;
int moterD2 = 5;

void setup() {
  Serial.begin(9600);
  
  // DC Moter
  pinMode(moterA1, OUTPUT);
  pinMode(moterA2, OUTPUT);
  pinMode(moterB1, OUTPUT);
  pinMode(moterB2, OUTPUT);

  pinMode(moterC1, OUTPUT);
  pinMode(moterC2, OUTPUT);
  pinMode(moterD1, OUTPUT);
  pinMode(moterD2, OUTPUT);

  // Stepper Moter
  myStepper.setSpeed(15);
}

void loop() {
  float offset_x = analogRead(A0) - 512;
  float offset_y = analogRead(A1) - 512;

  Serial.print(offset_x);
  Serial.print(",");
  Serial.println(offset_y);

  if(offset_x > 100){
    digitalWrite(moterA1, HIGH);
    digitalWrite(moterA2, LOW);
    digitalWrite(moterB1, LOW);
    digitalWrite(moterB2, HIGH);
  }
  else if(offset_x < -100){
    digitalWrite(moterA1, LOW);
    digitalWrite(moterA2, HIGH);
    digitalWrite(moterB1, HIGH);
    digitalWrite(moterB2, LOW);
  }
  else{
    digitalWrite(moterA1, LOW);
    digitalWrite(moterA2, LOW);
    digitalWrite(moterB1, LOW);
    digitalWrite(moterB2, LOW);
  }

  if(offset_y > 100){
    digitalWrite(moterC1, HIGH);
    digitalWrite(moterC2, LOW);
    digitalWrite(moterD1, LOW);
    digitalWrite(moterD2, HIGH);
  }
  else if(offset_y < -100){
    digitalWrite(moterC1, LOW);
    digitalWrite(moterC2, HIGH);
    digitalWrite(moterD1, HIGH);
    digitalWrite(moterD2, LOW);
  }
  else{
    digitalWrite(moterC1, LOW);
    digitalWrite(moterC2, LOW);
    digitalWrite(moterD1, LOW);
    digitalWrite(moterD2, LOW);
  }
}
