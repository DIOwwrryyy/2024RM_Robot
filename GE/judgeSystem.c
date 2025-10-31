#include "judgeSystem.h"
#include "user_define.h"
#include "switch.h"
#include "root.h"
#include "superCap.h"


//*UI数据*//
hypTypedef hyp={ 0 };
ziTypedef zi={ 0 };
dianrongTypedef dianrong={ 0 };
tuoluoTypedef  tuoluo={ 0 };
tupTypedef tup={ 0 };
uint8_t Judge_Self_ID;        //当前机器人ID
uint16_t Judge_SelfClient_ID; //发送者机器人对应的客户端ID
//*UI数据*//

struct twoJudgeData_typedef twoJudgeData ={ 0 };		//二次处理后的裁判系统数据
const unsigned char CRC8_INIT = 0xff;
uint8_t JudgeDataBuffer[JudgeBufferLength]={ 0 };
uint8_t JudgeDataBuffer_Send[JudgeBufferLength]={ 0 };
/***********************************    ↓    DJI提供的CRC校检函数   ↓  ***********************************/
//crc8 generator polynomial:G(x)=x8+x5+x4+1																						/*帧头*/             /*命令码*/  /*数据段id*/ /*发送id*/  /*接收id*/  /*数据1  数据2    数据3    灯   校验id*/
uint8_t client_custom_Send[client_custom_Length]={ 0xA5,0x13,0,0,0x6D,  0x01,0x03,  0x80,0xD1,   0x00,0x00,  0x00,0x00,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,    0,0 };
uint8_t  robot_custom_Send[client_custom_Length]={ 0xA5,0x13,0,0,0x6D,  0x01,0x03,  0x00,0x02,   0x00,0x00,  0x00,0x02,  0,0,1,1, 0,0,0,0, 0,0,0,0, 0,    0,0 };
JudgementDataTypedef JudgementData={ 0 };
const unsigned char CRC8_TAB[256] =
{
	0x00, 0x5e, 0xbc, 0xe2, 0x61, 0x3f, 0xdd, 0x83, 0xc2, 0x9c, 0x7e, 0x20, 0xa3, 0xfd, 0x1f, 0x41,
	0x9d, 0xc3, 0x21, 0x7f, 0xfc, 0xa2, 0x40, 0x1e, 0x5f, 0x01, 0xe3, 0xbd, 0x3e, 0x60, 0x82, 0xdc,
	0x23, 0x7d, 0x9f, 0xc1, 0x42, 0x1c, 0xfe, 0xa0, 0xe1, 0xbf, 0x5d, 0x03, 0x80, 0xde, 0x3c, 0x62,
	0xbe, 0xe0, 0x02, 0x5c, 0xdf, 0x81, 0x63, 0x3d, 0x7c, 0x22, 0xc0, 0x9e, 0x1d, 0x43, 0xa1, 0xff,
	0x46, 0x18, 0xfa, 0xa4, 0x27, 0x79, 0x9b, 0xc5, 0x84, 0xda, 0x38, 0x66, 0xe5, 0xbb, 0x59, 0x07,
	0xdb, 0x85, 0x67, 0x39, 0xba, 0xe4, 0x06, 0x58, 0x19, 0x47, 0xa5, 0xfb, 0x78, 0x26, 0xc4, 0x9a,
	0x65, 0x3b, 0xd9, 0x87, 0x04, 0x5a, 0xb8, 0xe6, 0xa7, 0xf9, 0x1b, 0x45, 0xc6, 0x98, 0x7a, 0x24,
	0xf8, 0xa6, 0x44, 0x1a, 0x99, 0xc7, 0x25, 0x7b, 0x3a, 0x64, 0x86, 0xd8, 0x5b, 0x05, 0xe7, 0xb9,
	0x8c, 0xd2, 0x30, 0x6e, 0xed, 0xb3, 0x51, 0x0f, 0x4e, 0x10, 0xf2, 0xac, 0x2f, 0x71, 0x93, 0xcd,
	0x11, 0x4f, 0xad, 0xf3, 0x70, 0x2e, 0xcc, 0x92, 0xd3, 0x8d, 0x6f, 0x31, 0xb2, 0xec, 0x0e, 0x50,
	0xaf, 0xf1, 0x13, 0x4d, 0xce, 0x90, 0x72, 0x2c, 0x6d, 0x33, 0xd1, 0x8f, 0x0c, 0x52, 0xb0, 0xee,
	0x32, 0x6c, 0x8e, 0xd0, 0x53, 0x0d, 0xef, 0xb1, 0xf0, 0xae, 0x4c, 0x12, 0x91, 0xcf, 0x2d, 0x73,
	0xca, 0x94, 0x76, 0x28, 0xab, 0xf5, 0x17, 0x49, 0x08, 0x56, 0xb4, 0xea, 0x69, 0x37, 0xd5, 0x8b,
	0x57, 0x09, 0xeb, 0xb5, 0x36, 0x68, 0x8a, 0xd4, 0x95, 0xcb, 0x29, 0x77, 0xf4, 0xaa, 0x48, 0x16,
	0xe9, 0xb7, 0x55, 0x0b, 0x88, 0xd6, 0x34, 0x6a, 0x2b, 0x75, 0x97, 0xc9, 0x4a, 0x14, 0xf6, 0xa8,
	0x74, 0x2a, 0xc8, 0x96, 0x15, 0x4b, 0xa9, 0xf7, 0xb6, 0xe8, 0x0a, 0x54, 0xd7, 0x89, 0x6b, 0x35,
};


uint8_t Get_CRC8_Check_Sum(uint8_t* pchMessage , uint16_t dwLength , uint8_t ucCRC8)
{
	uint8_t ucIndex;

	while (dwLength--)
	{
		ucIndex = ucCRC8^(*pchMessage++);
		ucCRC8 = CRC8_TAB[ucIndex];
	}
	return ucCRC8;
}


/*
** Descriptions: CRC8 Verify function
** Input: Data to Verify,Stream length = Data + checksum
** Output: True or False (CRC Verify Result)
*/
uint32_t Verify_CRC8_Check_Sum(uint8_t* pchMessage , uint16_t dwLength)
{
	uint8_t ucExpected = 0;

	if (pchMessage == 0 || dwLength <= 2)
	{
		return 0;
	}

	ucExpected = Get_CRC8_Check_Sum(pchMessage , dwLength-1 , CRC8_INIT);

	return (ucExpected == pchMessage[dwLength-1]);
}

