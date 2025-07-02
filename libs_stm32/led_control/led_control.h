#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#define SIMULINK_LED_CONTROL_USED (1U)

#ifndef MATLAB_MEX_FILE
    #include "stm32f2xx.h"
    #include "stm32f2xx_hal.h"
    #include "stm32f2xx_hal_gpio.h"
    #include <inttypes.h>
#else
    #include <inttypes.h>
#endif


void SetLedState(const uint8_t led, uint8_t state);


#endif /* LED_CONTROLI_H */