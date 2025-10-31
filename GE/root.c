#include "root.h"
#include "switch.h"

/*  ReadMe  ReadMe  ReadMe  ReadMe  ReadMe  ReadMe  ReadMe  ReadMe
	motor.c && motor.h
	步兵、英雄互换时需要更改 motor.c  中添加3510摩擦轮的定义 motor.h中更改3510的全局声明
	对应电机的PID //2006 6020 两个摩擦轮//
	PID解算函数里面正负号问题

	attack.h
	改变attack.h中的宏定义改为对应车辆

	can.c && can.h
	更改CAN摩擦轮接收的结构体为3510

	chassis.c && chassis.h
	麦轮解算的轴距和轮距

	gimbal.c && gimbal.h
	对应的pitch轴最大角以及最小角
	pitch轴遥控模式下对应的正负号问题

	tim.c
	改变云台发射机构对应的函数

	can.c
	改变对应CAN接收的结构体

	搜索//只有步兵才打开//步兵开启//英雄开启
	将对应的开关修改
*/
struct root_typedf root_t ={ df_offLine };
extern uint64_t RunTime;//时间轴

/************************************************************万能分隔符**************************************************************
*	@author:			//赵澍
*	@performance:	//离线检测程序
*	@parameter:		//NO
*	@time:				//22-01-06
*	@ReadMe:			//离线监视时需要在接收中断里面清空对应的时间累积
************************************************************************************************************************************/
uint8_t dog = 0;
void ErrorMonitor(void)
{
		/********************裁判系统监测***************/
	root_t.judgeRoot.time++;
	if (root_t.judgeRoot.time >= 143)
	{
		root_t.judgeRoot.time = 143;
		root_t.judgeRoot.communicat = df_offLine;

		BreatheIED(500 , df_Red , RunTime);	//红灯报警
	}
	else
	{
		root_t.judgeRoot.communicat = df_onLine;
	}

	/********************超级电容监测***************/
	root_t.superCapRoot.time++;
	if (root_t.superCapRoot.time >= 1000)
	{
		root_t.superCapRoot.time = 401;
		root_t.superCapRoot.communicat = df_offLine;

		BreatheIED(500 , df_Red , RunTime);	//红灯报警
	}
	else
	{
		root_t.superCapRoot.communicat = df_onLine;
	}
	/********************超级电容监测***************/
	/********************启动检测监测***************/
	root_t.carAllRoot.resteTime++;
	if (root_t.carAllRoot.resteTime >= df_resetTime)
	{
		root_t.carAllRoot.resteTime = df_resetTime;
		root_t.Init_t.statrInit = df_ok;
	}
}
/************************************************************万能分隔符**************************************************************
*	@author:			//赵澍
*	@performance:	//主控初始化程序
*	@parameter:		//NO
*	@time:				//22-01-07
* @UpData:          //小瑞 2022-05-30 17:36 增加了对switch.h的支持
*	@ReadMe:			//确定当前主控是在什么位置
************************************************************************************************************************************/
uint8_t PositionInit(void)
{
	root_t.Init_t.positionInit = df_chassisControl;
  return df_re_ok;
}
/************************************************************万能分隔符**************************************************************
*	@author:			//赵澍
*	@performance:	//帧率检测函数
*	@parameter:		//要打印的帧率//时间轴
*	@time:				//22-01-07
*	@ReadMe:			//返回值是当前帧率
								//刷新时间1s
************************************************************************************************************************************/
void DetectionFPS(uint16_t* FPS , uint32_t time)
{
	static uint16_t number = 0;
	static uint32_t TIME[2] ={ 0 };
	//记录运行次数
	number++;
	TIME[df_now] = time;

	if (TIME[df_now] - TIME[df_last]>=1000)
	{
		TIME[df_last] = TIME[df_now];                                                                                                                     
		*FPS = number;
		number = 0;
	}
}

void DetectionFPS_two(uint16_t* FPS , uint32_t time)
{
	static uint16_t number = 0;
	static uint32_t TIME[2] ={ 0 };
	//记录运行次数
	number++;
	TIME[df_now] = time;

	if (TIME[df_now] - TIME[df_last]>=1000)
	{
		TIME[df_last] = TIME[df_now];
		*FPS = number;
		number = 0;
	}
}

void DetectionFPS_three(uint16_t* FPS , uint32_t time)
{
	static uint16_t number = 0;
	static uint32_t TIME[2] ={ 0 };
	//记录运行次数
	number++;
	TIME[df_now] = time;

	if (TIME[df_now] - TIME[df_last]>=1000)
	{
		TIME[df_last] = TIME[df_now];
		*FPS = number;
		number = 0;
	}
}
/************************************************************万能分隔符**************************************************************
*	@author:			//赵澍
*	@performance:	//呼吸灯
*	@parameter:		//间隔时间(ms)//颜色//时间
*	@time:				//22-01-15
*	@ReadMe:			//提供一个直观的监测
								//闪烁时间不能短于定时器时间
								//如果有多个调用，一般会依照时间间隔最短的为准
************************************************************************************************************************************/
void BreatheIED(uint16_t intervalTime , uint8_t color , uint64_t time)
{
	static uint8_t RedBoll = 0 , BuleBoll = 0 , GreenBoll = 0;
	static uint64_t RedTIME[2] ={ 0 } , BuleTIME[2] ={ 0 } , GreenTIME[2] ={ 0 };

	RedTIME[df_now] 	= time;
	BuleTIME[df_now] 	= time;
	GreenTIME[df_now] = time;

	switch (color)
	{
	case df_Red:
	{		//红色报错
		if ((RedTIME[df_now] - RedTIME[df_last]) >= (intervalTime*0.5f))
		{
			RedBoll = !RedBoll;

			if (RedBoll == 0)
			{
				RedLED(GPIO_PIN_RESET);
			}
			else if (RedBoll == 1)
			{
				RedLED(GPIO_PIN_SET);
			}

			RedTIME[df_last] = RedTIME[df_now];
		}
	}break;
	case df_Bule:
	{		//蓝色呼吸灯
		if ((BuleTIME[df_now] - BuleTIME[df_last]) >= (intervalTime*0.5f))
		{
			BuleBoll = !BuleBoll;

			if (BuleBoll == 0)
			{
				BuleLED(GPIO_PIN_RESET);
			}
			else if (BuleBoll == 1)
			{
				BuleLED(GPIO_PIN_RESET);
			}

			BuleTIME[df_last] = BuleTIME[df_now];
		}
	}break;
	case df_Green:
	{		//绿色呼吸灯
		if ((GreenTIME[df_now] - GreenTIME[df_last]) >= (intervalTime*0.5f))
		{
			GreenBoll = !GreenBoll;

			if (GreenBoll == 0)
			{
				GreenLED(GPIO_PIN_RESET);
			}
			else if (GreenBoll == 1)
			{
				GreenLED(GPIO_PIN_RESET);
			}

			GreenTIME[df_last] = GreenTIME[df_now];
		}
	}break;
	}

}



//纪开给的字符串拼接方法
//#define pt(x) _pt(x)
//#define m_hoer skljfalkjsd

//#define _pt(x) pinrtf("%s",#x)

//pt(m_hoer);





