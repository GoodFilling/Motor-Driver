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
    }//PWM destructor
    void updateDutyCycle(int dutyCycle);
    void updateDutyCycle(int dutyCycle, int index);
    void print();

};

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
    void setPWM(int dutyCycle_perc);
    void setDirection(Direction dir);
    void toggleDirection();
};//class Motor    
#endif /* MOTOR_H */