#include "anonymity.h"
//#include "motor.h"
//#include "chassis.h"
#include "Read_Data.h"

/************************************************************���������**************************************************************/
uint8_t anonymity_au8[df_AnonymityLong] ={ 0 };
/************************************************************���ָܷ���**************************************************************
*	@author:			//����
*	@performance:	//�����������ڹۿ���������
*	@parameter:		//̫��//NO
*	@time:				//21-1-6
*	@ReadMe:			//Э�����������
************************************************************************************************************************************/
void Anonymity_TX(int16_t a_x , int16_t a_y , int16_t a_z , int16_t g_x , int16_t g_y , int16_t g_z , int16_t m_x , int16_t m_y , int16_t m_z , int32_t bar)
{
	//����V7����Э��
	uint8_t _cnt=0 , sum=0 , add=0 , i=0;
	int16_t _temp;

	anonymity_au8[_cnt++]=0xAA;
	anonymity_au8[_cnt++]=0xFF;
	anonymity_au8[_cnt++]=0xF1;
	anonymity_au8[_cnt++]=0;				//176

	_temp = a_x;
	anonymity_au8[_cnt++]=BYTE0(_temp);
	anonymity_au8[_cnt++]=BYTE1(_temp);
	_temp = a_y;
	anonymity_au8[_cnt++]=BYTE0(_temp);
	anonymity_au8[_cnt++]=BYTE1(_temp);
	_temp = a_z;
	anonymity_au8[_cnt++]=BYTE0(_temp);
	anonymity_au8[_cnt++]=BYTE1(_temp);

	_temp = g_x;
	anonymity_au8[_cnt++]=BYTE0(_temp);
	anonymity_au8[_cnt++]=BYTE1(_temp);
	_temp = g_y;
	anonymity_au8[_cnt++]=BYTE0(_temp);
	anonymity_au8[_cnt++]=BYTE1(_temp);
	_temp = g_z;
	anonymity_au8[_cnt++]=BYTE0(_temp);
	anonymity_au8[_cnt++]=BYTE1(_temp);

	_temp = m_x;
	anonymity_au8[_cnt++]=BYTE0(_temp);
	anonymity_au8[_cnt++]=BYTE1(_temp);
	_temp = m_y;
	anonymity_au8[_cnt++]=BYTE0(_temp);
	anonymity_au8[_cnt++]=BYTE1(_temp);
	_temp = m_z;
	anonymity_au8[_cnt++]=BYTE0(_temp);
	anonymity_au8[_cnt++]=BYTE1(_temp);

	anonymity_au8[3] = _cnt-4;

	for (i=0; (i<anonymity_au8[3]+4); i++)
	{
		sum += anonymity_au8[i];
		add += sum;
	}
	anonymity_au8[_cnt++]=sum;
	anonymity_au8[_cnt++]=add;
	//�����Ƕ�Ӧ�ķ������
//	my_USART3_DMA_TX(anonymity_au8 , _cnt);
	HAL_UART_Transmit_DMA(&huart2,anonymity_au8, _cnt);

}

