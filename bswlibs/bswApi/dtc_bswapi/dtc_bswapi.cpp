#include "dtc_bswapi.h"

#define MAX_DTCREG_COUNT (32U)


#ifdef BUILD_FOR_MCU
static DmJ1939 dtcManager;
static DmJ1939::MsgPriority dtcDm1MsgPriority = DmJ1939::MsgPriority::PRIORITY_6;
#endif

static uint32_t dtcClock_1s = 0;
static uint32_t dtcClock_1s_prev = 0;
bool isActiveDtc = false;


/*Do not generate Simulink block*/
void dtcProcces_100ms(void);
void dtcProcces_1sec(void);

void dtcDm1Init(int32_t can, uint8_t priority, uint8_t source_address)
{
	#ifdef BUILD_FOR_MCU
        dtcManager.init(static_cast<DmJ1939::CanModule>(can), source_address);
        dtcDm1MsgPriority = static_cast<DmJ1939::MsgPriority>(priority);
	#endif
}

void dtcDm1Register(uint32_t spn, uint8_t fmi, bool state)
{
    #ifdef BUILD_FOR_MCU
    if(state)
    {
        if(dtcManager.addDtc(spn, static_cast<DmJ1939::Fmi>(fmi)) == Status::OK)
        {
            isActiveDtc = true;
        }
    }
    else
    {
        dtcManager.deleteDtc(spn, static_cast<DmJ1939::Fmi>(fmi));
    }
	#endif
}

void dtcDm1LampSet(uint8_t lamp, uint8_t state, uint8_t flashState)
{
    #ifdef BUILD_FOR_MCU
    switch (lamp)
    {
    case 0:
        dtcManager.setLampStatus(DmJ1939::Lamp::PL, static_cast<DmJ1939::LampState>(state), static_cast<DmJ1939::LampFlashMode>(flashState));
        break;
    case 2:
        dtcManager.setLampStatus(DmJ1939::Lamp::AWL, static_cast<DmJ1939::LampState>(state), static_cast<DmJ1939::LampFlashMode>(flashState));
        break;
    case 4:
        dtcManager.setLampStatus(DmJ1939::Lamp::RSL, static_cast<DmJ1939::LampState>(state), static_cast<DmJ1939::LampFlashMode>(flashState));
        break;
    case 6:
        dtcManager.setLampStatus(DmJ1939::Lamp::MIL, static_cast<DmJ1939::LampState>(state), static_cast<DmJ1939::LampFlashMode>(flashState));    
        break; 
    default:
        break;
    }
	#endif
}

bool dtcDm1IsError(void)
{  
    bool result = false;
    #ifdef BUILD_FOR_MCU
    result = dtcManager.getCountOfDtc() > 0 ? true : false;
    #endif
    return result;
}

void dtcProcces_100ms(void)
{
    #ifdef BUILD_FOR_MCU
    if(isActiveDtc)
    {
        dtcManager.send(dtcDm1MsgPriority);
        isActiveDtc = false;
    }
    #endif
}

void dtcProcces_1sec(void)
{
    #ifdef BUILD_FOR_MCU
    isActiveDtc = false;
    dtcManager.send(dtcDm1MsgPriority);
    ++dtcClock_1s;
    #endif
}