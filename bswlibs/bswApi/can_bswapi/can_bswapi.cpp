#include "can_bswapi.h"
#include <cstring>


#define RX_MSG_MAX      (128UL)
#define INVALID_VALUE	(0xFFFFFFFFUL)
#define MAX_CAN_ID      (0x1FFFFFFFUL)

#define RQS_PGN_MAX      (16UL)

void simulinkRxProccesCan1(CanMessage *rxMsg);
void simulinkRxProccesCan2(CanMessage *rxMsg);

/*Params*/
bool BridgeCan1ToCan2 = false;
bool BridgeCan2ToCan1 = false;

/*Params*/
bool BridgeCan1ToCan2_Boot = true;
bool BridgeCan2ToCan1_Boot = true;

/*Buffers for All RxMsgs*/
static CanRxCircBuff can1RxAllBuff;
static CanRxCircBuff can2RxAllBuff;

/*Buffers for Msgs subscribe*/
/* CAN1 */
static CanMessageCnt can1RxList[RX_MSG_MAX] =
{
	{{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, // 16
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
	{{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, // 32
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
	{{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, // 48
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, // 64
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, // 80
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
	{{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, // 96
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
	{{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, // 112
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, // 128
};
/*  CAN2 */
static CanMessageCnt can2RxList[RX_MSG_MAX] =
{
	{{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, // 16
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
	{{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, // 32
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
	{{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, // 48
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, // 64
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, // 80
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
	{{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, // 96
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
	{{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, // 112
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0},
    {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, {{INVALID_VALUE, 0, {0}}, 0}, // 128
};

static int can1RxMsgTop = 0;            /* Pointer to top of array */
static int can2RxMsgTop = 0;            /* Pointer to top of array */


/*J1939 Rqst */
struct RqstConfig
{
    uint32_t rqstId = 0xEAFF28;  // Default Rx Id for Rqst
    bool onlyPgn; // Rx Rqst only by Pgn
    bool fromAll; // Rx Rqst for All
};

static RqstConfig can1RqstConfg;
static RqstConfig can2RqstConfg;

J1939RqstSts can1RqstPgnList[RQS_PGN_MAX] = 
{
    {INVALID_VALUE, 0}, {INVALID_VALUE, 0}, {INVALID_VALUE, 0}, {INVALID_VALUE, 0},
    {INVALID_VALUE, 0}, {INVALID_VALUE, 0}, {INVALID_VALUE, 0}, {INVALID_VALUE, 0},
    {INVALID_VALUE, 0}, {INVALID_VALUE, 0}, {INVALID_VALUE, 0}, {INVALID_VALUE, 0},
    {INVALID_VALUE, 0}, {INVALID_VALUE, 0}, {INVALID_VALUE, 0}, {INVALID_VALUE, 0},
};

J1939RqstSts can2RqstPgnList[RQS_PGN_MAX] = 
{
    {INVALID_VALUE, 0}, {INVALID_VALUE, 0}, {INVALID_VALUE, 0}, {INVALID_VALUE, 0},
    {INVALID_VALUE, 0}, {INVALID_VALUE, 0}, {INVALID_VALUE, 0}, {INVALID_VALUE, 0},
    {INVALID_VALUE, 0}, {INVALID_VALUE, 0}, {INVALID_VALUE, 0}, {INVALID_VALUE, 0},
    {INVALID_VALUE, 0}, {INVALID_VALUE, 0}, {INVALID_VALUE, 0}, {INVALID_VALUE, 0},
};

static int can1RqstPgnTop = 0;          /* Pointer to top of Rqst array */
static int can2RqstPgnTop = 0;          /* Pointer to top of Rqst array */


void canInit(int32_t baudrateCan1, int32_t baudrateCan2)
{
    #ifdef BUILD_FOR_MCU
    /* Incoming messages filter */
    Can1::addBroadcastFilter();
    Can2::addBroadcastFilter();

    switch (baudrateCan1)
    {
    case 1:
        Can1::begin(Can1::Baudrate::BAUD_125);
        break;
    case 2:
        Can1::begin(Can1::Baudrate::BAUD_250);
        break;
    case 3:
        Can1::begin(Can1::Baudrate::BAUD_500);
        break;
    case 4:
        Can1::begin(Can1::Baudrate::BAUD_1000);
        break;                
    default:
        break;
    }

    switch (baudrateCan2)
    {
    case 1:
        Can2::begin(Can2::Baudrate::BAUD_125);
        break;
    case 2:
        Can2::begin(Can2::Baudrate::BAUD_250);
        break;
    case 3:
        Can2::begin(Can2::Baudrate::BAUD_500);
        break;
    case 4:
        Can2::begin(Can2::Baudrate::BAUD_1000);
        break;                
    default:
        break;
    }
    #endif
}

void canConfigBridges(bool can1ToCan2, bool can2ToCan1)
{
    BridgeCan1ToCan2 = can1ToCan2;
    BridgeCan2ToCan1 = can2ToCan1;
}

void canConfigBootBridges(bool can1ToCan2, bool can2ToCan1)
{
    BridgeCan1ToCan2_Boot = can1ToCan2;
    BridgeCan2ToCan1_Boot = can2ToCan1;
}

int8_t canSendMessage(int32_t can, uint32_t canId, uint8_t length , const uint8_t *data)
{
    int8_t result = 0;
    if (length > 8 || canId > 0x1FFFFFFF || data == nullptr)
    {
        result = -1;
    }
    
    #ifdef BUILD_FOR_MCU
    CanMessage msg;
    msg.id = canId;
    msg.length = length;
    memcpy(msg.data, data, length);
    if(msg.length != 0)
    {
        if(can == 0)
        {
            if(Can1::send(&msg) == Status::OK)
                result = 0;
            else
                result = 1;
        }
        else if (can == 1)
        {
            if(Can2::send(&msg) == Status::OK)
                result = 0;
            else
                result = 1;
        }
    }
    #endif
    return result;
}

bool msgSubscribe(int32_t can, uint32_t id)
{
    int status = 0;

    if(can == 0) //Can 1
    {
        if(can1RxMsgTop < RX_MSG_MAX)
        {
            /* Looking for existing subscribers ID */
            for(int i = 0; i < can1RxMsgTop; ++i)
            {
                if(can1RxList[i].msg.id == id)
                {
                    status = 1;
                }
            }
            if(status == 0)
            {
                can1RxList[can1RxMsgTop].msg.id = id;
                ++can1RxMsgTop;
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    else if(can == 1) //Can 2
    {
        if(can2RxMsgTop < RX_MSG_MAX)
        {
            /* Looking for existing subscribers ID */
            for(int i = 0; i < can2RxMsgTop; ++i)
            {
                if(can2RxList[i].msg.id == id)
                {
                    status = 1;
                }
            }
            if(status == 0)
            {
                can2RxList[can2RxMsgTop].msg.id = id;
                ++can2RxMsgTop;
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

uint32_t canGetMessage(int32_t can, uint32_t id, CanMessage *rxMsg)
{
    //#ifdef BUILD_FOR_MCU
    uint32_t ret = 0;

    if(can == 0) //Can 1
    {
        for(int i = 0; i < can1RxMsgTop; ++i)
        {
            if(can1RxList[i].msg.id == id)
            {
                ret = can1RxList[i].counter;
                rxMsg->id = can1RxList[i].msg.id;
                rxMsg->length = can1RxList[i].msg.length;
                memcpy(rxMsg->data, can1RxList[i].msg.data, 8);
                break;
            }
        }
    }

    else if(can == 1) //Can 2
    {
        for(int i = 0; i < can2RxMsgTop; ++i)
        {
            if(can2RxList[i].msg.id == id)
            {
                rxMsg->id = can2RxList[i].msg.id;
                rxMsg->length = can2RxList[i].msg.length;
                ret = can2RxList[i].counter;
                memcpy(rxMsg->data, can2RxList[i].msg.data, 8);
                break;
            }
        }
    }

    return ret;
    //#endif
}

bool canGetAllMessages(int32_t can, CanMessage *rxMsg)
{
	if(can == 0) //Can 1
	{
        *rxMsg = can1RxAllBuff.get();
        return can1RxAllBuff.isEmpty();
	}

	else if(can == 1) //Can 2
	{
        *rxMsg = can2RxAllBuff.get();
        return can2RxAllBuff.isEmpty();
	}
    return 0;
}


void confiqRqstId(int32_t can, uint32_t id, bool onlyPgn_a, bool fromAll_a)
{
    if(can == 0)
    {
        can1RqstConfg.rqstId = id;
        can1RqstConfg.onlyPgn = onlyPgn_a;
        can1RqstConfg.fromAll = fromAll_a;
    }
    else if(can == 1)
    {
        can2RqstConfg.rqstId = id;
        can2RqstConfg.onlyPgn = onlyPgn_a;
        can2RqstConfg.fromAll = fromAll_a;   
    }
}

void rqstSubscribe(int32_t can, uint32_t pgn)
{
    if(pgn > 0x3FFFF)
    {
        /*Pgn is not valid*/
        return;
    }

    int status = 0;

    if(can == 0) //Can 1
    {
        if(can1RqstPgnTop < RQS_PGN_MAX)
        {
            /* Looking for existing subscribers PGN */
            for(int i = 0; i < can1RqstPgnTop; ++i)
            {
                if(can1RqstPgnList[i].pgn == pgn)
                {
                    status = 1;
                }
            }
            if(status == 0)
            {
                can1RqstPgnList[can1RqstPgnTop].pgn = pgn;
                ++can1RqstPgnTop;
            }
        }
    }

    else if(can == 1) //Can 2
    {
        if(can2RqstPgnTop < RQS_PGN_MAX)
        {
            /* Looking for existing subscribers PGN */
            for(int i = 0; i < can2RqstPgnTop; ++i)
            {
                if(can2RqstPgnList[i].pgn == pgn)
                {
                    status = 1;
                }
            }
            if(status == 0)
            {
                can2RqstPgnList[can2RqstPgnTop].pgn = pgn;
                ++can2RqstPgnTop;
            }
        }
    }

}

uint32_t getRqstJ1939(int32_t can, uint32_t pgn)
{
    uint32_t res = 0;
    if(can == 0)
    {
        for(int i = 0; i < can1RqstPgnTop; ++i)
        {
            if(can1RqstPgnList[i].pgn == pgn)
            {
                res = can1RqstPgnList[i].rqstCnt;
                break;
            }
        }
    }
    else if(can == 1)
    {
        for(int i = 0; i < can2RqstPgnTop; ++i)
        {
            if(can2RqstPgnList[i].pgn == pgn)
            {
                res = can2RqstPgnList[i].rqstCnt;
                break;
            }
        }
    }
    return res;
}



void simulinkRxProccesCan1(CanMessage *rxMsg)
{
    /* Write to All buff*/
    can1RxAllBuff.put(rxMsg);

    /* Find Id */
    for(int i = 0; i < can1RxMsgTop; ++i)
    {
        if(can1RxList[i].msg.id == rxMsg->id)
        {
            can1RxList[i].msg.length = rxMsg->length;
            memcpy(can1RxList[i].msg.data, rxMsg->data, 8);
            ++can1RxList[i].counter;
            break;
        }          
    }

    bool status = false;
    uint32_t mask = 0x3FFFFFF;
    uint32_t allMask = 0x3FF00FF;

    if(can1RqstConfg.onlyPgn)
    {
        mask = 0x3FFFF00;
        allMask = 0x3FF0000;
    }

    if(((rxMsg->id & mask) == (can1RqstConfg.rqstId & mask)) || 
        ((rxMsg->id & allMask) == (can1RqstConfg.rqstId & allMask) && can1RqstConfg.fromAll))
    {
        uint32_t rqstPgn =  static_cast<uint32_t>(rxMsg->data[0]) | 
                            static_cast<uint32_t>(rxMsg->data[1]) << 8 | 
                            static_cast<uint32_t>(rxMsg->data[2]) << 16;
        /* Find Rqst */
        for(int i = 0; i < can1RqstPgnTop; ++i)
        {
            if(rqstPgn == can1RqstPgnList[i].pgn)
            {
                ++can1RqstPgnList[i].rqstCnt;
                break;
            }          
        }
    }
}

void simulinkRxProccesCan2(CanMessage *rxMsg)
{
    /* Write to All buff*/
    can2RxAllBuff.put(rxMsg);

    /* Find Id */
    for(int i = 0; i < can2RxMsgTop; ++i)
    {
        if(can2RxList[i].msg.id == rxMsg->id)
        {
            can2RxList[i].msg.length = rxMsg->length;
            memcpy(can2RxList[i].msg.data, rxMsg->data, 8);
            ++can2RxList[i].counter;
            break;
        }
    }

    bool status = false;
    uint32_t mask = 0x3FFFFFF;
    uint32_t allMask = 0x3FF00FF;

    if(can2RqstConfg.onlyPgn)
    {
        mask = 0x3FFFF00;
        allMask = 0x3FF0000;
    }

    if(((rxMsg->id & mask) == (can2RqstConfg.rqstId & mask)) || 
        ((rxMsg->id & allMask) == (can2RqstConfg.rqstId & allMask) && can2RqstConfg.fromAll))
    {
        uint32_t rqstPgn =  static_cast<uint32_t>(rxMsg->data[0]) | 
                            static_cast<uint32_t>(rxMsg->data[1]) << 8 | 
                            static_cast<uint32_t>(rxMsg->data[2]) << 16;
        /* Find Rqst */
        for(int i = 0; i < can2RqstPgnTop; ++i)
        {
            if(rqstPgn == can2RqstPgnList[i].pgn)
            {
                ++can2RqstPgnList[i].rqstCnt;
                break;
            }          
        }
    } 
}

