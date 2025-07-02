#ifndef SYS_BSWAPI_H
#define SYS_BSWAPI_H

#define SIMULINK_SYSTEM_BSWAPI_USED (1U)

#include "bsw_version_defines.h"
#include "ecu_types_defines.h"

#ifdef BUILD_FOR_MCU
    #if (ECU_TYPE == ECU_TYPE_DBK_10) // Сборка для ДБК10
        #include "lib_dbk-10-AT32F437.h"
    #elif (ECU_TYPE == ECU_TYPE_BU_702) // Сборка для БУ702
        #include "lib_bu_702.h"
    #else
        #error "BswLib: ECU_TYPE not supported"
    #endif
#else // Для генерации в Simulink
    #include <inttypes.h>
#endif

class BootMasterPinCodeService
{
public:
    static uint8_t getCode();
    static void setCode(uint8_t bootPinCode);

private:
    static inline uint8_t bootMasterPinCode = 0x01;
};

/**
 * \brief   Set pin code for bootloder system
 * \param   bootPinCode - pinCode
 * \return  none
 */
void bswSysApiSetBootPinCode(uint8_t bootPinCode);

/**
 * \brief   Get the measured value of the on-board network voltage
 * \param   none
 * \return  The value of the measured voltage in Volts (float)
 */
float bswSysApiGetUpower(void);

/**
 * \brief   Get the measured value of the on-board network voltage
 * \param   none
 * \return  The value of the measured voltage in Volts (float)
 */
float bswSysApiGetUpower(void);

/**
 * \brief   Get ADC Raw Voltage
 * \param   adcNum - numberOfAdc (uint16_t)
 * \param   channel - channelNumber (uint16_t)
 * \return  float - raw Voltage
*/
float bswSysApiAdcGetRawVoltage(uint16_t adcNum, uint16_t channel);


#if ((ECU_TYPE == ECU_TYPE_BU_702) || (!defined BUILD_FOR_MCU))

    /**
     * \brief  Set value for supply voltage. For correct channels diagnostic
     * \param   voltage - 0 - RANGE_12V; 1 - RANGE_24V
     * \return  None
    */
    void bswSysApiSetSupplyVoltage(const uint8_t suppType);

    /**
     * \brief   Control of switching on/off the ground of frequency channels
     * \param   state - Key state, bool
     * \return  None
    */
    void bswSysApiFreqGndControl(const bool state);

    /**
     * \brief   UIR Ground On/Off control
     * \param   state - Key state, bool
     * \return  None
    */
    void bswSysApiUirGndControl(const bool state);

    /**
     * \brief   Sensor power on/off control
     * \param   state - 0-off, 1-on 5V, 2-on 12V, (uint8_t)
     * \return  None
    */
    void bswSysApiSensorsPwrControl(const uint8_t state);
#endif


#endif /* SYS_BSWAPI_H */