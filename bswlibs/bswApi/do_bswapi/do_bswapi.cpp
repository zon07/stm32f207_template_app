#include "do_bswapi.h"


void doGndChControl(const uint8_t channel, bool state)
{
    #ifdef BUILD_FOR_MCU
        #if (ECU_TYPE == ECU_TYPE_DBK_10)
            if(state)
            {
                Outputs::enable(static_cast<Outputs::Channel>(channel));
            }
            else
            {
                Outputs::disable(static_cast<Outputs::Channel>(channel));
            }
        #else
            #error BswLib ECU_TYPE not supported
        #endif
    #endif
}


