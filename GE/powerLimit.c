#include "powerLimit.h"
 #include "Read_Data.h"
#include "Write_Data.h"

/************************************************************���ָܷ���**************************************************************
*	@author:			//
*	@performance:	//���̹������ƺ���//ͨ�����ֵ���ʽ�����ֵ�����޷���
*	@parameter:		//����ʣ���ǰ���ʣ��趨���
*	@time:				//
*	@ReadMe:			//����ֵ�����ƹ������ֵ
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
/************************************************************���ָܷ���**************************************************************
*	@author:			//
*	@performance:	//���̹������ƺ���//ͨ�����幦�ʽ�������
*	@parameter:		//ʣ�໺��//�趨���
*	@time:				//
*	@ReadMe:			//����ֵ�����ƹ������ֵ
								//����������ϵͳ����ʹ��
								//�����趨ʣ��Ļ��幦��
************************************************************************************************************************************/
int32_t PowerLimBuffer(float buffer , int32_t setOut)
{
	const float residueBuffer = 15.0f;		//Ҫ�����ͻ���ʣ��
	static double Raid = 0.0f;
	double raid_temp = 0.0f;
	int32_t reData = 0;

	buffer -= residueBuffer;		//��ȥ����ʣ���Ļ���

	buffer = SectionLimit_f(200 , 0 , buffer-residueBuffer);
	//�������ϵ��
	Raid = (float) buffer/(60.0f - residueBuffer);
	Raid = SectionLimit_f(1.0f , 0.1f , Raid);
	//ƽ��
	raid_temp = Raid * Raid;

	reData = (raid_temp * setOut);

	AllotPower(reData);

	return reData;
}
/************************************************************���ָܷ���**************************************************************
*	@author:			//
*	@performance:	//���ĸ�������ʰ������ֵ���ȷ���
*	@parameter:		//������֮������ֵ
*	@time:				//
*	@ReadMe:			//
************************************************************************************************************************************/
void AllotPower(int32_t setOut)
{
		//�õ�δ����֮ǰ�������
	float allOutPower = abs_float(m_CH3508_1_t.PID_S.all_out) + abs_float(m_CH3508_2_t.PID_S.all_out) + \
		abs_float(m_CH3508_3_t.PID_S.all_out) + abs_float(m_CH3508_4_t.PID_S.all_out);

	m_CH3508_1_t.PID_S.all_out = setOut * (float) (m_CH3508_1_t.PID_S.all_out/allOutPower);
	m_CH3508_2_t.PID_S.all_out = setOut * (float) (m_CH3508_2_t.PID_S.all_out/allOutPower);
	m_CH3508_3_t.PID_S.all_out = setOut * (float) (m_CH3508_3_t.PID_S.all_out/allOutPower);
	m_CH3508_4_t.PID_S.all_out = setOut * (float) (m_CH3508_4_t.PID_S.all_out/allOutPower);
}
/************************************************************���ָܷ���**************************************************************
*	@author:			//
*	@performance:	//���̹������ƺ���//ͨ�����ֵ���ʽ�����ֵ�����޷���
*	@parameter:		//����ʣ���ǰ���ʣ��趨���
*	@time:				//
*	@ReadMe:			//����ֵ�����ƹ������ֵ
************************************************************************************************************************************/

/************************************************************���ָܷ���**************************************************************
*	@author:			//
*	@performance:	//б�º���
*	@parameter:		//��ʵֵ��ַ��Ŀ��ֵ����������� ʱ����
*	@time:				//
*	@ReadMe:			//�����̵��趨ֵ����//���������ڼ���ģʽ
************************************************************************************************************************************/
void SlopeKeyboard(int16_t* reality , int16_t aim , uint16_t intervalTime , uint64_t time)
{
	int16_t errAim = aim - *reality;		//��Բ�
	static int16_t lastAim = 0;		//Ŀ��ֵ
	static int16_t lastTime = 0;		//�ϴ�ʱ��
	float raid = 0.0f;

	if (lastAim == aim)
	{
		raid = (time - lastTime) / intervalTime;
		raid = SectionLimit_f(1.0f , 0.01f , raid);
		*reality += errAim * raid;
	}
	else
	{
		lastTime = time;		//����ʱ��
		raid = 0.0f;
	}
}

/************************************************************���ָܷ���**************************************************************
*	@author:			//
*	@performance:	//���ݹ������ƺ���//ͨ�����幦�ʽ�������
*	@parameter:		//ʣ�໺��//�趨���
*	@time:				//
*	@ReadMe:			//����ֵ�����ƹ������ֵ
                 **************����������ϵͳ����ʹ��***********/
								/**************����������ϵͳ����ʹ��***********/
//�����趨ʣ��Ļ��幦��
/************************************************************************************************************************************/
float residueBuffer = 15.0f;		//Ҫ�����ͻ���ʣ��
double Raid = 0.0f;
int32_t reData = 0;
int32_t PowerLimBuffer_Cap(uint16_t maxPower , float buffer , int32_t setOut)
{
	
	double raid_temp = 0.0f;
	

	capData_t.capGetDate.buffer += (maxPower - capData_t.capGetDate.nowPower - 6) * 0.0008f;
	capData_t.capGetDate.buffer = SectionLimit_f(60.0f , 0.01f , capData_t.capGetDate.buffer);

	buffer -= residueBuffer;		//��ȥ����ʣ���Ļ���

	buffer = SectionLimit_f(200 , 0 , buffer-residueBuffer);
	//�������ϵ��
	Raid = (float) buffer/(60.0f - residueBuffer);
	Raid = SectionLimit_f(1.0f , 0.1f , Raid);
	//ƽ��
	raid_temp = Raid * Raid;

	reData = (raid_temp * setOut);

	AllotPower(reData);

	return reData;
}