/*
** Descriptions: append CRC8 to the end of data
** Input: Data to CRC and append,Stream length = Data + checksum
** Output: True or False (CRC Verify Result)
*/
uint8_t ucCRC = 0;
void Append_CRC8_Check_Sum(uint8_t* pchMessage , uint16_t dwLength)
{
	ucCRC=0;

	if (pchMessage == 0 || dwLength <= 2)
	{
		return;
	}

	ucCRC = Get_CRC8_Check_Sum((uint8_t*) pchMessage , dwLength-1 , CRC8_INIT);

	pchMessage[dwLength-1] = ucCRC;
}

uint16_t CRC_INIT = 0xffff;

const uint16_t wCRC_Table[256] =
{
	0x0000, 0x1189, 0x2312, 0x329b, 0x4624, 0x57ad, 0x6536, 0x74bf,
	0x8c48, 0x9dc1, 0xaf5a, 0xbed3, 0xca6c, 0xdbe5, 0xe97e, 0xf8f7,
	0x1081, 0x0108, 0x3393, 0x221a, 0x56a5, 0x472c, 0x75b7, 0x643e,
	0x9cc9, 0x8d40, 0xbfdb, 0xae52, 0xdaed, 0xcb64, 0xf9ff, 0xe876,
	0x2102, 0x308b, 0x0210, 0x1399, 0x6726, 0x76af, 0x4434, 0x55bd,
	0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e, 0xfae7, 0xc87c, 0xd9f5,
	0x3183, 0x200a, 0x1291, 0x0318, 0x77a7, 0x662e, 0x54b5, 0x453c,
	0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef, 0xea66, 0xd8fd, 0xc974,
	0x4204, 0x538d, 0x6116, 0x709f, 0x0420, 0x15a9, 0x2732, 0x36bb,
	0xce4c, 0xdfc5, 0xed5e, 0xfcd7, 0x8868, 0x99e1, 0xab7a, 0xbaf3,
	0x5285, 0x430c, 0x7197, 0x601e, 0x14a1, 0x0528, 0x37b3, 0x263a,
	0xdecd, 0xcf44, 0xfddf, 0xec56, 0x98e9, 0x8960, 0xbbfb, 0xaa72,
	0x6306, 0x728f, 0x4014, 0x519d, 0x2522, 0x34ab, 0x0630, 0x17b9,
	0xef4e, 0xfec7, 0xcc5c, 0xddd5, 0xa96a, 0xb8e3, 0x8a78, 0x9bf1,
	0x7387, 0x620e, 0x5095, 0x411c, 0x35a3, 0x242a, 0x16b1, 0x0738,
	0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb, 0xa862, 0x9af9, 0x8b70,
	0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c, 0xd3a5, 0xe13e, 0xf0b7,
	0x0840, 0x19c9, 0x2b52, 0x3adb, 0x4e64, 0x5fed, 0x6d76, 0x7cff,
	0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad, 0xc324, 0xf1bf, 0xe036,
	0x18c1, 0x0948, 0x3bd3, 0x2a5a, 0x5ee5, 0x4f6c, 0x7df7, 0x6c7e,
	0xa50a, 0xb483, 0x8618, 0x9791, 0xe32e, 0xf2a7, 0xc03c, 0xd1b5,
	0x2942, 0x38cb, 0x0a50, 0x1bd9, 0x6f66, 0x7eef, 0x4c74, 0x5dfd,
	0xb58b, 0xa402, 0x9699, 0x8710, 0xf3af, 0xe226, 0xd0bd, 0xc134,
	0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7, 0x6e6e, 0x5cf5, 0x4d7c,
	0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028, 0x91a1, 0xa33a, 0xb2b3,
	0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60, 0x1de9, 0x2f72, 0x3efb,
	0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9, 0x8120, 0xb3bb, 0xa232,
	0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1, 0x0d68, 0x3ff3, 0x2e7a,
	0xe70e, 0xf687, 0xc41c, 0xd595, 0xa12a, 0xb0a3, 0x8238, 0x93b1,
	0x6b46, 0x7acf, 0x4854, 0x59dd, 0x2d62, 0x3ceb, 0x0e70, 0x1ff9,
	0xf78f, 0xe606, 0xd49d, 0xc514, 0xb1ab, 0xa022, 0x92b9, 0x8330,
	0x7bc7, 0x6a4e, 0x58d5, 0x495c, 0x3de3, 0x2c6a, 0x1ef1, 0x0f78
};


/*
** Descriptions: CRC16 checksum function
** Input: Data to check,Stream length, initialized checksum
** Output: CRC checksum
*/
uint16_t Get_CRC16_Check_Sum(uint8_t* pchMessage , uint32_t dwLength , uint16_t wCRC)
{
	uint8_t chData;
	if (pchMessage == 0)
	{
		return 0xFFFF;
	}
	while (dwLength--)
	{
		chData = *pchMessage++;
		(wCRC) = ((uint16_t) (wCRC) >> 8) ^ wCRC_Table[((uint16_t) (wCRC) ^
								   (uint16_t) (chData)) & 0x00ff];
	}
	return wCRC;
}


/*
** Descriptions: CRC16 Verify function
** Input: Data to Verify,Stream length = Data + checksum
** Output: True or False (CRC Verify Result)
*/

uint32_t Verify_CRC16_Check_Sum(uint8_t* pchMessage , uint32_t dwLength)
{
	uint16_t wExpected = 0;
	if ((pchMessage == 0) || (dwLength <= 2))
	{
		return 0;
	}
	wExpected = Get_CRC16_Check_Sum(pchMessage , dwLength - 2 , CRC_INIT);
	return ((wExpected & 0xff) == pchMessage[dwLength - 2] && ((wExpected >> 8) & 0xff) == pchMessage[dwLength - 1]);
}


/*
** Descriptions: append CRC16 to the end of data
** Input: Data to CRC and append,Stream length = Data + checksum
** Output: True or False (CRC Verify Result)
*/
void Append_CRC16_Check_Sum(uint8_t* pchMessage , uint32_t dwLength)
{
	uint16_t wCRC = 0;
	if ((pchMessage == 0) || (dwLength <= 2))
	{
		return;
	}
	wCRC = Get_CRC16_Check_Sum((uint8_t*) pchMessage , dwLength-2 , CRC_INIT);
	pchMessage[dwLength-2] = (uint8_t) (wCRC & 0x00ff);
	pchMessage[dwLength-1] = (uint8_t) ((wCRC >> 8) & 0x00ff);
}

