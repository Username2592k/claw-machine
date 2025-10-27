#include <Stepper.h>

const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

// DC Moter
int moterA1 = 2;
int moterA2 = 3;

int moterC1 = 6;
int moterC2 = 7;
int moterD1 = 4;
int moterD2 = 5;

int moterB1 = 8;
int moterB2 = 9;
int moterB3 = 10;
int moterB4 = 11;

// Status
int start_signal = 12;
bool isStarted = false;
bool isGrapping = false;

void setup() {
  Serial.begin(9600);
  
  // DC Moter
  pinMode(moterA1, OUTPUT);
  pinMode(moterA2, OUTPUT);

  pinMode(moterC1, OUTPUT);
  pinMode(moterC2, OUTPUT);
  pinMode(moterD1, OUTPUT);
  pinMode(moterD2, OUTPUT);

  pinMode(moterB1, OUTPUT);
  pinMode(moterB2, OUTPUT);
  pinMode(moterB3, OUTPUT);
  pinMode(moterB4, OUTPUT);

  // Status
  pinMode(start_signal, INPUT);

  // Stepper Moter
  myStepper.setSpeed(15);
}

void loop() {
  float offset_x = analogRead(A0) - 512;
  float offset_y = analogRead(A1) - 512;

  // Print Status
  Serial.print(offset_x);
  Serial.print(",");
  Serial.print(offset_y);
  Serial.print(" - ");
  if(isStarted){
    Serial.print("Started");
    if(isGrapping){
      Serial.print(": grapping");
    }
    else{
      Serial.print(": none");
    }
  }
  else{
    Serial.print("none");
  }
  Serial.println("");
  
  if(isStarted){
    // Movement
    if(offset_x > 250){
      digitalWrite(moterA1, HIGH);
      digitalWrite(moterA2, LOW);
    }
    else if(offset_x < -250){
      digitalWrite(moterA1, LOW);
      digitalWrite(moterA2, HIGH);
    }
    else{
      digitalWrite(moterA1, LOW);
      digitalWrite(moterA2, LOW);
    }
  
    if(offset_y > 250){
      digitalWrite(moterC1, HIGH);
      digitalWrite(moterC2, LOW);
      digitalWrite(moterD1, LOW);
      digitalWrite(moterD2, HIGH);
      analogWrite(A4, 200);
      analogWrite(A5, 200);
    }
    else if(offset_y < -250){
      digitalWrite(moterC1, LOW);
      digitalWrite(moterC2, HIGH);
      digitalWrite(moterD1, HIGH);
      digitalWrite(moterD2, LOW);
      analogWrite(A4, 200);
      analogWrite(A5, 200);
    }
    else{
      digitalWrite(moterC1, LOW);
      digitalWrite(moterC2, LOW);
      digitalWrite(moterD1, LOW);
      digitalWrite(moterD2, LOW);
      analogWrite(A4, 0);
      analogWrite(A5, 0);
    }

    if(start_signal == HIGH){
      //digitalWrite(moterB1, HIGH);
      //digitalWrite(moterB2, LOW);
      //digitalWrite(moterB3, HIGH);
      //digitalWrite(moterB4, LOW);
      isStarted = false;
    }
  }
  else if(start_signal == HIGH){
    isStarted = true;
    delay(1000);
  }

  Serial.println(start_signal);
}
