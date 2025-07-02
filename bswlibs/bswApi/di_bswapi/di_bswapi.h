#ifndef DI_BSWAPI_H
#define DI_BSWAPI_H

#define SIMULINK_DI_BSWAPI_USED (1U)

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
 * \brief   Конфигурация подтяжки канала channel
 * \param   channel - номер дискретного входа
 * \param   mode - режим подтяжки (0 - pullDown; 1 - pullUp)
 * \return  No
 */
void diConfigPullUp(uint8_t channel, uint8_t mode);

/**
 * \brief   Получить значение состояния дискретного входа channel
 *          Вернёт HIGH если напряжение на дискретном входе выше 
 *          HIGH_LVL_TRESHOLD и LOW если напряжение на входе ниже
 *          LOW_LVL_TRESHOLD (Состояние подтяжки не учитывается)
 * \param   channel Номер дискретного входа.
 * \return  Состояние канала 0 - замкнут на GND; 1 - замкнут на PWR +5V.
 */
uint8_t diGetState(uint8_t channel);

#endif /* DI_BSWAPI_H */