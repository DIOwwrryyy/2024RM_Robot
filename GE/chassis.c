#include "chassis.h"
#include "user_define.h"		//用于操作手自定义数据
struct chassis_typedef chassis_t ={ 0 };
RC_ctrl_t rc_ctrl;
struct visionData_typdef visionData_t;
/************************************************************步兵底盘总函数**************************************************************
*	@author:			    //赵澍
*	@performance:      	//步兵底盘总函数
*	@parameter:		    //陀螺仪状态
*	@time:				     //21-12-31
* @LastUpDataTime:  //2022-05-26 18:57    by 小瑞
* @UpData：         //地盘跟随取消PID
* @UpData：         //增加了打符模式下地盘不跟随
* @UpData           //地盘跟随换成了PID
*	@ReadMe:			//左负右正//前正后负//顺正逆负
								 矢量表     	//箭头代表每一个麦轮的分力方向，数字带表ID
								↑  ||  ↑
								1→ || ←2	.
								—————————   X轴
								4→ || ←3
								↓  ||  ↓
									车尾
								//目前仅仅支持到速度环
************************************************************************************************************************************/
float allOutPower = 0;
void CHInfantry(uint8_t topStata)
{
	double angle = 0.0;
	float speedRaid = 0.0f;
	
//		float riadFollow = 0.0f;		//底盘降差函数 
		//得到云台和底盘的相对角
	angle = m_GM6020_y_t.data.ralativeAngle * 0.0174444f;			//转化到弧度上

	//确定系数
	if (CanCommunit_t.gmTOch.dataNeaten.supUSe == df_open)
	{
		speedRaid = chassis_t.superCap.superCapRaid;
	}
	else
	{
		speedRaid = chassis_t.superCap.normalRaid;
	}

	//方便后面使用
	chassis_t.speed.vx_int16 = rc_ctrl.control.ch0_int16 * speedRaid;
	chassis_t.speed.vy_int16 = -rc_ctrl.control.ch1_int16 * speedRaid;
	chassis_t.speed.vr_int16 = rc_ctrl.control.direction * speedRaid/2.0f;



	//小陀螺模式下的一些处理 
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
	{		//底盘不跟随

	}
	else if (CanCommunit_t.gmTOch.dataNeaten.CHfollow == 1)
	{//底盘跟随
CHFollowTwoPID(&chassis_t);	
	}
//脉轮解算
	if (root_t.Init_t.chassisInit == df_re_ok)
	{
		MecanumResolve(chassis_t.speed.vx_int16 , chassis_t.speed.vy_int16 , chassis_t.speed.vr_int16 , angle);
	}
	else
	{	//新麦轮解算的初始化函数
		root_t.Init_t.chassisInit = CHInfantryInit();
	}

	//PID解算
	CHMotorSpeedPID(&m_CH3508_1_t);
	CHMotorSpeedPID(&m_CH3508_2_t);
	CHMotorSpeedPID(&m_CH3508_3_t);
	CHMotorSpeedPID(&m_CH3508_4_t);

	allOutPower = abs_float(m_CH3508_1_t.PID_S.all_out) + abs_float(m_CH3508_2_t.PID_S.all_out) + \
		abs_float(m_CH3508_3_t.PID_S.all_out) + abs_float(m_CH3508_4_t.PID_S.all_out);
//功率分配函数
	PowerAllot(10000);

	//*功率限制部分*//
	if (root_t.superCapRoot.communicat == 0)
	{		//超级电容离线后的处理
		PowerLimBuffer(judge_user_data.power_heat_data.buffer_energy , (int32_t) allOutPower);
//				SuperCapTransation(CanCommunit_t.gmTOch.dataNeaten.supUSe , (int32_t) allOutPower , RunTime);

	}
	else if (root_t.superCapRoot.communicat == 1)
	{		//超级电容在线
      //电容下的功率限制
		SuperCapTransation(CanCommunit_t.gmTOch.dataNeaten.supUSe , (int32_t) allOutPower , RunTime);
	}
}
/************************************************************万能分隔符**************************************************************
*	@author:			//
*	@performance:	//底盘锁死函数
*	@parameter:		//slow慢锁模式\quick快锁模式
*	@time:				//
*	@ReadMe:			//缓停模式，保护电机\快锁模式，会记录锁死位置
************************************************************************************************************************************/
void CHSpeedLock(uint8_t mod)
{
		//转换模式数据清空
	if (chassis_t.mods[df_now] != chassis_t.mods[df_last])
	{
		MotorReast3508(&m_CH3508_1_t);
		MotorReast3508(&m_CH3508_2_t);
		MotorReast3508(&m_CH3508_3_t);
		MotorReast3508(&m_CH3508_4_t);
		//为了程序安全性放在了if里面
		//防止因为中断而无法执行清零
		chassis_t.mods[df_last] = chassis_t.mods[df_now];
	}

	if (mod == df_solwLock)
	{
			//慢锁设置
		m_CH3508_1_t.data.aim = m_CH3508_1_t.data.reality;
		m_CH3508_2_t.data.aim = m_CH3508_2_t.data.reality;
		m_CH3508_3_t.data.aim = m_CH3508_3_t.data.reality;
		m_CH3508_4_t.data.aim = m_CH3508_4_t.data.reality;
	}
	else if (mod == df_quickLock)
	{

	}
	//PID解算
	CHMotorTwoPID(&m_CH3508_1_t);
	CHMotorTwoPID(&m_CH3508_2_t);
	CHMotorTwoPID(&m_CH3508_3_t);
	CHMotorTwoPID(&m_CH3508_4_t);
}
/************************************************************万能分隔符**************************************************************
*	@author:			//赵澍
*	@performance:	//带偏移量的
*	@parameter:		//入口参数是四个目标值的地址指针
								//返还值:是否初始化成功
*	@time:				//21-12-30
*	@ReadMe:			//使用麦轮解算之前，要先进行一次初始化
								 矢量表     	//箭头代表每一个麦轮的分力方向，数字带表ID
								↑  ||  ↑
								2→ || ←1
								—————————
								3→ || ←4
								↓  ||  ↓
									车尾
************************************************************************************************************************************/
struct mecanumInit_typdef mecanumInit_t ={ 0 };		//初始化使用的机构体
static float* mecanumOutAddre[4] ={ 0 };		//给后面的解算使用
uint8_t MecanumInit(void)
{
	mecanumOutAddre[0] = &m_CH3508_1_t.data.aim;		//对应每个电机的目标值
	mecanumOutAddre[1] = &m_CH3508_2_t.data.aim;
	mecanumOutAddre[2] = &m_CH3508_3_t.data.aim;
	mecanumOutAddre[3] = &m_CH3508_4_t.data.aim;

	mecanumInit_t.deceleration_ratio = 0.052075f;		//减速比1/19
	mecanumInit_t.max_vw_speed = 50000;		//r方向上的最大速度单位：毫米/秒
	mecanumInit_t.max_vx_speed = 50000;		//x方向上的最大速度单位：毫米/秒
	mecanumInit_t.max_vy_speed = 50000;		//y方向上的最大速度单位：毫米/秒
	mecanumInit_t.max_wheel_ramp = 8000;		//3508最大转速不包含限速箱
	mecanumInit_t.rotate_x_offset = 00.0f;		//云台在x轴的偏移量  mm
	mecanumInit_t.rotate_y_offset = 00.0f;		//云台在y轴的偏移量  mm
	mecanumInit_t.wheelbase = 300;		//轮距	mm
	mecanumInit_t.wheeltrack = 300;		//轴距	mm
	mecanumInit_t.wheel_perimeter = 478;	//轮子的周长(mm)


	/*计算旋转比率*/
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
//将算出来的数据转化到转每分钟上去 raid = 60/(电机减速比*轮的周长)			
	mecanumInit_t.wheel_rpm_ratio =	60.0f / (mecanumInit_t.wheel_perimeter * mecanumInit_t.deceleration_ratio);

	return df_re_ok;
}

