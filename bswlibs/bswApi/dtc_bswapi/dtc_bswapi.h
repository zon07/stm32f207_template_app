#ifndef DTC_BSWAPI_H
#define DTC_BSWAPI_H

#define SIMULINK_DTC_BSWAPI_USED (1U)

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
 * \brief   Инициализация сервиса Diagnostic Messages 1 CAN J1939
 * \param   can - номер модуля Can (0 - CAN_1, 1 - CAN_2)
 * \param   priority - Приоритет с которым будет передаваться сообшение
 * \param   source_address - source address согласно протоколу j1939
 * \return  none
 */
void dtcDm1Init(int32_t can, uint8_t priority, uint8_t source_address);

/**
 * \brief   Активировать/деактивировать DTC (Diagnostic trouble code)
 * \param   spn - Номер Spn DTC
 * \param   fmi - Номер Fmi DTC
 * \param   state - Состояние DTC (true - active, false - deactive)
 * \return  none
 */
void dtcDm1Register(uint32_t spn, uint8_t fmi, bool state);

/**
 * \brief   Управление лампами отказов
 * \param   lamp - Номер Spn DTC
 *          @n 0 - PL - protect lamp
 *          @n 1 - AWL - amber Warning lamp
 *          @n 2 - RSL - red stop lamp
 *          @n 3 - MIL - malfunction indicator lamp
 * \param   state - Состояние лампы
 *          @n 0 - LAMP_ON
 *          @n 1 - LAMP_OFF
 * \param   flashState - Режим моргания лампы
 *          @n FLASH_1HZ - lamp flash 1 Hz
 *          @n FLASH_2HZ - lamp flash 2 Hz
 *          @n FLASH_ON - lamp continuous illuminate
 * \return  none
 */
void dtcDm1LampSet(uint8_t lamp, uint8_t state, uint8_t flashState);

/**
 * \brief   Проверка наличия ошибок DTC
 * \return  True - если есть хотя бы одна активная ошибка DTC
 */
bool dtcDm1IsError(void);

#endif /* DTC_BSWAPI_H */