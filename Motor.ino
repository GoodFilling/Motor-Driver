#include <iostream>
using namespace std;
//#include "Motor.cpp"
#include "Motor.h"
#include "PinMap.h"


int percPWM = 0;
int i = 0;

//initialize 4 PWM and 4 Motors
PWM pwm1 = PWM(0, 1, 50, 10);
Motor motor1 = Motor(2, 1, pwm1);
PWM pwm2 = PWM(2, 3, 50, 10);
Motor motor2 = Motor(41, 42, pwm2);
PWM pwm3 = PWM(4, 5, 50, 10);
Motor motor3 = Motor(39, 40, pwm3);
PWM pwm4 = PWM(6, 7, 50, 10);
Motor motor4 = Motor(37, 38, pwm4);
//Motor motors[4] = {motor1, motor2, motor3, motor4};//delete array
int numPumps = 4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  /*for (i=0; i<motors.length(); i++) {
    motors[i].print();
    motors[i].setDirection(FORWARD);
    cout << "Setting PWM: " << percPWM << "%"<< endl;
    motors[i].setPWM(percPWM);//set pwm to 0 as a percent
  }

  cout <<"setting pin 5 high" << endl;
  pinMode(5, OUTPUT);//LED1
  digitalWrite(5, HIGH);
  pinMode(4, INPUT);//Button1

  pinMode(36, INPUT);//Flow1
  attachInterrupt(digitalPinToInterrupt(36), flowmeter, RISING);

  */

  for (int i = 0; i < numPumps; i++) {
    for (int j = IN1; j != TERMINATE; j++) {
      PinType pintype = static_cast<PinType>(j);
      cout << "pump #" << i+1 << " , enumInd: " << j << " pin Value: " << FetchMappedPin(i, pintype).PinNumber << endl;
    }
  }



  /*for (int k = 0; k<20; k++) {
    int i = (int) k/5;
    int j = k%5;
    PinType pintype = static_cast<PinType>(j);

    cout << "pump #" << i+1 << " , enumInd: " << j << " pin Value: " << getPin(k).PinNumber << endl;
    
  }*/
}

void loop() {
  //serial input code:
  /*int button1 = digitalRead(4);
  if (button1==HIGH) {
    cout<<"switch1 High"<<endl;
  } else {
    cout<<"switch1 Low"<<endl;
  }
  cout<<i<<endl;

  if (Serial.available()){
    int temp = Serial.peek();
    
    if (temp == 66) { //"B"
      motor4.setDirection(BACKWARD);
      float trash = Serial.parseFloat();

    } else if (temp == 70) { //"F"
      motor4.setDirection(FORWARD);
      float trash = Serial.parseFloat();
      
    } else {
      percPWM = Serial.parseFloat();
      cout << "Setting PWM: " << percPWM << "%"<< endl;
      motor4.setPWM(percPWM);
    }
  }*/
}

void flowmeter() {
  i++;
}