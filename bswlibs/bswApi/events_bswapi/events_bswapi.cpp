#include "events_bswapi.h"
#include "circbuff.h"

#define MAX_CAN_ID (0x1FFFFFFFU)
#define DEFAULT_EVENTS_CANID (0x18FFAA31U)


static uint32_t eventsCanId = DEFAULT_EVENTS_CANID; // Operator Wrong Actions Events
static CircBuff<uint16_t> evBuff;
static uint8_t canModule = 0;

/*Do not generate Simulink block*/
void eventSendProcess(void);

bool configEventManager(uint32_t canId, uint8_t can)
{
    canModule = can;
    if(canId >= 0 && canId <= MAX_CAN_ID)
    {
        eventsCanId = canId;
        return true;
    }
    return false;
}

void eventReg(uint16_t eventNum)
{
    if(!evBuff.isExist(eventNum))
    {
        evBuff.put(eventNum);
    }
}

void eventSendProcess(void)
{
    uint8_t count = 0;
    bool needToSend = false;
    #ifdef BUILD_FOR_MCU
    CanMessage msg;
    msg.id = eventsCanId;
    msg.length = 8;
    for(uint8_t i = 0; i < msg.length; ++i)
    {
        msg.data[i] = 0x00;
    }
    // Max 4 events in 1 msgs
    while(!evBuff.isEmpty() && (count <= 6))
    {
        uint16_t eventNum = evBuff.get();
        msg.data[count] = eventNum & 0xFF;
        msg.data[count + 1] = (eventNum & 0xFF00) >> 8;
        count += 2;
        needToSend = true;
    }
    if(needToSend)
    {
        if(0 == canModule)
            Can1::send(&msg);
        else
            Can2::send(&msg);
    }
    #endif    
}
