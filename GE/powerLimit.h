#ifndef POWERLIMIT__H
#define POWERLIMIT__H

#include "shu_math.h"
#include "motor.h"
#include "superCap.h"

/************************************************************��������**************************************************************/
//���̹������ƺ���//ͨ�����ֵ���ʽ�Թ��ʽ�������
int32_t PowerLimIntegral(uint16_t maxPower, float nowPower, int32_t setOut);
//ͨ�����幦�ʽ�������
int32_t PowerLimBuffer(float buffer, int32_t setOut);
//���������ƺ���
void AllotPower(int32_t setOut);
//б�º���//������ʹ��
void SlopeKeyboard(int16_t * reality, int16_t aim, uint16_t intervalTime, uint64_t time);
//��������ר�ù�������
int32_t PowerLimBuffer_Cap(uint16_t maxPower, float buffer, int32_t setOut);
#endif












