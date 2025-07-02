#ifndef NVMEM_BSWAPI_H
#define NVMEM_BSWAPI_H

#define SIMULINK_NVMEM_BSWAPI_USED (1U)

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

#ifdef BUILD_FOR_MCU
class NvMem
{
    enum class NvMemState: int8_t
    {
        STATE_INIT = 0,
        STATE_WAIT,
        STATE_WRITE,
        STATE_READ,
        STATE_ERROR,
        STATES_COUNT
    };

public:
    using Bank = Eeprom::Bank;

    void MemInit(const NvMem::Bank bank, uint8_t *data, size_t size, uint16_t proccesStepTime_ms = 100);
    void SetWriteFlg();
    void FsmProcces();
    Status GetStatus();

private:
    void ResetWriteFlg();
    uint16_t proccesStepTime_ms_m;
    uint16_t timeoutCnt_ms_m = 0;
    Status status_m = Status::NO_INIT;
    NvMemState state_m = NvMemState::STATE_INIT;
    bool writeProccesFlg_m = false;
    Eeprom::Bank bank_m;
    uint8_t *data_m;
    size_t dataSize_m;
    bool writeFlg_m;
};

namespace Bsw_NvMem
{
int8_t nvMemInit(uint8_t bank, uint8_t *data, size_t size);
}
#endif

void bswNvMemApi_SetWriteFlg(uint8_t bank);
int8_t bswNvMemApi_GetStatus(uint8_t bank);

#endif /* NVMEM_BSWAPI_H */