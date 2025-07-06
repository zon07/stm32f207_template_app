#include "can_control.h"

#ifndef MATLAB_MEX_FILE

extern osMessageQueueId_t appCan1TxQueueHandle;
extern osMessageQueueId_t appCan2TxQueueHandle;
extern osMessageQueueId_t appCan1RxQueueHandle;
extern osMessageQueueId_t appCan2RxQueueHandle;

#endif


bool CanGetAllMessages(int32_t can, CAN_Msg_t *rxMsg)
{
    if(rxMsg == NULL)
    {
        return false;
    }
#ifndef MATLAB_MEX_FILE
    if (can == 0)  // CAN1
    {
        // Пытаемся получить сообщение без ожидания (timeout = 0)
        if (osMessageQueueGet(appCan1RxQueueHandle, rxMsg, NULL, 0) == osOK)
        {
            return true;
        }
    }
    else if (can == 1)  // CAN2
    {
        if (osMessageQueueGet(appCan2RxQueueHandle, rxMsg, NULL, 0) == osOK)
        {
            return true;
        }
    }
#endif
    return false;
}


bool CanSendMessage(int32_t can, const CAN_Msg_t *txMsg)
{
    if(txMsg == NULL)
    {
        return false;
    }
    
#ifndef MATLAB_MEX_FILE
    if (can == 0)  // CAN1
    {
        if (osMessageQueuePut(appCan1TxQueueHandle, txMsg, 0, 0) == osOK)
        {
            return true;
        }
    }
    else if (can == 1)  // CAN2
    {
        if (osMessageQueuePut(appCan2TxQueueHandle, txMsg, 0, 0) == osOK)
        {
            return true;
        }
    }
#endif
    return false;
}