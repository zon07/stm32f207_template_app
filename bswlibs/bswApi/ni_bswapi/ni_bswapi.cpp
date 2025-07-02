#include "ni_bswapi.h"

constexpr uint32_t MAX_ATTEMPTS_COUNT = 200000U;

#ifdef BUILD_FOR_MCU

#if (ECU_TYPE == ECU_TYPE_DBK_10)
    #define FREQ_CH Freq_channel
#elif (ECU_TYPE == ECU_TYPE_BU_702)
    #define FREQ_CH FrequencyMeter::Channel
#else
    #error "BswLib: ECU_TYPE not supported"
#endif

static void configPullUp(uint8_t channel, uint8_t mode)
{
    if(mode)
    {
        FrequencyMeter::enablePullUp(static_cast<FREQ_CH>(channel));
    }
    else
    {
        FrequencyMeter::disablePullUp(static_cast<FREQ_CH>(channel));
    }
}
#endif

void bswFreqApiConfigPullUp(uint8_t channel, bool mode)
{
    #ifdef BUILD_FOR_MCU  
        configPullUp(channel, mode);
    #endif
}

int8_t bswFreqApiGetStatus(const uint8_t channel)
{
    int8_t result = 0;
    #ifdef BUILD_FOR_MCU
    result = static_cast<int8_t>(FrequencyMeter::getStatus(static_cast<FREQ_CH>(channel)));
    #endif
    return result;
}

float bswFreqApiGetPeriod(const uint8_t channel)
{
    float result = 0.0f;
    #ifdef BUILD_FOR_MCU
    result = FrequencyMeter::getPeriod(static_cast<FREQ_CH>(channel));
    #endif
    return result;
}

float bswFreqApiGetFrequency(const uint8_t channel)
{
    float result = 0.0f;
    #ifdef BUILD_FOR_MCU
    result = FrequencyMeter::getFrequency(static_cast<FREQ_CH>(channel));
    #endif
    return result;
}

float bswFreqApiGetDutyCycle(const uint8_t channel)
{
    float result = 0.0f;
    #ifdef BUILD_FOR_MCU
    result = FrequencyMeter::getDutyCycle(static_cast<FREQ_CH>(channel));
    #endif
    return result;
}

uint32_t bswFreqApiGetPulseCounterValue(const uint8_t channel)
{
    float result = 0.0f;
    #ifdef BUILD_FOR_MCU
    result = FrequencyMeter::getPulseCounterValue(static_cast<FREQ_CH>(channel));
    #endif
    return result;
}


/*Функции для ДБК10*/
#if ((BUILD_FOR_MCU && (ECU_TYPE == ECU_TYPE_DBK_10)) || (!defined BUILD_FOR_MCU))
    float bswFreqApiGetLevelValue(const uint8_t channel)
    {
        float result = 0;
        #ifdef BUILD_FOR_MCU
            result = FrequencyMeter::getLevelValue(static_cast<FREQ_CH>(channel));
        #else
            result = 0.0f;
        #endif
        return result;
    }

    int8_t bswFreqApiSetLevelTimeAvg(const uint8_t channel, float time)
    {
        int8_t result = 0;
        #ifdef BUILD_FOR_MCU
            result = static_cast<int8_t>(FrequencyMeter::setLevelTimeAvg(static_cast<FREQ_CH>(channel), time));
        #else
            result = 0;
        #endif
        return result;    
    }
#endif