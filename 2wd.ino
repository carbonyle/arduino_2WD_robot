#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <IRremote.h>

#define code1  4335 //  RIGHT 
#define code2  23205 // LEFT
#define code3  6375 //  FORWARD 
#define code4  19125 // BACKWARD

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *LeftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *RightMotor = AFMS.getMotor(3);

int RECV_PIN = 11; 
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {

Serial.begin(9600);
AFMS.begin();
LeftMotor->setSpeed(150);
RightMotor->setSpeed(150);
irrecv.enableIRIn();
}


void loop() {
      if (irrecv.decode(&results)) {
        unsigned int value = results.value;
        switch(value) {
           case code1:
             LeftMotor->run(FORWARD);
             delay(1000);
             LeftMotor->run(RELEASE);
             break; 
           case code2:
             RightMotor->run(BACKWARD);
             delay(1000);
             RightMotor->run(RELEASE);
             break;
           case code3:
             LeftMotor->run(FORWARD);
             RightMotor->run(BACKWARD);
             delay(1000);
             LeftMotor->run(RELEASE);
             RightMotor->run(RELEASE);
             break;
           case code4:
             LeftMotor->run(BACKWARD);
             RightMotor->run(FORWARD);
             delay(1000);
             LeftMotor->run(RELEASE);
             RightMotor->run(RELEASE);
             break;
        }
        irrecv.resume(); // Receive the next value
        Serial.println(value); // you can comment this line
      }
      else{
        delay(50);
        }
}
