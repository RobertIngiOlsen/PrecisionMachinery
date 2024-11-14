#include <Servo.h> 
const int analogPin1 = A0; //Measure state of the LED
Servo S1;  //Charging servo
Servo S2;  //Dispensing servo
int currentAngleS1 = 0;
int currentAngleS2 = 0;

void setup() {
  S1.attach(9);
  S2.attach(10);
  Serial.begin(9600);
  S1.write(currentAngleS1);
  S2.write(currentAngleS2);
}

void loop() {
  float initialVoltage = (analogRead(analogPin1) * 5.0) / 1023.0;
  unsigned long startTime = millis();
  bool isStable = true;
  bool isEmpty = true;
  moveServoToAngle(S1, currentAngleS1, 0);

  while (millis() - startTime < 5000) {
    float currentVoltage = (analogRead(analogPin1) * 5.0) / 1023.0;
    //Serial.println(currentVoltage);

    if (abs(currentVoltage - initialVoltage) > 0.5) {
      isStable = false;
      break;
    }
    if (currentVoltage >= 0.5) {
      isEmpty = false;
    }

    delay(100);
  }
  if (isEmpty){
    moveServoToAngle(S1, currentAngleS1, 10);
    Serial.println("Tomt");
    delay(30000);
  }
  else if (isStable) {
    moveServoToAngle(S1, currentAngleS1, 10);
    delay(100);
    moveServoToAngle(S2, currentAngleS2, 100);
    delay(1000);
    moveServoToAngle(S2, currentAngleS2, 10);
    delay(100);
    Serial.println("Tilbuid");
  } 
  else {
    Serial.print("Ad hlada");
    delay(30000);
  }
  delay(1000);
}

void moveServoToAngle(Servo &servo, int &currentAngle, int targetAngle) {
  while (currentAngle != targetAngle) {
    if (currentAngle < targetAngle) {
      currentAngle++;
    } else if (currentAngle > targetAngle) {
      currentAngle--;
    }
    servo.write(currentAngle);
    delay(15);
  }
}