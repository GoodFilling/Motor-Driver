#include "PWM.h"

PWM::PWM(){
    PWM(0, 1, 50, 10);
}

PWM::PWM(int channel1 = 0, int channel2 = 1, int freq = 10, int resolution = 12) {
      log("PWM Constructor");

      PWMChannel1 = channel1;
      PWMChannel2 = channel2;
      PWMFreq = freq; // default 10 hz (10)
      PWMResolution = resolution; //bit resolution for PWM, up to 16 bits
      MAX_DUTY_CYCLE = (int)(pow(2,resolution) - 1);
      ledcSetup(PWMChannel1, PWMFreq, PWMResolution);//initialize PWM on pin
      ledcSetup(PWMChannel2, PWMFreq, PWMResolution);//initialize PWM on pin

      //ledcAttachPin(LEDPin, PWMChannel); //Moved to motor constructor       
}

// PWM::~PWM()
// {
//     log("PWM Destructor");
//     //this->updateDutyCycle(0);
// }

void PWM::updateDutyCycle(int dutyCycle) {
  //base function to set both duty cycles
  //clean duty cycle: between 0 and MAX_DUTY_CYCLE
  dutyCycle = min(max(dutyCycle,0), this->MAX_DUTY_CYCLE);
  ledcWrite(this->PWMChannel1, dutyCycle);
  ledcWrite(this->PWMChannel2, dutyCycle);

  log("Setting Duty Cycle to %i of %i", dutyCycle, MAX_DUTY_CYCLE);
}

void PWM::updateDutyCycle(int dutyCycle, int index) {
  //Overload to allow for indexing the 2 PWM signals
  //clean duty cycle: between 0 and MAX_DUTY_CYCLE
  dutyCycle = min(max(dutyCycle,0), this->MAX_DUTY_CYCLE);
  if (index == 0) {
    ledcWrite(this->PWMChannel1, dutyCycle);
  } else {
    ledcWrite(this->PWMChannel2, dutyCycle);
  }
  log("Setting Duty Cycle %i to %i of %i", index, dutyCycle, MAX_DUTY_CYCLE);
}


void PWM::print() {
    log("PWM Frequency: %i Hz", this->PWMFreq);
    log("PWM Channel1: %i", this->PWMChannel1);
    log("PWM Channel2: %i", this->PWMChannel2);
    log("PWM Resolution: %i bit", this->PWMResolution);
    log("PWM Max Duty Cycle: %i", this->MAX_DUTY_CYCLE);
}