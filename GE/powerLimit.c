#include "powerLimit.h"
 #include "Read_Data.h"
#include "Write_Data.h"

/************************************************************万能分隔符**************************************************************
*	@author:			//
*	@performance:	//底盘功率限制函数//通过积分的形式对输出值进行限幅。
*	@parameter:		//最大功率，当前功率，设定输出
*	@time:				//
*	@ReadMe:			//反还值是限制过的输出值
************************************************************************************************************************************/
int32_t PowerLimIntegral(uint16_t maxPower , float nowPower , int32_t setOut)
{
	static double Raid = 1.0f;
	double raid_temp = 0.0f;
	double ki_1 = 0.0001f;
	double ki_2 = 0.00003f;
	float error = 0.0f;
	int32_t reData = 0;

	error = (float) maxPower - nowPower;
	if (error <= 0)
	{
		Raid += error*ki_1;
	}
	else
	{
		Raid += error*ki_2;
	}
	Raid = SectionLimit_f(1.0f , 0.1f , Raid);
	raid_temp = Raid;

	reData = (int32_t) (setOut * raid_temp);

	AllotPower(reData);

	return reData;
}
/************************************************************万能分隔符**************************************************************
*	@author:			//
*	@performance:	//底盘功率限制函数//通过缓冲功率进行限制
*	@parameter:		//剩余缓冲//设定输出
*	@time:				//
*	@ReadMe:			//返还值是限制过的输出值
								//必须接入裁判系统才能使用
								//可以设定剩余的缓冲功率
************************************************************************************************************************************/
int32_t PowerLimBuffer(float buffer , int32_t setOut)
{
	const float residueBuffer = 15.0f;		//要求的最低缓冲剩余
	static double Raid = 0.0f;
	double raid_temp = 0.0f;
	int32_t reData = 0;

	buffer -= residueBuffer;		//减去最少剩余后的缓冲

	buffer = SectionLimit_f(200 , 0 , buffer-residueBuffer);
	//计算比例系数
	Raid = (float) buffer/(60.0f - residueBuffer);
	Raid = SectionLimit_f(1.0f , 0.1f , Raid);
	//平方
	raid_temp = Raid * Raid;

	reData = (raid_temp * setOut);

	AllotPower(reData);

	return reData;
}
/************************************************************万能分隔符**************************************************************
*	@author:			//
*	@performance:	//将四个电机功率按照输出值按比分配
*	@parameter:		//被限制之后的输出值
*	@time:				//
*	@ReadMe:			//
************************************************************************************************************************************/
void AllotPower(int32_t setOut)
{
		//得到未限制之前的总输出
	float allOutPower = abs_float(m_CH3508_1_t.PID_S.all_out) + abs_float(m_CH3508_2_t.PID_S.all_out) + \
		abs_float(m_CH3508_3_t.PID_S.all_out) + abs_float(m_CH3508_4_t.PID_S.all_out);

	m_CH3508_1_t.PID_S.all_out = setOut * (float) (m_CH3508_1_t.PID_S.all_out/allOutPower);
	m_CH3508_2_t.PID_S.all_out = setOut * (float) (m_CH3508_2_t.PID_S.all_out/allOutPower);
	m_CH3508_3_t.PID_S.all_out = setOut * (float) (m_CH3508_3_t.PID_S.all_out/allOutPower);
	m_CH3508_4_t.PID_S.all_out = setOut * (float) (m_CH3508_4_t.PID_S.all_out/allOutPower);
}
/************************************************************万能分隔符**************************************************************
*	@author:			//
*	@performance:	//底盘功率限制函数//通过积分的形式对输出值进行限幅。
*	@parameter:		//最大功率，当前功率，设定输出
*	@time:				//
*	@ReadMe:			//反还值是限制过的输出值
************************************************************************************************************************************/

/************************************************************万能分隔符**************************************************************
*	@author:			//
*	@performance:	//斜坡函数
*	@parameter:		//真实值地址，目标值，期望间隔， 时间轴
*	@time:				//
*	@ReadMe:			//给底盘的设定值过滤//仅仅适用于键盘模式
************************************************************************************************************************************/
void SlopeKeyboard(int16_t* reality , int16_t aim , uint16_t intervalTime , uint64_t time)
{
	int16_t errAim = aim - *reality;		//相对差
	static int16_t lastAim = 0;		//目标值
	static int16_t lastTime = 0;		//上次时间
	float raid = 0.0f;

	if (lastAim == aim)
	{
		raid = (time - lastTime) / intervalTime;
		raid = SectionLimit_f(1.0f , 0.01f , raid);
		*reality += errAim * raid;
	}
	else
	{
		lastTime = time;		//跟新时间
		raid = 0.0f;
	}
}

/************************************************************万能分隔符**************************************************************
*	@author:			//
*	@performance:	//电容功率限制函数//通过缓冲功率进行限制
*	@parameter:		//剩余缓冲//设定输出
*	@time:				//
*	@ReadMe:			//返还值是限制过的输出值
                 **************必须接入裁判系统才能使用***********/
								/**************必须接入裁判系统才能使用***********/
//可以设定剩余的缓冲功率
/************************************************************************************************************************************/
float residueBuffer = 15.0f;		//要求的最低缓冲剩余
double Raid = 0.0f;
int32_t reData = 0;
int32_t PowerLimBuffer_Cap(uint16_t maxPower , float buffer , int32_t setOut)
{
	
	double raid_temp = 0.0f;
	

	capData_t.capGetDate.buffer += (maxPower - capData_t.capGetDate.nowPower - 6) * 0.0008f;
	capData_t.capGetDate.buffer = SectionLimit_f(60.0f , 0.01f , capData_t.capGetDate.buffer);

	buffer -= residueBuffer;		//减去最少剩余后的缓冲

	buffer = SectionLimit_f(200 , 0 , buffer-residueBuffer);
	//计算比例系数
	Raid = (float) buffer/(60.0f - residueBuffer);
	Raid = SectionLimit_f(1.0f , 0.1f , Raid);
	//平方
	raid_temp = Raid * Raid;

	reData = (raid_temp * setOut);

	AllotPower(reData);

	return reData;
}



