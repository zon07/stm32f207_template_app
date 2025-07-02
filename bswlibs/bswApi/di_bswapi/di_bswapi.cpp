#include "di_bswapi.h"

#ifdef BUILD_FOR_MCU
    #if (ECU_TYPE == ECU_TYPE_DBK_10) // Сборка для ДБК10
        #define DI_CLASS_NAME Input
    #elif (ECU_TYPE == ECU_TYPE_BU_702) // Сборка для БУ702
        #define DI_CLASS_NAME DigitalInputs
    #else
        #error "BswLib: ECU_TYPE not supported"
    #endif
#endif


static void configPullUp(uint8_t channel, uint8_t mode)
{
    #ifdef BUILD_FOR_MCU
    switch (mode)
    {
        case 0:
            DI_CLASS_NAME::enablePullUp(static_cast<DI_CLASS_NAME::Channel>(channel));
            break;
        case 1:
            DI_CLASS_NAME::enablePullDown(static_cast<DI_CLASS_NAME::Channel>(channel));
            break;    
        default:
            break;
    }
    #endif
}


void diConfigPullUp(uint8_t channel, uint8_t mode)
{
    #ifdef BUILD_FOR_MCU
        configPullUp(channel, mode);
    #endif
}


uint8_t diGetState(uint8_t channel)
{
    uint8_t result = 0;
    #ifdef BUILD_FOR_MCU
        #if (ECU_TYPE == ECU_TYPE_DBK_10) // Сборка для ДБК10
            result = static_cast<uint8_t>(Input::getState(static_cast<Input::Channel>(channel)));
        #elif (ECU_TYPE == ECU_TYPE_BU_702) // Сборка для БУ702
            result = static_cast<uint8_t>(DigitalInputs::get(static_cast<DigitalInputs::Channel>(channel)));
        #else
            #error "BswLib: ECU_TYPE not supported"
        #endif
    #endif
    return result;
}
