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
//����ģʽ�궨��
#ifndef LockAllMod
	#define LockAllMod
	#define df_solwLock 1
	#define df_quickLock 2
#endif
//�ٶȺ궨�� ������2PI
#define df_Period 0.003f		//�����ڳ��ȳ�һ�η���//��������ʱ��
#define df_MAXSpeed 2500			//�趨���Ǻ����Ĳ����С


//����ģʽ�궨��
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
//����̨
#ifndef RootCH
	#define	RootCH
	#define FollowGM df_on
	#define PowerLimit df_open
#endif

/******************************�ڱ�����ʹ��******************************/
//������йصĶ���
#ifndef df_Infrared
	#define df_Infrared
	#define RightDirction 1		//�ҷ���
	#define LeftDirction -1		//����
	#define StopDirction  0		//ֹͣ
	#define TriggerMod 0			//���ⴥ��״̬
	#define SilentMod 1				//����δ����״̬
	#define ReadIfraredRight	GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11)		//�ұߺ����Ӧ��GPIO
	#define ReadIfraredLeft		GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12)		//��ߺ����Ӧ��GPIO
#endif

/******************************************��������ʹ��***********************************/
union gmTOch_typdef		//ʹ�ù�������������
{
	struct
	{
		int16_t vx : 11;		//ƽ���ٶ�
		int16_t vy : 11;		//ǰ���ٶ�
		int16_t vr : 11;		//��ת�ٶ�
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
		uint16_t CHfollow : 1;	//�����Ƿ����
		uint16_t zhanwei : 2;		//ռλ//���ܸĳɣ�0
		uint16_t supUSe : 1;			//�Ƿ�ʹ�õ���
		uint16_t romoteOnLine : 1;			//ң���Ƿ�����
		uint16_t chMod : 2;		//����״̬
		uint16_t topSate : 1;		//������״̬
		int16_t ptichAgnle : 11;	//�����Ƿ��͵�pitch��Ƕ�
	}dataNeaten;
	//CAN���͵�����
	int16_t sendData[4];
	uint8_t getData[8];
};
union chTOgm_typdef		//ʹ�ù�������������
{
	struct
	{
		int16_t pitch;
		int16_t yaw;
		float time;
	}dataNeaten_angle;
	struct
	{
		uint64_t muzzleColing : 16;	//ǹ������
		uint64_t maxSpeed : 8;	//�������
		uint64_t nowSpeed : 8;	//��ǰ����
		uint64_t target : 1;	//�Ƿ�ʶ��ɹ���־λ
		uint64_t visionMod : 3;		//�Ӿ���״̬
		uint64_t visionState : 1;		//�Ӿ����ߵ�״̬
		uint64_t judgeState : 1;		//����ϵͳ��״̬
		uint64_t : 0;		//����
	}dataNeaten_another;
	//CAN���͵�����
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
	uint8_t superCapState:1;	//�����Ƿ�ʹ�õı�־
	float superCapRaid;				//���������µ��ٶ�ϵ��
	float normalRaid;					//����ģʽ�µ�ϵ��
	float slowRaid;				//����ģʽ�µ�ϵ��
	float slowKeyRaid;		//���̵�ϵ��
};
struct speed_typedef
{
	int16_t vx_int16;				//��ʽ���޸�
	int16_t vy_int16;
	int16_t vr_int16;
	int16_t v1_i16;		//ÿ�����ӵ��ٶȣ��͵��ID����һ�£�
	int16_t v2_i16;
	int16_t v3_i16;
	int16_t v4_i16;	
	float reality_vr;		//��ʵ����ת�ٶ�
};
 struct CanResevie_typedef
{
		int16_t vx ;		//�����ٶ�
		int16_t vy ;
		int16_t vr ;
		uint8_t superStata :2;		//��������
		uint8_t visionState:3;		//�Ӿ�
		uint8_t remoteStata:1;		//ң��״̬
		uint8_t moveState:2;			//����ģʽ
		int16_t angle;	//������̨����
}__attribute__ ((__packed__)) ;
//���̸���PID�ṹ��
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
//���̽ṹ��
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

//�����ķ�ֳ�ʼ���ṹ��
struct mecanumInit_typdef 
{
  float wheel_perimeter; /* �ֵ��ܳ���mm��*/
  float wheeltrack;      /* �־ࣨmm��*/
  float wheelbase;       /*��ࣨmm��*/
  float rotate_x_offset; /* ����ڵ������ĵ�x����תƫ����(mm) */
  float rotate_y_offset; /* ����ڵ������ĵ�y����תƫ����(mm) */
  float deceleration_ratio; /*������ٱ�*/
  int max_vx_speed;         /*���̵�x�������ٶ�(mm/s)*/
  int max_vy_speed;         /*���̵�y�������ٶ�(mm/s)*/
  int max_vw_speed;         /*���̵���ת������ٶ�(degree/s)*/
  int max_wheel_ramp;       /*3508���ת��*/
	//ÿһ�����ӵ���ת����//����ת���ĵ����
	float raid_fr;		//��ǰ
	float raid_fl;		//��ǰ
	float raid_bl;		//���
	float raid_br;		//�Һ�
	float wheel_rpm_ratio;	//�������ٶ�ת����תÿ����
};
//extern struct mecanumInit_typdef mecanumInit_t;
/******************************************��������ʹ��***********************************/

/********************************************��������*************************************/

//������������
void CHSpeedLock(uint8_t mod);

//�����ֽ���ĳ�ʼ������
uint8_t MecanumInit(void);
//�����ֽ���
void MecanumResolve(int16_t vx, int16_t vy, int16_t vr, float angle);
//�������̳�ʼ������
uint8_t CHInfantryInit(void);
//��������ִ�к���
void CHInfantry(uint8_t topStata);
//�������̵������ж�
void CHEmptyJudge(uint8_t mod);
//���͸���̨�Ľ��㺯��
uint8_t ChassisTXResolve(uint8_t boll);
//�������̨������������
uint8_t ChassisRXResolve(uint8_t * data);
//�����õĹ��ʷ��亯��
void UpHill(float topAngle);
//���̸���PID��ʼ������
uint8_t CHFollowPID_Init(void);
//���̸���PID
void CHFollowTwoPID(struct chassis_typedef * CHFollow);
//���ʷ��亯��
void PowerAllot(int32_t maxPower);
#endif


