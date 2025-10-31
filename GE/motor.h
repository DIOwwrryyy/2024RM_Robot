#ifndef MOTOR__H
#define MOTOR__H

#include "stdint.h"
#include "shu_math.h"
#include "switch.h"

/***********************五号步兵**********************/
#ifdef Infantry_Number_Five
#define YawInitialAngle 4700 //打符步兵
#define PitchInitialAngle 8850	//打符步兵
#endif
/***********************五号步兵**********************/


/***********************四号步兵**********************/
#ifdef Infantry_Number_Four
#define YawInitialAngle 6154 //联盟赛步兵
#define PitchInitialAngle 900	//联盟赛步兵没有装甲板
//************************************yaw轴数据************************************//
														//kp		//ki			//kd			//iLimit		//alLimit
#define df_yaw_angle {	9.0f,	0.0f,			0,				1000,					5000}
#define df_yaw_speed {	17,			0.1f,		0.0f,			0,			28000}


#define df_pitch_angle {	9.0f,		0.01f,			0,			  0,				4000}
#define df_pitch_speed {	6,			0.04f,		0.0f,			5000,		 	28000}
#endif
/***********************四号步兵**********************/


/***********************三号步兵**********************/
#ifdef Infantry_Number_Three
#define YawInitialAngle 3340	//自瞄步兵
#define PitchInitialAngle 247	//自瞄步兵
//************************************yaw轴数据************************************//
														//kp		//ki			//kd			//iLimit		//alLimit
#define  df_yaw_angle {	13.0f,	0.3f,			10.66,				1000,					8000}
#define  df_yaw_speed {	17,			0.62f,		18.0f,			20000,			28000}
        
        
#define  df_pitch_angle {	6.1f,		0.0f,			0,			  0,				4000}
#define  df_pitch_speed {	14,			0.43f,		0.0f,			5000,		 	28000}
#endif
/***********************三号步兵**********************/


#ifndef df_re_error
#define df_re_ok 1
#define df_re_error 0
#endif

#ifndef df_PID 
#define df_PID
#define one_PID 1
#define two_PID 2
#endif

#ifndef df_top
#define df_top 
#define df_off 0
#define df_open 1
#endif

#ifndef df_now
#define df_now 0
#define df_last 1
#define df_llast 2
#endif

#ifndef df_InitBoll
#define df_finish 1
#define df_unfish 0
#endif

//电机数据的结构体
#define I_length 20		//电流使用均值滤波，这里是滤波的长度
struct data_typedef
{ int16_t temp[2];
	int16_t angle[2];
	int16_t speed[2];
	int16_t I[I_length];		//读取转矩电流
	int16_t IDataAll;				//电流总值
	uint8_t head : 7;				//头指针
	uint8_t OpneIBool : 1;		//是否已经完成接收
	int16_t averageI;				//均值后的数据
	int16_t round;
	float aim;
	int32_t reality;
	int16_t initialAngle;
	float ralativeAngle;
};
//PID 结构体								
//#define CHM3508PID_P_Init {	1.2f,			0,			0,			0,			6400,{0},0,0,0,0}
struct PIDParameter_typedef
{
	float kp;
	float ki;
	float kd;
	int32_t iLt;
	int32_t alLt;
};
struct PID_typedef
{
	//初始化需要将该项化零
	float kp;
	float ki;
	float kd;
	int32_t iLt;
	int32_t alLt;
	float error[2];
	float p_out;
	float i_out;
	int32_t d_out;
	float all_out;
};


/***************3508电机结构体***************/
struct m_3508_typedef
{
	struct data_typedef data;
	struct PID_typedef PID_P;
	struct PID_typedef PID_S;
//	struct PID_typedef PID_temp;
};
extern struct m_3508_typedef m_CH3508_1_t;
extern struct m_3508_typedef m_CH3508_2_t;
extern struct m_3508_typedef m_CH3508_3_t;
extern struct m_3508_typedef m_CH3508_4_t;

extern struct m_3508_typedef m_AM2006_h_t;
extern struct m_3508_typedef m_AM3510_d_t;
extern struct m_3508_typedef m_AM3508_r_t;
extern struct m_3508_typedef m_AM3508_l_t;

/***************6020电机结构体***************/
struct m_6020_typedef
{
	uint8_t mod[2];
	uint8_t topStata[2];
	struct data_typedef data;
	struct PID_typedef PID_P;
	struct PID_typedef PID_S;
};
extern struct m_6020_typedef m_GM6020_y_t;
extern struct m_6020_typedef m_GM6020_p_t;


/*******************************3508电机有关函数*******************************/
//3508电机初始化函数
uint8_t CH3508M_Init(void);
//3508CAN数据解算函数
void CanManage_3508(uint8_t* can_data , struct data_typedef* data);
//3508清空函数
void MotorReast3508(struct m_3508_typedef* motor);
//2006CAN解算函数
void CanManage_2006(uint8_t* can_data , struct data_typedef* data);
//3508底盘双环PID解算函数
void CHMotorTwoPID(struct m_3508_typedef* motor);
//2006拨弹电机单环PID解算函数
void AMMotorSpeedPID(struct m_3508_typedef* motor);
//3508底盘单环PID解算函数
void CHMotorSpeedPID(struct m_3508_typedef* motor);
/*******************************6020电机有关函数*******************************/
//6020电机初始化函数
uint8_t GM6020M_Init(void);
void RUI_GM6020P_INIT(void);
uint8_t RUI_GM6020Y_INIT(void);
uint8_t RUI_GM6020Y_NOTOP_INTI(void);
//6020CAN数据解算函数
void CanManage_6020(uint8_t* can_data , struct data_typedef* data);
//6020pitch轴解算
uint8_t GMPitchPID(struct m_6020_typedef* motor , int8_t Stata , float TopPitchSpeed , float topAngle);
//6020yaw轴解算
uint8_t GMYawPID(struct m_6020_typedef* motor , int8_t Stata , float TopPitchSpeed , float topAngle);
/*******************************发射机构电机有关函数*******************************/
//发射机构初始化
uint8_t AttackInit(void);
//摩擦轮PID速度单环
void FirctionSpeedPID(struct m_3508_typedef* motor);
#endif


