//yaw���������  �ٶȻ�������
//void yawTXSpeed(void)
//{
//	Anonymity_TX((int16_t) (m_GM6020_y_t.PID_P.all_out)	//1//�ǶȻ������
//							, (int16_t) (TopData_t.yawSpeed_f)		//2
//							, (int16_t) (m_GM6020_y_t.PID_S.d_out)		//3
//							, (int16_t) (m_GM6020_y_t.data.aim)		//4//�ǶȲ�ֵ
//							, (int16_t) (m_GM6020_y_t.PID_S.error[df_last])	//5
//							, (int16_t) (m_GM6020_y_t.PID_S.p_out)	//6
//							, (int16_t) (m_GM6020_y_t.PID_S.i_out)		//7
//							, (int16_t) (m_GM6020_y_t.PID_S.all_out)	//8
//							, (int16_t) (m_GM6020_y_t.PID_P.all_out - TopData_t.yawSpeed_f)	//9	
//							, 200);
//}
////yaw���������  �ǶȻ�������
//void yawTXAngle(void)
//{
//	Anonymity_TX((int16_t) (m_GM6020_y_t.data.aim)	//1	
//							, (int16_t) (TopData_t.realityAngle)		//2
//							, (int16_t) (m_GM6020_y_t.data.reality)		//3
//							, (int16_t) (0)		//4//�ǶȲ�ֵ
//							, (int16_t) (m_GM6020_y_t.data.aim - 0)	//5
//							, (int16_t) (m_GM6020_y_t.PID_P.p_out)	//6
//							, (int16_t) (m_GM6020_y_t.PID_P.i_out)		//7
//							, (int16_t) (m_GM6020_y_t.PID_P.all_out)	//8
//							, (int16_t) (m_GM6020_y_t.PID_P.d_out)	//9	
//							, 200);
//}
////�Ӿ�������
//void visionTX(void)
//{
//	Anonymity_TX((int16_t) (visionData_t.receive.yawAngle[df_now])	//1	//�Ӿ��������ĽǶ�yaw
//							, (int16_t) (visionData_t.receive.pitchAngle[df_now])		//2
//							, (int16_t) (visionData_t.transmit.pitchAngle)		//3			//�����ʵֵ//�糵��
//							, (int16_t) (visionData_t.receive.pitchAngle[df_now] * 1000)		//4		//��������ʵֵ//������
//							, (int16_t) (5)	//5	//�������
//							, (int16_t) (6)	//6		//�糵���
//							, (int16_t) (7)		//7
//							, (int16_t) (((float) ((float) m_GM6020_p_t.data.aim - (float) m_GM6020_p_t.data.reality) * 0.044f) * 1000.0f)	//8
//							, (int16_t) (((float) ((float) m_GM6020_y_t.data.aim - (float) m_GM6020_y_t.data.reality) * 0.044f) * 1000.0f)	//9	
//							, 200);
//}
////��ʱ������
//void tempTX(void)
//{
//	Anonymity_TX((int16_t) (chassis_t.CHF_PID_P.P_out)	//1
//							, (int16_t) (chassis_t.CHF_PID_P.I_out)		//2
//							, (int16_t) (chassis_t.CHF_PID_P.D_out)		//3
//							, (int16_t) (chassis_t.CHF_PID_P.All_out)		//4
//							, (int16_t) (chassis_t.CHF_PID_P.Error[df_now])	//5
//							, (int16_t) (m_GM6020_y_t.PID_P.d_out)	//6
//							, (int16_t) (0 * 100)		//7
//							, (int16_t) (twoJudgeData.power.nowPower * 10)	//8
//							, (int16_t) (capData_t.capGetDate.nowPower * 10)	//9	
//							, 200);

