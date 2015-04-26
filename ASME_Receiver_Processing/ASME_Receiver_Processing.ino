#include <VSync.h>
#include <Wire.h> 
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"
#include <Servo.h>

//Receive data for 7 variables from Processing
ValueReceiver<7> receiver;

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

//Create motors
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);
Adafruit_DCMotor *motor3 = AFMS.getMotor(3);
Adafruit_DCMotor *motor4 = AFMS.getMotor(4);

//SERVO MOTOR
Servo servo1;

//Input variables -- received from the vSync library object
int up, down, left, right, front, back, servo;

/*******************
/ setup function 
/*******************/
void setup()
{
  Serial.begin(9600);
  //Begin motor shield
  AFMS.begin();
  // setup for vSync control. Order of these must correspond with
  // the order of the sender in Processing
  receiver.observe(up);
  receiver.observe(down);
  receiver.observe(left);
  receiver.observe(right);
  receiver.observe(front);
  receiver.observe(back);
  receiver.observe(servo);
}

/*******************
/ loop function 
/*******************/
void loop()
{ 
  //Iteration variables
  uint8_t i;
  
  //Sync variables between Processing and Arduino
  receiver.sync();
  sender.sync();
  
  //MOTOR CONTROL:
  //Stop all motion
  if(up == 0 || down == 0 || left == 0 || right == 0 || front == 0 || back == 0){
    motor1->setSpeed(0);
    motor2->setSpeed(0);
    motor3->setSpeed(0);
    motor4->setSpeed(0);
  }
  delay(200);
  //////////////////////////////////////////////
  //Move Forward
  //////////////////////////////////////////////
  if(up == 1 && down == 0 && left == 0 && right == 0 && front == 0 && back == 0){
    motor1->run(FORWARD);
    motor2->run(FORWARD);
    //Ramp up
    rampUp(12);
    //Maintain speed
    while(up == 1)
    {
      receiver.sync();
      sender.sync();
      steering();
    }
  }
  //////////////////////////////////////////////
  //Move Backward
  //////////////////////////////////////////////
  if(down == 1 && up == 0 && left == 0 && right == 0 && front == 0 && back == 0) {
    motor1->run(BACKWARD);
    motor2->run(BACKWARD);
    //Ramp up
    rampUp(12);
    //Maintain speed
    while(down == 1)
    {
      receiver.sync();
      sender.sync();
      steering();
    }
  }
  
  //////////////////////////////////////////////
  //Move Left
  //////////////////////////////////////////////
  if(left == 1 && right == 0 && up == 0 && down == 0){
    motor1->run(BACKWARD);
    motor2->run(FORWARD);
    //Ramp up
    rampUp(12);
    //Maintain speed
    while(left == 1)
    {
      motor1->setSpeed(255);
      motor2->setSpeed(255);
      receiver.sync();
      sender.sync();
    }
  }
  //////////////////////////////////////////////
  //Move Right
  //////////////////////////////////////////////
  if(right == 1 && left == 0 && up == 0 && down == 0 && front == 0 && back == 0){
    motor1->run(FORWARD);
    motor2->run(BACKWARD);
    //Ramp up
    rampUp(12);
    //Maintain speed
    while(right == 1)
    {
      motor1->setSpeed(255);
      motor2->setSpeed(255);
      receiver.sync();
      sender.sync();
    }
  }
  
  //////////////////////////////////////////////
  //Rotate Back Direction 1
  //////////////////////////////////////////////
  if(back == 1 && right == 0 && left == 0 && up == 0 && down == 0 && front == 0){
    motor3->run(FORWARD);
    //Ramp up
    rampUp(3);
    //Maintain speed
    while(back == 1)
    {
      receiver.sync();
      sender.sync();
      if(front == 0){
        motor3->setSpeed(255);
        motor4->setSpeed(0);
      }else if (front == 1){
        motor3->setSpeed(255);
        motor4->setSpeed(255);
      }
    }
  }
  
  //////////////////////////////////////////////
  //Rotate Back Direction 2
  //////////////////////////////////////////////
  if(back == 2 && right == 0 && left == 0 && up == 0 && down == 0 && front == 0){
    motor3->run(BACKWARD);
    //Ramp up
    rampUp(3);
    //Maintain speed
    while(back == 2)
    {
      motor3->setSpeed(255);
      receiver.sync();
      sender.sync();
    }
  }
  
  //////////////////////////////////////////////
  //Rotate Front Direction 1
  //////////////////////////////////////////////
  if(front == 1 && right == 0 && left == 0 && up == 0 && down == 0 && back == 0){
    motor4->run(FORWARD);
    //Ramp up
    rampUp(4);
    //Maintain speed
    while(front == 1)
    {
      receiver.sync();
      sender.sync();
      if(back == 0){
        motor4->setSpeed(255);
        motor3->setSpeed(0);
      }else if (back == 1){
        motor3->setSpeed(255);
        motor4->setSpeed(255);
      }
    }
  }
  
  //////////////////////////////////////////////
  //Rotate Front Direction 2
  //////////////////////////////////////////////
  if(front == 2 && right == 0 && left == 0 && up == 0 && down == 0 && back == 0){
    motor4->run(BACKWARD);
    //Ramp up
    rampUp(4);
    //Maintain speed
    while(front == 2)
    {
      motor4->setSpeed(255);
      receiver.sync();
      sender.sync();
    }
  }
  
  //////////////////////////////////////////////
  //COMBO Rotate Front Direction 2 & Move Forward
  //////////////////////////////////////////////
  if(up == 1 && down == 0 && left == 0 && right == 0 && front == 1 && back == 0){
    motor1->run(FORWARD);
    motor2->run(FORWARD);
    motor4->run(BACKWARD);
    //Ramp up
    rampUp(124);
    //Maintain speed
    while(up == 1 && front == 1)
    {
      motor1->setSpeed(255);
      motor2->setSpeed(255);
      motor4->setSpeed(255);
      receiver.sync();
      sender.sync();
    }
  }
  
  /////////////////////////////////////////////////////
  //COMBO Rotate Front Direction 1 & Back Direction 1
  /////////////////////////////////////////////////////
  
  if(up == 0 && down == 0 && left == 0 && right == 0 && front == 1 && back == 1){
    motor3->run(FORWARD);
    motor4->run(FORWARD);
    //Ramp up
    rampUp(34);
    //Maintain speed
    while(front == 1 && back == 1)
    {
      motor3->setSpeed(255);
      motor4->setSpeed(255);
      receiver.sync();
      sender.sync();
    }
  }
  
  /////////////////////////////////////////////////////
  //COMBO Rotate Front Direction 1 & Back Direction 1 & Move Forward
  /////////////////////////////////////////////////////
  
  if(up == 1 && down == 0 && left == 0 && right == 0 && front == 1 && back == 1){
    motor1->run(FORWARD);
    motor2->run(FORWARD);
    motor3->run(FORWARD);
    motor4->run(FORWARD);
    //Ramp up
    rampUp(1234);
    //Maintain speed
    while(front == 1 && back == 1 && up == 1)
    {
      motor1->setSpeed(255);
      motor2->setSpeed(255);
      motor3->setSpeed(255);
      motor4->setSpeed(255);
      receiver.sync();
      sender.sync();
    }
  }
  
  /////////////////////////////////////////////////////
  //COMBO Rotate Front Direction 2 & Back Direction 2
  /////////////////////////////////////////////////////
  
  if(up == 0 && down == 0 && left == 0 && right == 0 && front == 2 && back == 2){
    motor3->run(BACKWARD);
    motor4->run(BACKWARD);
    //Ramp upaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
    rampUp(34);
    //Maintain speed
    while(front == 2 && back == 2)
    {
      motor3->setSpeed(255);
      motor4->setSpeed(255);
      receiver.sync();
      sender.sync();
    }
  }
  
  ////////////////////////////////////////////////////////
  //Servo Pulley Open
  ////////////////////////////////////////////////////////
  if(up == 0 && down == 0 && left == 0 && right == 0 && front == 0 && back == 0 && servo == 1){
    //Attach servo motor to pin 10
    servo1.attach(10);
    if(servo1.read() < 10){
      for(i = 0; i <= 90; i=i+1){
        servo1.write(i);
        delay(15);
      }
    }
    servo1.detach();
  }
  
  ////////////////////////////////////////////////////////
  //Servo Pulley Close
  ////////////////////////////////////////////////////////
  if(up == 0 && down == 0 && left == 0 && right == 0 && front == 0 && back == 0 && servo == 2){
    servo1.attach(10);
    int k = 90;
    if(servo1.read() > 80){
      for(i = 0; i <= 90; i=i+1){
        servo1.write(k-i);
        delay(15);
      }
    }
    servo1.detach();
  }
}

