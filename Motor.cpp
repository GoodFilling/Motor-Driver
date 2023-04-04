/*
* Motor.cpp
*
*  Created on: Jan 5, 2023
*      Author: Chris Hanes for Good Filling LLC.
*      Reference: https://goodfilling.atlassian.net/l/cp/TmJou2ar
*      https://techexplorations.com/guides/esp32/begin/digitalout/ 
*      https://www.fluke.com/en-us/learn/blog/electrical/what-is-duty-cycle
*      https://www.tutorialspoint.com/cplusplus/cpp_this_pointer.htm
*      https://randomnerdtutorials.com/esp32-pinout-reference-gpios/: "All pins capable of output can be use for PWM"
*      https://www.electronicshub.org/esp32-pwm-tutorial/
*      https://learn.adafruit.com/improve-brushed-dc-motor-performance/choosing-decay-mode-and-pwm-frequency
*/
/*#include "Motor.h"

void PWM::updateDutyCycle(int dutyCycle) {
  //TODO: deterimine where we would want to implement transform from percent duty cycle to PWMResolution-bit duty cycle
  //Currently just using PWMResolution-bit duty cycle

  //clean duty cycle: between 0 and MAX_DUTY_CYCLE
  dutyCycle = min(max(dutyCycle,0), this->MAX_DUTY_CYCLE);
  ledcWrite(this->PWMChannel, dutyCycle);
  cout << "Setting Duty Cycle to: " << dutyCycle << " of " << MAX_DUTY_CYCLE <<endl;
};

void PWM::print() {
    cout << "Freq: " << this->PWMFreq << endl;
    cout << "Channel: " << this->PWMChannel << endl;
    cout << "Resolution: " << this->PWMResolution << endl;
    cout << "Max Duty Cycle: " << this->MAX_DUTY_CYCLE << endl;
}

void Motor::print() {
    cout << "Enable Pin: " << this->EnablePin << endl;
    cout << "In1Pin: " << this->In1Pin << endl;
    cout << "In2Pin " << this->In2Pin << endl;
    
    this->pwm.print();
};

void Motor::enable() {
  //this enables the indexed motor   
  digitalWrite(this->EnablePin, HIGH); //enable motor 1 (index 0)
};//Enable

void Motor::disable() {
  //disables the indexed motor, or all of them if none are specified
  digitalWrite(this->EnablePin, LOW); //enable motor 1
};//Disable()

void Motor::setPWM(float dutyCycle_Float) {
  //sets the PWM signal for the given motor.  
  //dutyCycle_Float is a float between 0.0 and 100.0 that controls the speed of the motor as a % duty cycle
  //pwm.updateDutyCycle() has cleaning for the duty cycle already, so no cleaning needed here
    int dutyCycle_Int = (int)(dutyCycle_Float/100 * this->pwm.MAX_DUTY_CYCLE);
    this->pwm.updateDutyCycle(dutyCycle_Int);
};//setPWM()

void Motor::setDirection(Direction dir) {
  //FORWARD and BACKWARD definitions are based on motor controller manufacturer
  this->disable();//disable motor
  this->dir = dir;//update stored motor direction in object
  /*^^^ (needed because PWM pin changes depending on direction to keep BRAKE type consistant)
  * see https://goodfilling.atlassian.net/l/cp/TmJou2ar PWM Control Block Diagram
  */
/*  if (dir == FORWARD){
    digitalWrite(this->In1Pin, HIGH);
    digitalWrite(this->In2Pin, LOW);
  } else if (dir == BACKWARD) {
    digitalWrite(this->In1Pin, LOW);
    digitalWrite(this->In2Pin, HIGH);
  }//else do nothing
  this->enable();//reenable motor
};//setDirection()
*/

