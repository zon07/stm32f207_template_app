#include "system_bswapi.h"

constexpr float PWRV_COEFF_BU702 = 11.0f; // Divider coefficient for ecu supply voltage

/*Функции для ДБК10 и БУ702*/
#if ((BUILD_FOR_MCU && (ECU_TYPE == ECU_TYPE_DBK_10) || (ECU_TYPE == ECU_TYPE_BU_702)) || (!defined BUILD_FOR_MCU))

void BootMasterPinCodeService::setCode(uint8_t bootPinCode)
{
    bootMasterPinCode = bootPinCode;
}

uint8_t BootMasterPinCodeService::getCode(void)
{
    return bootMasterPinCode;
}



void bswSysApiSetBootPinCode(uint8_t bootPinCode)
{
    BootMasterPinCodeService::setCode(bootPinCode);
}


float bswSysApiGetUpower(void)
{
    float result = 0.0f;
    #ifdef BUILD_FOR_MCU
        #if (ECU_TYPE == ECU_TYPE_DBK_10) // Сборка для ДБК10
            result = System::getPowerVoltage();
        #elif (ECU_TYPE == ECU_TYPE_BU_702) // Сборка для БУ702
            result = Adc1::getRawVoltage(Adc1::Channel::PWRvs) * PWRV_COEFF_BU702;
        #else
            #error "BswLib: ECU_TYPE not supported"
        #endif
    #else
        result = 0.0f;
    #endif
    return result;
}

float bswSysApiAdcGetRawVoltage(uint16_t adcNum, uint16_t channel)
{
    float result = 0.0f;
    #ifdef BUILD_FOR_MCU
        #if (ECU_TYPE == ECU_TYPE_DBK_10) // Сборка для ДБК10
            if(0 == adcNum)
            {
                result = Adc::getRawVoltage(static_cast<Adc_Channel>(channel));
            }
            else
            {
                result = 0.0f;           
            }
        #elif (ECU_TYPE == ECU_TYPE_BU_702) // Сборка для БУ702
            if(0 == adcNum)
            {
                result = Adc1::getRawVoltage(static_cast<Adc1::Channel>(channel));
            }
            else if(1 == adcNum)
            {
                result = Adc2::getRawVoltage(static_cast<Adc2::Channel>(channel));
            }
            else
            {
                result = 0.0f;        
            }            
        #else
            #error "BswLib: ECU_TYPE not supported"
        #endif
    #else
        result = 0.0f;
    #endif
    return result;
}
#endif

/*Функции для БУ702*/
#if ((BUILD_FOR_MCU && (ECU_TYPE == ECU_TYPE_BU_702)) || (!defined BUILD_FOR_MCU))
void bswSysApiSetSupplyVoltage(const uint8_t suppType)
{
    #ifdef BUILD_FOR_MCU
        #if (ECU_TYPE == ECU_TYPE_BU_702) // Сборка для БУ702
            PowerControl::setSupplyVoltage(static_cast<SupplyVoltage>(suppType));       
        #else
            #error "BswLib: ECU_TYPE not supported"
        #endif
    #endif
}

void bswSysApiFreqGndControl(const bool state)
{
    #ifdef BUILD_FOR_MCU
        #if (ECU_TYPE == ECU_TYPE_BU_702) // Сборка для БУ702
            if(state)
            {
                PowerControl::enableGnd_X2_13();
            }
            else
            {
                PowerControl::disableGnd_X2_13();
            }          
        #else
            #error "BswLib: ECU_TYPE not supported"
        #endif
    #endif
}

void bswSysApiUirGndControl(const bool state)
{
    #ifdef BUILD_FOR_MCU
        #if (ECU_TYPE == ECU_TYPE_BU_702) // Сборка для БУ702
            if(state)
            {
                PowerControl::enableGnd_X2_14();
            }
            else
            {
                PowerControl::disableGnd_X2_14();
            }
        #else 
            #error "BswLib: ECU_TYPE not supported"
        #endif
    #endif
}

void bswSysApiSensorsPwrControl(const uint8_t state)
{
    int8_t result = 0;
    #ifdef BUILD_FOR_MCU
        #if (ECU_TYPE == ECU_TYPE_BU_702) // Сборка для БУ702
        switch(state)
        {
            case 1:
                PowerControl::enablePower5V_X2_34();
                break;
            case 2:
                PowerControl::enablePower12V_X2_34();
                break;       
            default:
                PowerControl::disablePower_X2_34();
                break;
        }
        #else
            #error "BswLib: ECU_TYPE not supported"
        #endif
    #endif
}

#endif
