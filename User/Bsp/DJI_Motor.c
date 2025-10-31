/*
 *                                                     __----~~~~~~~~~~~------___
 *                                    .  .   ~~//====......          __--~ ~~
 *                    -.            \_|//     |||\\  ~~~~~~::::... /~
 *                 ___-==_       _-~o~  \/    |||  \\            _/~~-
 *         __---~~~.==~||\=_    -_--~/_-~|-   |\\   \\        _/~
 *     _-~~     .=~    |  \\-_    '-~7  /-   /  ||    \      /
 *   .~       .~       |   \\ -_    /  /-   /   ||      \   /
 *  /  ____  /         |     \\ ~-_/  /|- _/   .||       \ /
 *  |~~    ~~|--~~~~--_ \     ~==-/   | \~--===~~        .\
 *           '         ~-|      /|    |-~\~~       __--~~
 *                       |-~~-_/ |    |   ~\_   _-~            /\
 *                            /  \     \__   \/~                \__
 *                        _--~ _/ | .-~~____--~-/                  ~~==.
 *                       ((->/~   '.|||' -_|    ~~-/ ,              . _||
 *                                  -_     ~\      ~~---l__i__i__i--~~_/
 *                                  _-~-__   ~)  \--______________--~~
 *                                //.-~~~-~_--~- |-------~~~~~~~~
 *                                       //.-~~~--\
 *                       ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 
 *                               神兽保佑            永无BUG
 */

#include "DJI_Motor.h"

/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //3508电机解算函数
 *	@parameter:		    //@电机结构体  @can接收到的数组
 *	@time:				//22-11-23 18:50
 *	@ReadMe:			//
 ************************************************************万能分隔符**************************************************************/
void RUI_F_MOTOR_CAN_RX_3508RM(DJI_MOTOR_DATA_Typedef* DATA , uint8_t* can_data)
{
    DATA->Angle_last = DATA->Angle_now;

    DATA->Angle_now = (int16_t) (((can_data[0] << 8) | can_data[1]) & 0xFFFF);

    DATA->Speed_last = DATA->Speed_now;

    DATA->Speed_now = (int16_t) (((can_data[2] << 8) | can_data[3]) & 0xFFFF);

    DATA->current   = (int16_t) (((can_data[4] << 8) | can_data[5]) & 0xFFFF);

    DATA->temperature = can_data[6];

    if (DATA->Angle_now - DATA->Angle_last < -4000)
    {
        DATA->Laps++;
    }
    else if (DATA->Angle_now - DATA->Angle_last > 4000)
    {
        DATA->Laps--;
    }

    if ((DATA->Laps > 32500) | (DATA->Laps < -32500))
    {
        DATA->Laps = 0;
        DATA->Aim  = DATA->Angle_now;
    }

    DATA->ONLINE_JUDGE_TIME = RUI_DF_MOTOR_OFFLINE_TIME;

    DATA->Angle_Infinite = (int32_t) ((DATA->Laps << 13)+ DATA->Angle_now);

}

/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //2006电机解算函数
 *	@parameter:		    //@电机结构体  @can接收到的数组
 *	@time:				//22-11-23 18:49
 *	@ReadMe:			//
 ************************************************************万能分隔符**************************************************************/
void RUI_F_MOTOR_CAN_RX_2006RM(DJI_MOTOR_DATA_Typedef* DATA , uint8_t* can_data)
{
    DATA->Angle_last = DATA->Angle_now;

    DATA->Angle_now = (int16_t) (((can_data[0] << 8) | can_data[1]) & 0xFFFF);

    DATA->Speed_last = DATA->Speed_now;

    DATA->Speed_now = (int16_t) (((can_data[2] << 8) | can_data[3]) & 0xFFFF);

    DATA->current = (int16_t) (((can_data[4] << 8) | can_data[5]) & 0xFFFF);

    if (DATA->Angle_now - DATA->Angle_last < -4000)
    {
        DATA->Laps++;
    }
    else if (DATA->Angle_now - DATA->Angle_last > 4000)
    {
        DATA->Laps--;
    }

    if ((DATA->Laps > 32500) | (DATA->Laps < -32500))
    {
        DATA->Laps = 0;
        DATA->Aim  = DATA->Angle_now;
    }

    DATA->Angle_Infinite = (int32_t) ((DATA->Laps << 13) + DATA->Angle_now);
    DATA->ONLINE_JUDGE_TIME = RUI_DF_MOTOR_OFFLINE_TIME;
}

/************************************************************万能分隔符**************************************************************
 * 	@author:			//王涵炜
 *	@performance:	    //6020电机解算函数
 *	@parameter:		    //@电机结构体  @can接收到的数组
 *	@time:				//22-11-23 18:50
 *	@ReadMe:			//
 ************************************************************万能分隔符**************************************************************/
