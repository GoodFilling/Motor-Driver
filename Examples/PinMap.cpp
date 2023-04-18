#include "PinMap.h" 

//NOTE: this is what GPIO pin is used for each function 
struct MappedPin PinMapArray[20] = { //20 for 4 sets of 5 hardware pins
//INDEXES: IN1 = 0, IN2 = 1, FMCOUNT = 2, LED = 3, BUTT = 4
////PUMP1
    {//Motor1 IN1 -> Pin 2
        1,
        2,
        IN1
    },
    {//Motor1 IN2 -> Pin 1
        1,
        1,
        IN2
    },
    {//Flowmeter1  FMCOUNT-> Pin 36
        1,
        36,
        FMCOUNT
    },
    {//LED1 LED -> Pin 5
        1,
        5,
        LED
    },
    {//Button1 BUTT -> Pin 4
        1,
        4,
        BUTT
    }, 
////PUMP2
    {//Motor2 IN1 -> Pin 41
        2,
        41,
        IN1
    },
    {//Motor2 IN2 -> Pin 42
        2,
        42,
        IN2
    },
    {//Flowmeter2  FMCOUNT-> Pin 35
        2,
        35,
        FMCOUNT
    },
    {//LED2 LED -> Pin 7
        2,
        5,
        LED
    },
    {//Button2 BUTT -> Pin 6
        2,
        6,
        BUTT
    }, 
////PUMP3
    {//Motor3 IN1 -> Pin 39
        3,
        39,
        IN1
    },
    {//Motor3 IN2 -> Pin 40
        3,
        40,
        IN2
    },
    {//Flowmeter3  FMCOUNT-> Pin 0
        3,
        0,
        FMCOUNT
    },
    {//LED3 LED -> Pin 16
        3,
        16,
        LED
    },
    {//Button3 BUTT -> Pin 15
        3,
        15,
        BUTT
    }, 
////PUMP4
    {//Motor4 IN1 -> Pin 37
        4,
        37,
        IN1
    },
    {//Motor4 IN2 -> Pin 38
        4,
        38,
        IN2
    },
    {//Flowmeter4  FMCOUNT-> Pin 45
        4,
        45,
        FMCOUNT
    },
    {//LED4 LED -> Pin 18
        4,
        18,
        LED
    },
    {//Button4 BUTT -> Pin 17
        4,
        17,
        BUTT
    }, 
};

struct MappedPin getPin(int pinInd) {
  return PinMapArray[pinInd];
}

struct MappedPin FetchMappedPin(int pumpNumber, enum PinType pinType) { 
    /*for (int i = 0; i < sizeof(PinMapArray); i++) {
        if (PinMapArray[i].PumpNumber == pumpNumber && PinMapArray[i].PinType == pinType){
            return PinMapArray[i];
        }
    }

    struct MappedPin errorPinMap = {-9, -9, ENA};
    return errorPinMap;*/

    //get index from pintype:
    struct MappedPin output;
    //try {
    output = PinMapArray[(pumpNumber)*5 + pinType];
    /*} catch (){
      struct MappedPin errorPinMap = {-9, -9, ENA};

      return errorPinMap;
    }*/

    return output;
}