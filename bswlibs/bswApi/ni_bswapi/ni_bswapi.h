#ifndef NI_BSW_H
#define NI_BSW_H

#define SIMULINK_NI_BSWAPI_USED (1U)

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
 * \brief   Управление подтяжкой на канале channel
 * \param   channel - номер канала (смотри enum Channel)
 * \param   cmd - true - включить подтяжку, false - отключить
 * \return  None
 */
void bswFreqApiConfigPullUp(const uint8_t channel, bool mode);

/**
 * \brief   Получить статус диагностики канала индукционного
 *          датчика. Если выбран активный датчик вернется 
 *          статус NOT_FOUND.
 * \param   channel - номер канала (смотри enum Channel)
 * \return  uint8_t статус канала (Status - статус диагностики)
 *              @n Status::OK - канал работает в штатном режиме
 *              @n Status::BREAK - обрыв канала
 *              @n Status::SHORT_GND - короткое замыкание
 *              @n Status::NOT_FOUND - для данного типа датчиков диагностика не поддерживается
 */
int8_t bswFreqApiGetStatus(const uint8_t channel);


/**
 * \brief   Получить значение периода сигнала на канале channel
 * \param   channel - номер канала (смотри enum Channel)
 * \return  float значение периода сигнала в секундах
 */
float bswFreqApiGetPeriod(const uint8_t channel);

/**
 * \brief   Получить значение частоты сигнала на канале channel
 * \param   channel - номер канала (смотри enum Channel)
 * \return  float значение частоты сигнала в герцах
 */
float bswFreqApiGetFrequency(const uint8_t channel);

/**
 * \brief   Получить значение коэффициента заполнения сигнала на канале channel
 * \param   channel - номер канала (смотри enum Channel)
 * \return  float значение коэффициента заполнения сигнала в процентах
 */
float bswFreqApiGetDutyCycle(const uint8_t channel);

/**
 * \brief   Получить значение счётчика импульсов на канале channel
 * \param   channel - номер канала (смотри enum Channel)
 * \return  uint32_t значение счётчика импульсов на канале channel
 */
uint32_t bswFreqApiGetPulseCounterValue(const uint8_t channel);


#if ((ECU_TYPE == ECU_TYPE_DBK_10) || (!defined BUILD_FOR_MCU))
/**
* \brief   Получить коэффициент (уровень) заполнения импульсов на канале channel
* \param   channel - номер канала (смотри enum Freq_channel)
* \return  float значение уровня заполнения импульсов на канале channel
*/
float bswFreqApiGetLevelValue(const uint8_t channel);

/**
 * \brief   Установить время усреднения  коэффициента (уровеня) заполнения импульсов на канале channel
 * \param   channel - номер канала (смотри enum Freq_channel)
 * \param   time - время усреднения в секундах
 * \return  status результат выполнения
 */
int8_t bswFreqApiSetLevelTimeAvg(const uint8_t channel, float time);
#endif


#endif /* NI_BSW_H */