/************************************************************万能分隔符**************************************************************
*	@author:			//赵澍
*	@performance:	//裁判系统接收函数
*	@parameter:		//NO
*	@time:				//22-03-20
*	@ReadMe:			//待修改
								//直接在原版上面套用接收，是在原有基础上加上了自己的数组，并未改变接收逻辑，所以原来的数组还是能用。
************************************************************************************************************************************/
void judgeCalculate(uint8_t JudgeDataBuffer[JudgeBufferLength])//裁判系统解算
{
	static uint16_t start_pos=0 , next_start_pos=0;
	while (1)
	{
		memcpy(&JudgementData.frameHeader , &JudgeDataBuffer[start_pos] , FrameHeader_Len);	//shu//这里只把帧头搞过去，先校验对不对，对的话再开始判断发送内容，并且接收对应数据
		/*先校验头帧0xA5 然后crc8校验帧头 再crc16位校验整包*/
		if ((JudgementData.frameHeader.SOF==(uint16_t) JudgeFrameHeader) \
	&&(1==Verify_CRC8_Check_Sum(&JudgeDataBuffer[start_pos] , FrameHeader_Len)) \
	&&(1==Verify_CRC16_Check_Sum(&JudgeDataBuffer[start_pos] , JudgementData.frameHeader.DataLenth+FrameHeader_Len+4)))		//数据位长度+帧头长度+命令码长度+校验码长度
		{
			//两次校验都通过
			memcpy(&JudgementData.rxCmdId , (&JudgeDataBuffer[start_pos]+5) , sizeof(JudgementData.rxCmdId));			//得到命令码
			JudgeDataBuffer[start_pos]++;//每处理完一次就在帧头加一防止再次处理这帧数据
			next_start_pos=start_pos+9+JudgementData.frameHeader.DataLenth;//9为 5位帧头 2位数据长度 2校验位//指向下一帧的开始
			switch (JudgementData.rxCmdId)
			{
				//*************************************************************可编辑部分***************************************************************//
				//血量等级 各种上限
			case RobotStatus_ID:
			{
				//把数组中的数据复制到对应的结构体中去
				memcpy(&JudgementData.game_robot_state_t , (&JudgeDataBuffer[start_pos]+7) , JudgementData.frameHeader.DataLenth);
				Manage_RobotStatus();
			}break;

			//功率 缓冲 热量 电池信息
			case PowerHeat_ID:
			{
					//把数组中的数据复制到对应的结构体中去
				memcpy(&JudgementData.power_heat_data_t , (&JudgeDataBuffer[start_pos]+7) , JudgementData.frameHeader.DataLenth);
				Manage_PowerHeat();
			}break;

			//射频 射速
			case ShootState_ID:
			{
				//把数组中的数据复制到对应的结构体中去
				memcpy(&JudgementData.shoot_data_t , (&JudgeDataBuffer[start_pos]+7) , JudgementData.frameHeader.DataLenth);
				Manage_ShootState();
			}break;

			//伤害类型 伤害方向
			case RobotHurt_ID:
			{
				//把数组中的数据复制到对应的结构体中去
				memcpy(&JudgementData.robot_hurt_t , (&JudgeDataBuffer[start_pos]+7) , JudgementData.frameHeader.DataLenth);
				Manage_RobotHurt();
			}break;
		//*************************************************************可编辑部分***************************************************************//
			}
			start_pos=next_start_pos;
		}
		else
		{
			//校验未通过 //数据错误  数据解析完毕
			start_pos=0;
			break;
		}
		/**如果头指针越界了退出循环**/
		if (start_pos>JudgeBufferLength)
		{
			start_pos=0;
			break;
		}
	}
}


