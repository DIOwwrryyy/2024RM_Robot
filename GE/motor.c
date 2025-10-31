#include "motor.h"
//底盘电机
struct m_3508_typedef m_CH3508_1_t ={ 0 };
struct m_3508_typedef m_CH3508_2_t ={ 0 };
struct m_3508_typedef m_CH3508_3_t ={ 0 };
struct m_3508_typedef m_CH3508_4_t ={ 0 };
//发射机构电机
struct m_3508_typedef m_AM2006_h_t ={ 0 };
struct m_3508_typedef m_AM3510_d_t ={ 0 };
struct m_3508_typedef m_AM3508_r_t ={ 0 };			//步兵是3510，为了统一与方便命名为3508
struct m_3508_typedef m_AM3508_l_t ={ 0 };
//两个云台电机
struct m_6020_typedef m_GM6020_y_t ={ 0 };
struct m_6020_typedef m_GM6020_p_t ={ 0 };

//float NowPower = 0.0f;
//float raid = 2.8f;

/************************************************************万能分隔符**************************************************************
*	@author:			//赵澍
*	@performance:	//电机初始化函数
*	@parameter:		//将所有底盘电机
*	@time:				//21-12-1
* @LastUpDataTime:  //2022-05-25 21:07    by 小瑞
* @UpData： // 对每个电机PID进行调节
*	@ReadMe:			//改变的是PID参数
************************************************************************************************************************************/
uint8_t CH3508M_Init(void)
{
								//kp			//ki		//kd		//iLimit	//alLimit
	float PID_P_1[5] ={ 2.5,				0,			0,			0,				   1000 };
	float PID_S_1[5] ={ 15,				0.1f,			0,			3000,				300000 };

	float PID_P_2[5] ={ 2.5,				0,			0,			0,				   1000 };
	float PID_S_2[5] ={ 15,				0.1f,			0,			3000,				300000 };

	float PID_P_3[5] ={ 2.5,				0,			0,			0,				   1000 };
	float PID_S_3[5] ={ 15,				0.1f,			0,			3000,				300000 };

	float PID_P_4[5] ={ 2.5,				0,			0,			0,				   1000 };
	float PID_S_4[5] ={ 15,				0.1f,			0,			3000,				300000 };

	uint8_t i = 0;
	/***********************3508_1**********************/
	i = 0;
	m_CH3508_1_t.PID_P.kp = PID_P_1[i++];
	m_CH3508_1_t.PID_P.ki = PID_P_1[i++];
	m_CH3508_1_t.PID_P.kd = PID_P_1[i++];
	m_CH3508_1_t.PID_P.iLt = PID_P_1[i++];
	m_CH3508_1_t.PID_P.alLt = PID_P_1[i++];
	i = 0;
	m_CH3508_1_t.PID_S.kp = PID_S_1[i++];
	m_CH3508_1_t.PID_S.ki = PID_S_1[i++];
	m_CH3508_1_t.PID_S.kd = PID_S_1[i++];
	m_CH3508_1_t.PID_S.iLt = PID_S_1[i++];
	m_CH3508_1_t.PID_S.alLt = PID_S_1[i++];

	/***********************3508_2**********************/
	i = 0;
	m_CH3508_2_t.PID_P.kp = PID_P_2[i++];
	m_CH3508_2_t.PID_P.ki = PID_P_2[i++];
	m_CH3508_2_t.PID_P.kd = PID_P_2[i++];
	m_CH3508_2_t.PID_P.iLt = PID_P_2[i++];
	m_CH3508_2_t.PID_P.alLt = PID_P_2[i++];
	i = 0;
	m_CH3508_2_t.PID_S.kp = PID_S_2[i++];
	m_CH3508_2_t.PID_S.ki = PID_S_2[i++];
	m_CH3508_2_t.PID_S.kd = PID_S_2[i++];
	m_CH3508_2_t.PID_S.iLt = PID_S_2[i++];
	m_CH3508_2_t.PID_S.alLt = PID_S_2[i++];

	/***********************3508_3**********************/
	i = 0;
	m_CH3508_3_t.PID_P.kp = PID_P_3[i++];
	m_CH3508_3_t.PID_P.ki = PID_P_3[i++];
	m_CH3508_3_t.PID_P.kd = PID_P_3[i++];
	m_CH3508_3_t.PID_P.iLt = PID_P_3[i++];
	m_CH3508_3_t.PID_P.alLt = PID_P_3[i++];
	i = 0;
	m_CH3508_3_t.PID_S.kp = PID_S_3[i++];
	m_CH3508_3_t.PID_S.ki = PID_S_3[i++];
	m_CH3508_3_t.PID_S.kd = PID_S_3[i++];
	m_CH3508_3_t.PID_S.iLt = PID_S_3[i++];
	m_CH3508_3_t.PID_S.alLt = PID_S_3[i++];

	/***********************3508_4**********************/
	i = 0;
	m_CH3508_4_t.PID_P.kp = PID_P_4[i++];
	m_CH3508_4_t.PID_P.ki = PID_P_4[i++];
	m_CH3508_4_t.PID_P.kd = PID_P_4[i++];
	m_CH3508_4_t.PID_P.iLt = PID_P_4[i++];
	m_CH3508_4_t.PID_P.alLt = PID_P_4[i++];
	i = 0;
	m_CH3508_4_t.PID_S.kp = PID_S_4[i++];
	m_CH3508_4_t.PID_S.ki = PID_S_4[i++];
	m_CH3508_4_t.PID_S.kd = PID_S_4[i++];
	m_CH3508_4_t.PID_S.iLt = PID_S_4[i++];
	m_CH3508_4_t.PID_S.alLt = PID_S_4[i++];

	return df_re_ok;
}
/************************************************************万能分隔符**************************************************************
*	@author:			//赵澍
*	@performance:	//电机初始化函数(6020电机使用)
*	@parameter:		//将所有电机进行初始化
*	@time:				//21-12-14
*	@ReadMe:			//改变的是PID参数//以及yaw和pitch轴的零点问题//包含圈数矫正
************************************************************************************************************************************/
uint8_t GM6020M_Init(void)
{
	float P_PID_P[5] = df_pitch_angle;
	float P_PID_S[5] = df_pitch_speed;

	uint8_t i = 0;

	i = 0;
	m_GM6020_p_t.PID_P.kp = P_PID_P[i++];
	m_GM6020_p_t.PID_P.ki = P_PID_P[i++];
	m_GM6020_p_t.PID_P.kd = P_PID_P[i++];
	m_GM6020_p_t.PID_P.iLt = P_PID_P[i++];
	m_GM6020_p_t.PID_P.alLt = P_PID_P[i++];
	i = 0;
	m_GM6020_p_t.PID_S.kp = P_PID_S[i++];
	m_GM6020_p_t.PID_S.ki = P_PID_S[i++];
	m_GM6020_p_t.PID_S.kd = P_PID_S[i++];
	m_GM6020_p_t.PID_S.iLt = P_PID_S[i++];
	m_GM6020_p_t.PID_S.alLt = P_PID_S[i++];

	m_GM6020_p_t.data.initialAngle = PitchInitialAngle;		//初始角度
//不是很懂为什么
//	if (m_GM6020_p_t.data.angle[df_now] <= 4096)
//	{
//		m_GM6020_p_t.data.round=1;
//	}
	m_GM6020_p_t.data.aim = m_GM6020_p_t.data.initialAngle;

	float Y_PID_P[5] = df_yaw_angle;
	float Y_PID_S[5] = df_yaw_speed;
	i = 0;
	m_GM6020_y_t.PID_P.kp = Y_PID_P[i++];
	m_GM6020_y_t.PID_P.ki = Y_PID_P[i++];
	m_GM6020_y_t.PID_P.kd = Y_PID_P[i++];
	m_GM6020_y_t.PID_P.iLt = Y_PID_P[i++];
	m_GM6020_y_t.PID_P.alLt = Y_PID_P[i++];
	i = 0;
	m_GM6020_y_t.PID_S.kp = Y_PID_S[i++];
	m_GM6020_y_t.PID_S.ki = Y_PID_S[i++];
	m_GM6020_y_t.PID_S.kd = Y_PID_S[i++];
	m_GM6020_y_t.PID_S.iLt = Y_PID_S[i++];
	m_GM6020_y_t.PID_S.alLt = Y_PID_S[i++];

	m_GM6020_y_t.data.initialAngle = YawInitialAngle; 		//初始角度
	m_GM6020_y_t.data.aim = m_GM6020_y_t.data.initialAngle;

	return df_re_ok;
}
void RUI_GM6020P_INIT(void)
{
	float P_PID_P[5] = df_pitch_angle;
	float P_PID_S[5] = df_pitch_speed;

	uint8_t i = 0;

	i = 0;
	m_GM6020_p_t.PID_P.kp = P_PID_P[i++];
	m_GM6020_p_t.PID_P.ki = P_PID_P[i++];
	m_GM6020_p_t.PID_P.kd = P_PID_P[i++];
	m_GM6020_p_t.PID_P.iLt = P_PID_P[i++];
	m_GM6020_p_t.PID_P.alLt = P_PID_P[i++];
	i = 0;
	m_GM6020_p_t.PID_S.kp = P_PID_S[i++];
	m_GM6020_p_t.PID_S.ki = P_PID_S[i++];
	m_GM6020_p_t.PID_S.kd = P_PID_S[i++];
	m_GM6020_p_t.PID_S.iLt = P_PID_S[i++];
	//m_GM6020_p_t.PID_S.alLt = P_PID_S[i++];
}
uint8_t RUI_GM6020Y_INIT(void)
{
	float Y_PID_P[5] = df_yaw_angle;
	float Y_PID_S[5] = df_yaw_speed;
	uint8_t i = 0;
	m_GM6020_y_t.PID_P.kp = Y_PID_P[i++];
	m_GM6020_y_t.PID_P.ki = Y_PID_P[i++];
	m_GM6020_y_t.PID_P.kd = Y_PID_P[i++];
	m_GM6020_y_t.PID_P.iLt = Y_PID_P[i++];
	//m_GM6020_y_t.PID_P.alLt = Y_PID_P[i++];
	i = 0;
	m_GM6020_y_t.PID_S.kp = Y_PID_S[i++];
	m_GM6020_y_t.PID_S.ki = Y_PID_S[i++];
	m_GM6020_y_t.PID_S.kd = Y_PID_S[i++];
	m_GM6020_y_t.PID_S.iLt = Y_PID_S[i++];
	//m_GM6020_y_t.PID_S.alLt = Y_PID_S[i++];
	m_GM6020_y_t.data.initialAngle = YawInitialAngle; 		//初始角度
	m_GM6020_y_t.data.aim = m_GM6020_y_t.data.initialAngle;

	return 1;
}
uint8_t RUI_GM6020Y_NOTOP_INTI(void)
{
	float Y_PID_P[5] ={ 0.3 , 0 , 3 , 1, 100 };
	float Y_PID_S[5] ={ 330 , 1.9 , 30 ,1000, 28000 };
	m_GM6020_y_t.PID_P.kp = Y_PID_P[0];
	m_GM6020_y_t.PID_P.ki = Y_PID_P[1];
	m_GM6020_y_t.PID_P.kd = Y_PID_P[2];
	m_GM6020_y_t.PID_P.iLt = Y_PID_P[3];
	m_GM6020_y_t.PID_P.alLt = Y_PID_P[4];

	m_GM6020_y_t.PID_S.kp = Y_PID_S[0];
	m_GM6020_y_t.PID_S.ki = Y_PID_S[1];
	m_GM6020_y_t.PID_S.kd = Y_PID_S[2];
	m_GM6020_y_t.PID_S.iLt = Y_PID_S[3];
	m_GM6020_y_t.PID_S.alLt = Y_PID_S[4];

	return df_re_ok;
}

