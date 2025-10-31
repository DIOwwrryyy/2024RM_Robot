#ifndef POWERLIMIT__H
#define POWERLIMIT__H

#include "shu_math.h"
#include "motor.h"
#include "superCap.h"

/************************************************************函数声明**************************************************************/
//底盘功率限制函数//通过积分的形式对功率进行限制
int32_t PowerLimIntegral(uint16_t maxPower, float nowPower, int32_t setOut);
//通过缓冲功率进行限制
int32_t PowerLimBuffer(float buffer, int32_t setOut);
//电机输出限制函数
void AllotPower(int32_t setOut);
//斜坡函数//给键盘使用
void SlopeKeyboard(int16_t * reality, int16_t aim, uint16_t intervalTime, uint64_t time);
//超级电容专用功率限制
int32_t PowerLimBuffer_Cap(uint16_t maxPower, float buffer, int32_t setOut);
#endif












