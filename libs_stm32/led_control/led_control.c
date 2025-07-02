#include "led_control.h"


void SetLedState(const uint8_t led, uint8_t state)
{
#ifndef MATLAB_MEX_FILE
    uint16_t gpioPin = GPIO_PIN_14; 
    GPIO_PinState pinState = GPIO_PIN_RESET;

    switch (led)
    {
    case 1:
        gpioPin = GPIO_PIN_0;
        break;
    case 2:
        gpioPin = GPIO_PIN_7;
        break;
    case 3:
    default:
        gpioPin = GPIO_PIN_14;
        break;
    }

    pinState = (state) ? GPIO_PIN_SET : GPIO_PIN_RESET;
    HAL_GPIO_WritePin(GPIOB, gpioPin, pinState);
#endif
}