/************************************************************万能分隔符**************************************************************
*	@author:			//赵澍
*	@performance:	//发射机构的初始化函数
*	@parameter:		//
*	@time:				//22-01-10
*	@ReadMe:			//加入了过零点解算//对应的pitch轴电机角度不能超过180
************************************************************************************************************************************/
uint8_t AttackInit(void)
{

	/***********************步兵的PID参数*******************/
											//kp			//ki		//kd		//iLimit	//alLimit
	float PID_P[5] ={ 10.1f,			0,			0,			0,				4000 };
	float PID_S[5] ={ 5.1,			0.05f,	0,			1000,			9999 };
	
	/***********************英雄的PID参数*******************/
//											//kp			//ki		//kd		//iLimit	//alLimit
//	float PID_P[5] = {	5.1f,			0,			0,			0,				4000};
//	float PID_S[5] = {	1.1,			0.05f,	0,			1000,			7999};	

	uint8_t i = 0;
	//上面的2006拨弹电机
	i = 0;
	m_AM2006_h_t.PID_P.kp = PID_P[i++];
	m_AM2006_h_t.PID_P.ki = PID_P[i++];
	m_AM2006_h_t.PID_P.kd = PID_P[i++];
	m_AM2006_h_t.PID_P.iLt = PID_P[i++];
	m_AM2006_h_t.PID_P.alLt = PID_P[i++];
	i = 0;
	m_AM2006_h_t.PID_S.kp = PID_S[i++];
	m_AM2006_h_t.PID_S.ki = PID_S[i++];
	m_AM2006_h_t.PID_S.kd = PID_S[i++];
	m_AM2006_h_t.PID_S.iLt = PID_S[i++];
	m_AM2006_h_t.PID_S.alLt = PID_S[i++];
	
											//kp			//ki		//kd		//iLimit	//alLimit
	float PID_PP[5] ={ 3.0f,				0,			0,			0,				2000 };
	float PID_SS[5] ={ 3,				0.20f,			0,			4000,				20000 };
	//
	//下面的3510拨弹电机
	i = 0;
	m_AM3510_d_t.PID_P.kp = PID_PP[i++];
	m_AM3510_d_t.PID_P.ki = PID_PP[i++];
	m_AM3510_d_t.PID_P.kd = PID_PP[i++];
	m_AM3510_d_t.PID_P.iLt = PID_PP[i++];
	m_AM3510_d_t.PID_P.alLt = PID_PP[i++];
	i = 0;
	m_AM3510_d_t.PID_S.kp = PID_SS[i++];
	m_AM3510_d_t.PID_S.ki = PID_SS[i++];
	m_AM3510_d_t.PID_S.kd = PID_SS[i++];
	m_AM3510_d_t.PID_S.iLt = PID_SS[i++];
	m_AM3510_d_t.PID_S.alLt = PID_SS[i++];
	//****************************************摩擦轮需要使用和拨弹电机不一样的PID***************************************//

	/***********************三号步兵*******************/
#ifdef Infantry_Number_Three
											//kp			//ki		//kd		//iLimit	//alLimit
	float PID_s[5]  ={ 6,			0.0002,	   0.6,			1500,			15000 };
#endif 
/***********************四号步兵*******************/
#ifdef Infantry_Number_Four
											//kp			//ki		//kd		//iLimit	//alLimit
	//float PID_s[5] ={ 9,				0.0069999f,	   4,			30,			15000 };
	float PID_s[5] ={ 20,				0.0069999f,	   4,			300,			15000 };
	// 9 0.005 4 25//最大15.1最低14.6 射速4235

#endif

//右摩擦轮
	i = 0;
	m_AM3508_r_t.PID_S.kp = PID_s[i++];
	m_AM3508_r_t.PID_S.ki = PID_s[i++];
	m_AM3508_r_t.PID_S.kd = PID_s[i++];
	m_AM3508_r_t.PID_S.iLt = PID_s[i++];
	m_AM3508_r_t.PID_S.alLt = PID_s[i++];
	//左摩擦轮
	i = 0;
	m_AM3508_l_t.PID_S.kp = PID_s[i++];
	m_AM3508_l_t.PID_S.ki = PID_s[i++];
	m_AM3508_l_t.PID_S.kd = PID_s[i++];
	m_AM3508_l_t.PID_S.iLt = PID_s[i++];
	m_AM3508_l_t.PID_S.alLt = PID_s[i++];
	
	return df_re_ok;
}
/************************************************************万能分隔符**************************************************************
*	@author:			//赵澍
*	@performance:	//底盘电机CAN处理函数
*	@parameter:		//can_data:CAN接收数组motor：电机结构体指针变量。
*	@time:				//20-8-14
*	@ReadMe:			//(360/8192) = 0.044//将8192转化到了360上去
************************************************************************************************************************************/
void CanManage_3508(uint8_t* can_data , struct data_typedef* data)
{
/*************************角度与速度的计算*************************/
	data->angle[df_last] 			=  data->angle[df_now];
	data->angle[df_now]  			= (int16_t) (((can_data[0]<<8) | can_data[1])&0xFFFF);
	data->speed[df_last] 			=  data->speed[df_now];
	data->speed[df_now]  			= (int16_t) (((can_data[2]<<8) | can_data[3])&0xFFFF);
	data->temp[df_last]        =  data->temp[df_now];
	data->temp[df_now]        =  (int16_t) (((can_data[6]<<8) | can_data[7])&0xFFFF);
	/*圈数的计算*/
	if ((data->angle[df_now] - data->angle[df_last])< -4096)
	{
		data->round++;
	}
	else if ((data->angle[df_now] - data->angle[df_last]) > 4096)
	{
		data->round--;
	}
	/*圈数清零保证不会疯转*/
	if ((data->round > 32000) | (data->round < -32000))
	{
		data->round = 0;
		data->aim = data->angle[df_now];
	}
	data->reality = (int32_t) ((data->round * 360)+(float) (data->angle[df_now]*(0.044f)));

///*************************电流及其均值滤波*************************/
//	if( data->OpneIBool == df_re_error)
//	{
//			data->I[data->head++] = (int16_t)(((can_data[4]<<8) | can_data[5])&0xFFFF);
//	}
//	else if(data->OpneIBool == df_re_ok)
//	{
//			data->IDataAll -= data->I[data->head];
//			data->I[data->head++] = (int16_t)(((can_data[4]<<8) | can_data[5])&0xFFFF); 
//			data->IDataAll += data->I[data->head-1];
//			data->averageI = data->IDataAll/I_length;
//	}
//	//说明数据接收满了整个数组
//	if(data->head >= I_length)
//	{
//			data->head = I_length-1;
//			//求和并且将标志位置为：OK	//仅能进入一次
//			while((data->OpneIBool == df_re_error) && 1 )
//			{
//					data->IDataAll += data->I[data->head--];
//					if(data->head <= 0)
//					{
//							data->IDataAll += data->I[data->head];
//							data->head = 0;
//							break;
//					}
//			}
//			data->head = 0;
//			data->OpneIBool = df_re_ok;
//	}
//	
}
/************************************************************万能分隔符**************************************************************
*	@author:			//赵澍
*	@performance:	//2006电机CAN处理函数
*	@parameter:		//can_data:CAN接收数组。motor：电机结构体指针变量。
*	@time:				//22-01-19
*	@ReadMe:			//(360/8192) = 0.044//将8192转化到了360上去
************************************************************************************************************************************/
void CanManage_2006(uint8_t* can_data , struct data_typedef* data)
{
/*************************角度与速度的计算*************************/
	data->angle[df_last] 	=  data->angle[df_now];
	data->angle[df_now]  	= (int16_t) (((can_data[0]<<8) | can_data[1])&0xFFFF);
	data->speed[df_last] 	=  data->speed[df_now];
	data->speed[df_now]  	= (int16_t) (((can_data[2]<<8) | can_data[3])&0xFFFF);
	/*圈数的计算*/
	if ((data->angle[df_now] - data->angle[df_last])< -4096)
	{
		data->round++;
	}
	else if ((data->angle[df_now] - data->angle[df_last]) > 4096)
	{
		data->round--;
	}
	/*圈数清零保证不会疯转*/
	if ((data->round > 32000) | (data->round < -32000))
	{
		data->round = 0;
		data->aim = data->angle[df_now];
	}
	data->reality = (int32_t) ((data->round * 360)+(float) (data->angle[df_now]*(0.0439453125f)));

/*************************电流及其均值滤波*************************/
	if (data->OpneIBool == df_re_error)
	{
		data->I[data->head++] = (int16_t) (((can_data[4]<<8) | can_data[5])&0xFFFF);
	}
	else if (data->OpneIBool == df_re_ok)
	{
		data->IDataAll -= data->I[data->head];
		data->I[data->head++] = (int16_t) (((can_data[4]<<8) | can_data[5])&0xFFFF);
		data->IDataAll += data->I[data->head-1];
		data->averageI = data->IDataAll/I_length;
	}
	//说明数据接收满了整个数组
	if (data->head >= I_length)
	{
		data->head = I_length-1;
		//求和并且将标志位置为：OK	//仅能进入一次
		while ((data->OpneIBool == df_re_error) && 1)
		{
			data->IDataAll += data->I[data->head--];
			if (data->head <= 0)
			{
				data->IDataAll += data->I[data->head];
				data->head = 0;
				break;
			}
		}
		data->head = 0;
		data->OpneIBool = df_re_ok;
	}

}
/************************************************************万能分隔符**************************************************************
*	@author:			//赵澍
*	@performance:	//6020电机CAN解算函数
*	@parameter:		//对应的序列以及电机结构体
*	@time:				//22-01-03
*	@ReadMe:			//没有加入过零点解算
************************************************************************************************************************************/
void CanManage_6020(uint8_t* can_data , struct data_typedef* data)
{
	int16_t angleError = 0;
/*************************角度与速度的计算*************************/
	data->angle[df_last] 			=  data->angle[df_now];
	data->angle[df_now]  			= (int16_t) (((can_data[0]<<8) | can_data[1])&0xFFFF);
	data->speed[df_last] 			=  data->speed[df_now];
	data->speed[df_now]  			= (int16_t) (((can_data[2]<<8) | can_data[3])&0xFFFF);
	//data->speed[df_now] *= 100;			//和陀螺仪单位统一，掉线之后不需要再改变PID参数
/*************************相对于初始点的角度(±180)*************************/
		m_GM6020_y_t.data.initialAngle = YawInitialAngle; 		//初始角度

	angleError = data->angle[df_now] - data->initialAngle;
	if (angleError > 4096)
	{
		angleError -= 8192;
	}
	else if (angleError < -4096)
	{
		angleError += 8192;
	}
	data->ralativeAngle = angleError * 0.044f;
	/*圈数的计算*/
	if ((data->angle[df_now] - data->angle[df_last])< -4096)
	{
		data->round++;
	}
	else if ((data->angle[df_now] - data->angle[df_last]) > 4096)
	{
		data->round--;
	}
	/*圈数清零保证不会疯转*/
	if ((data->round > 32000) | (data->round < -32000))
	{
		data->round = 0;
		data->aim = data->angle[df_now];
	}
	data->reality = (int32_t) ((data->round << 13)+(float) (data->angle[df_now]));

/*************************电流及其均值滤波*************************/
	if (data->OpneIBool == df_re_error)
	{
		data->I[data->head++] = (int16_t) (((can_data[4]<<8) | can_data[5])&0xFFFF);
	}
	else if (data->OpneIBool == df_re_ok)
	{
		data->IDataAll -= data->I[data->head];
		data->I[data->head++] = (int16_t) (((can_data[4]<<8) | can_data[5])&0xFFFF);
		data->IDataAll += data->I[data->head-1];
		data->averageI = data->IDataAll/I_length;
	}
	//说明数据接收满了整个数组
	if (data->head >= I_length)
	{
		data->head = I_length-1;
		//求和并且将标志位置为：OK	//仅能进入一次
		while ((data->OpneIBool == df_re_error) && 1)
		{
			data->IDataAll += data->I[data->head--];
			if (data->head <= 0)
			{
				if (data->angle[df_now] > 4096)		//圈数矫正//让电机无论在哪里启动都保证是零圈
					data->round++;
				data->IDataAll += data->I[data->head];
				data->head = 0;
				break;
			}
		}
		data->head = 0;
		data->OpneIBool = df_re_ok;
	}
}
/************************************************************万能分隔符**************************************************************
*	@author:			//赵澍
*	@performance:	//3508电机清空函数
*	@parameter:		//入口参数，3508电机结构体//0.44是将编码器转换为360度
*	@time:				//20-10-7
*	@ReadMe:			//电机设定等于电机真实值//如果包含角度环PID请使用角度
								//如果只是速度PID令第三、二项直接等于0
************************************************************************************************************************************/
void MotorReast3508(struct m_3508_typedef* motor)
{
	motor->data.round = 0;
	motor->data.reality = (int32_t) ((motor->data.round * 360) + (motor->data.angle[df_now]*(0.044)));
	motor->data.aim = (int32_t) (motor->data.angle[df_now]*(0.044));
	motor->PID_P.i_out = 0;
	motor->PID_S.i_out = 0;

}
/************************************************************万能分隔符**************************************************************
*	@author:			//赵澍
*	@performance:	//底盘电机单速度环PID
*	@parameter:		//motor：3508电机结构体指针变量。
*	@time:				//2021-12-2
*	@ReadMe:			//无论使用几个环来控制电机都一定是要使用速度环PID。!!!!!!!
************************************************************************************************************************************/
void CHMotorSpeedPID(struct m_3508_typedef* motor)
{
	const float MAXERROR = 800.0f;		//改变这个值控制斜坡的斜率
	motor->data.aim = SectionLimit_f((motor->data.speed[df_now] + MAXERROR) , (motor->data.speed[df_now] - MAXERROR) , motor->data.aim);
  /**************************速度环处理**************************/
	motor->PID_S.error[df_now] = motor->data.aim - motor->data.speed[df_now];
	/*比例输出*/
	motor->PID_S.p_out  = (motor->PID_S.error[df_now] * motor->PID_S.kp);
	/*积分输出*/
	motor->PID_S.i_out += (motor->PID_S.error[df_now] * motor->PID_S.ki);
	/*积分限幅*/
	motor->PID_S.i_out = SectionLimit_f(motor->PID_S.iLt , -motor->PID_S.iLt , motor->PID_S.i_out);
	/*微分输出*/
	motor->PID_S.d_out = (motor->PID_S.error[df_now] - motor->PID_S.error[df_last]) * motor->PID_S.kd;
	//数据迭代
	motor->PID_S.error[df_last] = motor->PID_S.error[df_now];
	//角度环总输出
	motor->PID_S.all_out = (motor->PID_S.p_out + motor->PID_S.i_out + motor->PID_S.d_out);
	/*总输出限幅*/
	motor->PID_S.all_out = SectionLimit_i(motor->PID_S.alLt , -motor->PID_S.alLt , motor->PID_S.all_out);
}
/************************************************************万能分隔符**************************************************************
*	@author:			//赵澍
*	@performance:	//底盘电机双环PID解算函数
*	@parameter:		//motor：3508电机结构体指针变量。
*	@time:				//20-10-26
*	@ReadMe:			//结算完之后的值储存于电机结构体的PID输出中//待调整
								//无论使用几个环来控制电机都一定是要使用速度环PID。!!!!!!!
************************************************************************************************************************************/
void CHMotorTwoPID(struct m_3508_typedef* motor)
{
	const int32_t MAXError = 100;			//控制加速度

/**************************角度环处理**************************/
	motor->PID_P.error[df_now] = (motor->data.aim - motor->data.reality);

	motor->PID_P.error[df_now] = (int32_t) SectionLimit_f(motor->PID_P.error[df_last]+MAXError , motor->PID_P.error[df_last]-MAXError , (float) motor->PID_P.error[df_now]);

	/*比例输出*/
	motor->PID_P.p_out  = (motor->PID_P.error[df_now] * motor->PID_P.kp);
	/*积分输出*/
	motor->PID_P.i_out += (motor->PID_P.error[df_now] * motor->PID_P.ki);
	/*积分限幅*/
	motor->PID_P.i_out = SectionLimit_f(motor->PID_P.iLt , -motor->PID_P.iLt , motor->PID_P.i_out);
	/*微分输出*/
	motor->PID_P.d_out = (motor->PID_P.error[df_now] - motor->PID_P.error[df_last]) * motor->PID_P.kd;
	//数据迭代
	motor->PID_P.error[df_last] = motor->PID_P.error[df_now];
	//角度环总输出
	motor->PID_P.all_out = (motor->PID_P.p_out + motor->PID_P.i_out + motor->PID_P.d_out);
	/*总输出限幅*/
	motor->PID_P.all_out = SectionLimit_i(motor->PID_P.alLt , -motor->PID_P.alLt , motor->PID_P.all_out);
/**************************速度环处理**************************/
	motor->PID_S.error[df_now] = motor->PID_P.all_out - motor->data.speed[df_now];
	/*比例输出*/
	motor->PID_S.p_out  = (motor->PID_S.error[df_now] * motor->PID_S.kp);
	/*积分输出*/
	motor->PID_S.i_out += (motor->PID_S.error[df_now] * motor->PID_S.ki);
	/*积分限幅*/
	motor->PID_S.i_out = SectionLimit_f(motor->PID_S.iLt , -motor->PID_S.iLt , motor->PID_S.i_out);
	/*微分输出*/
	motor->PID_S.d_out = (motor->PID_S.error[df_now] - motor->PID_S.error[df_last]) * motor->PID_S.kd;
	//数据迭代
	motor->PID_S.error[df_last] = motor->PID_S.error[df_now];
	//角度环总输出
	motor->PID_S.all_out = (motor->PID_S.p_out + motor->PID_S.i_out + motor->PID_S.d_out);
	/*总输出限幅*/
	motor->PID_S.all_out = SectionLimit_i(motor->PID_S.alLt , -motor->PID_S.alLt , motor->PID_S.all_out);
//加到限幅之内还是之外呢？
}
/************************************************************万能分隔符**************************************************************
*	@author:			//赵澍
*	@performance:	//2006拨弹电机单速度环PID
*	@parameter:		//motor：3508电机结构体指针变量。
*	@time:				//22-01-18
*	@ReadMe:			//无论使用几个环来控制电机都一定是要使用速度环PID。!!!!!!!
************************************************************************************************************************************/
void AMMotorSpeedPID(struct m_3508_typedef* motor)
{
/**************************速度环处理**************************/
	motor->PID_S.error[df_now] = motor->data.aim - motor->data.speed[df_now];
	/*比例输出*/
	motor->PID_S.p_out  = (motor->PID_S.error[df_now] * motor->PID_S.kp);
	/*积分输出*/
	motor->PID_S.i_out += (motor->PID_S.error[df_now] * motor->PID_S.ki);
	/*积分限幅*/
	motor->PID_S.i_out = SectionLimit_f(motor->PID_S.iLt , -motor->PID_S.iLt , motor->PID_S.i_out);
	/*微分输出*/
	motor->PID_S.d_out = (motor->PID_S.error[df_now] - motor->PID_S.error[df_last]) * motor->PID_S.kd;
	//数据迭代
	motor->PID_S.error[df_last] = motor->PID_S.error[df_now];
	//角度环总输出
	motor->PID_S.all_out = (motor->PID_S.p_out + motor->PID_S.i_out + motor->PID_S.d_out);
	/*总输出限幅*/
	motor->PID_S.all_out = SectionLimit_i(motor->PID_S.alLt , -motor->PID_S.alLt , motor->PID_S.all_out);
}
/************************************************************万能分隔符**************************************************************
*	@author:		//赵澍
*	@performance:	//摩擦轮速度环PID
*	@parameter:		//motor：3508电机结构体指针变量。
*	@time:			//22-01-11
*	@ReadMe:		//无论使用几个环来控制电机都一定是要使用速度环PID。!!!!!!!
************************************************************************************************************************************/
void FirctionSpeedPID(struct m_3508_typedef* motor)
{
/**************************速度环处理**************************/
	motor->PID_S.error[df_now] = motor->data.aim - motor->data.speed[df_now];
	/*比例输出*/
	motor->PID_S.p_out  = (motor->PID_S.error[df_now] * motor->PID_S.kp);
	/*积分输出*/
	motor->PID_S.i_out += (motor->PID_S.error[df_now] * motor->PID_S.ki);
	/*积分限幅*/
	motor->PID_S.i_out = SectionLimit_f(motor->PID_S.iLt , -motor->PID_S.iLt , motor->PID_S.i_out);
	/*微分输出*/
	motor->PID_S.d_out = (motor->PID_S.error[df_now] - motor->PID_S.error[df_last]) * motor->PID_S.kd;
	//数据迭代
	motor->PID_S.error[df_last] = motor->PID_S.error[df_now];
	//角度环总输出
	motor->PID_S.all_out = 15*(motor->data.temp[df_now]-motor->data.temp[df_last] )+(motor->PID_S.p_out + motor->PID_S.i_out + motor->PID_S.d_out);
	/*总输出限幅*/
	motor->PID_S.all_out = SectionLimit_i(motor->PID_S.alLt , -motor->PID_S.alLt , motor->PID_S.all_out);
}
/************************************************************万能分隔符**************************************************************
*	@author:		//赵澍
*	@performance:	//6020对应的pitch轴解算
*	@parameter:		//对应的电机结构体//是否使用陀螺仪
*	@time:			//21-12-14
*	@ReadMe:		//加入了过零点解算//对应的pitch轴电机角度不能超过180
************************************************************************************************************************************/

