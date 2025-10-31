#include "chassis.h"
#include "user_define.h"		//���ڲ������Զ�������
struct chassis_typedef chassis_t ={ 0 };
RC_ctrl_t rc_ctrl;
struct visionData_typdef visionData_t;
/************************************************************���������ܺ���**************************************************************
*	@author:			    //����
*	@performance:      	//���������ܺ���
*	@parameter:		    //������״̬
*	@time:				     //21-12-31
* @LastUpDataTime:  //2022-05-26 18:57    by С��
* @UpData��         //���̸���ȡ��PID
* @UpData��         //�����˴��ģʽ�µ��̲�����
* @UpData           //���̸��滻����PID
*	@ReadMe:			//������//ǰ����//˳���渺
								 ʸ����     	//��ͷ����ÿһ�����ֵķ����������ִ���ID
								��  ||  ��
								1�� || ��2	.
								������������������   X��
								4�� || ��3
								��  ||  ��
									��β
								//Ŀǰ����֧�ֵ��ٶȻ�
************************************************************************************************************************************/
float allOutPower = 0;
void CHInfantry(uint8_t topStata)
{
	double angle = 0.0;
	float speedRaid = 0.0f;
	
//		float riadFollow = 0.0f;		//���̽���� 
		//�õ���̨�͵��̵���Խ�
	angle = m_GM6020_y_t.data.ralativeAngle * 0.0174444f;			//ת����������

	//ȷ��ϵ��
	if (CanCommunit_t.gmTOch.dataNeaten.supUSe == df_open)
	{
		speedRaid = chassis_t.superCap.superCapRaid;
	}
	else
	{
		speedRaid = chassis_t.superCap.normalRaid;
	}

	//�������ʹ��
	chassis_t.speed.vx_int16 = rc_ctrl.control.ch0_int16 * speedRaid;
	chassis_t.speed.vy_int16 = -rc_ctrl.control.ch1_int16 * speedRaid;
	chassis_t.speed.vr_int16 = rc_ctrl.control.direction * speedRaid/2.0f;



	//С����ģʽ�µ�һЩ���� 
	if (my_abs((int32_t) chassis_t.speed.vr_int16) >=50)
	{
		if (RUI_F_MATH_ABS_int16_t(chassis_t.speed.vx_int16)|| RUI_F_MATH_ABS_int16_t(chassis_t.speed.vy_int16))
		{
			chassis_t.speed.vr_int16 *= 0.15f;
		}
		else
		{
			chassis_t.speed.vr_int16 *= 0.70f;
		}
		chassis_t.speed.vx_int16 *= 0.40f;
		chassis_t.speed.vy_int16 *= 0.70f;

	}
	else if (CanCommunit_t.gmTOch.dataNeaten.CHfollow == 0)
	{		//���̲�����

	}
	else if (CanCommunit_t.gmTOch.dataNeaten.CHfollow == 1)
	{//���̸���
CHFollowTwoPID(&chassis_t);	
	}
//���ֽ���
	if (root_t.Init_t.chassisInit == df_re_ok)
	{
		MecanumResolve(chassis_t.speed.vx_int16 , chassis_t.speed.vy_int16 , chassis_t.speed.vr_int16 , angle);
	}
	else
	{	//�����ֽ���ĳ�ʼ������
		root_t.Init_t.chassisInit = CHInfantryInit();
	}

	//PID����
	CHMotorSpeedPID(&m_CH3508_1_t);
	CHMotorSpeedPID(&m_CH3508_2_t);
	CHMotorSpeedPID(&m_CH3508_3_t);
	CHMotorSpeedPID(&m_CH3508_4_t);

	allOutPower = abs_float(m_CH3508_1_t.PID_S.all_out) + abs_float(m_CH3508_2_t.PID_S.all_out) + \
		abs_float(m_CH3508_3_t.PID_S.all_out) + abs_float(m_CH3508_4_t.PID_S.all_out);
//���ʷ��亯��
	PowerAllot(10000);

	//*�������Ʋ���*//
	if (root_t.superCapRoot.communicat == 0)
	{		//�����������ߺ�Ĵ���
		PowerLimBuffer(judge_user_data.power_heat_data.buffer_energy , (int32_t) allOutPower);
//				SuperCapTransation(CanCommunit_t.gmTOch.dataNeaten.supUSe , (int32_t) allOutPower , RunTime);

	}
	else if (root_t.superCapRoot.communicat == 1)
	{		//������������
      //�����µĹ�������
		SuperCapTransation(CanCommunit_t.gmTOch.dataNeaten.supUSe , (int32_t) allOutPower , RunTime);
	}
}
/************************************************************���ָܷ���**************************************************************
*	@author:			//
*	@performance:	//������������
*	@parameter:		//slow����ģʽ\quick����ģʽ
*	@time:				//
*	@ReadMe:			//��ͣģʽ���������\����ģʽ�����¼����λ��
************************************************************************************************************************************/
void CHSpeedLock(uint8_t mod)
{
		//ת��ģʽ�������
	if (chassis_t.mods[df_now] != chassis_t.mods[df_last])
	{
		MotorReast3508(&m_CH3508_1_t);
		MotorReast3508(&m_CH3508_2_t);
		MotorReast3508(&m_CH3508_3_t);
		MotorReast3508(&m_CH3508_4_t);
		//Ϊ�˳���ȫ�Է�����if����
		//��ֹ��Ϊ�ж϶��޷�ִ������
		chassis_t.mods[df_last] = chassis_t.mods[df_now];
	}

	if (mod == df_solwLock)
	{
			//��������
		m_CH3508_1_t.data.aim = m_CH3508_1_t.data.reality;
		m_CH3508_2_t.data.aim = m_CH3508_2_t.data.reality;
		m_CH3508_3_t.data.aim = m_CH3508_3_t.data.reality;
		m_CH3508_4_t.data.aim = m_CH3508_4_t.data.reality;
	}
	else if (mod == df_quickLock)
	{

	}
	//PID����
	CHMotorTwoPID(&m_CH3508_1_t);
	CHMotorTwoPID(&m_CH3508_2_t);
	CHMotorTwoPID(&m_CH3508_3_t);
	CHMotorTwoPID(&m_CH3508_4_t);
}
/************************************************************���ָܷ���**************************************************************
*	@author:			//����
*	@performance:	//��ƫ������
*	@parameter:		//��ڲ������ĸ�Ŀ��ֵ�ĵ�ַָ��
								//����ֵ:�Ƿ��ʼ���ɹ�
*	@time:				//21-12-30
*	@ReadMe:			//ʹ�����ֽ���֮ǰ��Ҫ�Ƚ���һ�γ�ʼ��
								 ʸ����     	//��ͷ����ÿһ�����ֵķ����������ִ���ID
								��  ||  ��
								2�� || ��1
								������������������
								3�� || ��4
								��  ||  ��
									��β
************************************************************************************************************************************/
struct mecanumInit_typdef mecanumInit_t ={ 0 };		//��ʼ��ʹ�õĻ�����
static float* mecanumOutAddre[4] ={ 0 };		//������Ľ���ʹ��
uint8_t MecanumInit(void)
{
	mecanumOutAddre[0] = &m_CH3508_1_t.data.aim;		//��Ӧÿ�������Ŀ��ֵ
	mecanumOutAddre[1] = &m_CH3508_2_t.data.aim;
	mecanumOutAddre[2] = &m_CH3508_3_t.data.aim;
	mecanumOutAddre[3] = &m_CH3508_4_t.data.aim;

	mecanumInit_t.deceleration_ratio = 0.052075f;		//���ٱ�1/19
	mecanumInit_t.max_vw_speed = 50000;		//r�����ϵ�����ٶȵ�λ������/��
	mecanumInit_t.max_vx_speed = 50000;		//x�����ϵ�����ٶȵ�λ������/��
	mecanumInit_t.max_vy_speed = 50000;		//y�����ϵ�����ٶȵ�λ������/��
	mecanumInit_t.max_wheel_ramp = 8000;		//3508���ת�ٲ�����������
	mecanumInit_t.rotate_x_offset = 00.0f;		//��̨��x���ƫ����  mm
	mecanumInit_t.rotate_y_offset = 00.0f;		//��̨��y���ƫ����  mm
	mecanumInit_t.wheelbase = 300;		//�־�	mm
	mecanumInit_t.wheeltrack = 300;		//���	mm
	mecanumInit_t.wheel_perimeter = 478;	//���ӵ��ܳ�(mm)


	/*������ת����*/
	mecanumInit_t.raid_fr = ((mecanumInit_t.wheelbase + mecanumInit_t.wheeltrack) / 2.0f -
														mecanumInit_t.rotate_x_offset + mecanumInit_t.rotate_y_offset) /
		shu_COEF;
	mecanumInit_t.raid_fl = ((mecanumInit_t.wheelbase + mecanumInit_t.wheeltrack) / 2.0f -
														mecanumInit_t.rotate_x_offset - mecanumInit_t.rotate_y_offset) /
		shu_COEF;
	mecanumInit_t.raid_bl = ((mecanumInit_t.wheelbase + mecanumInit_t.wheeltrack) / 2.0f +
														mecanumInit_t.rotate_x_offset - mecanumInit_t.rotate_y_offset) /
		shu_COEF;
	mecanumInit_t.raid_br = ((mecanumInit_t.wheelbase + mecanumInit_t.wheeltrack) / 2.0f +
														mecanumInit_t.rotate_x_offset + mecanumInit_t.rotate_y_offset) /
		shu_COEF;
//�������������ת����תÿ������ȥ raid = 60/(������ٱ�*�ֵ��ܳ�)			
	mecanumInit_t.wheel_rpm_ratio =	60.0f / (mecanumInit_t.wheel_perimeter * mecanumInit_t.deceleration_ratio);

	return df_re_ok;
}