/************************************************************万能分隔符**************************************************************
*	@author:			//赵澍
*	@performance:	//带中心点的麦轮解算。可以让车辆绕着一个中心点转动,在移动时保证以操作手为正方向
*	@parameter:		//平移速度//前进速度//旋转速度//云台与底盘的相对角度(弧度制)
*	@time:				//21-12-30
*	@ReadMe:			//左负右正//前正后负//顺正逆负
								//带有中心偏移量，可以调节旋转中心
								//要在初始化函数结束之后才能调用
								 矢量表     	//箭头代表每一个麦轮的分力方向，数字带表ID
								↑  ||  ↑
								2→ || ←1
								—————————   Y轴  左正右负，上正下负
								3→ || ←4
								↓  ||  ↓
									车尾
								//目前仅仅支持到速度环
************************************************************************************************************************************/
int8_t rui = 0;
//目前输出的是带减速箱的可能导致转速过快
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
		//旋转之后会导致减震两边不一致//只有步兵才打开
		mecanumInit_t.rotate_y_offset = -3 * ((float) vr /700);
	}
	else if (rui == 1)
	{
		mecanumInit_t.rotate_y_offset = 0.0f;
	}
	/*计算旋转比率*/
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
//将算出来的数据转化到转每分钟上去 raid = 60/(电机减速比*轮的周长)			
	mecanumInit_t.wheel_rpm_ratio =	60.0f / (mecanumInit_t.wheel_perimeter * mecanumInit_t.deceleration_ratio);

	if (angle == 0)
	{			//防止角度为零，产生误差//待测试
		angle = 0.0001f;
	}
	//得到相对角度的sin，cos
	angleSin = sin(angle);
	angleCos = cos(angle);
	//得到转化后的vx,vy,vr
	vx = -vx_temp * angleSin + vy_temp * angleCos;
	vy = 	vx_temp * angleCos + vy_temp * angleSin;

	wheel_rpm[0] = (-vx + vy - vr * mecanumInit_t.raid_fr) * mecanumInit_t.wheel_rpm_ratio;
	wheel_rpm[1] = (vx + vy - vr * mecanumInit_t.raid_fl) * mecanumInit_t.wheel_rpm_ratio;
	wheel_rpm[2] = (vx - vy - vr * mecanumInit_t.raid_bl) * mecanumInit_t.wheel_rpm_ratio;
	wheel_rpm[3] = (-vx - vy - vr * mecanumInit_t.raid_br) * mecanumInit_t.wheel_rpm_ratio;
	//寻找四个轮子里面的最大值		
	for (uint8_t i = 0; i < 4; i++)
	{
		if (fabs(wheel_rpm[i]) > max)
			max = fabs(wheel_rpm[i]);
	}
	//如果超出了最大值，则进行等比例降速
	if (max > mecanumInit_t.max_wheel_ramp)
	{
		float rate = mecanumInit_t.max_wheel_ramp / max;
		for (uint8_t i = 0; i < 4; i++)
			wheel_rpm[i] *= rate;
	}
	//赋值
	*mecanumOutAddre[0] = wheel_rpm[0];
	*mecanumOutAddre[1] = wheel_rpm[1];
	*mecanumOutAddre[2] = wheel_rpm[2];
	*mecanumOutAddre[3] = wheel_rpm[3];
}
/************************************************************万能分隔符**************************************************************
*	@author:			//赵澍
*	@performance:	//步兵底盘总函数初始化函数
*	@parameter:		//模式//陀螺仪状态
*	@time:				//21-12-31
* @LastUpDataTime:  //2022-05-23 17:14    by 小瑞
* @UpData： //增加了跟随PID初始化
*	@ReadMe:			//只需要执行一次，但是在使用底盘总函数之前必须完成一次初始化
								//在这边配置每一个速度和推杆的对应关系
************************************************************************************************************************************/
uint8_t CHInfantryInit(void)
{
	chassis_t.superCap.normalRaid = 3.50f;			//普通模式下的系数
	chassis_t.superCap.slowRaid = 0.5f;
	chassis_t.superCap.slowKeyRaid = 330.0f;
	chassis_t.superCap.superCapRaid = 8.0f;		//超级电容模式下的倍增系数

	CH3508M_Init();
	CHFollowPID_Init();

	return df_re_ok;
}
/************************************************************万能分隔符**************************************************************
*	@author:			//赵澍
*	@performance:	//步兵底盘电机清空判断
*	@parameter:		//模式
*	@time:				//21-12-31
*	@ReadMe:			//当两次运行状态不一样时函数会执行清空
************************************************************************************************************************************/
void CHEmptyJudge(uint8_t mod)
{
	chassis_t.mods[df_now] = mod;
	if (chassis_t.mods[df_now] != chassis_t.mods[df_last])
	{
		//清空
		MotorReast3508(&m_CH3508_1_t);
		MotorReast3508(&m_CH3508_2_t);
		MotorReast3508(&m_CH3508_3_t);
		MotorReast3508(&m_CH3508_4_t);
		//状态迭代
		chassis_t.mods[df_last] = chassis_t.mods[df_now];
	}
}
/************************************************************万能分隔符**************************************************************
*	@author:			//赵澍
*	@performance:	//上坡检测函数
*	@parameter:		//陀螺仪角度pitch轴
*	@time:				//22-03-24
*	@ReadMe:			//在最后进行功率分配
								//角度检测版本
************************************************************************************************************************************/
void UpHill(float topAngle)
{
	float relativeAngle = m_GM6020_p_t.data.ralativeAngle;	//云台和底盘的相对角
	float AngleCH = (topAngle/10.0f) - relativeAngle;		//底盘和地面的猜测角度

//		AngleCH = AngleCH * ( -(m_GM6020_y_t.data.ralativeAngle - 90.0f) / 90.0f);	//底盘和地面的实际角度//近似拟合

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
/************************************************************万能分隔符**************************************************************
*	@author:			//赵澍
*	@performance:	//底盘接收云台CAN解算
*	@parameter:		//需要解算的数组
*	@time:				//22-01-03
*	@ReadMe:			//接收到的数据放到了底盘结构体里面
								//协议：[0][1] = vx  ||  [2][3] = vy  ||  [4][5] = vr
												[6] : {1}:是否使用超级电容 {2}：遥控是否在线 {34}：底盘的期望状态
												[7] 空闲
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
	//赋值给遥控	
	rc_ctrl.control.ch0_int16 = CanCommunit_t.gmTOch.dataNeaten.vx;
	rc_ctrl.control.ch1_int16 = CanCommunit_t.gmTOch.dataNeaten.vy;
	rc_ctrl.control.direction = CanCommunit_t.gmTOch.dataNeaten.vr * 2.0f;
	rc_ctrl.key_board.c = CanCommunit_t.gmTOch.dataNeaten.key_c;
	rc_ctrl.key_board.ctrl = CanCommunit_t.gmTOch.dataNeaten.key_ctrl;

	//陀螺仪检测
	root_t.topRoot.state = CanCommunit_t.gmTOch.dataNeaten.topSate;
	if (CanCommunit_t.gmTOch.dataNeaten.topSate == 1)
	{
		root_t.topRoot.time = 0;
	}


	if (CanCommunit_t.gmTOch.dataNeaten.romoteOnLine == df_onLine)
	{		//遥控丢失检测
		root_t.remoteRoot.time = 0;
	}
	return df_re_ok;
}
/************************************************************万能分隔符**************************************************************
*	@author:			//赵澍
*	@performance:	//底盘给云台的CAN发送解算函数
*	@parameter:		//存放发送的数组
*	@time:				//22-01-04
*	@ReadMe:			//运行完成之后数据可以直接CAN发送
								//协议：第一个数组
												[12] pitchAngle [34] yawAngle	[4567] 时间轴
												第二个数组
												[12] 枪口热量
												[3] 最大射速
												[4]	当前射速
												[5]	{1}视觉是否识别到目标 {234} 视觉的当前状态 {5}视觉是否离线 {6}裁判系统是否离线
* @UpData:          //小瑞 2023-04-20 01:08 CanCommunit_t.chTOgm.dataNeaten_another.visionMod被我改为车辆颜色
************************************************************************************************************************************/
uint8_t ChassisTXResolve(uint8_t boll)
{
		//新协议
	if (boll == 0)
	{
//第一帧
		CanCommunit_t.chTOgm.dataNeaten_angle.pitch = SectionLimit_i(30000 , -30000 , (visionData_t.receive.pitchAngle[df_now] * 100));
		CanCommunit_t.chTOgm.dataNeaten_angle.yaw 	= SectionLimit_i(30000 , -30000 , (visionData_t.receive.yawAngle[df_now] * 100));
		CanCommunit_t.chTOgm.dataNeaten_angle.time	= (float) RunTime;
	}
	else
	{
//		if (twoJudgeData.RoboSate.color == 2) twoJudgeData.RoboSate.color = 0;
//		//第二帧				
//		CanCommunit_t.chTOgm.dataNeaten_another.muzzleColing = twoJudgeData.muzzle.maxCooling - twoJudgeData.muzzle.nowCooling;	//剩余枪口热量
//		CanCommunit_t.chTOgm.dataNeaten_another.maxSpeed = twoJudgeData.muzzle.maxShootSpeed;	//最大射速
//		CanCommunit_t.chTOgm.dataNeaten_another.nowSpeed = twoJudgeData.muzzle.shootSpeed; //当前射速
//		CanCommunit_t.chTOgm.dataNeaten_another.target = twoJudgeData.RoboSate.color & 0x01;		//视觉是否识别到目标//被我改为车辆颜色
//		CanCommunit_t.chTOgm.dataNeaten_another.visionMod = visionData_t.receive.visionState;		//视觉的当前状态
//		CanCommunit_t.chTOgm.dataNeaten_another.visionState = root_t.visionRoot.communicat;		//视觉离线信息
//		CanCommunit_t.chTOgm.dataNeaten_another.judgeState = 1;//root_t.judgeRoot.communicat;		//裁判系统离线信息
	}
	return df_re_ok;
}
/************************************************************万能分隔符**************************************************************
*	@author:			//小瑞
*	@performance: //步兵底盘跟随PID初始化函数
*	@parameter:		//
*	@time:				//22-5-22
* @LastUpDataTime:  //2022-05-23 12:58    by 小瑞
* @UpData： //
*	@ReadMe:		//双环PID
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
/************************************************************万能分隔符**************************************************************
*	@author:			//小瑞
*	@performance: //步兵底盘跟随PID
*	@parameter:		
*	@time:				//22-5-22
* @UpData:          //小瑞于 2022-05-26 19:10 改变了速度环的真实值
* @LastUpDataTime:  //2022-05-25 21:10    by 小瑞
* @UpData： //取消变参PID
* @UpData： //试图加入变参PID
* @UpData： //试图加积分项目   by赵澍
* @UpData： //改成了单环
*	@ReadMe:		//双环PID
************************************************************************************************************************************/
void CHFollowTwoPID(struct chassis_typedef* CHFollow)
{
	float iLitAdd = abs_float(CHFollow->speed.vx_int16) + abs_float(CHFollow->speed.vy_int16);
	iLitAdd *= 0.05f;
	/**************************角度环处理**************************/
	CHFollow->CHF_PID_P.Error[df_now] = m_GM6020_y_t.data.ralativeAngle;

	//比例输出
	CHFollow->CHF_PID_P.P_out = (CHFollow->CHF_PID_P.Error[df_now] * CHFollow->CHF_PID_P.Kp);
	//微分输出
	CHFollow->CHF_PID_P.D_out = (CHFollow->CHF_PID_P.Error[df_now] - CHFollow->CHF_PID_P.Error[df_last]) * CHFollow->CHF_PID_P.Kd;
	//积分输出
	CHFollow->CHF_PID_P.I_out += (CHFollow->CHF_PID_P.Error[df_now] * CHFollow->CHF_PID_P.Ki);
	CHFollow->CHF_PID_P.I_out += CHFollow->CHF_PID_P.D_out;
	//积分限幅
	CHFollow->CHF_PID_P.I_out = SectionLimit_f(CHFollow->CHF_PID_P.ILt + iLitAdd , -CHFollow->CHF_PID_P.ILt - iLitAdd , CHFollow->CHF_PID_P.I_out);
	//数据迭代
	CHFollow->CHF_PID_P.Error[df_last] = CHFollow->CHF_PID_P.Error[df_now];
	//角度环总输出
	CHFollow->CHF_PID_P.All_out = (CHFollow->CHF_PID_P.P_out + CHFollow->CHF_PID_P.I_out +CHFollow->CHF_PID_P.D_out);
	//总输出限幅
	CHFollow->CHF_PID_P.All_out = SectionLimit_i(CHFollow->CHF_PID_P.AlLt , -CHFollow->CHF_PID_P.AlLt , CHFollow->CHF_PID_P.All_out);

	CHFollow->speed.vr_int16 = CHFollow->CHF_PID_P.All_out;
}

/************************************************************万能分隔符**************************************************************
*	@author:			//赵澍
*	@performance: //功率分配实验版本
*	@parameter:		//最大输出
*	@time:				//22-6-5
*	@ReadMe:			//对输出值做了限幅
************************************************************************************************************************************/

void PowerAllot(int32_t maxPower)
{
	float raid = 0.0f;		//同比降低的幅度
	int32_t maxOut = 0;		//当前求得的最大输出
	
	//求最大值
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