/************************************************************万能分隔符**************************************************************
*	@author:			//赵澍
*	@performance:	//对RobotHurt_ID数据的二次处理
*	@parameter:		//NO
*	@time:				//22-03-20
*	@ReadMe:			//伤害类型
************************************************************************************************************************************/
void Manage_RobotHurt(void)
{
		//装甲伤害
	if (JudgementData.robot_hurt_t.hurt_type == 0)
	{
		twoJudgeData.HurtSource.ArmorBack = 0;
		twoJudgeData.HurtSource.ArmorFront = 0;
		twoJudgeData.HurtSource.ArmorRight = 0;
		twoJudgeData.HurtSource.ArmorLeft = 0;
		switch (JudgementData.robot_hurt_t.armor_id)
		{
		case 0:
		{
			twoJudgeData.HurtSource.ArmorFront = 1;
		}break;
		case 1:
		{
			twoJudgeData.HurtSource.ArmorLeft = 1;
		}break;
		case 2:
		{
			twoJudgeData.HurtSource.ArmorBack = 1;
		}break;
		case 3:
		{
			twoJudgeData.HurtSource.ArmorRight = 1;
		}break;
		}
	}
	//其他伤害
	else
	{
		twoJudgeData.HurtSource.ExceedHead = 0;
		twoJudgeData.HurtSource.ExceedPower = 0;
		twoJudgeData.HurtSource.ExceedSpeed = 0;
		twoJudgeData.HurtSource.Mods_OffLine = 0;
		switch (JudgementData.robot_hurt_t.armor_id)
		{
		case 1:
		{
			twoJudgeData.HurtSource.Mods_OffLine = 1;
		}break;
		case 2:
		{
			twoJudgeData.HurtSource.ExceedSpeed = 1;
		}break;
		case 3:
		{
			twoJudgeData.HurtSource.ExceedHead = 1;
		}break;
		case 4:
		{
			twoJudgeData.HurtSource.ExceedPower = 1;
		}break;
		}
	}
}
/************************************************************万能分隔符**************************************************************
*	@author:			//赵澍
*	@performance:	//对PowerHeat_ID数据的二次处理
*	@parameter:		//NO
*	@time:				//22-03-20
*	@ReadMe:			//当前枪口热量  当前功率 当前缓冲
************************************************************************************************************************************/
void Manage_PowerHeat(void)
{
		//当前功率
	twoJudgeData.power.nowPower = JudgementData.power_heat_data_t.chassis_power;
	//缓冲处理
	twoJudgeData.power.buffer = JudgementData.power_heat_data_t.chassis_power_buffer;
	twoJudgeData.power.maxBuffer = 60;		//人为设置最大缓冲
	twoJudgeData.power.bufferProportion = (float) (twoJudgeData.power.buffer)/(float) (twoJudgeData.power.maxBuffer);
	//枪口当前热量
	if (twoJudgeData.RoboSate.mod == HoreRobot)
	{
		twoJudgeData.muzzle.nowCooling = JudgementData.power_heat_data_t.shooter_id1_42mm_cooling_heat;
	}
	else
	{
		twoJudgeData.muzzle.nowCooling = JudgementData.power_heat_data_t.shooter_id1_17mm_cooling_heat;
	}
	//电池电压
	twoJudgeData.power.volt = JudgementData.power_heat_data_t.chassis_volt;
}
/************************************************************万能分隔符**************************************************************
*	@author:			//赵澍
*	@performance:	//对ShootState_ID数据的二次处理
*	@parameter:		//NO
*	@time:				//22-03-20
*	@ReadMe:			//子弹射速
************************************************************************************************************************************/
void Manage_ShootState(void)
{
	twoJudgeData.muzzle.shootSpeed = JudgementData.shoot_data_t.bullet_speed;		//子弹射速
}
/************************************************************万能分隔符**************************************************************
*	@author:			//赵澍
*	@performance:	//对RobotStatus_ID据的二次处理
*	@parameter:		//NO
*	@time:				//22-03-20
*	@ReadMe:			//得到颜色，兵种，血量，热量上限，射速上限，冷却值，功率上限
************************************************************************************************************************************/
void Manage_RobotStatus(void)
{
	uint8_t id = 0;
	//颜色得到
	if (JudgementData.game_robot_state_t.robot_id >= 100)
	{
		twoJudgeData.RoboSate.color = BuleColor;
	}
	else
	{
		twoJudgeData.RoboSate.color = RedColor;
	}
	//兵种得到
	id = JudgementData.game_robot_state_t.robot_id % 100;
	switch (id)
	{
	case 1:
	{
		twoJudgeData.RoboSate.mod = HoreRobot;
	}break;
	case 2:
	{
		twoJudgeData.RoboSate.mod = RescueRobot;
	}break;
	case 3:
	{
		twoJudgeData.RoboSate.mod = InfantryRobot;
	}break;
	case 4:
	{
		twoJudgeData.RoboSate.mod = InfantryRobot;
	}break;
	case 5:
	{
		twoJudgeData.RoboSate.mod = InfantryRobot;
	}break;
	case 6:
	{
		twoJudgeData.RoboSate.mod = AirRobot;
	}break;
	case 7:
	{
		twoJudgeData.RoboSate.mod = SentryRobot;
	}break;
	case 8:
	{
		twoJudgeData.RoboSate.mod = DartsRobot;
	}break;
	case 9:
	{
		twoJudgeData.RoboSate.mod = RadarRobot;
	}break;
	}
	//等级得到
	twoJudgeData.RoboSate.level = JudgementData.game_robot_state_t.robot_level;
	//血量得到
	twoJudgeData.RoboSate.hp = JudgementData.game_robot_state_t.remain_HP;
	twoJudgeData.RoboSate.maxHp = JudgementData.game_robot_state_t.max_HP;
	//射速上限  热量上限  
	if (twoJudgeData.RoboSate.mod == HoreRobot)
	{
		twoJudgeData.muzzle.coolingRate = JudgementData.game_robot_state_t.shooter_id1_42mm_cooling_rate;
		twoJudgeData.muzzle.maxCooling = JudgementData.game_robot_state_t.shooter_id1_42mm_cooling_limit;
		twoJudgeData.muzzle.maxShootSpeed = JudgementData.game_robot_state_t.shooter_id1_42mm_speed_limit;
	}
	else
	{
		twoJudgeData.muzzle.coolingRate = JudgementData.game_robot_state_t.shooter_id1_17mm_cooling_rate;
		twoJudgeData.muzzle.maxCooling = JudgementData.game_robot_state_t.shooter_id1_17mm_cooling_limit;
		twoJudgeData.muzzle.maxShootSpeed = JudgementData.game_robot_state_t.shooter_id1_17mm_speed_limit;
	}
	//功率上限//得到
	twoJudgeData.power.maxPower = JudgementData.game_robot_state_t.chassis_power_limit;
}






/************************************************************万能分隔符**************************************************************
*	@author:			//小何同学
*	@performance:	//判断红蓝方以及自身ID
*	@parameter:		//NO
*	@time:				//22-04-16
*	@ReadMe:			//机器人之间信息的交互，客户端和裁判系统之间的信息交互
************************************************************************************************************************************/
_Bool Color;
_Bool is_red_or_blue(void)
{
	Judge_Self_ID =JudgementData.game_robot_state_t.robot_id;; //读取当前机器人ID

	if (JudgementData.game_robot_state_t.robot_id> 10)
	{
		return 0; //蓝方
	}
	else
	{
		return 1; //红方
	}
}

void determine_ID(void)
{
	Color = is_red_or_blue();
	if (JudgementData.game_robot_state_t.robot_id> 10)
	{
		Judge_SelfClient_ID = 0x0100 + JudgementData.game_robot_state_t.robot_id;; //计算客户端ID
	}
	else
	{
		Judge_SelfClient_ID = 0x0100 + JudgementData.game_robot_state_t.robot_id;; //计算客户端ID

	}
}


