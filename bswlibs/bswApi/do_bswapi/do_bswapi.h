#ifndef DO_BSWAPI_H
#define DO_BSWAPI_H

#define SIMULINK_DO_BSWAPI_USED (1U)

#include "bsw_version_defines.h"
#include "ecu_types_defines.h"

#ifdef BUILD_FOR_MCU
    #if (ECU_TYPE == ECU_TYPE_DBK_10) // Сборка для ДБК10
        #include "lib_dbk-10-AT32F437.h"
    #else
        #error "BswLib: ECU_TYPE not supported"
    #endif
#else // Для генерации в Simulink
    #include <inttypes.h>
#endif


/**
 * \brief   Управление дискретным выходом DO- (на GND)
 * \param   channel - Номер канала DO-, uint8_t (Приводится к enum Outputs::Channel)
 * \param   state - True - Включить/ False - выключить канал
 * \return  
*/
void doGndChControl(const uint8_t channel, bool state);



#endif /* DO_BSWAPI_H */