uint8_t GMPitchPID(struct m_6020_typedef* motor , int8_t Stata , float TopPitchSpeed , float topAngle)
{
	uint8_t topState = Stata & 0x0f;
	uint8_t visinoState = (Stata & 0x10) >>4;
	float raid_95 = 0.0f;
	/**************************角度环处理（待完善）**************************/
	if (topState == df_off)
	{		//陀螺仪或者风车
		motor->PID_P.error[df_now] = (motor->data.aim - motor->data.reality);
	}
	else if (topState == df_open)
	{		//手动和自瞄
		motor->PID_P.error[df_now] = (motor->data.aim - topAngle);
	}
	raid_95 =  my_abs(motor->PID_P.error[df_now]) / 100.0f;
	raid_95 = SectionLimit_f(1.0f , 0.0f , raid_95);
//	raid_95 = 1.0f;
	/**************************角度环处理**************************/
	/*比例输出*/
	motor->PID_P.p_out  = (motor->PID_P.error[df_now] * motor->PID_P.kp);
	/*积分输出*/
	motor->PID_P.i_out += (motor->PID_P.error[df_now] * motor->PID_P.ki);
	/*积分限幅*/
	if (topState == df_open)
	{
		motor->PID_P.i_out = SectionLimit_f(my_abs(TopPitchSpeed/3) * raid_95 , -my_abs(TopPitchSpeed/3) * raid_95 , motor->PID_P.i_out);
	}
	else
	{
		motor->PID_P.i_out = SectionLimit_f(motor->PID_P.iLt , -motor->PID_P.iLt , motor->PID_P.i_out);
	}
	/*微分输出*/
	motor->PID_P.d_out = (motor->PID_P.error[df_now] - motor->PID_P.error[df_last]) * motor->PID_P.kd;
	//数据迭代
	motor->PID_P.error[df_last] = motor->PID_P.error[df_now];
	//角度环总输出
	motor->PID_P.all_out = (motor->PID_P.p_out + motor->PID_P.i_out + motor->PID_P.d_out);
	/*总输出限幅*/
	motor->PID_P.all_out = SectionLimit_f(motor->PID_P.alLt , -motor->PID_P.alLt , motor->PID_P.all_out);

	/**************************速度环处理**************************/
	//对角速度的来源做出判断
	if (topState == df_open || visinoState == 0x01)
	{		//陀螺仪在线，使用陀螺仪角速度
		motor->PID_S.error[df_now] = motor->PID_P.all_out - TopPitchSpeed;
//		motor->PID_S.kp = 14;
//		motor->PID_S.ki = 0.43;
//		motor->PID_S.kd = 0;
//		motor->PID_S.iLt = 5000;

	}
	else if (topState == df_off)
	{		//陀螺仪离线，使用电机角速度
		motor->PID_S.error[df_now] = motor->PID_P.all_out - motor->data.speed[df_now];
//		motor->PID_S.kp = 40;
//		motor->PID_S.ki = 0.23;
//		motor->PID_S.kd = 120;
//		motor->PID_S.iLt = 7500;


	}
	else
	{
		return df_re_error;
	}

	/*比例输出*/
	motor->PID_S.p_out  = (motor->PID_S.error[df_now] * motor->PID_S.kp);
	/*积分输出*/
	motor->PID_S.i_out += (motor->PID_S.error[df_now] * motor->PID_S.ki);
	/*积分限幅*/
	motor->PID_S.i_out = SectionLimit_f(motor->PID_S.iLt , -motor->PID_S.iLt , motor->PID_S.i_out);
	/*微分输出*/
	motor->PID_S.d_out = (motor->PID_S.error[df_now] - motor->PID_S.error[df_last]) * motor->PID_S.kd;
	//数据迭代
	motor->PID_S.error[df_last] = motor->PID_S.error[df_now];
	//角度环总输出
	motor->PID_S.all_out = (motor->PID_S.p_out + motor->PID_S.i_out + motor->PID_S.d_out);
	/*总输出限幅*/
	motor->PID_S.all_out = SectionLimit_i(motor->PID_S.alLt , -motor->PID_S.alLt , motor->PID_S.all_out);

	return df_re_ok;
}
/************************************************************万能分隔符**************************************************************
*	@author:			//赵澍
*	@performance:	//6020对应的Yaw轴解算
*	@parameter:		//对应的电机结构体//状态位//陀螺仪的角速度//陀螺仪的角度
*	@time:				//21-12-29
*	@ReadMe:			//状态位说明：{1}位是陀螺仪状态，{5}位是是否打符
************************************************************************************************************************************/
uint8_t GMYawPID(struct m_6020_typedef* motor , int8_t Stata , float TopyawSpeed , float topAngle)
{
	uint8_t topState = Stata & 0x0f;
	uint8_t visinoState = (Stata & 0x10) >>4;
	/**************************角度环处理(待完善)**************************/
//	if ((topState == df_off) || (visinoState == 0x01))
//	{		//陀螺仪或者风车
//		motor->PID_P.error[df_now] = (motor->data.aim - motor->data.reality);
//	}
//	else if (topState == df_open)
//	{		
	if (topState == df_open)
	{
		motor->PID_P.error[df_now] = (motor->data.aim - topAngle);
	}
	if (topState == df_off)
	{
		motor->PID_P.error[df_now] = (motor->data.aim - motor->data.reality);
	}


  /*比例输出*/
	motor->PID_P.p_out  = (motor->PID_P.error[df_now] * motor->PID_P.kp);
	/*微分输出*/
	motor->PID_P.d_out = (motor->PID_P.error[df_now] - motor->PID_P.error[df_last]) * motor->PID_P.kd;
	/*积分输出*/
	motor->PID_P.i_out += (motor->PID_P.error[df_now] * motor->PID_P.ki);
	motor->PID_P.i_out += motor->PID_P.d_out;
	/*积分限幅*/
	motor->PID_P.i_out = SectionLimit_f(motor->PID_P.iLt , -motor->PID_P.iLt , motor->PID_P.i_out);
	if(isnan(motor->PID_P.i_out))motor->PID_P.i_out = 0;
	//数据迭代
	motor->PID_P.error[df_last] = motor->PID_P.error[df_now];
	//角度环总输出
	motor->PID_P.all_out = (motor->PID_P.p_out + motor->PID_P.i_out);// + motor->PID_P.d_out  );
	/*总输出限幅*/
	motor->PID_P.all_out = SectionLimit_f(motor->PID_P.alLt , -motor->PID_P.alLt , motor->PID_P.all_out);

	/**************************速度环处理**************************/
	//对角速度的来源做出判断
	if (topState == df_open)
	{		//陀螺仪在线，使用陀螺仪角速度error=aim-now
		motor->PID_S.error[df_now] = motor->PID_P.all_out - TopyawSpeed;
		//*步兵开启*//
		motor->PID_S.error[df_now] *= -1;
		if (visinoState == 0x01)
		{
			motor->PID_S.error[df_now] = motor->PID_P.all_out + TopyawSpeed;
		}
		//*步兵开启*//
	}
	else if (topState == df_off)
	{		//陀螺仪离线，使用电机角速度
		motor->PID_S.error[df_now] = motor->PID_P.all_out - motor->data.speed[df_now];
//			motor->PID_S.kp = 4.0f;
//			motor->PID_S.ki = 0.02f;
//			motor->PID_S.iLt = 6000;
	}
	else
	{
		return df_re_error;
	}

	/*比例输出*/
	motor->PID_S.p_out  = (motor->PID_S.error[df_now] * motor->PID_S.kp);
	/*微分输出*/
	motor->PID_S.d_out = (motor->PID_S.error[df_now] - motor->PID_S.error[df_last]) * motor->PID_S.kd;
	/*积分输出*/
	motor->PID_S.i_out += (motor->PID_S.error[df_now] * motor->PID_S.ki);
	motor->PID_S.i_out += motor->PID_S.d_out;
	/*积分限幅*/
	motor->PID_S.i_out = SectionLimit_f(motor->PID_S.iLt , -motor->PID_S.iLt , motor->PID_S.i_out);
	if(isnan(motor->PID_S.i_out))motor->PID_S.i_out = 0;
	//数据迭代
	motor->PID_S.error[df_last] = motor->PID_S.error[df_now];
	//速度环总输出
	motor->PID_S.all_out = (motor->PID_S.p_out + motor->PID_S.i_out); //+ motor->PID_S.d_out);
	/*总输出限幅*/
	motor->PID_S.all_out = SectionLimit_i(motor->PID_S.alLt , -motor->PID_S.alLt , motor->PID_S.all_out);

	return df_re_ok;
}
















