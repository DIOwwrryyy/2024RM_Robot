#ifndef CHASSIS__H
#define CHASSIS__H

#include "shu_math.h"
#include "motor.h"
#include "math.h"
#include "tim.h"
//#include "judgeSystem.h"
#include "powerLimit.h"
 #include "Read_Data.h"
#include "Write_Data.h"

#define MotorMaxSpeed_3508 16000
//锁定模式宏定义
#ifndef LockAllMod
	#define LockAllMod
	#define df_solwLock 1
	#define df_quickLock 2
#endif
//速度宏定义 上限是2PI
#define df_Period 0.003f		//与周期长度成一次反比//横坐标是时间
#define df_MAXSpeed 2500			//设定三角函数的波峰大小


//底盘模式宏定义
#ifndef CHMOD
	#define CHMOD
	#define CHMODRemote 2			
	#define CHMODLock 3
	#define CHMODFollow 2
	#define CHMODAutomatic 1	
	#define CHMODNone	0
#endif

#ifndef df_open
	#define df_open 1
	#define df_off 0
#endif
//控制台
#ifndef RootCH
	#define	RootCH
	#define FollowGM df_on
	#define PowerLimit df_open
#endif

/******************************哨兵底盘使用******************************/
//与红外有关的定义
#ifndef df_Infrared
	#define df_Infrared
	#define RightDirction 1		//右方向
	#define LeftDirction -1		//左方向
	#define StopDirction  0		//停止
	#define TriggerMod 0			//红外触发状态
	#define SilentMod 1				//红外未触发状态
	#define ReadIfraredRight	GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11)		//右边红外对应的GPIO
	#define ReadIfraredLeft		GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12)		//左边红外对应的GPIO
#endif

/******************************************步兵底盘使用***********************************/
union gmTOch_typdef		//使用共用体整合数据
{
	struct
	{
		int16_t vx : 11;		//平移速度
		int16_t vy : 11;		//前进速度
		int16_t vr : 11;		//旋转速度
		uint16_t key_q : 1;
		uint16_t key_e : 1;
		uint16_t key_r : 1;
		uint16_t key_z : 1;
		uint16_t key_x : 1;
		uint16_t key_c : 1;
		uint16_t key_v : 1;
		uint16_t key_shift : 1;
		uint16_t key_ctrl : 1;
		uint16_t key_f : 1;
		uint16_t key_g : 1;
		uint16_t key_b : 1;
		uint16_t CHfollow : 1;	//底盘是否跟随
		uint16_t zhanwei : 2;		//占位//不能改成：0
		uint16_t supUSe : 1;			//是否使用电容
		uint16_t romoteOnLine : 1;			//遥控是否在线
		uint16_t chMod : 2;		//底盘状态
		uint16_t topSate : 1;		//陀螺仪状态
		int16_t ptichAgnle : 11;	//陀螺仪发送的pitch轴角度
	}dataNeaten;
	//CAN发送的数据
	int16_t sendData[4];
	uint8_t getData[8];
};
union chTOgm_typdef		//使用共用体整合数据
{
	struct
	{
		int16_t pitch;
		int16_t yaw;
		float time;
	}dataNeaten_angle;
	struct
	{
		uint64_t muzzleColing : 16;	//枪口热量
		uint64_t maxSpeed : 8;	//最大射速
		uint64_t nowSpeed : 8;	//当前射速
		uint64_t target : 1;	//是否识别成功标志位
		uint64_t visionMod : 3;		//视觉的状态
		uint64_t visionState : 1;		//视觉在线的状态
		uint64_t judgeState : 1;		//裁判系统的状态
		uint64_t : 0;		//保留
	}dataNeaten_another;
	//CAN发送的数据
	uint16_t sendData[4];
	uint8_t getData[8];
};
struct CanCommunit_typedef
{
	union chTOgm_typdef chTOgm;
	union gmTOch_typdef gmTOch;
};
extern struct CanCommunit_typedef CanCommunit_t;

