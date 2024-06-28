#pragma once
#include <CassouletEngineLibrarie/System/Libs.h>

static uint16_t Read2Bytes(const uint8_t* pWADData, int offset)
{
    uint16_t ReadValue;
    std::memcpy(&ReadValue, pWADData + offset, sizeof(uint16_t));
    return ReadValue;
}

static uint32_t Read4Bytes(const uint8_t* pWADData, int offset)
{
    uint32_t ReadValue;
    std::memcpy(&ReadValue, pWADData + offset, sizeof(uint32_t));
    return ReadValue;
}
