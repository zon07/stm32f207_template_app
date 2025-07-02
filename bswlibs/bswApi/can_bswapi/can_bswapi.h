#ifndef CAN_BSWAPI_H
#define CAN_BSWAPI_H

#define SIMULINK_CAN_BSWAPI_USED (1U)

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
#include "canrxcircbuff.h"

struct CanMessageCnt
{
    CanMessage msg;      /* Message ID  */
    uint32_t counter;
};

struct J1939RqstSts
{
    uint32_t pgn;      /* Rqsted Pgn  */
    uint32_t rqstCnt;
};


void canInit(int32_t baudrateCan1, int32_t baudrateCan2);
void canConfigBridges(bool can1ToCan2, bool can2ToCan1);
void canConfigBootBridges(bool can1ToCan2, bool can2ToCan1);

int8_t canSendMessage(int32_t can, uint32_t canId, uint8_t length , const uint8_t *data);

bool msgSubscribe(int32_t can, uint32_t id);
uint32_t canGetMessage(int32_t can, uint32_t id, CanMessage *rxMsg);
bool canGetAllMessages(int32_t can, CanMessage *rxMsg);


void confiqRqstId(int32_t can, uint32_t id, bool onlyPgn_a, bool fromAll_a);
void rqstSubscribe(int32_t can, uint32_t pgn);
uint32_t getRqstJ1939(int32_t can, uint32_t pgn);


#endif  /* CAN_BSWAPI_H */