/*
* Motor.cpp
*
*  Created on: Jan 5, 2023
*      Author: Chris Hanes for Good Filling LLC.
*/
#include "Motor.h"

Motor::Motor(){
  //do nothing
}

Motor::Motor(int I1P, int I2P, int pwmChannel1, int pwmChannel2) {
  log("Motor Constructor");
  In1Pin = I1P;
  In2Pin = I2P;
  this->pwm = PWM(pwmChannel1, pwmChannel2, 50, 10);
  dir = FORWARD;
  ledcAttachPin(In1Pin, this->pwm.PWMChannel1);
  ledcAttachPin(In2Pin, this->pwm.PWMChannel2);
}//Motor Constructor

// Motor::~Motor() {
//   log("Motor Destructor");
//   //pwm.~PWM();
//   ledcDetachPin(this->In1Pin);
//   ledcDetachPin(this->In2Pin);

// }//Motor destructor - it should automatically destruct when it leaves scope, but keeping this here just in case we find we need it

void Motor::print() {
  //int dir = this->dir;
  log("In1Pin: %i", this->In1Pin);
  log("In2Pin: %i", this->In2Pin);
  log("Direction: %i  (Forward = 0, Backward = 1)", this->dir);
  pwm.print();
}//Motor::print()

void Motor::enable() {
  isMotorEnabled = true;
  log("Motor Enable");
  //turn on motor
  int dutyCycle_Int = (int)(((float)this->dutyCycle/100) * this->pwm.MAX_DUTY_CYCLE);//convert duty cycle to N bit integer

  if (this->dir == FORWARD){
    this->pwm.updateDutyCycle(dutyCycle_Int, 0); //enable the forward pin
    this->pwm.updateDutyCycle(0, 1); //disable the other pin
  } else {
    this->pwm.updateDutyCycle(0, 0); //disable the forward pin
    this->pwm.updateDutyCycle(dutyCycle_Int, 1); //enable the other pin
  }
}//Motor::enable()

void Motor::disable() {
  isMotorEnabled = false;
  log("Motor Disable");
  //disables the motor
  this->pwm.updateDutyCycle(0); //disable both pins
}//Motor::disable()

void Motor::setPWM(int dutyCycle_perc = 100) {
  //sets the PWM signal for the given motor.  
  //dutyCycle_Float is a float between 0.0 and 100.0 that controls the speed of the motor as a % duty cycle
  this->dutyCycle = (float)dutyCycle_perc;
  log("DutyCycle%%: %i", dutyCycle_perc);
}//Motor::setPWM()

void Motor::setDirection(Direction dir) {
  log("Motor Set Direction");
  //FORWARD and BACKWARD definitions are based on motor controller manufacturer
  this->disable();//disable motor
  this->dir = dir;//update stored motor direction in object
  usleep(1000000);//pause for 1 second for motor to stop
  /*^^^ (needed because PWM pin changes depending on direction to keep BRAKE type consistant)
  */
  if (dir == FORWARD){
    log("ONWARDS, TO VICTORY");
  } else if (dir == BACKWARD) {
    log("RETREAT");
  }
}//Motor::setDirection()

void Motor::toggleDirection() {
  this->disable();//disable motor
  if (this->dir == FORWARD){
    this->setDirection(BACKWARD);
  } else {
    this->setDirection(FORWARD);
  }
}//Motor::toggleDirection()