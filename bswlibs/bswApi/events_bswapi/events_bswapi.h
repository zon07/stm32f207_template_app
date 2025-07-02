#ifndef EVENTS_BSWAPI_H
#define EVENTS_BSWAPI_H

#define SIMULINK_EVENTS_BSWAPI_USED (1U)

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
 * \brief   Инициализация сервиса событий (Events)
 * \param   canId - CanId сообщений с событиями
 * \param   can - номер модуля Can (0 - CAN_1, 1 - CAN_2)
 * \return  True - ok; False - error
 */
bool configEventManager(uint32_t canId, uint8_t can);

/**
 * \brief   Инициализация сервиса событий (Events)
 * \param   eventNum - Номер события
 */
void eventReg(uint16_t eventNum);


#endif  /* EVENTS_BSWAPI_H */