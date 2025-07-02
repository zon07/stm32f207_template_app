#ifndef CANRXBUFF_H_
#define CANRXBUFF_H_

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
    struct CanMessage
    {
        uint32_t id;      /* Message ID  */
        uint8_t length;   /* Data length */
        uint8_t data[8];  /* Data        */
    };
#endif


class CanRxCircBuff
{
public:
    uint16_t getBuffSize(void)
    {
        return BUFFER_SIZE;
    }

    uint16_t getCount(void)
    {
        uint16_t retval = 0;
        if (head < tail) retval = BUFFER_SIZE + head - tail;    
        else retval = head - tail;
        return retval;
    }

    bool isEmpty()
    {
        return head == tail;
    }

    bool isFull()
    {
        return ((head + 1) % BUFFER_SIZE) == tail;
    }

    void put(const CanMessage *msg)
    {
        msgs[head].id = msg->id;
        msgs[head].length = msg->length;

        for(uint8_t i = 0; i < msg->length; ++i)
        {
            msgs[head].data[i] = msg->data[i];
        }
        head = (head + 1) % BUFFER_SIZE;
        if(head == tail)
            tail = (tail + 1) % BUFFER_SIZE;
    }

    CanMessage get(void)
    {
        CanMessage res = {0xFFFFFFFFUL, 0, {0}};
        if(!isEmpty())
        {
            res = msgs[tail];
            tail = (tail + 1) % BUFFER_SIZE;
        }
        return res;
    }


private:
    uint16_t head = 0;
    uint16_t tail = 0;
    static constexpr uint16_t BUFFER_SIZE = 128;
    CanMessage msgs[BUFFER_SIZE] = {0};
    
    void reset(void)
    {
       head = 0;
       tail = 0; 
    }    
};

#endif /* CANRXBUFF_H_ */