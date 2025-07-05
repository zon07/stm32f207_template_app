#ifndef CAN_CONTROL_H
#define CAN_CONTROL_H

#define SIMULINK_LED_CONTROL_USED (1U)

#ifndef MATLAB_MEX_FILE
    #include <inttypes.h>
    #include <stdbool.h>
    #include "FreeRTOS.h"
    #include "task.h"
    #include "cmsis_os.h"

    #include "canMsgs.h"
#else
    #include <inttypes.h>
    #include <stdbool.h>

typedef struct {
    uint8_t   Extended;   ///< Тип идентификатора: `0` (11-битный ID) или `1` (29-битный ID).
    uint8_t   Length;     ///< Длина данных в байтах (0..8). Соответствует полю `DLC` в CAN.
    uint8_t   Remote;     ///< Флаг удалённого запроса: `0` (данные) или `1` (remote frame).
    uint8_t   Error;      ///< Флаг ошибки (опционально, зависит от реализации драйвера).
    uint32_t  ID;         ///< Идентификатор: 11 или 29 бит (зависит от `Extended`).
    uint32_t  Timestamp;  ///< Метка времени приёма/отправки (в мкс или тиках системы).
    uint8_t   Data[8];    ///< Полезная нагрузка (максимум 8 байт).
} CAN_Msg_t;
#endif


bool CanGetAllMessages(int32_t can, CAN_Msg_t *rxMsg);

bool CanSendMessage(int32_t can, const CAN_Msg_t *rxMsg);



#endif /* CAN_CONTROL_H */