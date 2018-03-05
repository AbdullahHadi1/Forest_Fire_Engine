#include <Wire.h>
#include <Adafruit_MotorShield.h> /motorshield library
#include "utility/Adafruit_MS_PWMServoDriver.h"
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);

const int trigPin = 12;
const int echoPin = 13;

void setup() {
  AFMS.begin();  // default frequency 1.6KHz
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT_PULLUP);
  myMotor->setSpeed(100);
  myMotor2->setSpeed(100);

}

void loop() {
 
  long duration, distance;

  // The Trig ping is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Use echoPin to read the receiving signal: a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29; //divide by 2 to get one way distance
  // convert the time into a distance

  if(distance < 40){ //if object within 40 cm
  myMotor->run(FORWARD);
  myMotor2->run(BACKWARD);
}
  else{
    delay(40);
    myMotor->run(FORWARD);
    myMotor2->run(FORWARD);
  }
}
