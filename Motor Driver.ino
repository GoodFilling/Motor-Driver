#include <iostream>
using namespace std;
//#include "Motor.cpp"
#include "Motor.h"

int percPWM = 100;
PWM pwm = PWM(0, 1, 50, 10);
Motor motor = Motor(1, 2, pwm);
bool new_serial= true;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  motor.print();
  //motor.setDirection(FORWARD);
  cout << "Setting PWM: " << percPWM << "%"<< endl;
  motor.setPWM(percPWM);//set pwm as a percent
}


void loop() {
  // put your main code here, to run repeatedly:

  if (Serial.available()){
    int temp = Serial.peek();
    

    if (temp == 66) { //"B"
      motor.setDirection(BACKWARD);
      float trash = Serial.parseFloat();

    } else if (temp == 70) { //"F"
      motor.setDirection(FORWARD);
      float trash = Serial.parseFloat();

      
    } else {
      percPWM = Serial.parseFloat();
      cout << "Setting PWM: " << percPWM << "%"<< endl;
      motor.setPWM(percPWM);
    }
  }
}