#ifndef PWM_H
#define PWM_H
#include <math.h>
#include <Arduino.h>
#include <iostream>
#include <algorithm>

class PWM {
  public:
    PWM();
    PWM(int channel1, int channel2, int freq, int resolution);
    // ~PWM();
    int PWMFreq; 
    int PWMChannel1;
    int PWMChannel2;
    int PWMResolution;
    int MAX_DUTY_CYCLE;

    void updateDutyCycle(int dutyCycle);
    void updateDutyCycle(int dutyCycle, int index);
    void print();
};

#endif