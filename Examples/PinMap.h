#ifndef PIN_MAP_H
#define PIN_MAP_H

//used for pump direction
#define FRONT_TO_BACK HIGH
#define BACK_TO_FRONT LOW

//list of pin types from the 633W pump motor
enum PinType {
    /*
    Each motor driver has IN1 and IN2. This is the GPIO pin that leads to that for a specific motor.  Used in PWM
    */
    IN1 = 0,
    IN2 = 1,
    //The flow meter will be mapped to a GPIO pin
    FMCOUNT = 2,
    //Each button has an LED that should light when ready to dispense
    LED = 3,
    // Each pump needs a push button signal
    BUTT = 4,
    //this allows for looping through the enum - it isn't actually used otherwise
    TERMINATE,
    ENA
};

struct MappedPin {
    int PumpNumber;
    int PinNumber;  //GPIO pin number on the ESP
    enum PinType PinType;
};

extern struct MappedPin getPin(int pinInd);

extern struct MappedPin FetchMappedPin(int pumpNumber, enum PinType pinType);

//array for all 4 pumps on the ESP
extern struct MappedPin PinMapArray[20]; 



#endif