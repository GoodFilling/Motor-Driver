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
#include <unistd.h>
#include "PWM.h"
//#include "esp32-hal.h"


enum Direction {
  FORWARD, BACKWARD
};

class Motor {
  public:
    Motor();
    Motor(int I1P, int I2P, int pwmChannel1, int pwmChannel2);
    // ~Motor();
    int In1Pin;
    int In2Pin;
    Direction dir;//holds pin data for motors, not hard coded/initialized here so it can be set/edited in main
    float dutyCycle;
    void print();
    void enable();
    void disable();
    void setPWM(int dutyCycle_perc);
    void setDirection(Direction dir);
    void toggleDirection();
  private:
    PWM pwm;
};//class Motor    
#endif /* MOTOR_H */