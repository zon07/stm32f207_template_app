#ifndef EVNCIRCBUFF_H_
#define EVNCIRCBUFF_H_

#include <inttypes.h>

template <typename T>
class CircBuff
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

    bool isExist(T data)
    {
        for(uint16_t i = 0; i < BUFFER_SIZE; ++i)
        {
            if(events[i] == data)
            {
                return true;
            }         
        }
        return false;
    }


    bool isEmpty()
    {
        return head == tail;
    }

    bool isFull()
    {
        return ((head + 1) % BUFFER_SIZE) == tail;
    }

    void put(const T &data)
    {
        events[head] = data;
        head = (head + 1) % BUFFER_SIZE;
        if(head == tail)
            tail = (tail + 1) % BUFFER_SIZE;
    }

    T get(void)
    {
        T res = {0};
        if(!isEmpty())
        {
            res = events[tail];
            events[tail] = 0;
            tail = (tail + 1) % BUFFER_SIZE;
        }
        return res;
    }

private:
    uint16_t head = 0;
    uint16_t tail = 0;
    static constexpr uint16_t BUFFER_SIZE = 32;
    T events[BUFFER_SIZE] = {0};
    
    void reset(void)
    {
       head = 0;
       tail = 0; 
    }    
};

#endif /* EVNCIRCBUFF_H_ */