/************************************************************���ָܷ���**************************************************************
*	@author:			//����
*	@performance:	//�����ĵ�����ֽ��㡣�����ó�������һ�����ĵ�ת��,���ƶ�ʱ��֤�Բ�����Ϊ������
*	@parameter:		//ƽ���ٶ�//ǰ���ٶ�//��ת�ٶ�//��̨����̵���ԽǶ�(������)
*	@time:				//21-12-30
*	@ReadMe:			//������//ǰ����//˳���渺
								//��������ƫ���������Ե�����ת����
								//Ҫ�ڳ�ʼ����������֮����ܵ���
								 ʸ����     	//��ͷ����ÿһ�����ֵķ����������ִ���ID
								��  ||  ��
								2�� || ��1
								������������������   Y��  �����Ҹ��������¸�
								3�� || ��4
								��  ||  ��
									��β
								//Ŀǰ����֧�ֵ��ٶȻ�
************************************************************************************************************************************/
int8_t rui = 0;
//Ŀǰ������Ǵ�������Ŀ��ܵ���ת�ٹ���
void MecanumResolve(int16_t vx_temp , int16_t vy_temp , int16_t vr , float angle)
{
	float angleSin = 0.0f , angleCos = 0.0f;
	float max = 0;
	float wheel_rpm[4] ={ 0 };
	float vx = 0.0f , vy = 0.0f;

	if (root_t.Init_t.mecanumInit != df_re_ok)
	{
		root_t.Init_t.mecanumInit = MecanumInit();
		return;
	}
	if (rui == 0)
	{
		//��ת֮��ᵼ�¼������߲�һ��//ֻ�в����Ŵ�
		mecanumInit_t.rotate_y_offset = -3 * ((float) vr /700);
	}
	else if (rui == 1)
	{
		mecanumInit_t.rotate_y_offset = 0.0f;
	}
	/*������ת����*/
	mecanumInit_t.raid_fr = ((mecanumInit_t.wheelbase + mecanumInit_t.wheeltrack) / 2.0f -
														mecanumInit_t.rotate_x_offset + mecanumInit_t.rotate_y_offset) /
		shu_COEF;
	mecanumInit_t.raid_fl = ((mecanumInit_t.wheelbase + mecanumInit_t.wheeltrack) / 2.0f -
														mecanumInit_t.rotate_x_offset - mecanumInit_t.rotate_y_offset) /
		shu_COEF;
	mecanumInit_t.raid_bl = ((mecanumInit_t.wheelbase + mecanumInit_t.wheeltrack) / 2.0f +
														mecanumInit_t.rotate_x_offset - mecanumInit_t.rotate_y_offset) /
		shu_COEF;
	mecanumInit_t.raid_br = ((mecanumInit_t.wheelbase + mecanumInit_t.wheeltrack) / 2.0f +
														mecanumInit_t.rotate_x_offset + mecanumInit_t.rotate_y_offset) /
		shu_COEF;
//�������������ת����תÿ������ȥ raid = 60/(������ٱ�*�ֵ��ܳ�)			
	mecanumInit_t.wheel_rpm_ratio =	60.0f / (mecanumInit_t.wheel_perimeter * mecanumInit_t.deceleration_ratio);

	if (angle == 0)
	{			//��ֹ�Ƕ�Ϊ�㣬�������//������
		angle = 0.0001f;
	}
	//�õ���ԽǶȵ�sin��cos
	angleSin = sin(angle);
	angleCos = cos(angle);
	//�õ�ת�����vx,vy,vr
	vx = -vx_temp * angleSin + vy_temp * angleCos;
	vy = 	vx_temp * angleCos + vy_temp * angleSin;

	wheel_rpm[0] = (-vx + vy - vr * mecanumInit_t.raid_fr) * mecanumInit_t.wheel_rpm_ratio;
	wheel_rpm[1] = (vx + vy - vr * mecanumInit_t.raid_fl) * mecanumInit_t.wheel_rpm_ratio;
	wheel_rpm[2] = (vx - vy - vr * mecanumInit_t.raid_bl) * mecanumInit_t.wheel_rpm_ratio;
	wheel_rpm[3] = (-vx - vy - vr * mecanumInit_t.raid_br) * mecanumInit_t.wheel_rpm_ratio;
	//Ѱ���ĸ�������������ֵ		
	for (uint8_t i = 0; i < 4; i++)
	{
		if (fabs(wheel_rpm[i]) > max)
			max = fabs(wheel_rpm[i]);
	}
	//������������ֵ������еȱ�������
	if (max > mecanumInit_t.max_wheel_ramp)
	{
		float rate = mecanumInit_t.max_wheel_ramp / max;
		for (uint8_t i = 0; i < 4; i++)
			wheel_rpm[i] *= rate;
	}
	//��ֵ
	*mecanumOutAddre[0] = wheel_rpm[0];
	*mecanumOutAddre[1] = wheel_rpm[1];
	*mecanumOutAddre[2] = wheel_rpm[2];
	*mecanumOutAddre[3] = wheel_rpm[3];
}
/************************************************************���ָܷ���**************************************************************
*	@author:			//����
*	@performance:	//���������ܺ�����ʼ������
*	@parameter:		//ģʽ//������״̬
*	@time:				//21-12-31
* @LastUpDataTime:  //2022-05-23 17:14    by С��
* @UpData�� //�����˸���PID��ʼ��
*	@ReadMe:			//ֻ��Ҫִ��һ�Σ�������ʹ�õ����ܺ���֮ǰ�������һ�γ�ʼ��
								//���������ÿһ���ٶȺ��Ƹ˵Ķ�Ӧ��ϵ
************************************************************************************************************************************/
uint8_t CHInfantryInit(void)
{
	chassis_t.superCap.normalRaid = 3.50f;			//��ͨģʽ�µ�ϵ��
	chassis_t.superCap.slowRaid = 0.5f;
	chassis_t.superCap.slowKeyRaid = 330.0f;
	chassis_t.superCap.superCapRaid = 8.0f;		//��������ģʽ�µı���ϵ��

	CH3508M_Init();
	CHFollowPID_Init();

	return df_re_ok;
}
/************************************************************���ָܷ���**************************************************************
*	@author:			//����
*	@performance:	//�������̵������ж�
*	@parameter:		//ģʽ
*	@time:				//21-12-31
*	@ReadMe:			//����������״̬��һ��ʱ������ִ�����
************************************************************************************************************************************/
void CHEmptyJudge(uint8_t mod)
{
	chassis_t.mods[df_now] = mod;
	if (chassis_t.mods[df_now] != chassis_t.mods[df_last])
	{
		//���
		MotorReast3508(&m_CH3508_1_t);
		MotorReast3508(&m_CH3508_2_t);
		MotorReast3508(&m_CH3508_3_t);
		MotorReast3508(&m_CH3508_4_t);
		//״̬����
		chassis_t.mods[df_last] = chassis_t.mods[df_now];
	}
}
/************************************************************���ָܷ���**************************************************************
*	@author:			//����
*	@performance:	//���¼�⺯��
*	@parameter:		//�����ǽǶ�pitch��
*	@time:				//22-03-24
*	@ReadMe:			//�������й��ʷ���
								//�Ƕȼ��汾
************************************************************************************************************************************/
void UpHill(float topAngle)
{
	float relativeAngle = m_GM6020_p_t.data.ralativeAngle;	//��̨�͵��̵���Խ�
	float AngleCH = (topAngle/10.0f) - relativeAngle;		//���̺͵���Ĳ²�Ƕ�

//		AngleCH = AngleCH * ( -(m_GM6020_y_t.data.ralativeAngle - 90.0f) / 90.0f);	//���̺͵����ʵ�ʽǶ�//�������

	if (abs_float(AngleCH) >= 5.0f)
	{


		float raid = AngleCH / 25.0f;

		SectionLimit_f(1.0f , 0.0f , raid);

		float frintRaid = 0.5f - (raid * 0.3f);
		float backRaid = 0.5f + (raid * 0.3f);

		float AllPower = abs_float(m_CH3508_1_t.PID_S.all_out) + abs_float(m_CH3508_2_t.PID_S.all_out)
			+ abs_float(m_CH3508_3_t.PID_S.all_out) + abs_float(m_CH3508_4_t.PID_S.all_out);

		float frintAllPower = abs_float(m_CH3508_1_t.PID_S.all_out) + abs_float(m_CH3508_2_t.PID_S.all_out);
		float backAllPower  = abs_float(m_CH3508_3_t.PID_S.all_out) + abs_float(m_CH3508_4_t.PID_S.all_out);

		float frintPower = frintRaid * AllPower;
		float backPower  = backRaid * AllPower;

		m_CH3508_1_t.PID_S.all_out = (m_CH3508_1_t.PID_S.all_out / frintAllPower) * frintPower;
		m_CH3508_2_t.PID_S.all_out = (m_CH3508_2_t.PID_S.all_out / frintAllPower) * frintPower;

		m_CH3508_3_t.PID_S.all_out = (m_CH3508_3_t.PID_S.all_out / backAllPower) * backPower;
		m_CH3508_4_t.PID_S.all_out = (m_CH3508_4_t.PID_S.all_out / backAllPower) * backPower;
	}
}
/************************************************************���ָܷ���**************************************************************
*	@author:			//����
*	@performance:	//���̽�����̨CAN����
*	@parameter:		//��Ҫ���������
*	@time:				//22-01-03
*	@ReadMe:			//���յ������ݷŵ��˵��̽ṹ������
								//Э�飺[0][1] = vx  ||  [2][3] = vy  ||  [4][5] = vr
												[6] : {1}:�Ƿ�ʹ�ó������� {2}��ң���Ƿ����� {34}�����̵�����״̬
												[7] ����
************************************************************************************************************************************/
int rui_temp1 = 0 , rui_temp2 = 0 , rui_temp3 = 0;
uint8_t ChassisRXResolve(uint8_t* data)
{
	CanCommunit_t.gmTOch.getData[0] = data[0];
	CanCommunit_t.gmTOch.getData[1] = data[1];
	CanCommunit_t.gmTOch.getData[2] = data[2];
	CanCommunit_t.gmTOch.getData[3] = data[3];
	CanCommunit_t.gmTOch.getData[4] = data[4];
	CanCommunit_t.gmTOch.getData[5] = data[5];
	CanCommunit_t.gmTOch.getData[6] = data[6];
	CanCommunit_t.gmTOch.getData[7] = data[7];
	//��ֵ��ң��	
	rc_ctrl.control.ch0_int16 = CanCommunit_t.gmTOch.dataNeaten.vx;
	rc_ctrl.control.ch1_int16 = CanCommunit_t.gmTOch.dataNeaten.vy;
	rc_ctrl.control.direction = CanCommunit_t.gmTOch.dataNeaten.vr * 2.0f;
	rc_ctrl.key_board.c = CanCommunit_t.gmTOch.dataNeaten.key_c;
	rc_ctrl.key_board.ctrl = CanCommunit_t.gmTOch.dataNeaten.key_ctrl;

	//�����Ǽ��
	root_t.topRoot.state = CanCommunit_t.gmTOch.dataNeaten.topSate;
	if (CanCommunit_t.gmTOch.dataNeaten.topSate == 1)
	{
		root_t.topRoot.time = 0;
	}


	if (CanCommunit_t.gmTOch.dataNeaten.romoteOnLine == df_onLine)
	{		//ң�ض�ʧ���
		root_t.remoteRoot.time = 0;
	}
	return df_re_ok;
}
/************************************************************���ָܷ���**************************************************************
*	@author:			//����
*	@performance:	//���̸���̨��CAN���ͽ��㺯��
*	@parameter:		//��ŷ��͵�����
*	@time:				//22-01-04
*	@ReadMe:			//�������֮�����ݿ���ֱ��CAN����
								//Э�飺��һ������
												[12] pitchAngle [34] yawAngle	[4567] ʱ����
												�ڶ�������
												[12] ǹ������
												[3] �������
												[4]	��ǰ����
												[5]	{1}�Ӿ��Ƿ�ʶ��Ŀ�� {234} �Ӿ��ĵ�ǰ״̬ {5}�Ӿ��Ƿ����� {6}����ϵͳ�Ƿ�����
* @UpData:          //С�� 2023-04-20 01:08 CanCommunit_t.chTOgm.dataNeaten_another.visionMod���Ҹ�Ϊ������ɫ
************************************************************************************************************************************/
uint8_t ChassisTXResolve(uint8_t boll)
{
		//��Э��
	if (boll == 0)
	{
//��һ֡
		CanCommunit_t.chTOgm.dataNeaten_angle.pitch = SectionLimit_i(30000 , -30000 , (visionData_t.receive.pitchAngle[df_now] * 100));
		CanCommunit_t.chTOgm.dataNeaten_angle.yaw 	= SectionLimit_i(30000 , -30000 , (visionData_t.receive.yawAngle[df_now] * 100));
		CanCommunit_t.chTOgm.dataNeaten_angle.time	= (float) RunTime;
	}
	else
	{
//		if (twoJudgeData.RoboSate.color == 2) twoJudgeData.RoboSate.color = 0;
//		//�ڶ�֡				
//		CanCommunit_t.chTOgm.dataNeaten_another.muzzleColing = twoJudgeData.muzzle.maxCooling - twoJudgeData.muzzle.nowCooling;	//ʣ��ǹ������
//		CanCommunit_t.chTOgm.dataNeaten_another.maxSpeed = twoJudgeData.muzzle.maxShootSpeed;	//�������
//		CanCommunit_t.chTOgm.dataNeaten_another.nowSpeed = twoJudgeData.muzzle.shootSpeed; //��ǰ����
//		CanCommunit_t.chTOgm.dataNeaten_another.target = twoJudgeData.RoboSate.color & 0x01;		//�Ӿ��Ƿ�ʶ��Ŀ��//���Ҹ�Ϊ������ɫ
//		CanCommunit_t.chTOgm.dataNeaten_another.visionMod = visionData_t.receive.visionState;		//�Ӿ��ĵ�ǰ״̬
//		CanCommunit_t.chTOgm.dataNeaten_another.visionState = root_t.visionRoot.communicat;		//�Ӿ�������Ϣ
//		CanCommunit_t.chTOgm.dataNeaten_another.judgeState = 1;//root_t.judgeRoot.communicat;		//����ϵͳ������Ϣ
	}
	return df_re_ok;
}
/************************************************************���ָܷ���**************************************************************
*	@author:			//С��
*	@performance: //�������̸���PID��ʼ������
*	@parameter:		//
*	@time:				//22-5-22
* @LastUpDataTime:  //2022-05-23 12:58    by С��
* @UpData�� //
*	@ReadMe:		//˫��PID
************************************************************************************************************************************/
uint8_t CHFollowPID_Init(void)
{
								//kp			//ki		//kd		//iLimit	//alLimit
	float PID_P[5] ={ 20,	0.1,			25,			40,				  250 };
//	float PID_S[5] ={ 30,			0.1,			0.1,			30,				15000 };
	uint8_t i = 0;

	i = 0;
	chassis_t.CHF_PID_P.Kp = PID_P[i++];
	chassis_t.CHF_PID_P.Ki = PID_P[i++];
	chassis_t.CHF_PID_P.Kd = PID_P[i++];
	chassis_t.CHF_PID_P.ILt = PID_P[i++];
	chassis_t.CHF_PID_P.AlLt = PID_P[i++];
//	i = 0;
//	chassis_t.CHF_PID_S.Kp = PID_S[i++];
//	chassis_t.CHF_PID_S.Ki = PID_S[i++];
//	chassis_t.CHF_PID_S.Kd = PID_S[i++];
//	chassis_t.CHF_PID_S.ILt = PID_S[i++];
//	chassis_t.CHF_PID_S.AlLt = PID_S[i++];

	return df_re_ok;
}
/************************************************************���ָܷ���**************************************************************
*	@author:			//С��
*	@performance: //�������̸���PID
*	@parameter:		
*	@time:				//22-5-22
* @UpData:          //С���� 2022-05-26 19:10 �ı����ٶȻ�����ʵֵ
* @LastUpDataTime:  //2022-05-25 21:10    by С��
* @UpData�� //ȡ�����PID
* @UpData�� //��ͼ������PID
* @UpData�� //��ͼ�ӻ�����Ŀ   by����
* @UpData�� //�ĳ��˵���
*	@ReadMe:		//˫��PID
************************************************************************************************************************************/
void CHFollowTwoPID(struct chassis_typedef* CHFollow)
{
	float iLitAdd = abs_float(CHFollow->speed.vx_int16) + abs_float(CHFollow->speed.vy_int16);
	iLitAdd *= 0.05f;
	/**************************�ǶȻ�����**************************/
	CHFollow->CHF_PID_P.Error[df_now] = m_GM6020_y_t.data.ralativeAngle;

	//�������
	CHFollow->CHF_PID_P.P_out = (CHFollow->CHF_PID_P.Error[df_now] * CHFollow->CHF_PID_P.Kp);
	//΢�����
	CHFollow->CHF_PID_P.D_out = (CHFollow->CHF_PID_P.Error[df_now] - CHFollow->CHF_PID_P.Error[df_last]) * CHFollow->CHF_PID_P.Kd;
	//�������
	CHFollow->CHF_PID_P.I_out += (CHFollow->CHF_PID_P.Error[df_now] * CHFollow->CHF_PID_P.Ki);
	CHFollow->CHF_PID_P.I_out += CHFollow->CHF_PID_P.D_out;
	//�����޷�
	CHFollow->CHF_PID_P.I_out = SectionLimit_f(CHFollow->CHF_PID_P.ILt + iLitAdd , -CHFollow->CHF_PID_P.ILt - iLitAdd , CHFollow->CHF_PID_P.I_out);
	//���ݵ���
	CHFollow->CHF_PID_P.Error[df_last] = CHFollow->CHF_PID_P.Error[df_now];
	//�ǶȻ������
	CHFollow->CHF_PID_P.All_out = (CHFollow->CHF_PID_P.P_out + CHFollow->CHF_PID_P.I_out +CHFollow->CHF_PID_P.D_out);
	//������޷�
	CHFollow->CHF_PID_P.All_out = SectionLimit_i(CHFollow->CHF_PID_P.AlLt , -CHFollow->CHF_PID_P.AlLt , CHFollow->CHF_PID_P.All_out);

	CHFollow->speed.vr_int16 = CHFollow->CHF_PID_P.All_out;
}

