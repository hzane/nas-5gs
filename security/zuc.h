#ifndef ZUC_H
#define ZUC_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
/**
    @P CK key
    @P COUNT 计数器
    @P BEARER
    @P DIRECTION 方向
    @P LENGTH    加密位数
    @P M    加密输入数据
    @P C    加密输出数据
*/

void EEA3(uint8_t* CK, uint32_t COUNT, uint32_t BEARER, uint32_t DIRECTION, uint32_t LENGTH, uint32_t* M, uint32_t* C);

void ZUC_EEA3(unsigned char* key,
              unsigned int   COUNT,
              unsigned int   BEARER,
              unsigned int   DIRECTION,
              unsigned char* data,
              unsigned int   length);
// void EEA31(uint8_t* CK,uint8_t* IV,uint32_t COUNT,uint32_t BEARER,uint32_t DIRECTION,uint32_t LENGTH,uint32_t* M,uint32_t* C);

#endif