//}
////pitch���������  �ٶȻ�������
//void pitchTXSpeed(void)
//{
//	Anonymity_TX((int16_t) (m_GM6020_p_t.PID_P.all_out)	//1	
//							, (int16_t) (TopData_t.pitchSpeed_f)		//2
//							, (int16_t) (m_GM6020_p_t.PID_S.d_out)		//3
//							, (int16_t) (m_GM6020_p_t.data.speed[df_now])		//4//�ǶȲ�ֵ
//							, (int16_t) (m_GM6020_p_t.PID_S.error[df_last])	//5
//							, (int16_t) (m_GM6020_p_t.PID_S.p_out)	//6
//							, (int16_t) (m_GM6020_p_t.PID_S.i_out)		//7
//							, (int16_t) (m_GM6020_p_t.PID_S.all_out)	//8
//							, (int16_t) (m_GM6020_p_t.PID_P.all_out - TopData_t.pitchSpeed_f)*100	//9	
//							, 200);
//}
////pitch���������  �ǶȻ�������
//void pitchTXAngle(void)
//{
//	Anonymity_TX((int16_t) (m_GM6020_p_t.data.aim)	//1	
//							, (int16_t) (TopData_t.pitchAgnle_f * 22.755555f + m_GM6020_p_t.data.initialAngle)		//2
//							, (int16_t) (m_GM6020_p_t.data.reality)		//3
//							, (int16_t) (0)		//4//�ǶȲ�ֵ
//							, (int16_t) (m_GM6020_p_t.data.aim - 0)	//5
//							, (int16_t) (m_GM6020_p_t.PID_P.p_out)	//6
//							, (int16_t) (m_GM6020_p_t.PID_P.i_out)		//7
//							, (int16_t) (m_GM6020_p_t.PID_P.all_out)	//8
//							, (int16_t) (m_GM6020_p_t.PID_P.d_out)	//9	
//							, 200);
//}
////���������������  
//void attackTX(void)
//{
//	Anonymity_TX((int16_t) (m_AM3508_r_t.data.speed[df_now])	//1		//�����
//							, (int16_t) (m_AM3508_r_t.data.aim)		//2	//�趨ֵ
//							, (int16_t) (0)		//3		��ǰ״̬
//							, (int16_t) (0)		//4//ʱ��
//							, (int16_t) (m_AM3508_r_t.PID_S.p_out)	//5
//							, (int16_t) (m_AM3508_r_t.PID_S.i_out)	//6
//							, (int16_t) (m_AM3508_r_t.PID_S.d_out)		//7
//							, (int16_t) (m_AM3508_r_t.PID_S.all_out)	//8
//							, (int16_t) (m_AM3508_r_t.data.aim - m_AM3508_r_t.data.speed[df_now])	//9	
//							, 200);
//}
////���̵������
//void chassisTX(void)
//{
//	Anonymity_TX((int16_t) (m_CH3508_1_t.data.aim)	//1	
//							, (int16_t) (m_CH3508_1_t.data.speed[df_now])		//2
//							, (int16_t) (m_CH3508_2_t.data.aim)		//3
//							, (int16_t) (m_CH3508_2_t.data.speed[df_now])		//4//�ǶȲ�ֵ
//							, (int16_t) (m_CH3508_3_t.data.aim)	//5
//							, (int16_t) (m_CH3508_3_t.data.speed[df_now])	//6
//							, (int16_t) (m_CH3508_4_t.data.aim)		//7
//							, (int16_t) (m_CH3508_4_t.data.speed[df_now])	//8
//							, (int16_t) (m_CH3508_1_t.PID_S.i_out)	//9	
//							, 200);
//}
////������̨��׷�����
//void ��̨׷��(void)
//{
//	Anonymity_TX((int16_t) (m_GM6020_y_t.data.aim)	//1	
//							, (int16_t) (0)		//2
//							, (int16_t) (m_GM6020_y_t.data.reality)		//3
//							, (int16_t) (m_GM6020_p_t.data.aim)		//4//�ǶȲ�ֵ
//							, (int16_t) (0)	//5
//							, (int16_t) (m_GM6020_p_t.data.reality)	//6
//							, (int16_t) (m_CH3508_4_t.data.aim)		//7
//							, (int16_t) (m_CH3508_4_t.data.speed[df_now])	//8
//							, (int16_t) (m_CH3508_1_t.PID_S.i_out)	//9	
//							, 200);
//}
////�����Ǽ�����
//void topTX(void)
//{
//	Anonymity_TX((int16_t) (TopData_t.pitchSpeed[df_now])	//1
//							, (int16_t) (TopData_t.yawSpeed[df_now])		//2
//							, (int16_t) (TopData_t.pitchSpeed[df_now])		//3
//							, (int16_t) (TopData_t.yawSpeed[df_now])		//4//�ǶȲ�ֵ
//							, (int16_t) (TopData_t.pitchAgnle_f)	//5
//							, (int16_t) (TopData_t.yawAgnle_f)	//6
//							, (int16_t) (TopData_t.pitchAgnle_f * 0.01f)		//7
//							, (int16_t) (m_GM6020_y_t.PID_S.all_out)	//8
//							, (int16_t) (m_GM6020_y_t.PID_P.all_out - TopData_t.yawSpeed_f)	//9	
//							, 200);
//}
////�����������
//void SupplyTXAngle(void)
//{
//	Anonymity_TX((int16_t) (m_AM2006_h_t.data.aim)		//1		//�趨�ٶ�
//							, (int16_t) (m_AM2006_h_t.data.reality)		//2	//ʵ���ٶ�
//							, (int16_t) (m_AM2006_h_t.PID_P.p_out)		//3		
//							, (int16_t) (m_AM2006_h_t.PID_P.i_out)		//4		
//							, (int16_t) (m_AM2006_h_t.PID_P.all_out)	//5		//�趨�ٶ�
//							, (int16_t) (m_AM2006_h_t.data.speed[df_now])	//6		//��ǰ�ٶ�
//							, (int16_t) (m_AM2006_h_t.PID_S.p_out)		//7
//							, (int16_t) (m_AM2006_h_t.PID_S.i_out)	//8
//							, (int16_t) (m_AM2006_h_t.PID_S.all_out)	//9	
//							, 200);
//}
////Ħ���ּ���
////void FirctionTXSpeed(void)
////{
////				Anonymity_TX((int16_t)(m_AM3508_r_t.data.speed[df_now])	//1		//�����
////										,(int16_t)(m_AM3508_r_t.data.aim)		//2	//�趨ֵ
////										,(int16_t)(attack_t.muzzle.SupHightMod)		//3		��ǰ״̬
////										,(int16_t)(attack_t.muzzle.SupHightTime)		//4//ʱ��
////										,(int16_t)(shu_temp)	//5
////										,(int16_t)(m_AM3508_r_t.PID_S.p_out)	//6
////										,(int16_t)(m_AM3508_r_t.PID_S.i_out)		//7
////										,(int16_t)(m_AM3508_r_t.PID_S.all_out)	//8
////										,(int16_t)(m_AM3508_r_t.data.aim - m_AM3508_r_t.data.speed[df_now])	//9	
////										,200);		
////}
////���̲����������
//void DownTXSpeed(void)
//{
////				Anonymity_TX((int16_t)(m_AM3510_d_t.PID_P.all_out)	//1		//�����
////										,(int16_t)(m_AM3510_d_t.data.speed[df_now])		//2	//�趨ֵ
////										,(int16_t)(0)		//3		��ǰ״̬
////										,(int16_t)(2)		//4//ʱ��
////										,(int16_t)(0)	//5
////										,(int16_t)(m_AM3510_d_t.PID_S.p_out)	//6
////										,(int16_t)(m_AM3510_d_t.PID_S.i_out)		//7
////										,(int16_t)(m_AM3510_d_t.PID_S.all_out)	//8
////										,(int16_t)(m_AM3510_r_t.data.aim - m_AM3510_r_t.data.speed[df_now])	//9	
////										,200);		
//}
////���״̬����
//void motorTXSpeed(void)
//{
//	Anonymity_TX((int16_t) (0)		//1		//�����
//							, (int16_t) (0)		//2	//�趨ֵ
//							, (int16_t) (attack_t.back.FirctStateL)		//3		��ǰ״̬
//							, (int16_t) (attack_t.back.FirctStateR)		//4//ʱ��
//							, (int16_t) (0)										//5
//							, (int16_t) (0)		//6
//							, (int16_t) (2)		//7
//							, (int16_t) (m_AM3510_d_t.PID_S.all_out)	//8
//							, (int16_t) (0)		//9	
//							, 200);
//}
//void ���ʼ���(void)		//���ʼ���
//{
//	Anonymity_TX((int16_t) (0)	//1	
//							, (int16_t) (twoJudgeData.power.nowPower * 100)		//2
//							, (int16_t) (60 * 100)	//3
//							, (int16_t) (twoJudgeData.power.buffer * 100)		//4//�ǶȲ�ֵ
//							, (int16_t) (m_GM6020_y_t.PID_S.error[df_last])	//5
//							, (int16_t) (m_GM6020_y_t.PID_P.p_out)	//6
//							, (int16_t) (m_GM6020_y_t.PID_P.i_out)		//7
//							, (int16_t) (m_GM6020_y_t.PID_P.all_out)	//8
//							, (int16_t) (m_GM6020_y_t.PID_P.d_out)	//9	
//							, 200);
//}
void power(){
	Anonymity_TX(  0
              , (int16_t) (judge_user_data.power_heat_data.buffer_energy)		//2
							, (int16_t) (judge_user_data.power_heat_data.chassis_voltage/1000)//3
							, (int16_t) (0)		//4//�ǶȲ�ֵ
							, (int16_t) (0)	//5
							, (int16_t) (0)	//6
							, (int16_t) (0)		//7
							, (int16_t) (0)	//8
							, (int16_t) (0)	//9	
							, 200);
}