/************************************************************万能分隔符**************************************************************
*	@author:			//小何同学
*	@performance:	//静态图层 1 //瞄准线//倒车线
*	@parameter:		//NO
*	@time:				//22-04-16
*	@ReadMe:			//机器人之间信息的交互，客户端和裁判系统之间的信息交互
************************************************************************************************************************************/
uint8_t data_au8[255];
int bg=100;
void Usart4_TX_staticUI(void)//画图形	
{
	hyp.frameHeader.SOF=0xA5;//SOF
	hyp.frameHeader.DataLenth=sizeof(hyp.data.data_id)+sizeof(hyp.data.receive_ID)+sizeof(hyp.data.send_ID)+sizeof(hyp.uixianduan.graphic_data_struct_t);//数据长度

	hyp.frameHeader.Seq=1;
	memcpy(data_au8 , &hyp.frameHeader , sizeof(hyp.frameHeader));

	Append_CRC8_Check_Sum(data_au8 , sizeof(hyp.frameHeader));

	hyp.frameHeader.CRC8 = data_au8[4];// frame_header

	//命令码ID
	hyp.CmdId=0x0301;

	hyp.data.data_id=0x104;//绘制图形OR绘制字符
	determine_ID();
	hyp.data.send_ID=JudgementData.game_robot_state_t.robot_id;

	hyp.data.receive_ID=Judge_SelfClient_ID;//客户端ID
/**********************************可编辑的UI*****************/
	//***竖线***//
	hyp.uixianduan.graphic_data_struct_t[0].graphic_name[0]=1;
	hyp.uixianduan.graphic_data_struct_t[0].operate_tpye=1;//1增加2修改3删除
	hyp.uixianduan.graphic_data_struct_t[0].graphic_tpye=0;//图形类型
	hyp.uixianduan.graphic_data_struct_t[0].layer=1;//图层数
	hyp.uixianduan.graphic_data_struct_t[0].width=3;
	hyp.uixianduan.graphic_data_struct_t[0].color=3;
	hyp.uixianduan.graphic_data_struct_t[0].start_x=960;
	hyp.uixianduan.graphic_data_struct_t[0].start_y=240;
	hyp.uixianduan.graphic_data_struct_t[0].end_x=960;
	hyp.uixianduan.graphic_data_struct_t[0].end_y=640;//竖线
	//**3米线**//
	hyp.uixianduan.graphic_data_struct_t[1].graphic_name[0]=2;
	hyp.uixianduan.graphic_data_struct_t[1].operate_tpye=1;//1增加2修改3删除
	hyp.uixianduan.graphic_data_struct_t[1].graphic_tpye=0;//图形类型
	hyp.uixianduan.graphic_data_struct_t[1].layer=1;//图层数
	hyp.uixianduan.graphic_data_struct_t[1].width=3;
	hyp.uixianduan.graphic_data_struct_t[1].color=4;
#ifdef Infantry_Number_Four
	hyp.uixianduan.graphic_data_struct_t[1].start_x=800;
	hyp.uixianduan.graphic_data_struct_t[1].start_y=438;
	hyp.uixianduan.graphic_data_struct_t[1].end_x=1120;//3米线
	hyp.uixianduan.graphic_data_struct_t[1].end_y=438;
#endif

#ifdef Infantry_Number_Three
	hyp.uixianduan.graphic_data_struct_t[1].start_x=800;
	hyp.uixianduan.graphic_data_struct_t[1].start_y=445;
	hyp.uixianduan.graphic_data_struct_t[1].end_x=1120;//3米线
	hyp.uixianduan.graphic_data_struct_t[1].end_y=445;
#endif
//	//**2m线**//
//	hyp.uixianduan.graphic_data_struct_t[2].graphic_name[0]=3;
//	hyp.uixianduan.graphic_data_struct_t[2].operate_tpye=1;//1增加2修改3删除
//	hyp.uixianduan.graphic_data_struct_t[2].graphic_tpye=0;//图形类型
//	hyp.uixianduan.graphic_data_struct_t[2].layer=1;//图层数
//	hyp.uixianduan.graphic_data_struct_t[2].width=3;
//	hyp.uixianduan.graphic_data_struct_t[2].color=3;
//	hyp.uixianduan.graphic_data_struct_t[2].start_x=910;
//	hyp.uixianduan.graphic_data_struct_t[2].start_y=400;
//	hyp.uixianduan.graphic_data_struct_t[2].end_x=1050;
//	hyp.uixianduan.graphic_data_struct_t[2].end_y=400;
//	//**7M线**//
//	hyp.uixianduan.graphic_data_struct_t[3].graphic_name[0]=4;
//	hyp.uixianduan.graphic_data_struct_t[3].operate_tpye=1;//1增加2修改3删除
//	hyp.uixianduan.graphic_data_struct_t[3].graphic_tpye=0;//图形类型
//	hyp.uixianduan.graphic_data_struct_t[3].layer=1;//图层数
//	hyp.uixianduan.graphic_data_struct_t[3].width=3;
//	hyp.uixianduan.graphic_data_struct_t[3].color=3;
//	hyp.uixianduan.graphic_data_struct_t[3].start_x=925;
//	hyp.uixianduan.graphic_data_struct_t[3].start_y=360;
//	hyp.uixianduan.graphic_data_struct_t[3].end_x=1025;
//	hyp.uixianduan.graphic_data_struct_t[3].end_y=360;
	//**吊射线**//
//	hyp.uixianduan.graphic_data_struct_t[4].graphic_name[0]=5;
//	hyp.uixianduan.graphic_data_struct_t[4].operate_tpye=1;//1增加2修改3删除
//	hyp.uixianduan.graphic_data_struct_t[4].graphic_tpye=0;//图形类型
//	hyp.uixianduan.graphic_data_struct_t[4].layer=1;//图层数
//	hyp.uixianduan.graphic_data_struct_t[4].width=3;
//	hyp.uixianduan.graphic_data_struct_t[4].color=3;
//	hyp.uixianduan.graphic_data_struct_t[4].start_x=950;
//	hyp.uixianduan.graphic_data_struct_t[4].start_y=320;
//	hyp.uixianduan.graphic_data_struct_t[4].end_x=1000;
//	hyp.uixianduan.graphic_data_struct_t[4].end_y=320;
	//**倒车左线**//
	hyp.uixianduan.graphic_data_struct_t[5].graphic_name[0]=6;
	hyp.uixianduan.graphic_data_struct_t[5].operate_tpye=1;//1增加2修改3删除
	hyp.uixianduan.graphic_data_struct_t[5].graphic_tpye=0;//图形类型
	hyp.uixianduan.graphic_data_struct_t[5].layer=1;//图层数
	hyp.uixianduan.graphic_data_struct_t[5].width=3;
	hyp.uixianduan.graphic_data_struct_t[5].color=3;
	hyp.uixianduan.graphic_data_struct_t[5].start_x=590;
	hyp.uixianduan.graphic_data_struct_t[5].start_y=0;
	hyp.uixianduan.graphic_data_struct_t[5].end_x=762;
	hyp.uixianduan.graphic_data_struct_t[5].end_y=340;
	//**倒车右线**//
	hyp.uixianduan.graphic_data_struct_t[6].graphic_name[0]=7;
	hyp.uixianduan.graphic_data_struct_t[6].operate_tpye=1;//1增加2修改3删除
	hyp.uixianduan.graphic_data_struct_t[6].graphic_tpye=0;//图形类型
	hyp.uixianduan.graphic_data_struct_t[6].layer=1;//图层数
	hyp.uixianduan.graphic_data_struct_t[6].width=3;
	hyp.uixianduan.graphic_data_struct_t[6].color=3;
	hyp.uixianduan.graphic_data_struct_t[6].start_x=1330;
	hyp.uixianduan.graphic_data_struct_t[6].start_y=0;
	hyp.uixianduan.graphic_data_struct_t[6].end_x=1158;
	hyp.uixianduan.graphic_data_struct_t[6].end_y=340;
//	 if(UIUPDATE == 1)
//	{
//		//dianrong.dong.fu[1].operate_tpye=2;
//		g = 1; 
//	}
//	if(g == 1)//改变值
//	{
//		hyp.uixianduan.graphic_data_struct_t[6].operate_tpye=2;
//	}
//	else if(g == 5)//初始值
//	{
//		hyp.uixianduan.graphic_data_struct_t[6].operate_tpye=1;
//	}

//	hyp.uixianduan.graphic_data_struct_t[6].graphic_name[2]=29;
//	//hyp.uixianduan.graphic_data_struct_t[6].operate_tpye=2;//1增加2修改3删除
//	hyp.uixianduan.graphic_data_struct_t[6].graphic_tpye=6;//图形类型圆型
//	hyp.uixianduan.graphic_data_struct_t[6].layer=1;//图层数
//	hyp.uixianduan.graphic_data_struct_t[6].width=3;
//	hyp.uixianduan.graphic_data_struct_t[6].color=3;
//	hyp.uixianduan.graphic_data_struct_t[6].start_angle=20;
//	hyp.uixianduan.graphic_data_struct_t[6].start_x=10;
//	hyp.uixianduan.graphic_data_struct_t[6].start_y=760;
//	hyp.uixianduan.graphic_data_struct_t[6].radius=(int32_t)bg;bg--;  //圆圈

/**************************************end**************************/
	memcpy(data_au8 , &hyp , sizeof(hyp));

	Append_CRC16_Check_Sum(data_au8 , sizeof(hyp));

	hyp.CRC16=(int16_t) (data_au8[sizeof(hyp)-1] <<8)| data_au8[sizeof(hyp)];

	//串口DMA发送
  HAL_UART_Transmit_DMA(&huart3,data_au8, sizeof(hyp));

//	my_USART4_DMA_TX(data_au8 , sizeof(hyp));
}
/************************************************************万能分隔符**************************************************************
*	@author:			//小何同学
*	@performance:	//静态图层 1 //字母打印
*	@parameter:		//NO
*	@time:				//22-05-07
*	@ReadMe:			//机器人之间信息的交互，客户端和裁判系统之间的信息交互
************************************************************************************************************************************/
uint8_t data_zifu[255];
void Usart4_TX_Letter(void)
{
	zi.frameHeader.SOF=0xA5;//SOF
	zi.frameHeader.DataLenth=sizeof(zi.data.data_id)+sizeof(zi.data.receive_ID)+sizeof(zi.data.send_ID)+sizeof(zi.zifu);//数据长度

	zi.frameHeader.Seq=1;
	memcpy(data_zifu , &zi.frameHeader , sizeof(zi.frameHeader));

	Append_CRC8_Check_Sum(data_zifu , sizeof(zi.frameHeader));

	zi.frameHeader.CRC8 = data_zifu[4];// frame_header

	zi.CmdId=0x0301;//命令码ID

	zi.data.data_id=0x0110;//绘制字符
	determine_ID();
	zi.data.send_ID=JudgementData.game_robot_state_t.robot_id;

	zi.data.receive_ID=Judge_SelfClient_ID;//客户端ID
/**********************************可编辑的UI*****************/

	zi.zifu.graphic_data_struct_t.graphic_name[0]=8;
	zi.zifu.graphic_data_struct_t.operate_tpye=1;//1增加2修改3删除
	zi.zifu.graphic_data_struct_t.graphic_tpye=7;//图形类型
	zi.zifu.graphic_data_struct_t.layer=1;//图层数
	zi.zifu.graphic_data_struct_t.width=2;
	zi.zifu.graphic_data_struct_t.color=1;
	zi.zifu.graphic_data_struct_t.start_x=10;
	zi.zifu.graphic_data_struct_t.start_y=880;
	zi.zifu.graphic_data_struct_t.start_angle=20;//字体大小
	zi.zifu.graphic_data_struct_t.end_angle=20;//字符长度

	strncpy(zi.zifu.shuju , "SuperCap:\n\n\n\nPitch:" , sizeof("SuperCap:\n\n\n\nPitch:"));

/**************************************end**************************/
	memcpy(data_zifu , &zi , sizeof(zi));

	Append_CRC16_Check_Sum(data_zifu , sizeof(zi));

	zi.CRC16=(int16_t) (data_zifu[sizeof(zi)-1] <<8)| data_zifu[sizeof(zi)];
	//串口DMA发送
	  HAL_UART_Transmit_DMA(&huart3,data_zifu, sizeof(zi));

}


