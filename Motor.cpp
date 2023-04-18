/*
* Motor.cpp
*
*  Created on: Jan 5, 2023
*      Author: Chris Hanes for Good Filling LLC.
*/
#include "Motor.h"

void PWM::updateDutyCycle(int dutyCycle) {
  //base function to set both duty cycles
  //clean duty cycle: between 0 and MAX_DUTY_CYCLE
  dutyCycle = min(max(dutyCycle,0), this->MAX_DUTY_CYCLE);
  ledcWrite(this->PWMChannel1, dutyCycle);
  ledcWrite(this->PWMChannel2, dutyCycle);

  cout << "Setting Duty Cycle to: " << dutyCycle << " of " << MAX_DUTY_CYCLE <<endl;
};

void PWM::updateDutyCycle(int dutyCycle, int index) {
  //Overload to allow for indexing the 2 PWM signals
  //clean duty cycle: between 0 and MAX_DUTY_CYCLE
  dutyCycle = min(max(dutyCycle,0), this->MAX_DUTY_CYCLE);
  if (index == 0) {
    ledcWrite(this->PWMChannel1, dutyCycle);
  } else {
    ledcWrite(this->PWMChannel2, dutyCycle);
  }
  cout << "Setting Duty Cycle "<< index <<  " to: " << dutyCycle << " of " << MAX_DUTY_CYCLE <<endl;
};


void PWM::print() {
    cout << "Freq: " << this->PWMFreq << endl;
    cout << "Channel1: " << this->PWMChannel1 << endl;
    cout << "Channel1: " << this->PWMChannel2 << endl;
    cout << "Resolution: " << this->PWMResolution << "bit"<< endl;
    cout << "Max Duty Cycle: " << this->MAX_DUTY_CYCLE << endl;
}

void Motor::print() {
    cout << "In1Pin: " << this->In1Pin << endl;
    cout << "In2Pin " << this->In2Pin << endl;
    cout << "Direction " << this->dir << endl;
    this->pwm.print();
};//Motor::print()

void Motor::enable() {
  //turn on motor
  int dutyCycle_Int = (int)(((float)this->dutyCycle/100) * this->pwm.MAX_DUTY_CYCLE);//convert duty cycle to N bit integer

  if (this->dir == FORWARD){
    this->pwm.updateDutyCycle(dutyCycle_Int, 0); //enable the forward pin
    this->pwm.updateDutyCycle(0, 1); //disable the other pin
  } else {
    this->pwm.updateDutyCycle(0, 0); //enable the forward pin
    this->pwm.updateDutyCycle(dutyCycle_Int, 1); //disable the other pin
  }
};//Motor::enable()

void Motor::disable() {
  //disables the motor
  this->pwm.updateDutyCycle(0); //disable both pins
};//Motor::disable()

void Motor::setPWM(int dutyCycle_perc = 100) {
  //sets the PWM signal for the given motor.  
  //dutyCycle_Float is a float between 0.0 and 100.0 that controls the speed of the motor as a % duty cycle
  this->dutyCycle = dutyCycle_perc;
};//Motor::setPWM()

void Motor::setDirection(Direction dir) {
  //FORWARD and BACKWARD definitions are based on motor controller manufacturer
  this->disable();//disable motor
  this->dir = dir;//update stored motor direction in object
  usleep(1000000);//pause for 1 second for motor to stop
  /*^^^ (needed because PWM pin changes depending on direction to keep BRAKE type consistant)
  */
  if (dir == FORWARD){
    cout << "ONWARDS, TO VICTORY" << endl;
  } else if (dir == BACKWARD) {
    cout << "RETREAT" << endl;
  }//else if Backward
  this->pwm.updateDutyCycle(100); //enable the PWM pin at 100% duty cycle to ensure startup.  Do not overwrite motor's saved dutycycle
  usleep(100000);//pause for 0.1 seconds for motor to start
  this->pwm.updateDutyCycle(this->dutyCycle); //enable the PWM pin at desired duty cycle
};//Motor::setDirection()

void Motor::toggleDirection() {
  this->disable();//disable motor
  if (this->dir == FORWARD){
    this->setDirection(BACKWARD);
  } else {
    this->setDirection(FORWARD);
  }
};//Motor::toggleDirection()