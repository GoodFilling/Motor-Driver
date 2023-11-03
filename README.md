# Motor-Driver
Created on: Jan 5, 2023
Author: Chris Hanes for Good Filling LLC.

PURPOSE: This library allows us to use the DRV8251 with the ESP32-S2. 

DISCLAIMER: This is a work in progress. Changes are frequent and not guaranteed to work with your specific scenario. Review code carefully before using. Use at your own discretion

## Usage Instructions
This library was written specifically for the DRV8251, but it may work with other motor drivers, as well. Refer to the documentation provided by Texas Instruments for details on the DRV8251 (https://www.ti.com/lit/ds/symlink/drv8251.pdf) and to adapt this library to the specifics of your motor driver.

Initialize the motor driver as follows:
```
Motor motor = Motor(IN1, IN2, Channel1, Channel2);
```

IN1 and IN2 are the pins that are used to interface with a motor driver (TI's DRV8251). The names line up with the pin-in from this chip.

Channel1 and Channel2 are integers corresponding to the PWM channel you want to attach (ESP32s have 16 independent PWM channels labeled 0-15).

Disable the motor:
``` motor.disable(); ```

Enable the motor:
```motor.enable();```

Set or toggle direction:
``` motor.setDirection(BACKWARD);
    motor.setDirection(FORWARD);
    motor.toggleDirection();
```

Set PWM Duty Cycle:
``` motor.setPWM(duty cycle); ```

Detach PWM signal from pins - prevents multiple motors being run:
``` motor.detach(); ```
