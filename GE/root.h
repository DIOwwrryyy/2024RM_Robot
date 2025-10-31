#ifndef ROOT__H
#define ROOT__H

#include "stdint.h"
#include "string.h"
#include "gpio.h"
#include "motor.h"

//�����õĽӿں�
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
	#define ReadCHPin	GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15)		//���̶�Ӧ��GPIO
	#define ReadGMPin GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4)		//��̨��Ӧ��GPIO	
	
	#define RedLED(level) 		 HAL_GPIO_WritePin(GPIOE,GPIO_PIN_0,level)//��ɫ������		//��ɫ��������˸˵����������
	#define df_Red 1
	#define GreenLED(level) HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,level)		//��ɫ������		//
	#define df_Green 2
	#define BuleLED(level) HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,level)		//��ɫ������
	#define df_Bule 3
#endif

//��ʼ������
 struct Init_typedf
{
		uint8_t mecanumInit :1;		//�����ֽ����ʼ��
		uint8_t gimbalInit :1;		//������̨��ʼ��
		uint8_t chassisInit :1;		//���̵����ʼ��
		uint8_t attackInit	:1;		//���������ʼ��(����Ħ����//һ���������)
		uint8_t statrInit :1;		//������ʼ��
		uint8_t resurgenceInit :1;				//�����ʼ��
		uint8_t positionInit :2;	//���ص�λ��//01�ǵ���10����̨��������������Ч
}__attribute__ ((__packed__));
//�Ӿ�������Ϣ
 struct visionRoot_typedef			
{
	uint8_t vision_all :1;		
	uint8_t communicat :1;	//�Ӿ�ͨ��
	uint8_t dataRight :1;			//������ȷ��
	uint8_t time;			//ʱ��
}__attribute__ ((__packed__));
//ң�ؼ�����Ϣ
 struct remoteRoot_typedef			
{
	uint8_t communicat :1;	//ң��ͨ��
	uint8_t acceptor :1;	//���ջ�״̬
	uint8_t time;			//ʱ��
}__attribute__ ((__packed__));
//����ϵͳ����Ϣ
 struct judgeRoot_typedef			
{
	uint8_t communicat :1;	//����ϵͳͨ��
	uint8_t dataRight :1;	//����ϵͳ������ȷ���ж�
	uint8_t time;			//ʱ��
}__attribute__ ((__packed__));
//�������ݵ�״̬
 struct superCapRoot_typedef			
{
	uint8_t communicat :1;	//��������ͨ��
	uint8_t state :1;	//��������ʹ��״̬
	uint16_t time;			//ʱ��
}__attribute__ ((__packed__));
//�����ǵ�״̬
 struct topRoot_typedef			
{
	uint8_t state :1;		//������״̬
	uint8_t time;			//ʱ��
	uint16_t statrTime;	//����������ʱ��
}__attribute__ ((__packed__));
//�����״̬
 struct motorRoot_typedef			
{
	uint8_t pitch :1;		//pitch����
	uint8_t yaw :1;			//yaw����
	uint8_t frictionR:1;//��Ħ����
	uint8_t frictionL:1;//��Ħ����
	uint8_t feedAmmoH:1;//�����ϵ��
	uint8_t feedAmmoD:1;//�����µ��
	uint8_t CH1:1;		//����ID1���
	uint8_t CH2:1;		//����ID2���
	uint8_t CH3:1;		//����ID3���
	uint8_t CH4:1;		//����ID4���
	
	uint8_t pitchTime;
	uint8_t pawTime;
	uint8_t frictionRTime;//��Ħ����
	uint8_t frictionLTime;//��Ħ����
	uint8_t feedAmmoHTime;//�����ϵ��
	uint8_t feedAmmoDTime;//�����µ��
	uint8_t CH1Time;		//����ID1���
	uint8_t CH2Time;		//����ID2���
	uint8_t CH3Time;		//����ID3���
	uint8_t CH4Time;		//����ID4���
}__attribute__ ((__packed__));

 struct carAllRoot_typedef
{
		uint8_t chassisMod:4;	//����ģʽ
		uint8_t gimbalMod:4;	//��̨ģʽ
		uint8_t attackMod:4;	//�������ģʽ
		uint16_t resteTime;		//���������ʱ��	
}__attribute__ ((__packed__));
//�ܼ�����Ϣ
 struct root_typedf
{	
	struct visionRoot_typedef visionRoot;		//�Ӿ���״̬
	struct remoteRoot_typedef remoteRoot;		//ң�ص�״̬
	struct judgeRoot_typedef judgeRoot; 		//����ϵͳ��״̬
	struct superCapRoot_typedef superCapRoot;	//��������״̬
	struct motorRoot_typedef motorRoot;			//ÿ�����״̬
	struct topRoot_typedef topRoot;		//�����ǵ�״̬	
	struct Init_typedf Init_t;	//��ʼ����״̬
	struct carAllRoot_typedef carAllRoot;		//����״̬
}__attribute__ ((__packed__));
extern struct root_typedf root_t;

//�������
void ErrorMonitor(void);
//���س�ʼ������
uint8_t PositionInit(void);
//֡������
void DetectionFPS(uint16_t * FPS, uint32_t time);
void DetectionFPS_two(uint16_t * FPS, uint32_t time);
void DetectionFPS_three(uint16_t * FPS, uint32_t time);
//�����ƺ���
void BreatheIED(uint16_t intervalTime, uint8_t color, uint64_t time);
#endif



