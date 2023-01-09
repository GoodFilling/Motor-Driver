#include "Motor.cpp"
#include "Motor.h"


void setup() {
  // put your setup code here, to run once:

 PWM pwm = PWM();
    Motor motor = Motor(1, 2, 3, pwm);
    motor.print();
    motor.Motor_setPWM(100);//set pwm as a percent
    //test for PWM::updateDutyCycle()
    /*pwm.print();
    for (int i = 0; i<1030; i++) {
        pwm.updateDutyCycle(i);
    }
    */

}


void loop() {
  // put your main code here, to run repeatedly:
}