/************************************************************万能分隔符**************************************************************
*	@author:			//小何同学
*	@performance:	//静态图层 2 //电容电量//pitch轴角度
*	@parameter:		//NO
*	@time:				//22-05-07
* @LastUpDataTime:  //2022-05-25 22:31    by 小瑞
* @UpData： //  增加弹仓开关提示
*	@ReadMe:			//机器人之间信息的交互，客户端和裁判系统之间的信息交互
************************************************************************************************************************************/
uint8_t data_dainrong[255];
void Usart4_TX_Number(int32_t residueCap , int32_t pitchAngle , float angle)
{
	dianrong.frameHeader.SOF=0xA5;//SOF
	dianrong.frameHeader.DataLenth=sizeof(dianrong.data.data_id)+sizeof(dianrong.data.receive_ID)+sizeof(dianrong.data.send_ID)+sizeof(dianrong.dong);//数据长度

	dianrong.frameHeader.Seq=1;
	memcpy(data_dainrong , &dianrong.frameHeader , sizeof(dianrong.frameHeader));

	Append_CRC8_Check_Sum(data_dainrong , sizeof(dianrong.frameHeader));

	dianrong.frameHeader.CRC8 = data_dainrong[4];// frame_header

	dianrong.CmdId=0x0301;//命令码ID

	dianrong.data.data_id=0x0104;//绘制字符
	determine_ID();
	dianrong.data.send_ID=JudgementData.game_robot_state_t.robot_id;

	dianrong.data.receive_ID=Judge_SelfClient_ID;//客户端ID
/**********************************可编辑的UI*****************/
	//	//电容的剩余电量
	dianrong.dong.fu[0].graphic_name[1]=1;

	if (user_NumberUpData == 1)
	{
		dianrong.dong.fu[0].operate_tpye=1;
	}
	else
	{
		dianrong.dong.fu[0].operate_tpye=2;
	}
	dianrong.dong.fu[0].graphic_tpye=6;//图形类型
	dianrong.dong.fu[0].layer=2;//图层数
	dianrong.dong.fu[0].width=3;
	dianrong.dong.fu[0].color=5;
	dianrong.dong.fu[0].start_x=200;
	dianrong.dong.fu[0].start_y=880;
	dianrong.dong.fu[0].radius=residueCap;
	dianrong.dong.fu[0].start_angle=20;//字体大小
	dianrong.dong.fu[0].end_angle=2;//小数的有效位数

	//英雄P轴的角度	
	dianrong.dong.fu[1].graphic_name[1]=2;
	if (user_NumberUpData == 1)
	{
		dianrong.dong.fu[1].operate_tpye=1;
	}
	else
	{
		dianrong.dong.fu[1].operate_tpye=2;
	}
	dianrong.dong.fu[1].graphic_tpye=6;//图形类型
	dianrong.dong.fu[1].layer=1;//图层数
	dianrong.dong.fu[1].width=3;
	dianrong.dong.fu[1].color=5;
	dianrong.dong.fu[1].start_x=120;
	dianrong.dong.fu[1].start_y=760;
	dianrong.dong.fu[1].radius=my_abs(pitchAngle);
	dianrong.dong.fu[1].start_angle=25;//字体大小
	dianrong.dong.fu[1].end_angle=2;//小数的有效位数
	//底盘状态指示
	dianrong.dong.fu[2].graphic_name[0]=20;
	dianrong.dong.fu[2].operate_tpye=1;
	dianrong.dong.fu[2].graphic_tpye=2;
	dianrong.dong.fu[2].layer=9;
	dianrong.dong.fu[2].width=3;
	dianrong.dong.fu[2].color=1;
	dianrong.dong.fu[2].start_x=1760;
	dianrong.dong.fu[2].start_y=640;
	dianrong.dong.fu[2].radius=160;
	//**圆弧**//
	dianrong.dong.fu[3].graphic_name[1]=55;
	if (user_NumberUpData == 1)
	{
		dianrong.dong.fu[3].operate_tpye=1;
	}
	else
	{
		dianrong.dong.fu[3].operate_tpye=2;
	}
	dianrong.dong.fu[3].graphic_tpye=4;
	dianrong.dong.fu[3].layer=2;
	dianrong.dong.fu[3].width=15;
	if (TIM4->CCR2 == 25)
	{
		dianrong.dong.fu[3].color=6;
	}
	else if (TIM4->CCR2 == 5)
	{
		dianrong.dong.fu[3].color=6;
	}
	dianrong.dong.fu[3].start_x=1760;
	dianrong.dong.fu[3].start_y=640;
	dianrong.dong.fu[3].end_x=160;
	dianrong.dong.fu[3].end_y=160;
	dianrong.dong.fu[3].start_angle=angle;
	dianrong.dong.fu[3].end_angle=angle+30;//????????

/**************************************end**************************/
	memcpy(data_dainrong , &dianrong , sizeof(dianrong));

	Append_CRC16_Check_Sum(data_dainrong , sizeof(dianrong));

	dianrong.CRC16=(int16_t) (data_dainrong[sizeof(dianrong)-1] <<8)| data_dainrong[sizeof(dianrong)];
	//串口DMA发送
	  HAL_UART_Transmit_DMA(&huart3,data_dainrong,sizeof(dianrong));

//	my_USART4_DMA_TX(data_dainrong , sizeof(dianrong));
}