struct superCap_typedef
{
	uint8_t superCapState:1;	//电容是否被使用的标志
	float superCapRaid;				//超级电容下的速度系数
	float normalRaid;					//正常模式下的系数
	float slowRaid;				//缓慢模式下的系数
	float slowKeyRaid;		//键盘的系数
};
struct speed_typedef
{
	int16_t vx_int16;				//形式待修改
	int16_t vy_int16;
	int16_t vr_int16;
	int16_t v1_i16;		//每个轮子的速度（和电机ID保持一致）
	int16_t v2_i16;
	int16_t v3_i16;
	int16_t v4_i16;	
	float reality_vr;		//真实的旋转速度
};
 struct CanResevie_typedef
{
		int16_t vx ;		//三个速度
		int16_t vy ;
		int16_t vr ;
		uint8_t superStata :2;		//超级电容
		uint8_t visionState:3;		//视觉
		uint8_t remoteStata:1;		//遥控状态
		uint8_t moveState:2;			//底盘模式
		int16_t angle;	//底盘云台相差角
}__attribute__ ((__packed__)) ;
//底盘跟随PID结构体
struct CHFollowPID_typedef
{
	float Kp;
	float Ki;
	float Kd;
	int32_t ILt;
	int32_t AlLt;
	float Error[2];
	float P_out;
	float I_out;
	int32_t D_out;
	float All_out;
};
//底盘结构体
struct chassis_typedef		
{
	struct speed_typedef speed;
	struct superCap_typedef superCap;
	uint8_t mods[2];
	float AllowOutPower;
	struct CanResevie_typedef CanResevie;
	struct CHFollowPID_typedef CHF_PID_S;
	struct CHFollowPID_typedef CHF_PID_P;
};
extern struct chassis_typedef chassis_t;

//麦克纳姆轮初始化结构体
struct mecanumInit_typdef 
{
  float wheel_perimeter; /* 轮的周长（mm）*/
  float wheeltrack;      /* 轮距（mm）*/
  float wheelbase;       /*轴距（mm）*/
  float rotate_x_offset; /* 相对于底盘中心的x轴旋转偏移量(mm) */
  float rotate_y_offset; /* 相对于底盘中心的y轴旋转偏移量(mm) */
  float deceleration_ratio; /*电机减速比*/
  int max_vx_speed;         /*底盘的x轴的最大速度(mm/s)*/
  int max_vy_speed;         /*底盘的y轴的最大速度(mm/s)*/
  int max_vw_speed;         /*底盘的自转的最大速度(degree/s)*/
  int max_wheel_ramp;       /*3508最大转速*/
	//每一个轮子的旋转比率//与旋转中心点相关
	float raid_fr;		//右前
	float raid_fl;		//左前
	float raid_bl;		//左后
	float raid_br;		//右后
	float wheel_rpm_ratio;	//用来将速度转化成转每分钟
};
//extern struct mecanumInit_typdef mecanumInit_t;
/******************************************步兵底盘使用***********************************/

/********************************************函数部分*************************************/

//底盘锁定函数
void CHSpeedLock(uint8_t mod);

//新麦轮解算的初始化函数
uint8_t MecanumInit(void);
//新麦轮解算
void MecanumResolve(int16_t vx, int16_t vy, int16_t vr, float angle);
//步兵底盘初始化函数
uint8_t CHInfantryInit(void);
//步兵底盘执行函数
void CHInfantry(uint8_t topStata);
//步兵底盘电机清空判断
void CHEmptyJudge(uint8_t mod);
//发送给云台的解算函数
uint8_t ChassisTXResolve(uint8_t boll);
//解算从云台发送来的数据
uint8_t ChassisRXResolve(uint8_t * data);
//上坡用的功率分配函数
void UpHill(float topAngle);
//地盘跟随PID初始化函数
uint8_t CHFollowPID_Init(void);
//地盘跟随PID
void CHFollowTwoPID(struct chassis_typedef * CHFollow);
//功率分配函数
void PowerAllot(int32_t maxPower);
#endif


