#include "contorl.h"
#include "user_define.h"		//���ڲ������Զ�������
/************************************************************���ָܷ���**************************************************************
*	@author:			//
*	@performance:	//���̿��ƺ���
*	@parameter:		//ģʽ���ƶ�Ӧһ�����˵�ֵ
*	@time:				//
*	@ReadMe:			//�����йص�ȫ�������������ˣ�ֱ���ӵ���ʱ���Ϳ���
************************************************************************************************************************************/
uint8_t ControlCH(uint8_t mod)
{
//	if (root_t.Init_t.statrInit == df_error)
//	{
//		return df_error;			//������δ�������
//	}

//	if (root_t.Init_t.chassisInit != df_re_ok)
//	{			//�ж���̨����Ƿ��ʼ��
//		root_t.Init_t.chassisInit = CH3508M_Init();
//		return df_re_error;
//	}

	switch (mod)
	{
		/*************  ����ģʽ11111*************/
	case CHMODAutomatic:
	{
		root_t.carAllRoot.chassisMod = CHMODAutomatic;
		CHEmptyJudge(mod);
		//2023-06-03 03:14 | ����л�������ʱ����תȦ
		CHInfantry(root_t.topRoot.state);

	}break;
	/************* �ƶ�ģʽ 33333*************/
	case CHMODLock:
	{
		root_t.carAllRoot.chassisMod = CHMODLock;
		CHEmptyJudge(mod);
		CHSpeedLock(df_solwLock);

	}break;
	/************* �ֶ�ģʽ 2222*************/
	case CHMODRemote:
	{
		root_t.carAllRoot.chassisMod = CHMODRemote;
		CHEmptyJudge(mod);
		CHInfantry(root_t.topRoot.state);
	}break;
	/************* ������ *************/
	default:
	{
		root_t.carAllRoot.chassisMod = CHMODNone;
		CHEmptyJudge(mod);
		CHSpeedLock(df_solwLock);
	}break;
	}
	//���̷���
	my_CAN_Send(&hcan2 , 0x200 , m_CH3508_1_t.PID_S.all_out , m_CH3508_2_t.PID_S.all_out ,  m_CH3508_3_t.PID_S.all_out , m_CH3508_4_t.PID_S.all_out , 8);
												

	return df_re_ok;
}