/************************************************************万能分隔符**************************************************************
*	@author:			//小何同学
*	@performance:	//静态图层 2 //陀螺仪打印
*	@parameter:		//NO
*	@time:				//22-05-07
*	@ReadMe:			//机器人之间信息的交互，客户端和裁判系统之间的信息交互
************************************************************************************************************************************/
uint8_t data_tuoluo[255];
int c=100;
int d=10;
void Usart4_TX_Top(uint8_t state)
{
	tuoluo.frameHeader.SOF=0xA5;//SOF
	tuoluo.frameHeader.DataLenth=sizeof(tuoluo.data.data_id)+sizeof(tuoluo.data.receive_ID)+sizeof(tuoluo.data.send_ID)+sizeof(tuoluo.zifu);//数据长度

	tuoluo.frameHeader.Seq=1;
	memcpy(data_tuoluo , &tuoluo.frameHeader , sizeof(tuoluo.frameHeader));

	Append_CRC8_Check_Sum(data_tuoluo , sizeof(tuoluo.frameHeader));

	tuoluo.frameHeader.CRC8 = data_tuoluo[4];// frame_header

	tuoluo.CmdId=0x0301;//命令码ID

	tuoluo.data.data_id=0x0110;//绘制字符
	determine_ID();
	tuoluo.data.send_ID=JudgementData.game_robot_state_t.robot_id;

	tuoluo.data.receive_ID=Judge_SelfClient_ID;//客户端ID
/**********************************可编辑的UI*****************/
	//陀螺仪在线状态
	tuoluo.zifu.graphic_data_struct_t.graphic_name[1]=3;
	if (user_NumberUpData == 1)
	{
		tuoluo.zifu.graphic_data_struct_t.operate_tpye=1;
	}
	else
	{
		tuoluo.zifu.graphic_data_struct_t.operate_tpye=2;
	}
	tuoluo.zifu.graphic_data_struct_t.graphic_tpye=7;//图形类型
	tuoluo.zifu.graphic_data_struct_t.layer=2;//图层数
	tuoluo.zifu.graphic_data_struct_t.width=6;
	//*颜色控制*//
	if (rc_ctrl.key_board.c == 1)
	{
		tuoluo.zifu.graphic_data_struct_t.color=2;//绿色
	}
	else if (rc_ctrl.key_board.c == 0)
	{
		tuoluo.zifu.graphic_data_struct_t.color=7;//红色
	}
	tuoluo.zifu.graphic_data_struct_t.start_x=10;
	tuoluo.zifu.graphic_data_struct_t.start_y=820;
	tuoluo.zifu.graphic_data_struct_t.start_angle=40;//字体大小
	tuoluo.zifu.graphic_data_struct_t.end_angle=sizeof("supercap");//字符长度


	strncpy(tuoluo.zifu.shuju , "supercap" , sizeof("supercap"));

  /**************************************end**************************/
	memcpy(data_tuoluo , &tuoluo , sizeof(tuoluo));

	Append_CRC16_Check_Sum(data_tuoluo , sizeof(tuoluo));

	tuoluo.CRC16=(int16_t) (data_tuoluo[sizeof(tuoluo)-1] <<8)| data_tuoluo[sizeof(tuoluo)];
	//串口DMA发送
		  HAL_UART_Transmit_DMA(&huart3,data_tuoluo,sizeof(tuoluo));

//	my_USART4_DMA_TX(data_tuoluo , sizeof(tuoluo));
}
/************************************************************万能分隔符**************************************************************
*	@author:			//小何同学
*	@performance:	//动态图层 2 //底盘指示图形
*	@parameter:		//NO
*	@time:				//22-05-13
*	@ReadMe:			//机器人之间信息的交互，客户端和裁判系统之间的信息交互
************************************************************************************************************************************/
void Usart4_TX_ChassisFriction(float angle)
{
	dianrong.dong.fu[2].graphic_name[0]=20;
	dianrong.dong.fu[2].operate_tpye=1;//1??2??3??
	dianrong.dong.fu[2].graphic_tpye=2;//????
	dianrong.dong.fu[2].layer=9;//???
	dianrong.dong.fu[2].width=1;
	dianrong.dong.fu[2].color=1;
	dianrong.dong.fu[2].start_x=160;
	dianrong.dong.fu[2].start_y=440;
	dianrong.dong.fu[2].radius=70;//??????

	dianrong.dong.fu[3].graphic_name[1]=12;
	dianrong.dong.fu[3].operate_tpye=2;
	dianrong.dong.fu[3].graphic_tpye=4;
	dianrong.dong.fu[3].layer=2;
	dianrong.dong.fu[3].width=15;
	dianrong.dong.fu[3].color=6;
	dianrong.dong.fu[3].start_x=160;
	dianrong.dong.fu[3].start_y=440;
	dianrong.dong.fu[3].end_x=70;
	dianrong.dong.fu[3].end_y=70;
	dianrong.dong.fu[3].start_angle=-((int32_t) angle-20);
	dianrong.dong.fu[3].end_angle=-((int32_t) angle+20);//????????
}
/************************************************************万能分隔符**************************************************************
*	@author:			//赵澍
*	@performance:	//打印控制总函数
*	@parameter:		//NO
*	@time:				//22-05-08
*	@ReadMe:			//定时器周期执行即可
************************************************************************************************************************************/
void AllPrintfControl(uint64_t time)
{
	static uint64_t time_static = 0;
	static uint64_t time_static_2 = 0;
	static uint64_t time_dynamic = 0;
	static uint64_t time_dynamic_2 = 0;
	static uint64_t time_dynamic_3 = 0;

	float angleTemp = 0.0f;
	//如果不是底盘主控直接退出
	if (root_t.Init_t.positionInit != df_chassisControl)
	{
		return;
	}
	//画静态图层
	if ((time-time_static)>=2000)
	{			//两秒一画												
		time_static = time;		//跟新时间
		Usart4_TX_staticUI();		//画辅助线
	}
	if ((time-time_static_2)>=2500)
	{			//两秒一画												
		time_static_2 = time;		//跟新时间
		Usart4_TX_Letter();			//字母打印
	}
	//画动态图层2
	if ((time-time_dynamic)>=200)
	{				//一秒五画												
		time_dynamic = time;		//跟新时间
		angleTemp = m_GM6020_y_t.data.ralativeAngle;
		if (m_GM6020_y_t.data.ralativeAngle <= 0)
		{
			angleTemp += 360;
		}
		Usart4_TX_Number((int32_t) capData_t.capGetDate.capVolt * 4 , (int32_t) (m_GM6020_p_t.data.ralativeAngle*10) , angleTemp);
	}
	if ((time-time_dynamic_2)>=199)
	{				//一秒五画												
		time_dynamic_2 = time;		//跟新时间
		Usart4_TX_Top(root_t.topRoot.state);
	}
	if ((time-time_dynamic_3)>=100)
	{				//一秒五画												
		time_dynamic_3 = time;		//跟新时间
//				shu_temp84 = (m_GM6020_y_t.data.ralativeAngle + 180.0f);
//				Usart4_TX_ChassisFriction(shu_temp84);
	}

}



