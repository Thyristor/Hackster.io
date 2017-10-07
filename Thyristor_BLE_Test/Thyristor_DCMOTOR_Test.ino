/* 
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2 
---->	http://www.adafruit.com/products/1438
*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
//Adafruit_DCMotor *myMotor = AFMS.getMotor(1);

// Javi TEST: create pointer for the 4 motors
#define MOTOR_FRONT_LEFT  0
#define MOTOR_FRONT_RIGHT 1
#define MOTOR_REAR_LEFT   2
#define MOTOR_REAR_RIGHT  3

Adafruit_DCMotor *Motor[] = { AFMS.getMotor(MOTOR_FRONT_LEFT  + 1), 
                              AFMS.getMotor(MOTOR_FRONT_RIGHT + 1), 
                              AFMS.getMotor(MOTOR_REAR_LEFT   + 1),
                              AFMS.getMotor(MOTOR_REAR_RIGHT  + 1) };

// You can also make another motor on port M2
//Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);

// DECLARE FUNCTION PROTOTYPES
void MoveForward(void);
void MoveBackward(void);
void TurnLeft(void);
void TurnRight(void);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  /*myMotor->setSpeed(150);
  myMotor->run(FORWARD);
  myMotor->run(RELEASE);
*/

  // JAVI TEST: test the 4 motors 
  for(uint8_t i = 0; i != 4; ++i) {
    Motor[i]->setSpeed(150);
    Motor[i]->run(FORWARD);
    Motor[i]->run(RELEASE);
  }
}

void loop() {
  uint8_t j;
  
  Serial.print("tick");
  MoveForward();
  TurnLeft();
  
  Serial.print("tock");
  MoveBackward();
  TurnRight();
  
  Serial.print("tech");
  for(j = 0; j != 4; ++j)
    Motor[j]->run(RELEASE);
  delay(100);
}

void MoveForward() {
  uint8_t i, j;
  
  for(j = 0; j != 4; ++j) {
    Motor[j]->run(FORWARD);
    for(i=0; i<255; i++) {
      Motor[j]->setSpeed(i);  
      delay(10);
    }
    for(i = 255; i != 0; i--) {
      Motor[j]->setSpeed(i);  
      delay(10);
    }
  } // end for
}

void MoveBackward() {
  uint8_t i, j;
  
  for(j = 0; j != 4; ++j) {
    Motor[j]->run(BACKWARD);
    for(i = 0; i < 255; i++) {
      Motor[j]->setSpeed(i);  
      delay(10);
    }
    for(i = 255; i != 0; i--) {
      Motor[j]->setSpeed(i);  
      delay(10);
    }
  } // end for
}

void TurnLeft() {
  uint8_t i, j;

  Motor[MOTOR_FRONT_LEFT] ->run(BACKWARD);
  Motor[MOTOR_FRONT_RIGHT]->run(FORWARD);
  Motor[MOTOR_REAR_LEFT]  ->run(BACKWARD);
  Motor[MOTOR_REAR_RIGHT] ->run(FORWARD);
  for(j = 0; j != 4; ++j) {
    for(i = 0; i < 255; i++) {
      Motor[j]->setSpeed(i);  
      delay(10);
    }
    for(i = 255; i != 0; i--) {
      Motor[j]->setSpeed(i);  
      delay(10);
    }
  } // end for  
}
 
void TurnRight() {
  uint8_t i, j;

  Motor[MOTOR_FRONT_LEFT] ->run(FORWARD);
  Motor[MOTOR_FRONT_RIGHT]->run(BACKWARD);
  Motor[MOTOR_REAR_LEFT]  ->run(FORWARD);
  Motor[MOTOR_REAR_RIGHT] ->run(BACKWARD);
  for(j = 0; j != 4; ++j) {
    for(i = 0; i < 255; i++) {
      Motor[j]->setSpeed(i);  
      delay(10);
    }
    for(i = 255; i != 0; i--) {
      Motor[j]->setSpeed(i);  
      delay(10);
    }
  } // end for  
}

