#include "nvmem_bswapi.h"


#ifdef BUILD_FOR_MCU
NvMem NvMemBank1;
NvMem NvMemBank2;
NvMem NvMemBank3;
NvMem NvMemBank4;

namespace Bsw_NvMem
{
int8_t nvMemInit(uint8_t bank, uint8_t *data, size_t size)
{
    int8_t status = -1;

    if(data != nullptr)
    {
        switch (bank)
        {
        case 0:
            NvMemBank1.MemInit(static_cast<NvMem::Bank>(bank), data, size);
            break;
        case 1:
            NvMemBank2.MemInit(static_cast<NvMem::Bank>(bank), data, size);
            break;
        case 2:
            NvMemBank3.MemInit(static_cast<NvMem::Bank>(bank), data, size);
            break;
        case 3:
            NvMemBank4.MemInit(static_cast<NvMem::Bank>(bank), data, size);
            break;    
        default:
            break;
        }
    }

    return status;
}
}

void NvMem::MemInit(const NvMem::Bank bank, uint8_t *data, size_t size, uint16_t proccesStepTime_ms)
{
    status_m = Status::NO_INIT;
    if(data != nullptr)
    {
        bank_m = bank;
        data_m = data;
        dataSize_m = size;
        writeFlg_m = false;
        writeProccesFlg_m = false;
        proccesStepTime_ms_m = proccesStepTime_ms;
        timeoutCnt_ms_m = 0;

        /* Инициализируем EEPROM. Если в памяти будут актуальные данные они будут прочитаны.
        Если данных в памяти нет или память повреждена на входах останутся значения по умолчанию */
        if(Eeprom::init(bank_m, (void*)data_m, dataSize_m) == Status::OK)
        {
            status_m = Status::OK;
        }
    }
}

void NvMem::SetWriteFlg()
{
    writeFlg_m = true;
}

void NvMem::ResetWriteFlg()
{
    writeFlg_m = false;   
}

Status NvMem::GetStatus()
{
    return this->status_m;
}

void NvMem::FsmProcces()
{  
    Status eepromStatus = Eeprom::getStatus(bank_m);
    switch(state_m)
    {
    case NvMemState::STATE_INIT:
        if((eepromStatus == Status::OK) && (status_m == Status::OK))
        {
            state_m = NvMemState::STATE_WAIT;
        }
        else
        {
            state_m = NvMemState::STATE_ERROR;
        }
        break;

    case NvMemState::STATE_WAIT:
        timeoutCnt_ms_m = 0;
        if(eepromStatus == Status::OK)
        {
            if(writeFlg_m)
            {
                state_m = NvMemState::STATE_WRITE;
            }
        }
        else
        {
            state_m = NvMemState::STATE_ERROR;
        }
        break;

    case NvMemState::STATE_WRITE:
        timeoutCnt_ms_m += proccesStepTime_ms_m;
        if(timeoutCnt_ms_m > 1000)
        {
            state_m = NvMemState::STATE_ERROR;
            break;
        }
        else
        {
            if(eepromStatus == Status::OK)
            {
                if(!writeProccesFlg_m)
                {
                    Eeprom::write(bank_m, reinterpret_cast<void*>(data_m), dataSize_m);
                    writeProccesFlg_m = true; // Начинаем процесс записи
                }
                else
                {
                    //Запись закончена
                    writeProccesFlg_m = false;
                    state_m = NvMemState::STATE_READ; // Переход к чтению
                }
            }
            else
            {
                state_m = NvMemState::STATE_ERROR; // Ошибка, если статус EEPROM не OK
            }             
        }    
        break;

    case NvMemState::STATE_READ:
        this->ResetWriteFlg();
        if (eepromStatus != Status::OK) {
            state_m = NvMemState::STATE_ERROR; // Ошибка, если статус EEPROM не OK
            break;
        }
        state_m = NvMemState::STATE_WAIT;
        break;
        
    case NvMemState::STATE_ERROR:
        status_m == Status::ERROR;
        break;

    default:
        state_m = NvMemState::STATE_INIT;
        break;
    }
}
#endif

void bswNvMemApi_SetWriteFlg(uint8_t bank)
{
    #ifdef BUILD_FOR_MCU
    switch (bank)
    {
    case 0:
        NvMemBank1.SetWriteFlg();
        break;
    case 1:
        NvMemBank2.SetWriteFlg();
        break;
    case 2:
        NvMemBank3.SetWriteFlg();
        break;
    case 3:
        NvMemBank4.SetWriteFlg();
        break;    
    default:
        break;
    }
    #endif
}

int8_t bswNvMemApi_GetStatus(uint8_t bank)
{
    int8_t status = 0;
    #ifdef BUILD_FOR_MCU
    switch (bank)
    {
    case 0:
        status = static_cast<int8_t>(NvMemBank1.GetStatus());
        break;
    case 1:
        status = static_cast<int8_t>(NvMemBank2.GetStatus());
        break;
    case 2:
        status = static_cast<int8_t>(NvMemBank3.GetStatus());
        break;
    case 3:
        status = static_cast<int8_t>(NvMemBank4.GetStatus());
        break;    
    default:
        break;
    }
    #endif
    return status;
}