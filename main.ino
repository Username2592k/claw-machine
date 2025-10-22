#include <Stepper.h>

const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup()
{
  myStepper.setSpeed(15);
  pinMode(3, INPUT);
  Serial.begin(9600);

  float offset_x = 0;
  float offset_y = 0;
}

void loop()
{
  Serial.println(digitalRead(3));
  
  if(digitalRead(3)){
    myStepper.step(stepsPerRevolution);
  }
  
  float offset_x = analogRead(A0) - 512;
  float offset_y = analogRead(A1) - 512;

  if( -20 < offset_x < 20 ){
    offset_x = 0; 
  }
  if( -20 < offset_y < 20 ){
    offset_y = 0;
  }
  
  String output = "X: " + String(offset_x) + " Y: " + String(offset_y);
  Serial.println(output);

  delay(500);
}