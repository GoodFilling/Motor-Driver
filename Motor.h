/*
* Motor.h
*
*  Created on: Jan 5, 2023
*      Author: Chris Hanes for Good Filling LLC.
* https://www.learncpp.com/cpp-tutorial/class-code-and-header-files/
*/

#ifndef MOTOR_H
#define MOTOR_H

enum Direction {
  FORWARD, BACKWARD
};

class PWM {
  public:
    int PWMFreq; 
    int PWMChannel;
    int PWMResolution;
    int MAX_DUTY_CYCLE;
    PWM(int channel = 0, int freq = 50, int resolution = 10);
    void updateDutyCycle(int dutyCycle);
    void print();
};

class Motor {
  public:
    Motor(int EP, int I1P, int I2P);//enable pin, In1Pin, In2Pin
    void print(string str);
    void enable(int motor);
    void disable(int motor);
    void setPWM(unsigned int PWM);
    void setDirection(int motor, int dir);
    void print();

};



#endif /* MOTOR_H */