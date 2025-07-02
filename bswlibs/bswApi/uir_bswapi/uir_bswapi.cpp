#include "uir_bswapi.h"

#ifdef BUILD_FOR_MCU
    #if (ECU_TYPE == ECU_TYPE_DBK_10) // Сборка для ДБК10
        #define BSWAPI_UIR_MODE_VOLTAGE                Uir::Mode::VOLTAGE
        #define BSWAPI_UIR_MODE_CURRENT                Uir::Mode::CURRENT_MEASURE
        #define BSWAPI_UIR_MODE_RESISTANCEE            Uir::Mode::RESISTANCE_MEASURE

        #define BSWAPI_UIR_SET_MODE(channel, mode)     Uir::setMode(static_cast<Uir::Channel>(channel), static_cast<Uir::Mode>(mode))
        #define BSWAPI_UIR_GET_MODE(channel)           Uir::getMode(static_cast<Uir::Channel>(channel))

        #define BSWAPI_UIR_GET_STATUS(channel)         Uir::getStatus(static_cast<Uir::Channel>(channel))

        #define BSWAPI_UIR_GET_CURRENT(channel)        Uir::getCurrent(static_cast<Uir::Channel>(channel))
        #define BSWAPI_UIR_GET_VOLTAGE(channel)        Uir::getVoltage(static_cast<Uir::Channel>(channel))
        #define BSWAPI_UIR_GET_RESISTANCE(channel)     Uir::getVoltage(static_cast<Uir::Channel>(channel))



    #elif (ECU_TYPE == ECU_TYPE_BU_702) // Сборка для БУ702
        #define BSWAPI_UIR_MODE_VOLTAGE                Uir::Mode::VOLTAGE
        #define BSWAPI_UIR_MODE_CURRENT                Uir::Mode::CURRENT
        #define BSWAPI_UIR_MODE_RESISTANCEE            Uir::Mode::RESISTANCE

        #define BSWAPI_UIR_SET_MODE(channel, mode)     Uir::setMode(static_cast<Uir::Channel>(channel), static_cast<Uir::Mode>(mode))
        #define BSWAPI_UIR_GET_MODE(channel)           Uir::getMode(static_cast<Uir::Channel>(channel))

        #define BSWAPI_UIR_GET_STATUS(channel)         Uir::getStatus(static_cast<Uir::Channel>(channel))

        #define BSWAPI_UIR_GET(channel)                Uir::get(static_cast<Uir::Channel>(channel))
        #define BSWAPI_UIR_GET_CURRENT(channel)        BSWAPI_UIR_GET(channel)
        #define BSWAPI_UIR_GET_VOLTAGE(channel)        BSWAPI_UIR_GET(channel)
        #define BSWAPI_UIR_GET_RESISTANCE(channel)     BSWAPI_UIR_GET(channel)

    #else
        #error "BswLib: ECU_TYPE not supported"
    #endif
#endif



void uirChannelConfig(uint8_t channel, uint8_t mode)
{
    int8_t result = 0;
    #ifdef BUILD_FOR_MCU
        BSWAPI_UIR_SET_MODE(channel, mode);
    #endif
}

float uirGetVoltage(uint8_t channel)
{
    float result = 0.0f;
    #ifdef BUILD_FOR_MCU
    if(BSWAPI_UIR_MODE_VOLTAGE == BSWAPI_UIR_GET_MODE(channel))
    {
        result = BSWAPI_UIR_GET_VOLTAGE(channel);
    }
    else
    {
        result = 0;
    }
    #endif
    return result;
}

float uirGetCurrent(uint8_t channel)
{
    float result = 0.0f;
    #ifdef BUILD_FOR_MCU
    if(BSWAPI_UIR_MODE_CURRENT == BSWAPI_UIR_GET_MODE(channel))
    {
        result = BSWAPI_UIR_GET_CURRENT(channel);
    }
    else
    {
        result = 0;
    }
    #endif
    return result;
}

float uirGetResistance(uint8_t channel)
{
    float result = 0.0f;
    #ifdef BUILD_FOR_MCU
    if(BSWAPI_UIR_MODE_RESISTANCEE == BSWAPI_UIR_GET_MODE(channel))
    {
        result = BSWAPI_UIR_GET_RESISTANCE(channel);
    }
    else
    {
        result = 0;
    }
    #endif
    return result;
}

int8_t uirGetStatus(uint8_t channel)
{
    int8_t result = 0;
    #ifdef BUILD_FOR_MCU
        result = static_cast<int8_t>(BSWAPI_UIR_GET_STATUS(channel));
    #else
        result = 0;
    #endif
    return result;
}