//*能用的发送函数，留个样板，勿删*//


//////////////////////////////////////////////////////////////////////
//void Usart4_TX_Sentry(int8_t ZhuangTai)
//{
//	shu_send_t.frameHeader.SOF = 0xA5;
//	shu_send_t.frameHeader.DataLenth = sizeof(shu_send_t.send_ID) + sizeof(shu_send_t.TongXin_ID) + sizeof(shu_send_t.receive_ID) + sizeof(shu_send_t.send_data);
//	shu_send_t.frameHeader.Seq = 1;
//	
//	memcpy(data_au8,&shu_send_t.frameHeader,sizeof(shu_send_t.frameHeader));
//	
//	Append_CRC8_Check_Sum(data_au8,sizeof(shu_send_t.frameHeader));

//	shu_send_t.frameHeader.CRC8 = data_au8[4];
//	
//	shu_send_t.rxCmdId = 0x301;
//	
//	shu_send_t.TongXin_ID = 0x201;
//	
////	shu_send_t.send_ID=3;
////	
////	shu_send_t.receive_ID=7;
//	
//	switch(JudgementData.game_robot_state_t.robot_id)
//	
//{
//		case 4:
//			{
//			shu_send_t.send_ID = JudgementData.game_robot_state_t.robot_id;

//			shu_send_t.receive_ID = 7;
//			break;

//			}
//		case 104:
//			{
//			shu_send_t.send_ID = JudgementData.game_robot_state_t.robot_id;

//			shu_send_t.receive_ID = 107;
//			break;
//	    }
//		default: break;
//}

//	shu_send_t.send_data = ZhuangTai;	
//  memcpy(data_au8,&shu_send_t,sizeof(shu_send_t));

//	Append_CRC16_Check_Sum(data_au8,sizeof(shu_send_t));
//	
//	data_au8[22] = sizeof(shu_send_t.frameHeader);
//	data_au8[23] = sizeof(shu_send_t.send_data);
//	data_au8[24] = sizeof(shu_send_t.receive_ID);
//	data_au8[25] = sizeof(shu_send_t.TongXin_ID);
//	data_au8[26] = sizeof(shu_send_t.send_ID);
//	data_au8[27] = sizeof(shu_send_t);

//	HAL_UART_Transmit(&huart4, data_au8,sizeof(shu_send_t),0xff);
//}








