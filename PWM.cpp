#include "PWM.h"

PWM::PWM(){
    PWM(0, 1, 50, 10);
}

PWM::PWM(int channel1 = 0, int channel2 = 1, int freq = 50, int resolution = 10) {
      std::cout << "PWM con" << std::endl;
      log("PWM Constructor");

      PWMChannel1 = channel1;
      PWMChannel2 = channel2;
      PWMFreq = freq; // default 50 hz (50)
      PWMResolution = resolution; //bit resolution for PWM, up to 16 bits
      MAX_DUTY_CYCLE = (int)(pow(2,resolution) - 1);
      ledcSetup(PWMChannel1, PWMFreq, PWMResolution);//initialize PWM on pin
      ledcSetup(PWMChannel2, PWMFreq, PWMResolution);//initialize PWM on pin

      //ledcAttachPin(LEDPin, PWMChannel); //Moved to motor constructor       
}

// PWM::~PWM()
// {
//     std::cout << "PWM destructor" << std::endl;
//     //this->updateDutyCycle(0);
// }

void PWM::updateDutyCycle(int dutyCycle) {
  //base function to set both duty cycles
  //clean duty cycle: between 0 and MAX_DUTY_CYCLE
  dutyCycle = min(max(dutyCycle,0), this->MAX_DUTY_CYCLE);
  ledcWrite(this->PWMChannel1, dutyCycle);
  ledcWrite(this->PWMChannel2, dutyCycle);

  std::cout << "Setting Duty Cycle to: " << dutyCycle << " of " << MAX_DUTY_CYCLE <<std::endl;
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
  std::cout << "Setting Duty Cycle "<< index <<  " to: " << dutyCycle << " of " << MAX_DUTY_CYCLE <<std::endl;
  log("Setting Duty Cycle %i to %i of %i", index, dutyCycle, MAX_DUTY_CYCLE);
}


void PWM::print() {
    std::cout << "Freq: " << this->PWMFreq << std::endl;
    std::cout << "Channel1: " << this->PWMChannel1 << std::endl;
    std::cout << "Channel1: " << this->PWMChannel2 << std::endl;
    std::cout << "Resolution: " << this->PWMResolution << "bit"<< std::endl;
    std::cout << "Max Duty Cycle: " << this->MAX_DUTY_CYCLE << std::endl;
}