/////////////////////////////////////////////////////
// Steering while moving forward/backward
/////////////////////////////////////////////////////
void steering(){
  if(left == 0 && right == 0 && front == 0 && back == 0){
      motor1->setSpeed(120);
      motor2->setSpeed(120);
      motor3->setSpeed(0);
      motor4->setSpeed(0);
  }else if(left == 1){
    motor1->setSpeed(122);
    motor2->setSpeed(255);
  }else if(right == 1){
    motor1->setSpeed(255);
    motor2->setSpeed(122);
  }else if(front == 1){
    motor1->setSpeed(255);
    motor2->setSpeed(255);
    motor4->run(FORWARD);
    motor4->setSpeed(255);
  }else if(front == 2){
    motor1->setSpeed(255);
    motor2->setSpeed(255);
    motor4->run(BACKWARD);
    motor4->setSpeed(255);
  }else if(back == 1){
    motor1->setSpeed(255);
    motor2->setSpeed(255);
    motor3->run(FORWARD);
    motor3->setSpeed(255);
  }else if(back == 2){
    motor1->setSpeed(255);
    motor2->setSpeed(255);
    motor3->run(BACKWARD);
    motor3->setSpeed(255);
  }
}

void rampUp(int motors) {
  //Iteration variables
  uint8_t i;
  //Switch for different motors
  switch (motors) {
    case 12:
      for (i=5; i<120; i+=2) {
        motor1->setSpeed(i); 
        motor2->setSpeed(i); 
        delay(1);
      }
      break;
    case 3:
      for (i=5; i<255; i+=2) {
        motor3->setSpeed(i); 
        delay(1);
      }
      break;
    case 4:
      for (i=5; i<255; i+=2) {
        motor4->setSpeed(i); 
        delay(1);
      }
      break;
    case 124:
      for (i=5; i<255; i+=2) {
        motor1->setSpeed(i); 
        motor2->setSpeed(i); 
        motor4->setSpeed(i);
        delay(1);
      }
      break;
    case 34:
      for (i=5; i<255; i+=2) {
        motor3->setSpeed(i); 
        motor4->setSpeed(i); 
        delay(1);
      }
      break;
    case 1234:
      for (i=5; i<255; i+=2) {
        motor1->setSpeed(i); 
        motor2->setSpeed(i); 
        motor3->setSpeed(i); 
        motor4->setSpeed(i); 
        delay(1);
      }
      break;
    default:
      break;
  }
}
