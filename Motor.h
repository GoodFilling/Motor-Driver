/*
* Motor.h
*
*  Created on: Jan 5, 2023
*      Author: Chris Hanes for Good Filling LLC.
* https://www.learncpp.com/cpp-tutorial/class-code-and-header-files/
*/

#ifndef MOTOR_H
#define MOTOR_H
#include <algorithm>
#include <math.h>
#include <Arduino.h>
#include <iostream>
using namespace std;
#include <unistd.h>
//#include "esp32-hal.h"


enum Direction {
  FORWARD, BACKWARD
};

class PWM {
  public:
    int PWMFreq; 
    int PWMChannel1;
    int PWMChannel2;
    int PWMResolution;
    int MAX_DUTY_CYCLE;

    PWM(int channel1 = 0, int channel2 = 1, int freq = 50, int resolution = 10) {
      PWMChannel1 = channel1;
      PWMChannel2 = channel2;
      PWMFreq = freq; // default 50 hz (50)
      PWMResolution = resolution; //bit resolution for PWM, up to 16 bits
      MAX_DUTY_CYCLE = (int)(pow(2,resolution) - 1);
      ledcSetup(PWMChannel1, PWMFreq, PWMResolution);//initialize PWM on pin
      ledcSetup(PWMChannel2, PWMFreq, PWMResolution);//initialize PWM on pin

      //ledcAttachPin(LEDPin, PWMChannel); //Moved to motor constructor       
    }
    ~PWM() {
      this->updateDutyCycle(0);
    }//PWM destructor - shouldn't need since no pointers or dynamically allocated memory, but it's here just in case
    void updateDutyCycle(int dutyCycle);
    void updateDutyCycle(int dutyCycle, int index);
    void print();

};

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


class Motor {
  public:
    int In1Pin;
    int In2Pin;
    PWM pwm;
    Direction dir;//holds pin data for motors, not hard coded/initialized here so it can be set/edited in main
    float dutyCycle;
    Motor(int I1P = NULL, int I2P = NULL, PWM pwm_in = NULL) {
      In1Pin = I1P;
      In2Pin = I2P;
      pwm = pwm_in;
      dir = FORWARD;
      ledcAttachPin(In1Pin, pwm.PWMChannel1);
      ledcAttachPin(In2Pin, pwm.PWMChannel2);
    };//Motor Constructor
    ~Motor() {
      this->pwm.~PWM();
      ledcDetachPin(this->In1Pin);
      ledcDetachPin(this->In2Pin);

    }//Motor destructor - it should automatically destruct when it leaves scope, but keeping this here just in case we find we need it
    void print();
    void enable();
    void disable();
    void setPWM(float dutyCycle_Float);
    void setDirection(Direction dir);
    void toggleDirection();
};//class Motor    

void Motor::print() {
    cout << "In1Pin: " << this->In1Pin << endl;
    cout << "In2Pin " << this->In2Pin << endl;
    cout << "Direction " << this->dir << endl;
    this->pwm.print();
};//Motor::print()

void Motor::enable() {
  //turn on motor
  int dutyCycle_Int = (int)(this->dutyCycle/100 * this->pwm.MAX_DUTY_CYCLE);//convert duty cycle to N bit integer

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

void Motor::setPWM(float dutyCycle_Float = 100) {
  //sets the PWM signal for the given motor.  
  //dutyCycle_Float is a float between 0.0 and 100.0 that controls the speed of the motor as a % duty cycle
  //pwm.updateDutyCycle() has cleaning for the duty cycle already, so no cleaning needed here
  this->dutyCycle = dutyCycle_Float;
};//Motor::setPWM()

void Motor::setDirection(Direction dir) {
  //FORWARD and BACKWARD definitions are based on motor controller manufacturer
  this->disable();//disable motor
  this->dir = dir;//update stored motor direction in object
  usleep(1000000);//pause for 1 second for motor to stop
  /*^^^ (needed because PWM pin changes depending on direction to keep BRAKE type consistant)
  * see https://goodfilling.atlassian.net/l/cp/TmJou2ar PWM Control Block Diagram
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

#endif /* MOTOR_H */