void WHW_F_MOTOR_CAN_RX_6020RM(DJI_MOTOR_DATA_Typedef* DATA , uint8_t* can_data)
{
    DATA->Angle_last = DATA->Angle_now;

    DATA->Angle_now = (int16_t) (((can_data[0] << 8) | can_data[1]) & 0xFFFF);

    DATA->Speed_last = DATA->Speed_now;

    DATA->Speed_now = (int16_t) (((can_data[2] << 8) | can_data[3]) & 0xFFFF);

    DATA->current   = (int16_t) (((can_data[4] << 8) | can_data[5]) & 0xFFFF);

    DATA->temperature = can_data[6];

//    if(DATA->Angle_now < 2900)	DATA->Laps = 1;
//    if(DATA->Angle_now > 4000)	DATA->Laps = 0;

    if (DATA->Angle_now - DATA->Angle_last < -4000)
    {
        DATA->Laps++;
    }
    else if (DATA->Angle_now - DATA->Angle_last > 4000)
    {
        DATA->Laps--;
    }

    if ((DATA->Laps > 32500) | (DATA->Laps < -32500))
    {
        DATA->Laps = 0;
        DATA->Aim  = DATA->Angle_now;
    }

    DATA->ONLINE_JUDGE_TIME = RUI_DF_MOTOR_OFFLINE_TIME;

    DATA->Angle_Infinite = (int32_t) ((DATA->Laps << 13)+ DATA->Angle_now);

}

/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //电机清空函数
 *	@parameter:		    //
 *	@time:				//23-04-13 19:23
 *	@ReadMe:			//
 *  @LastUpDataTime:    //2023-05-07 17:06    bestrui
 *  @UpData：           //不太好描述
 ************************************************************万能分隔符**************************************************************/
void RUI_F_HEAD_MOTOR_CLEAR(DJI_MOTOR_Typedef* MOTOR , uint8_t mode)
{
    MOTOR->PID_P.Iout  = 0.0f;
    MOTOR->PID_S.Iout  = 0.0f;
    MOTOR->DATA.Aim    = (float)MOTOR->DATA.Angle_Infinite;
    if (mode)       MOTOR->DATA.Laps = 0;
}

/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //2006电机堵转检测函数
 *	@parameter:		    //
 *	@time:				//23-04-13 20:31
 *	@ReadMe:			//
 *  @LastUpDataTime:    //2023-04-14 15:34    bestrui
 *  @UpData：           //给电机结构体增加堵转时间
 ************************************************************万能分隔符**************************************************************/
void RUI_F_HEAD_MOTOR2006_STUCK(DJI_MOTOR_Typedef* MOTOR , float ERROR_ANGLE , float ERROR_SPEED , uint16_t ERROR_TIME)
{
    //一定误差  速度小于某个值初步判断电机卡住，接下来去判断卡住的时间
    if (RUI_F_MATH_ABS_float(MOTOR->PID_P.Err) > ERROR_ANGLE && RUI_F_MATH_ABS_float(MOTOR->DATA.Speed_now) < ERROR_SPEED)
    {
        MOTOR->DATA.Stuck_Time++;
        if (MOTOR->DATA.Stuck_Time > ERROR_TIME)
        {
            RUI_F_HEAD_MOTOR_CLEAR(MOTOR, 0);
            MOTOR->DATA.Stuck_Time = 0;
            MOTOR->DATA.Stuck_Flag[0]++;
        }
    }
    else
    {
        MOTOR->DATA.Stuck_Time = 0;
    }
    MOTOR->DATA.Aim_last = MOTOR->DATA.Aim;

}

/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //3508堵转检测
 *	@parameter:		    //
 *	@time:				//23-05-25 18:14
 *	@ReadMe:			//
 ************************************************************万能分隔符**************************************************************/
void RUI_F_HEAD_MOTOR3508_STUCK(DJI_MOTOR_Typedef* MOTOR , float ERROR_CURRENT , float ERROR_SPEED)
{
    if (RUI_F_MATH_ABS_float(MOTOR->DATA.Speed_now) < ERROR_SPEED)
    {
        if (RUI_F_MATH_ABS_float(MOTOR->DATA.current) > ERROR_CURRENT)
        {
            RUI_F_HEAD_MOTOR_CLEAR(MOTOR, 0);
            MOTOR->DATA.Stuck_Flag[0]++;
        }
    }
}

void DJI_Current_Ctrl(hcan_t* hcan, uint16_t stdid, int16_t num1, int16_t num2, int16_t num3, int16_t num4)
{
    uint8_t Data[8];

    Data[0] = ((num1) >> 8);
    Data[1] = (num1);
    Data[2] = ((num2) >> 8);
    Data[3] = (num2);
    Data[4] = ((num3) >> 8);
    Data[5] = (num3);
    Data[6] = ((num4) >> 8);
    Data[7] = (num4);

    canx_send_data(hcan, stdid, Data);
}
