#include "motor.h"
//���̵��
struct m_3508_typedef m_CH3508_1_t ={ 0 };
struct m_3508_typedef m_CH3508_2_t ={ 0 };
struct m_3508_typedef m_CH3508_3_t ={ 0 };
struct m_3508_typedef m_CH3508_4_t ={ 0 };
//����������
struct m_3508_typedef m_AM2006_h_t ={ 0 };
struct m_3508_typedef m_AM3510_d_t ={ 0 };
struct m_3508_typedef m_AM3508_r_t ={ 0 };			//������3510��Ϊ��ͳһ�뷽������Ϊ3508
struct m_3508_typedef m_AM3508_l_t ={ 0 };
//������̨���
struct m_6020_typedef m_GM6020_y_t ={ 0 };
struct m_6020_typedef m_GM6020_p_t ={ 0 };

//float NowPower = 0.0f;
//float raid = 2.8f;

/************************************************************���ָܷ���**************************************************************
*	@author:			//����
*	@performance:	//�����ʼ������
*	@parameter:		//�����е��̵��
*	@time:				//21-12-1
* @LastUpDataTime:  //2022-05-25 21:07    by С��
* @UpData�� // ��ÿ�����PID���е���
*	@ReadMe:			//�ı����PID����
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
/************************************************************���ָܷ���**************************************************************
*	@author:			//����
*	@performance:	//�����ʼ������(6020���ʹ��)
*	@parameter:		//�����е�����г�ʼ��
*	@time:				//21-12-14
*	@ReadMe:			//�ı����PID����//�Լ�yaw��pitch����������//����Ȧ������
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

	m_GM6020_p_t.data.initialAngle = PitchInitialAngle;		//��ʼ�Ƕ�
//���Ǻܶ�Ϊʲô
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

	m_GM6020_y_t.data.initialAngle = YawInitialAngle; 		//��ʼ�Ƕ�
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
	m_GM6020_y_t.data.initialAngle = YawInitialAngle; 		//��ʼ�Ƕ�
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

/************************************************************���ָܷ���**************************************************************
*	@author:			//����
*	@performance:	//��������ĳ�ʼ������
*	@parameter:		//
*	@time:				//22-01-10
*	@ReadMe:			//�����˹�������//��Ӧ��pitch�����ǶȲ��ܳ���180
************************************************************************************************************************************/
uint8_t AttackInit(void)
{

	/***********************������PID����*******************/
											//kp			//ki		//kd		//iLimit	//alLimit
	float PID_P[5] ={ 10.1f,			0,			0,			0,				4000 };
	float PID_S[5] ={ 5.1,			0.05f,	0,			1000,			9999 };
	
	/***********************Ӣ�۵�PID����*******************/
//											//kp			//ki		//kd		//iLimit	//alLimit
//	float PID_P[5] = {	5.1f,			0,			0,			0,				4000};
//	float PID_S[5] = {	1.1,			0.05f,	0,			1000,			7999};	

	uint8_t i = 0;
	//�����2006�������
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
	//�����3510�������
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
	//****************************************Ħ������Ҫʹ�úͲ��������һ����PID***************************************//

	/***********************���Ų���*******************/
#ifdef Infantry_Number_Three
											//kp			//ki		//kd		//iLimit	//alLimit
	float PID_s[5]  ={ 6,			0.0002,	   0.6,			1500,			15000 };
#endif 
/***********************�ĺŲ���*******************/
#ifdef Infantry_Number_Four
											//kp			//ki		//kd		//iLimit	//alLimit
	//float PID_s[5] ={ 9,				0.0069999f,	   4,			30,			15000 };
	float PID_s[5] ={ 20,				0.0069999f,	   4,			300,			15000 };
	// 9 0.005 4 25//���15.1���14.6 ����4235

#endif

//��Ħ����
	i = 0;
	m_AM3508_r_t.PID_S.kp = PID_s[i++];
	m_AM3508_r_t.PID_S.ki = PID_s[i++];
	m_AM3508_r_t.PID_S.kd = PID_s[i++];
	m_AM3508_r_t.PID_S.iLt = PID_s[i++];
	m_AM3508_r_t.PID_S.alLt = PID_s[i++];
	//��Ħ����
	i = 0;
	m_AM3508_l_t.PID_S.kp = PID_s[i++];
	m_AM3508_l_t.PID_S.ki = PID_s[i++];
	m_AM3508_l_t.PID_S.kd = PID_s[i++];
	m_AM3508_l_t.PID_S.iLt = PID_s[i++];
	m_AM3508_l_t.PID_S.alLt = PID_s[i++];
	
	return df_re_ok;
}
/************************************************************���ָܷ���**************************************************************
*	@author:			//����
*	@performance:	//���̵��CAN������
*	@parameter:		//can_data:CAN��������motor������ṹ��ָ�������
*	@time:				//20-8-14
*	@ReadMe:			//(360/8192) = 0.044//��8192ת������360��ȥ
************************************************************************************************************************************/
void CanManage_3508(uint8_t* can_data , struct data_typedef* data)
{
/*************************�Ƕ����ٶȵļ���*************************/
	data->angle[df_last] 			=  data->angle[df_now];
	data->angle[df_now]  			= (int16_t) (((can_data[0]<<8) | can_data[1])&0xFFFF);
	data->speed[df_last] 			=  data->speed[df_now];
	data->speed[df_now]  			= (int16_t) (((can_data[2]<<8) | can_data[3])&0xFFFF);
	data->temp[df_last]        =  data->temp[df_now];
	data->temp[df_now]        =  (int16_t) (((can_data[6]<<8) | can_data[7])&0xFFFF);
	/*Ȧ���ļ���*/
	if ((data->angle[df_now] - data->angle[df_last])< -4096)
	{
		data->round++;
	}
	else if ((data->angle[df_now] - data->angle[df_last]) > 4096)
	{
		data->round--;
	}
	/*Ȧ�����㱣֤�����ת*/
	if ((data->round > 32000) | (data->round < -32000))
	{
		data->round = 0;
		data->aim = data->angle[df_now];
	}
	data->reality = (int32_t) ((data->round * 360)+(float) (data->angle[df_now]*(0.044f)));

///*************************���������ֵ�˲�*************************/
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
//	//˵�����ݽ���������������
//	if(data->head >= I_length)
//	{
//			data->head = I_length-1;
//			//��Ͳ��ҽ���־λ��Ϊ��OK	//���ܽ���һ��
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
/************************************************************���ָܷ���**************************************************************
*	@author:			//����
*	@performance:	//2006���CAN������
*	@parameter:		//can_data:CAN�������顣motor������ṹ��ָ�������
*	@time:				//22-01-19
*	@ReadMe:			//(360/8192) = 0.044//��8192ת������360��ȥ
************************************************************************************************************************************/
void CanManage_2006(uint8_t* can_data , struct data_typedef* data)
{
/*************************�Ƕ����ٶȵļ���*************************/
	data->angle[df_last] 	=  data->angle[df_now];
	data->angle[df_now]  	= (int16_t) (((can_data[0]<<8) | can_data[1])&0xFFFF);
	data->speed[df_last] 	=  data->speed[df_now];
	data->speed[df_now]  	= (int16_t) (((can_data[2]<<8) | can_data[3])&0xFFFF);
	/*Ȧ���ļ���*/
	if ((data->angle[df_now] - data->angle[df_last])< -4096)
	{
		data->round++;
	}
	else if ((data->angle[df_now] - data->angle[df_last]) > 4096)
	{
		data->round--;
	}
	/*Ȧ�����㱣֤�����ת*/
	if ((data->round > 32000) | (data->round < -32000))
	{
		data->round = 0;
		data->aim = data->angle[df_now];
	}
	data->reality = (int32_t) ((data->round * 360)+(float) (data->angle[df_now]*(0.0439453125f)));

/*************************���������ֵ�˲�*************************/
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
	//˵�����ݽ���������������
	if (data->head >= I_length)
	{
		data->head = I_length-1;
		//��Ͳ��ҽ���־λ��Ϊ��OK	//���ܽ���һ��
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
/************************************************************���ָܷ���**************************************************************
*	@author:			//����
*	@performance:	//6020���CAN���㺯��
*	@parameter:		//��Ӧ�������Լ�����ṹ��
*	@time:				//22-01-03
*	@ReadMe:			//û�м����������
************************************************************************************************************************************/
void CanManage_6020(uint8_t* can_data , struct data_typedef* data)
{
	int16_t angleError = 0;
/*************************�Ƕ����ٶȵļ���*************************/
	data->angle[df_last] 			=  data->angle[df_now];
	data->angle[df_now]  			= (int16_t) (((can_data[0]<<8) | can_data[1])&0xFFFF);
	data->speed[df_last] 			=  data->speed[df_now];
	data->speed[df_now]  			= (int16_t) (((can_data[2]<<8) | can_data[3])&0xFFFF);
	//data->speed[df_now] *= 100;			//�������ǵ�λͳһ������֮����Ҫ�ٸı�PID����
/*************************����ڳ�ʼ��ĽǶ�(��180)*************************/
		m_GM6020_y_t.data.initialAngle = YawInitialAngle; 		//��ʼ�Ƕ�

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
	/*Ȧ���ļ���*/
	if ((data->angle[df_now] - data->angle[df_last])< -4096)
	{
		data->round++;
	}
	else if ((data->angle[df_now] - data->angle[df_last]) > 4096)
	{
		data->round--;
	}
	/*Ȧ�����㱣֤�����ת*/
	if ((data->round > 32000) | (data->round < -32000))
	{
		data->round = 0;
		data->aim = data->angle[df_now];
	}
	data->reality = (int32_t) ((data->round << 13)+(float) (data->angle[df_now]));

/*************************���������ֵ�˲�*************************/
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
	//˵�����ݽ���������������
	if (data->head >= I_length)
	{
		data->head = I_length-1;
		//��Ͳ��ҽ���־λ��Ϊ��OK	//���ܽ���һ��
		while ((data->OpneIBool == df_re_error) && 1)
		{
			data->IDataAll += data->I[data->head--];
			if (data->head <= 0)
			{
				if (data->angle[df_now] > 4096)		//Ȧ������//�õ��������������������֤����Ȧ
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
/************************************************************���ָܷ���**************************************************************
*	@author:			//����
*	@performance:	//3508�����պ���
*	@parameter:		//��ڲ�����3508����ṹ��//0.44�ǽ�������ת��Ϊ360��
*	@time:				//20-10-7
*	@ReadMe:			//����趨���ڵ����ʵֵ//��������ǶȻ�PID��ʹ�ýǶ�
								//���ֻ���ٶ�PID�����������ֱ�ӵ���0
************************************************************************************************************************************/
void MotorReast3508(struct m_3508_typedef* motor)
{
	motor->data.round = 0;
	motor->data.reality = (int32_t) ((motor->data.round * 360) + (motor->data.angle[df_now]*(0.044)));
	motor->data.aim = (int32_t) (motor->data.angle[df_now]*(0.044));
	motor->PID_P.i_out = 0;
	motor->PID_S.i_out = 0;

}
/************************************************************���ָܷ���**************************************************************
*	@author:			//����
*	@performance:	//���̵�����ٶȻ�PID
*	@parameter:		//motor��3508����ṹ��ָ�������
*	@time:				//2021-12-2
*	@ReadMe:			//����ʹ�ü����������Ƶ����һ����Ҫʹ���ٶȻ�PID��!!!!!!!
************************************************************************************************************************************/
void CHMotorSpeedPID(struct m_3508_typedef* motor)
{
	const float MAXERROR = 800.0f;		//�ı����ֵ����б�µ�б��
	motor->data.aim = SectionLimit_f((motor->data.speed[df_now] + MAXERROR) , (motor->data.speed[df_now] - MAXERROR) , motor->data.aim);
  /**************************�ٶȻ�����**************************/
	motor->PID_S.error[df_now] = motor->data.aim - motor->data.speed[df_now];
	/*�������*/
	motor->PID_S.p_out  = (motor->PID_S.error[df_now] * motor->PID_S.kp);
	/*�������*/
	motor->PID_S.i_out += (motor->PID_S.error[df_now] * motor->PID_S.ki);
	/*�����޷�*/
	motor->PID_S.i_out = SectionLimit_f(motor->PID_S.iLt , -motor->PID_S.iLt , motor->PID_S.i_out);
	/*΢�����*/
	motor->PID_S.d_out = (motor->PID_S.error[df_now] - motor->PID_S.error[df_last]) * motor->PID_S.kd;
	//���ݵ���
	motor->PID_S.error[df_last] = motor->PID_S.error[df_now];
	//�ǶȻ������
	motor->PID_S.all_out = (motor->PID_S.p_out + motor->PID_S.i_out + motor->PID_S.d_out);
	/*������޷�*/
	motor->PID_S.all_out = SectionLimit_i(motor->PID_S.alLt , -motor->PID_S.alLt , motor->PID_S.all_out);
}
/************************************************************���ָܷ���**************************************************************
*	@author:			//����
*	@performance:	//���̵��˫��PID���㺯��
*	@parameter:		//motor��3508����ṹ��ָ�������
*	@time:				//20-10-26
*	@ReadMe:			//������֮���ֵ�����ڵ���ṹ���PID�����//������
								//����ʹ�ü����������Ƶ����һ����Ҫʹ���ٶȻ�PID��!!!!!!!
************************************************************************************************************************************/
void CHMotorTwoPID(struct m_3508_typedef* motor)
{
	const int32_t MAXError = 100;			//���Ƽ��ٶ�

/**************************�ǶȻ�����**************************/
	motor->PID_P.error[df_now] = (motor->data.aim - motor->data.reality);

	motor->PID_P.error[df_now] = (int32_t) SectionLimit_f(motor->PID_P.error[df_last]+MAXError , motor->PID_P.error[df_last]-MAXError , (float) motor->PID_P.error[df_now]);

	/*�������*/
	motor->PID_P.p_out  = (motor->PID_P.error[df_now] * motor->PID_P.kp);
	/*�������*/
	motor->PID_P.i_out += (motor->PID_P.error[df_now] * motor->PID_P.ki);
	/*�����޷�*/
	motor->PID_P.i_out = SectionLimit_f(motor->PID_P.iLt , -motor->PID_P.iLt , motor->PID_P.i_out);
	/*΢�����*/
	motor->PID_P.d_out = (motor->PID_P.error[df_now] - motor->PID_P.error[df_last]) * motor->PID_P.kd;
	//���ݵ���
	motor->PID_P.error[df_last] = motor->PID_P.error[df_now];
	//�ǶȻ������
	motor->PID_P.all_out = (motor->PID_P.p_out + motor->PID_P.i_out + motor->PID_P.d_out);
	/*������޷�*/
	motor->PID_P.all_out = SectionLimit_i(motor->PID_P.alLt , -motor->PID_P.alLt , motor->PID_P.all_out);
/**************************�ٶȻ�����**************************/
	motor->PID_S.error[df_now] = motor->PID_P.all_out - motor->data.speed[df_now];
	/*�������*/
	motor->PID_S.p_out  = (motor->PID_S.error[df_now] * motor->PID_S.kp);
	/*�������*/
	motor->PID_S.i_out += (motor->PID_S.error[df_now] * motor->PID_S.ki);
	/*�����޷�*/
	motor->PID_S.i_out = SectionLimit_f(motor->PID_S.iLt , -motor->PID_S.iLt , motor->PID_S.i_out);
	/*΢�����*/
	motor->PID_S.d_out = (motor->PID_S.error[df_now] - motor->PID_S.error[df_last]) * motor->PID_S.kd;
	//���ݵ���
	motor->PID_S.error[df_last] = motor->PID_S.error[df_now];
	//�ǶȻ������
	motor->PID_S.all_out = (motor->PID_S.p_out + motor->PID_S.i_out + motor->PID_S.d_out);
	/*������޷�*/
	motor->PID_S.all_out = SectionLimit_i(motor->PID_S.alLt , -motor->PID_S.alLt , motor->PID_S.all_out);
//�ӵ��޷�֮�ڻ���֮���أ�
}
/************************************************************���ָܷ���**************************************************************
*	@author:			//����
*	@performance:	//2006����������ٶȻ�PID
*	@parameter:		//motor��3508����ṹ��ָ�������
*	@time:				//22-01-18
*	@ReadMe:			//����ʹ�ü����������Ƶ����һ����Ҫʹ���ٶȻ�PID��!!!!!!!
************************************************************************************************************************************/
void AMMotorSpeedPID(struct m_3508_typedef* motor)
{
/**************************�ٶȻ�����**************************/
	motor->PID_S.error[df_now] = motor->data.aim - motor->data.speed[df_now];
	/*�������*/
	motor->PID_S.p_out  = (motor->PID_S.error[df_now] * motor->PID_S.kp);
	/*�������*/
	motor->PID_S.i_out += (motor->PID_S.error[df_now] * motor->PID_S.ki);
	/*�����޷�*/
	motor->PID_S.i_out = SectionLimit_f(motor->PID_S.iLt , -motor->PID_S.iLt , motor->PID_S.i_out);
	/*΢�����*/
	motor->PID_S.d_out = (motor->PID_S.error[df_now] - motor->PID_S.error[df_last]) * motor->PID_S.kd;
	//���ݵ���
	motor->PID_S.error[df_last] = motor->PID_S.error[df_now];
	//�ǶȻ������
	motor->PID_S.all_out = (motor->PID_S.p_out + motor->PID_S.i_out + motor->PID_S.d_out);
	/*������޷�*/
	motor->PID_S.all_out = SectionLimit_i(motor->PID_S.alLt , -motor->PID_S.alLt , motor->PID_S.all_out);
}
/************************************************************���ָܷ���**************************************************************
*	@author:		//����
*	@performance:	//Ħ�����ٶȻ�PID
*	@parameter:		//motor��3508����ṹ��ָ�������
*	@time:			//22-01-11
*	@ReadMe:		//����ʹ�ü����������Ƶ����һ����Ҫʹ���ٶȻ�PID��!!!!!!!
************************************************************************************************************************************/
void FirctionSpeedPID(struct m_3508_typedef* motor)
{
/**************************�ٶȻ�����**************************/
	motor->PID_S.error[df_now] = motor->data.aim - motor->data.speed[df_now];
	/*�������*/
	motor->PID_S.p_out  = (motor->PID_S.error[df_now] * motor->PID_S.kp);
	/*�������*/
	motor->PID_S.i_out += (motor->PID_S.error[df_now] * motor->PID_S.ki);
	/*�����޷�*/
	motor->PID_S.i_out = SectionLimit_f(motor->PID_S.iLt , -motor->PID_S.iLt , motor->PID_S.i_out);
	/*΢�����*/
	motor->PID_S.d_out = (motor->PID_S.error[df_now] - motor->PID_S.error[df_last]) * motor->PID_S.kd;
	//���ݵ���
	motor->PID_S.error[df_last] = motor->PID_S.error[df_now];
	//�ǶȻ������
	motor->PID_S.all_out = 15*(motor->data.temp[df_now]-motor->data.temp[df_last] )+(motor->PID_S.p_out + motor->PID_S.i_out + motor->PID_S.d_out);
	/*������޷�*/
	motor->PID_S.all_out = SectionLimit_i(motor->PID_S.alLt , -motor->PID_S.alLt , motor->PID_S.all_out);
}
/************************************************************���ָܷ���**************************************************************
*	@author:		//����
*	@performance:	//6020��Ӧ��pitch�����
*	@parameter:		//��Ӧ�ĵ���ṹ��//�Ƿ�ʹ��������
*	@time:			//21-12-14
*	@ReadMe:		//�����˹�������//��Ӧ��pitch�����ǶȲ��ܳ���180
************************************************************************************************************************************/

uint8_t GMPitchPID(struct m_6020_typedef* motor , int8_t Stata , float TopPitchSpeed , float topAngle)
{
	uint8_t topState = Stata & 0x0f;
	uint8_t visinoState = (Stata & 0x10) >>4;
	float raid_95 = 0.0f;
	/**************************�ǶȻ����������ƣ�**************************/
	if (topState == df_off)
	{		//�����ǻ��߷糵
		motor->PID_P.error[df_now] = (motor->data.aim - motor->data.reality);
	}
	else if (topState == df_open)
	{		//�ֶ�������
		motor->PID_P.error[df_now] = (motor->data.aim - topAngle);
	}
	raid_95 =  my_abs(motor->PID_P.error[df_now]) / 100.0f;
	raid_95 = SectionLimit_f(1.0f , 0.0f , raid_95);
//	raid_95 = 1.0f;
	/**************************�ǶȻ�����**************************/
	/*�������*/
	motor->PID_P.p_out  = (motor->PID_P.error[df_now] * motor->PID_P.kp);
	/*�������*/
	motor->PID_P.i_out += (motor->PID_P.error[df_now] * motor->PID_P.ki);
	/*�����޷�*/
	if (topState == df_open)
	{
		motor->PID_P.i_out = SectionLimit_f(my_abs(TopPitchSpeed/3) * raid_95 , -my_abs(TopPitchSpeed/3) * raid_95 , motor->PID_P.i_out);
	}
	else
	{
		motor->PID_P.i_out = SectionLimit_f(motor->PID_P.iLt , -motor->PID_P.iLt , motor->PID_P.i_out);
	}
	/*΢�����*/
	motor->PID_P.d_out = (motor->PID_P.error[df_now] - motor->PID_P.error[df_last]) * motor->PID_P.kd;
	//���ݵ���
	motor->PID_P.error[df_last] = motor->PID_P.error[df_now];
	//�ǶȻ������
	motor->PID_P.all_out = (motor->PID_P.p_out + motor->PID_P.i_out + motor->PID_P.d_out);
	/*������޷�*/
	motor->PID_P.all_out = SectionLimit_f(motor->PID_P.alLt , -motor->PID_P.alLt , motor->PID_P.all_out);

	/**************************�ٶȻ�����**************************/
	//�Խ��ٶȵ���Դ�����ж�
	if (topState == df_open || visinoState == 0x01)
	{		//���������ߣ�ʹ�������ǽ��ٶ�
		motor->PID_S.error[df_now] = motor->PID_P.all_out - TopPitchSpeed;
//		motor->PID_S.kp = 14;
//		motor->PID_S.ki = 0.43;
//		motor->PID_S.kd = 0;
//		motor->PID_S.iLt = 5000;

	}
	else if (topState == df_off)
	{		//���������ߣ�ʹ�õ�����ٶ�
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

	/*�������*/
	motor->PID_S.p_out  = (motor->PID_S.error[df_now] * motor->PID_S.kp);
	/*�������*/
	motor->PID_S.i_out += (motor->PID_S.error[df_now] * motor->PID_S.ki);
	/*�����޷�*/
	motor->PID_S.i_out = SectionLimit_f(motor->PID_S.iLt , -motor->PID_S.iLt , motor->PID_S.i_out);
	/*΢�����*/
	motor->PID_S.d_out = (motor->PID_S.error[df_now] - motor->PID_S.error[df_last]) * motor->PID_S.kd;
	//���ݵ���
	motor->PID_S.error[df_last] = motor->PID_S.error[df_now];
	//�ǶȻ������
	motor->PID_S.all_out = (motor->PID_S.p_out + motor->PID_S.i_out + motor->PID_S.d_out);
	/*������޷�*/
	motor->PID_S.all_out = SectionLimit_i(motor->PID_S.alLt , -motor->PID_S.alLt , motor->PID_S.all_out);

	return df_re_ok;
}
/************************************************************���ָܷ���**************************************************************
*	@author:			//����
*	@performance:	//6020��Ӧ��Yaw�����
*	@parameter:		//��Ӧ�ĵ���ṹ��//״̬λ//�����ǵĽ��ٶ�//�����ǵĽǶ�
*	@time:				//21-12-29
*	@ReadMe:			//״̬λ˵����{1}λ��������״̬��{5}λ���Ƿ���
************************************************************************************************************************************/
uint8_t GMYawPID(struct m_6020_typedef* motor , int8_t Stata , float TopyawSpeed , float topAngle)
{
	uint8_t topState = Stata & 0x0f;
	uint8_t visinoState = (Stata & 0x10) >>4;
	/**************************�ǶȻ�����(������)**************************/
//	if ((topState == df_off) || (visinoState == 0x01))
//	{		//�����ǻ��߷糵
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


  /*�������*/
	motor->PID_P.p_out  = (motor->PID_P.error[df_now] * motor->PID_P.kp);
	/*΢�����*/
	motor->PID_P.d_out = (motor->PID_P.error[df_now] - motor->PID_P.error[df_last]) * motor->PID_P.kd;
	/*�������*/
	motor->PID_P.i_out += (motor->PID_P.error[df_now] * motor->PID_P.ki);
	motor->PID_P.i_out += motor->PID_P.d_out;
	/*�����޷�*/
	motor->PID_P.i_out = SectionLimit_f(motor->PID_P.iLt , -motor->PID_P.iLt , motor->PID_P.i_out);
	if(isnan(motor->PID_P.i_out))motor->PID_P.i_out = 0;
	//���ݵ���
	motor->PID_P.error[df_last] = motor->PID_P.error[df_now];
	//�ǶȻ������
	motor->PID_P.all_out = (motor->PID_P.p_out + motor->PID_P.i_out);// + motor->PID_P.d_out  );
	/*������޷�*/
	motor->PID_P.all_out = SectionLimit_f(motor->PID_P.alLt , -motor->PID_P.alLt , motor->PID_P.all_out);

	/**************************�ٶȻ�����**************************/
	//�Խ��ٶȵ���Դ�����ж�
	if (topState == df_open)
	{		//���������ߣ�ʹ�������ǽ��ٶ�error=aim-now
		motor->PID_S.error[df_now] = motor->PID_P.all_out - TopyawSpeed;
		//*��������*//
		motor->PID_S.error[df_now] *= -1;
		if (visinoState == 0x01)
		{
			motor->PID_S.error[df_now] = motor->PID_P.all_out + TopyawSpeed;
		}
		//*��������*//
	}
	else if (topState == df_off)
	{		//���������ߣ�ʹ�õ�����ٶ�
		motor->PID_S.error[df_now] = motor->PID_P.all_out - motor->data.speed[df_now];
//			motor->PID_S.kp = 4.0f;
//			motor->PID_S.ki = 0.02f;
//			motor->PID_S.iLt = 6000;
	}
	else
	{
		return df_re_error;
	}

	/*�������*/
	motor->PID_S.p_out  = (motor->PID_S.error[df_now] * motor->PID_S.kp);
	/*΢�����*/
	motor->PID_S.d_out = (motor->PID_S.error[df_now] - motor->PID_S.error[df_last]) * motor->PID_S.kd;
	/*�������*/
	motor->PID_S.i_out += (motor->PID_S.error[df_now] * motor->PID_S.ki);
	motor->PID_S.i_out += motor->PID_S.d_out;
	/*�����޷�*/
	motor->PID_S.i_out = SectionLimit_f(motor->PID_S.iLt , -motor->PID_S.iLt , motor->PID_S.i_out);
	if(isnan(motor->PID_S.i_out))motor->PID_S.i_out = 0;
	//���ݵ���
	motor->PID_S.error[df_last] = motor->PID_S.error[df_now];
	//�ٶȻ������
	motor->PID_S.all_out = (motor->PID_S.p_out + motor->PID_S.i_out); //+ motor->PID_S.d_out);
	/*������޷�*/
	motor->PID_S.all_out = SectionLimit_i(motor->PID_S.alLt , -motor->PID_S.alLt , motor->PID_S.all_out);

	return df_re_ok;
}
















