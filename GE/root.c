#include "root.h"
#include "switch.h"

/*  ReadMe  ReadMe  ReadMe  ReadMe  ReadMe  ReadMe  ReadMe  ReadMe
	motor.c && motor.h
	������Ӣ�ۻ���ʱ��Ҫ���� motor.c  �����3510Ħ���ֵĶ��� motor.h�и���3510��ȫ������
	��Ӧ�����PID //2006 6020 ����Ħ����//
	PID���㺯����������������

	attack.h
	�ı�attack.h�еĺ궨���Ϊ��Ӧ����

	can.c && can.h
	����CANĦ���ֽ��յĽṹ��Ϊ3510

	chassis.c && chassis.h
	���ֽ���������־�

	gimbal.c && gimbal.h
	��Ӧ��pitch�������Լ���С��
	pitch��ң��ģʽ�¶�Ӧ������������

	tim.c
	�ı���̨���������Ӧ�ĺ���

	can.c
	�ı��ӦCAN���յĽṹ��

	����//ֻ�в����Ŵ�//��������//Ӣ�ۿ���
	����Ӧ�Ŀ����޸�
*/
struct root_typedf root_t ={ df_offLine };
extern uint64_t RunTime;//ʱ����

/************************************************************���ָܷ���**************************************************************
*	@author:			//����
*	@performance:	//���߼�����
*	@parameter:		//NO
*	@time:				//22-01-06
*	@ReadMe:			//���߼���ʱ��Ҫ�ڽ����ж�������ն�Ӧ��ʱ���ۻ�
************************************************************************************************************************************/
uint8_t dog = 0;
void ErrorMonitor(void)
{
		/********************����ϵͳ���***************/
	root_t.judgeRoot.time++;
	if (root_t.judgeRoot.time >= 143)
	{
		root_t.judgeRoot.time = 143;
		root_t.judgeRoot.communicat = df_offLine;

		BreatheIED(500 , df_Red , RunTime);	//��Ʊ���
	}
	else
	{
		root_t.judgeRoot.communicat = df_onLine;
	}

	/********************�������ݼ��***************/
	root_t.superCapRoot.time++;
	if (root_t.superCapRoot.time >= 1000)
	{
		root_t.superCapRoot.time = 401;
		root_t.superCapRoot.communicat = df_offLine;

		BreatheIED(500 , df_Red , RunTime);	//��Ʊ���
	}
	else
	{
		root_t.superCapRoot.communicat = df_onLine;
	}
	/********************�������ݼ��***************/
	/********************���������***************/
	root_t.carAllRoot.resteTime++;
	if (root_t.carAllRoot.resteTime >= df_resetTime)
	{
		root_t.carAllRoot.resteTime = df_resetTime;
		root_t.Init_t.statrInit = df_ok;
	}
}
/************************************************************���ָܷ���**************************************************************
*	@author:			//����
*	@performance:	//���س�ʼ������
*	@parameter:		//NO
*	@time:				//22-01-07
* @UpData:          //С�� 2022-05-30 17:36 �����˶�switch.h��֧��
*	@ReadMe:			//ȷ����ǰ��������ʲôλ��
************************************************************************************************************************************/
uint8_t PositionInit(void)
{
	root_t.Init_t.positionInit = df_chassisControl;
  return df_re_ok;
}
/************************************************************���ָܷ���**************************************************************
*	@author:			//����
*	@performance:	//֡�ʼ�⺯��
*	@parameter:		//Ҫ��ӡ��֡��//ʱ����
*	@time:				//22-01-07
*	@ReadMe:			//����ֵ�ǵ�ǰ֡��
								//ˢ��ʱ��1s
************************************************************************************************************************************/
void DetectionFPS(uint16_t* FPS , uint32_t time)
{
	static uint16_t number = 0;
	static uint32_t TIME[2] ={ 0 };
	//��¼���д���
	number++;
	TIME[df_now] = time;

	if (TIME[df_now] - TIME[df_last]>=1000)
	{
		TIME[df_last] = TIME[df_now];                                                                                                                     
		*FPS = number;
		number = 0;
	}
}

void DetectionFPS_two(uint16_t* FPS , uint32_t time)
{
	static uint16_t number = 0;
	static uint32_t TIME[2] ={ 0 };
	//��¼���д���
	number++;
	TIME[df_now] = time;

	if (TIME[df_now] - TIME[df_last]>=1000)
	{
		TIME[df_last] = TIME[df_now];
		*FPS = number;
		number = 0;
	}
}

void DetectionFPS_three(uint16_t* FPS , uint32_t time)
{
	static uint16_t number = 0;
	static uint32_t TIME[2] ={ 0 };
	//��¼���д���
	number++;
	TIME[df_now] = time;

	if (TIME[df_now] - TIME[df_last]>=1000)
	{
		TIME[df_last] = TIME[df_now];
		*FPS = number;
		number = 0;
	}
}
/************************************************************���ָܷ���**************************************************************
*	@author:			//����
*	@performance:	//������
*	@parameter:		//���ʱ��(ms)//��ɫ//ʱ��
*	@time:				//22-01-15
*	@ReadMe:			//�ṩһ��ֱ�۵ļ��
								//��˸ʱ�䲻�ܶ��ڶ�ʱ��ʱ��
								//����ж�����ã�һ�������ʱ������̵�Ϊ׼
************************************************************************************************************************************/
void BreatheIED(uint16_t intervalTime , uint8_t color , uint64_t time)
{
	static uint8_t RedBoll = 0 , BuleBoll = 0 , GreenBoll = 0;
	static uint64_t RedTIME[2] ={ 0 } , BuleTIME[2] ={ 0 } , GreenTIME[2] ={ 0 };

	RedTIME[df_now] 	= time;
	BuleTIME[df_now] 	= time;
	GreenTIME[df_now] = time;

	switch (color)
	{
	case df_Red:
	{		//��ɫ����
		if ((RedTIME[df_now] - RedTIME[df_last]) >= (intervalTime*0.5f))
		{
			RedBoll = !RedBoll;

			if (RedBoll == 0)
			{
				RedLED(GPIO_PIN_RESET);
			}
			else if (RedBoll == 1)
			{
				RedLED(GPIO_PIN_SET);
			}

			RedTIME[df_last] = RedTIME[df_now];
		}
	}break;
	case df_Bule:
	{		//��ɫ������
		if ((BuleTIME[df_now] - BuleTIME[df_last]) >= (intervalTime*0.5f))
		{
			BuleBoll = !BuleBoll;

			if (BuleBoll == 0)
			{
				BuleLED(GPIO_PIN_RESET);
			}
			else if (BuleBoll == 1)
			{
				BuleLED(GPIO_PIN_RESET);
			}

			BuleTIME[df_last] = BuleTIME[df_now];
		}
	}break;
	case df_Green:
	{		//��ɫ������
		if ((GreenTIME[df_now] - GreenTIME[df_last]) >= (intervalTime*0.5f))
		{
			GreenBoll = !GreenBoll;

			if (GreenBoll == 0)
			{
				GreenLED(GPIO_PIN_RESET);
			}
			else if (GreenBoll == 1)
			{
				GreenLED(GPIO_PIN_RESET);
			}

			GreenTIME[df_last] = GreenTIME[df_now];
		}
	}break;
	}

}



//�Ϳ������ַ���ƴ�ӷ���
//#define pt(x) _pt(x)
//#define m_hoer skljfalkjsd

//#define _pt(x) pinrtf("%s",#x)

//pt(m_hoer);





