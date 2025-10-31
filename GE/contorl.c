#include "contorl.h"
#include "user_define.h"		//用于操作手自定义数据
/************************************************************万能分隔符**************************************************************
*	@author:			//
*	@performance:	//底盘控制函数
*	@parameter:		//模式控制对应一个拨杆的值
*	@time:				//
*	@ReadMe:			//底盘有关的全部都在这里面了，直接扔到定时器就可以
************************************************************************************************************************************/
uint8_t ControlCH(uint8_t mod)
{
//	if (root_t.Init_t.statrInit == df_error)
//	{
//		return df_error;			//车辆尚未启动完成
//	}

//	if (root_t.Init_t.chassisInit != df_re_ok)
//	{			//判断云台电机是否初始化
//		root_t.Init_t.chassisInit = CH3508M_Init();
//		return df_re_error;
//	}

	switch (mod)
	{
		/*************  自瞄模式11111*************/
	case CHMODAutomatic:
	{
		root_t.carAllRoot.chassisMod = CHMODAutomatic;
		CHEmptyJudge(mod);
		//2023-06-03 03:14 | 解决切换到自瞄时底盘转圈
		CHInfantry(root_t.topRoot.state);

	}break;
	/************* 制动模式 33333*************/
	case CHMODLock:
	{
		root_t.carAllRoot.chassisMod = CHMODLock;
		CHEmptyJudge(mod);
		CHSpeedLock(df_solwLock);

	}break;
	/************* 手动模式 2222*************/
	case CHMODRemote:
	{
		root_t.carAllRoot.chassisMod = CHMODRemote;
		CHEmptyJudge(mod);
		CHInfantry(root_t.topRoot.state);
	}break;
	/************* 错误处理 *************/
	default:
	{
		root_t.carAllRoot.chassisMod = CHMODNone;
		CHEmptyJudge(mod);
		CHSpeedLock(df_solwLock);
	}break;
	}
	//底盘发送
	my_CAN_Send(&hcan2 , 0x200 , m_CH3508_1_t.PID_S.all_out , m_CH3508_2_t.PID_S.all_out ,  m_CH3508_3_t.PID_S.all_out , m_CH3508_4_t.PID_S.all_out , 8);
												

	return df_re_ok;
}

