#ifndef UIR_BSWAPI_H
#define UIR_BSWAPI_H

#define SIMULINK_UIR_BSWAPI_USED (1U)

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


/**
 * \brief   Конфигурация канала UIR
 * \param   channel - Номер канала UIR, uint8_t (Приводится к enum Channel)
 * \param   mode - Режим работы канала UIR, uint8_t (Приводится к enum Mode)
 * \return  None
*/
void uirChannelConfig(uint8_t channel, uint8_t mode);

/**
 * \brief   Получить измеренное значение напряжения канала channel UIR
 * \param   channel - Номер канала UIR, uint8_t (Приводится к enum Channel)
 * \return  Значение измеренного напряжения в Вольтах (float)
 */
float uirGetVoltage(uint8_t channel);

/**
 * \brief   Получить измеренное значение тока канала channel UIR
 * \param   channel - Номер канала UIR, uint8_t (Приводится к enum Channel)
 * \return  Значение измеренного тока в Амперах (float)
 */
float uirGetCurrent(uint8_t channel);

/**
 * \brief   Получить измеренное значение сопротивления канала channel UIR
 * \param   channel - Номер канала UIR, uint8_t (Приводится к enum Channel)
 * \return  Значение измеренного сопротивления в Омах (float)
 */
float uirGetResistance(uint8_t channel);

/**
 * \brief   Статус канала UIR
 * \param   channel - Номер канала UIR, uint8_t (Приводится к enum Channel)
 * \return  Статус канала, uint8_t, (Приводится от enum Status)
*/
int8_t uirGetStatus(uint8_t channel);
#endif /* UIR_BSWAPI_H */