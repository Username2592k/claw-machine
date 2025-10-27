#include <Stepper.h>

const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

// DC Motor
int xMoterA1 = 2;
int xMoterA2 = 3;

int armMoterA1 = 6;
int armMoterA2 = 7;
int armMoterB1 = 4;
int armMoterB2 = 5;

int zMoterA1 = 8;
int zMoterA2 = 9;
int zMoterB1 = 10;
int zMoterB2 = 11;

// Status
int start_signal = 12;
bool isStarted = false;
int grapper_status = 0; // 0: None, 1: Grapping, 2: Moving-down, 3: Moving-up

void setup() {
  Serial.begin(9600);
  
  // DC Motor
  pinMode(xMoterA1, OUTPUT);
  pinMode(xMoterA2, OUTPUT);

  pinMode(zMoterA1, OUTPUT);
  pinMode(zMoterA2, OUTPUT);
  pinMode(zMoterB1, OUTPUT);
  pinMode(zMoterB2, OUTPUT);

  pinMode(armMoterA1, OUTPUT);
  pinMode(armMoterA2, OUTPUT);
  pinMode(armMoterB1, OUTPUT);
  pinMode(armMoterB2, OUTPUT);

  // Status
  pinMode(start_signal, INPUT);

  // Stepper Motor
  myStepper.setSpeed(15);
}

void loop() {
  float offset_x = analogRead(A0) - 512;
  float offset_y = analogRead(A1) - 512;

  // === Print System Status ===
  Serial.print("[X:");
  Serial.print(offset_x);
  Serial.print(" | Y:");
  Serial.print(offset_y);
  Serial.print("] ");

  if (isStarted) {
    Serial.print("Started ");
    switch (grapper_status) {
      case 0: Serial.print("(None)"); break;
      case 1: Serial.print("(Grapping)"); break;
      case 2: Serial.print("(Moving-down)"); break;
      case 3: Serial.print("(Moving-up)"); break;
    }
  } else {
    Serial.print("Idle");
  }

  Serial.print(" | Start Signal: ");
  Serial.println(digitalRead(start_signal));

  // === Control Logic ===
  if (isStarted) {
    // X-axis movement
    if (offset_x > 250) {
      digitalWrite(xMoterA1, HIGH);
      digitalWrite(xMoterA2, LOW);
    } 
    else if (offset_x < -250) {
      digitalWrite(xMoterA1, LOW);
      digitalWrite(xMoterA2, HIGH);
    } 
    else {
      digitalWrite(xMoterA1, LOW);
      digitalWrite(xMoterA2, LOW);
    }

    // X-axis movement
    if (offset_y > 250) {
      digitalWrite(zMoterA1, HIGH);
      digitalWrite(zMoterA2, LOW);
      digitalWrite(zMoterB1, LOW);
      digitalWrite(zMoterB2, HIGH);
    } 
    else if (offset_y < -250) {
      digitalWrite(zMoterA1, LOW);
      digitalWrite(zMoterA2, HIGH);
      digitalWrite(zMoterB1, HIGH);
      digitalWrite(zMoterB2, LOW);
    } 
    else {
      digitalWrite(zMoterA1, LOW);
      digitalWrite(zMoterA2, LOW);
      digitalWrite(zMoterB1, LOW);
      digitalWrite(zMoterB2, LOW);
    }

    // Grapper control
    if (digitalRead(start_signal) == HIGH) {
      if (grapper_status == 0) { 
        // if none -> moving-down
        digitalWrite(armMoterA1, LOW);
        digitalWrite(armMoterA2, HIGH);
        digitalWrite(armMoterB1, HIGH);
        digitalWrite(armMoterB2, LOW);
        analogWrite(A4, 100);
        analogWrite(A5, 100);
        grapper_status = 2;

        delay(1000);
      }
      else if (grapper_status == 2) {
        // if moving-down -> grapping -> moving-up
        
        
        digitalWrite(armMoterA1, HIGH);
        digitalWrite(armMoterA2, LOW);
        digitalWrite(armMoterB1, LOW);
        digitalWrite(armMoterB2, HIGH);
        analogWrite(A4, 100);
        analogWrite(A5, 100);
        grapper_status = 3;

        delay(1000);
      }
      else if(grapper_status == 3) {
        // if moving-up -> grapping
        digitalWrite(armMoterA1, LOW);
        digitalWrite(armMoterA2, LOW);
        digitalWrite(armMoterB1, LOW);
        digitalWrite(armMoterB2, LOW);
        analogWrite(A4, 0);
        analogWrite(A5, 0);
        grapper_status = 2;

        delay(1000);
      }
      else if(grapper_status == 2) {
        isStarted = false;
      }
    }
  } 
  else if (digitalRead(start_signal) == HIGH) {
    isStarted = true;
    delay(1000);
  }
}