/************************************************************���ָܷ���**************************************************************
*	@author:			//����
*	@performance: //���ʷ���ʵ��汾
*	@parameter:		//������
*	@time:				//22-6-5
*	@ReadMe:			//�����ֵ�����޷�
************************************************************************************************************************************/

void PowerAllot(int32_t maxPower)
{
	float raid = 0.0f;		//ͬ�Ƚ��͵ķ���
	int32_t maxOut = 0;		//��ǰ��õ�������
	
	//�����ֵ
	if (abs_float(m_CH3508_1_t.PID_S.all_out) > maxOut)
	{
		maxOut = m_CH3508_1_t.PID_S.all_out;
	}
	if (abs_float(m_CH3508_2_t.PID_S.all_out) > maxOut)
	{
		maxOut = m_CH3508_2_t.PID_S.all_out;
	}
	if (abs_float(m_CH3508_3_t.PID_S.all_out) > maxOut)
	{
		maxOut = m_CH3508_3_t.PID_S.all_out;
	}
	if (abs_float(m_CH3508_4_t.PID_S.all_out) > maxOut)
	{
		maxOut = m_CH3508_4_t.PID_S.all_out;
	}

	raid = (float) maxPower/(float) maxOut;
	raid = SectionLimit_f(1.0f , 0.1f , raid);

	m_CH3508_1_t.PID_S.all_out *= raid;
	m_CH3508_2_t.PID_S.all_out *= raid;
	m_CH3508_3_t.PID_S.all_out *= raid;
	m_CH3508_4_t.PID_S.all_out *= raid;
}



