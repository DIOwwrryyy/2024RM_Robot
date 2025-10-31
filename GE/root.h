#ifndef ROOT__H
#define ROOT__H

#include "stdint.h"
#include "string.h"
#include "gpio.h"
#include "motor.h"

//供调用的接口宏
#define Root_topState root_t.topRoot.state

#define df_resetTime 1000

#ifndef df_root
	#define df_root
	#define df_offLine 0
	#define df_onLine	1
	#define df_open 1
	#define df_off 0
	#define df_error 0
	#define df_ok 1
#endif
#ifndef df_control
	#define df_control
	#define df_gimbalControl 0x02
	#define df_chassisControl 0x01
	#define ReadCHPin	GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15)		//底盘对应的GPIO
	#define ReadGMPin GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4)		//云台对应的GPIO	
	
	#define RedLED(level) 		 HAL_GPIO_WritePin(GPIOE,GPIO_PIN_0,level)//红色呼吸灯		//红色呼吸灯闪烁说明出现问题
	#define df_Red 1
	#define GreenLED(level) HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,level)		//绿色呼吸灯		//
	#define df_Green 2
	#define BuleLED(level) HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,level)		//蓝色呼吸灯
	#define df_Bule 3
#endif

//初始化监视
 struct Init_typedf
{
		uint8_t mecanumInit :1;		//新麦轮解算初始化
		uint8_t gimbalInit :1;		//两个云台初始化
		uint8_t chassisInit :1;		//底盘电机初始化
		uint8_t attackInit	:1;		//发射机构初始化(两个摩擦轮//一个拨弹电机)
		uint8_t statrInit :1;		//启动初始化
		uint8_t resurgenceInit :1;				//复活初始化
		uint8_t positionInit :2;	//主控的位置//01是底盘10是云台，另外两种是无效
}__attribute__ ((__packed__));
//视觉监视信息
 struct visionRoot_typedef			
{
	uint8_t vision_all :1;		
	uint8_t communicat :1;	//视觉通信
	uint8_t dataRight :1;			//数据正确性
	uint8_t time;			//时间
}__attribute__ ((__packed__));
//遥控监视信息
 struct remoteRoot_typedef			
{
	uint8_t communicat :1;	//遥控通信
	uint8_t acceptor :1;	//接收机状态
	uint8_t time;			//时间
}__attribute__ ((__packed__));
//裁判系统的信息
 struct judgeRoot_typedef			
{
	uint8_t communicat :1;	//裁判系统通信
	uint8_t dataRight :1;	//裁判系统数据正确性判断
	uint8_t time;			//时间
}__attribute__ ((__packed__));
//超级电容的状态
 struct superCapRoot_typedef			
{
	uint8_t communicat :1;	//超级电容通信
	uint8_t state :1;	//超级电容使用状态
	uint16_t time;			//时间
}__attribute__ ((__packed__));
//陀螺仪的状态
 struct topRoot_typedef			
{
	uint8_t state :1;		//陀螺仪状态
	uint8_t time;			//时间
	uint16_t statrTime;	//陀螺仪启动时间
}__attribute__ ((__packed__));
//电机的状态
 struct motorRoot_typedef			
{
	uint8_t pitch :1;		//pitch轴电机
	uint8_t yaw :1;			//yaw轴电机
	uint8_t frictionR:1;//右摩擦轮
	uint8_t frictionL:1;//左摩擦轮
	uint8_t feedAmmoH:1;//供弹上电机
	uint8_t feedAmmoD:1;//供弹下电机
	uint8_t CH1:1;		//底盘ID1电机
	uint8_t CH2:1;		//底盘ID2电机
	uint8_t CH3:1;		//底盘ID3电机
	uint8_t CH4:1;		//底盘ID4电机
	
	uint8_t pitchTime;
	uint8_t pawTime;
	uint8_t frictionRTime;//右摩擦轮
	uint8_t frictionLTime;//左摩擦轮
	uint8_t feedAmmoHTime;//供弹上电机
	uint8_t feedAmmoDTime;//供弹下电机
	uint8_t CH1Time;		//底盘ID1电机
	uint8_t CH2Time;		//底盘ID2电机
	uint8_t CH3Time;		//底盘ID3电机
	uint8_t CH4Time;		//底盘ID4电机
}__attribute__ ((__packed__));

 struct carAllRoot_typedef
{
		uint8_t chassisMod:4;	//底盘模式
		uint8_t gimbalMod:4;	//云台模式
		uint8_t attackMod:4;	//发射机构模式
		uint16_t resteTime;		//复活和启动时间	
}__attribute__ ((__packed__));
//总监视信息
 struct root_typedf
{	
	struct visionRoot_typedef visionRoot;		//视觉的状态
	struct remoteRoot_typedef remoteRoot;		//遥控的状态
	struct judgeRoot_typedef judgeRoot; 		//裁判系统的状态
	struct superCapRoot_typedef superCapRoot;	//超级电容状态
	struct motorRoot_typedef motorRoot;			//每个电机状态
	struct topRoot_typedef topRoot;		//陀螺仪的状态	
	struct Init_typedf Init_t;	//初始化的状态
	struct carAllRoot_typedef carAllRoot;		//整车状态
}__attribute__ ((__packed__));
extern struct root_typedf root_t;

//整体监视
void ErrorMonitor(void);
//主控初始化程序
uint8_t PositionInit(void);
//帧数函数
void DetectionFPS(uint16_t * FPS, uint32_t time);
void DetectionFPS_two(uint16_t * FPS, uint32_t time);
void DetectionFPS_three(uint16_t * FPS, uint32_t time);
//呼吸灯函数
void BreatheIED(uint16_t intervalTime, uint8_t color, uint64_t time);
#endif



