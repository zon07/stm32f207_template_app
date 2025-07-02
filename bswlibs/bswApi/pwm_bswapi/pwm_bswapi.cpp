#include "pwm_bswapi.h"


void pwmFreqConfig(const uint8_t pwmNum, const uint8_t pwmFreqNum)
{
    #ifdef BUILD_FOR_MCU
        #if (ECU_TYPE == ECU_TYPE_BU_702) // Сборка для БУ702
            switch (pwmNum)
            {
            case 1:
                Pwm1::begin(static_cast<Pwm1::Frequency>(pwmFreqNum));
                break;
            case 2:
                Pwm2::begin(static_cast<Pwm2::Frequency>(pwmFreqNum));
                break;            
            default:
                break;
            }
        #else
            #error BswLib: ECU_TYPE not supported
        #endif
    #else // Для генерации в Simulink
    #endif
}

void pwmChConfig(const uint8_t pwmNum, const uint8_t channel, const uint8_t mode, const bool checkEnable)
{
    #ifdef BUILD_FOR_MCU
        #if (ECU_TYPE == ECU_TYPE_BU_702) // Сборка для БУ702
            switch (pwmNum)
            {
            case 1:
                Pwm1::setMode(static_cast<Pwm1::Channel>(channel), static_cast<Pwm1::Mode>(mode));
                if(checkEnable)
                {
                    Pwm1::checkEnable(static_cast<Pwm1::Channel>(channel));
                }
                else
                {
                    Pwm1::checkDisable(static_cast<Pwm1::Channel>(channel));
                }
                break;
            case 2:
                Pwm2::setMode(static_cast<Pwm2::Channel>(channel), static_cast<Pwm1::Mode>(mode));
                if(checkEnable)
                {
                    Pwm2::checkEnable(static_cast<Pwm2::Channel>(channel));
                }
                else
                {
                    Pwm2::checkDisable(static_cast<Pwm2::Channel>(channel));
                }
                break;            
            default:
                break;
            }
        #else
            #error BswLib: ECU_TYPE not supported
        #endif
    #else // Для генерации в Simulink
    #endif
}

void pwmChControl(const uint8_t pwmNum, const uint8_t channel, const uint8_t mode, const uint16_t value)
{
    #ifdef BUILD_FOR_MCU
        #if (ECU_TYPE == ECU_TYPE_BU_702) // Сборка для БУ702
            switch (pwmNum)
            {
            case 1:
                Pwm1::set(static_cast<Pwm1::Channel>(channel), value);
                break;
            case 2:
                Pwm2::set(static_cast<Pwm2::Channel>(channel), value);
                break;            
            default:
                break;
            }
        #else
            #error BswLib: ECU_TYPE not supported
        #endif
    #else // Для генерации в Simulink
    #endif
}

int8_t pwmChFb(const uint8_t pwmNum, const uint8_t channel, uint16_t *fbCurrent)
{
    int8_t result = 0;
    #ifdef BUILD_FOR_MCU
        #if (ECU_TYPE == ECU_TYPE_BU_702) // Сборка для БУ702
            switch (pwmNum)
            {
            case 1:
                *fbCurrent = Pwm1::getFeedbackCurrent(static_cast<Pwm1::Channel>(channel));
                result = static_cast<uint8_t>(Pwm1::getStatus(static_cast<Pwm1::Channel>(channel)));
                break;
            case 2:
                *fbCurrent = Pwm2::getFeedbackCurrent(static_cast<Pwm2::Channel>(channel));
                result = static_cast<uint8_t>(Pwm2::getStatus(static_cast<Pwm2::Channel>(channel)));
                break;            
            default:
                *fbCurrent = 0;
                result = static_cast<uint8_t>(Status::NOT_FOUND);
                break;
            }
        #else
            #error BswLib: ECU_TYPE not supported
        #endif
    #else // Для генерации в Simulink
    result = 0;
    #endif
    return result; 
}

