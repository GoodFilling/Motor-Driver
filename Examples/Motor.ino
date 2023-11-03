#include <iostream>
using namespace std;
//#include "Motor.cpp"
#include "Motor.h"


int percPWM = 0;
int i = 0;

//initialize 4 PWM and 4 Motors
/*PWM pwm1 = PWM(0, 1, 50, 10);
Motor motor1 = Motor(2, 1, pwm1);
PWM pwm2 = PWM(2, 3, 50, 10);
Motor motor2 = Motor(41, 42, pwm2);
PWM pwm3 = PWM(4, 5, 50, 10);
Motor motor3 = Motor(39, 40, pwm3);*/
Motor motor = Motor(2, 1, 0, 1);
int numPumps = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello World");
  /*for (i=0; i<motors.length(); i++) {
    motors[i].print();
    motors[i].setDirection(FORWARD);
    motors[i].setPWM(percPWM);//set pwm to 0 as a percent
  }

  pinMode(5, OUTPUT);//LED1
  digitalWrite(5, HIGH);
  pinMode(4, INPUT);//Button1

  pinMode(36, INPUT);//Flow1
  attachInterrupt(digitalPinToInterrupt(36), flowmeter, RISING);

  */

  //How to iterate through all pins - example of how pins are indexed
  /*for (int i = 0; i < numPumps; i++) {
    for (int j = IN1; j != TERMINATE; j++) {
      PinType pintype = static_cast<PinType>(j);
      std::cout << "pump #" << i+1 << " , enumInd: " << j << " pin Value: " << FetchMappedPin(i, pintype).PinNumber << std::endl;
    }
  }*/


  //another way to iterate through all pins
  /*for (int k = 0; k<20; k++) {
    int i = (int) k/5;
    int j = k%5;
    PinType pintype = static_cast<PinType>(j);

    std::cout << "pump #" << i+1 << " , enumInd: " << j << " pin Value: " << getPin(k).PinNumber << std::endl;
    
  }*/
}

void loop() {
  //serial input code:
  /*int button1 = digitalRead(4);
  if (button1==HIGH) {
    log("Switch1 High");
  } else {
    log("Switch1 Low");
  }
  */
  if (Serial.available()){
    int temp = Serial.peek();
    
    if (temp == 66) { //"B"
      motor.setDirection(BACKWARD);
      float trash = Serial.parseFloat();
    } else if (temp == 70) { //"F"
      motor.setDirection(FORWARD);
      float trash = Serial.parseFloat();
    } else if (temp == 68) { //"D"
      motor.disable();
      float trash = Serial.parseFloat();
    } else if (temp == 69) { //"E"
      motor.enable();
      float trash = Serial.parseFloat();
    } else if (temp == 80) { //"P"
      motor.print();
      float trash = Serial.parseFloat();
    } else {
      percPWM = Serial.parseFloat();
      motor.setPWM(percPWM);
      motor.enable();

    }
  }
}

void flowmeter() {
  i++;
}