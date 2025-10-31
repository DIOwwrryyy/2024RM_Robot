#ifndef _ANONYMITY_H_
#define _ANONYMITY_H_

#include "stdint.h"
#include "dma.h"
#include "usart.h"

#define df_AnonymityLong 70
#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)		) )
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )

extern uint8_t anonymity_au8[df_AnonymityLong];												//匿名用数组
//匿名发送函数一共十个第十个不能用
void Anonymity_TX(int16_t a_x,int16_t a_y,int16_t a_z,int16_t g_x,int16_t g_y,int16_t g_z,int16_t m_x,int16_t m_y,int16_t m_z,int32_t bar);
//检测yaw轴时使用
void yawTXSpeed(void);
void yawTXAngle(void);
//检测pitch轴时使用
void pitchTXAngle(void);
void pitchTXSpeed(void);
//临时监视器
void tempTX(void);
//视觉监视器
void visionTX(void);
//发射机构监视数据  
void attackTX(void);
//底盘监视函数
void chassisTX(void);
//陀螺仪监视器
void topTX(void);
//2006发弹监视
void SupplyTXAngle(void);
//摩擦轮监视
void FirctionTXSpeed(void);
//底盘拨弹电机监视
void DownTXSpeed(void);
//电机状态监视
void motorTXSpeed(void);
//云台追差监视
//void 云台追差(void);
////功率限制监视
//void 功率监视(void);
#endif







