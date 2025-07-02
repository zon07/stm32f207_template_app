#ifndef PWM_BSWAPI_H
#define PWM_BSWAPI_H

#define SIMULINK_PWM_BSWAPI_USED (1U)

#include "bsw_version_defines.h"
#include "ecu_types_defines.h"

#ifdef BUILD_FOR_MCU
    #if (ECU_TYPE == ECU_TYPE_BU_702) // Сборка для БУ702
        #include "lib_bu_702.h"
    #else
        #error "BswLib: ECU_TYPE not supported"
    #endif
#else // Для генерации в Simulink
    #include <inttypes.h>
#endif

/**
 * \brief   Конфигурация частоты PWM
 * \param   pwmNum   - Номер модуля PWM, uint8_t
 * \param   pwm2Freq - Частота для PWM, uint8_t (Приводится к enum PwmX::Frequency)
 * \return  none
*/
void pwmFreqConfig(const uint8_t pwmNum, const uint8_t pwmFreqNum);

/**
 * \brief   Конфигурация канала PWM
 * \param   pwmNum   - Номер модуля PWM, uint8_t
 * \param   channel - Номер канала PWM, uint8_t (Приводится к enum PwmX::Channel)
 * \param   mode - Частота для PWM, uint8_t (Приводится к enum PwmX::Mode)
 * \param  checkEnable - Включить диагностику канала
 * \return  none
*/
void pwmChConfig(const uint8_t pwmNum, const uint8_t channel, const uint8_t mode, const bool checkEnable);

/**
 * \brief   Управление током/коэфф заполнения канала PWM
 * \param   pwmNum   - Номер модуля PWM, uint8_t
 * \param   channel - Номер канала PWM, uint8_t (Приводится к enum PwmX::Channel)
 * \param   mode - Частота для PWM, uint8_t (Приводится к enum PwmX::Mode)
 * \param   value - значение тока в мА или коэффициента заполнения ШИМ (от 0 до 1000)
         *              @n value = ((значение в %) * 10)
 * \return  none
*/
void pwmChControl(const uint8_t pwmNum, const uint8_t channel, const uint8_t mode, const uint16_t value);

/**
 * \brief   Статус канала PWM
 * \param   pwmNum   - Номер модуля PWM, uint8_t
 * \param   channel - Номер канала PWM, uint8_t (Приводится к enum PwmX::Channel)
 * \param   fbCurrent - Ток обратной связи мА
 * \return  статус канала, int8_t (Приводится к enum Status)
*/
int8_t pwmChFb(const uint8_t pwmNum, const uint8_t channel, uint16_t *fbCurrent);



#endif /* PWM_BSWAPI_H */