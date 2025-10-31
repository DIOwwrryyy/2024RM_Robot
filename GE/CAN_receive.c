/**
  ****************************(C) COPYRIGHT 2019 DJI****************************
  * @file       can_receive.c/h
  * @brief      there is CAN interrupt function  to receive motor data,
  *             and CAN send function to send motor current to control motor.
  *             这里是CAN中断接收函数，接收电机数据,CAN发送函数发送电机电流控制电机.
  * @note       
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     Dec-26-2018     RM              1. done
  *
  @verbatim
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2019 DJI****************************
  */

#include "CAN_receive.h"
#include "main.h"
#include "switch.h"
#include "can.h"
#include "motor.h"

struct canBoll_typedef canBoll_t ={ 0 };

extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;

 uint8_t    can_send_data[8];
		
 uint8_t    can_union_txdata[8];

	CAN_RxHeaderTypeDef rx_header;//can接收头
  uint8_t rx_data[8];//can接收数据暂存		
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef* hcan)
{

//    HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, rx_data);
	if (hcan == &hcan1)
	{     HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &rx_header, rx_data);

		 if (root_t.Init_t.positionInit == df_chassisControl)
		{				//底盘CAN1接收
			switch (rx_header.StdId)
			{
			   case df_GMmotor_y_ID:		//yaw轴电机
			       {
			      	 CanManage_6020(rx_data , &m_GM6020_y_t.data);
			        }break;
						 
			   case df_GMmotor_p_ID:		//pitch轴电机 
			       {
			      	 CanManage_6020(rx_data , &m_GM6020_p_t.data);
			        }break;
						 
			    case df_GMControl_ID:	//云台传来的数据
			       {
			       	 ChassisRXResolve(rx_data);
			        }break;
			    default:
			    {
			    	canBoll_t.my_can1.RxResolver = df_re_error;
			     }  
			}
		}
		canBoll_t.my_can1.RxResolver = df_end;
	}
	else if (hcan == &hcan2)
	{	//CAN2总线判断	
		    HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO0, &rx_header, rx_data);

		 if (root_t.Init_t.positionInit == df_chassisControl)
		{		//底盘CAN2接收
			switch (rx_header.StdId)
			  {
			     case df_CHmotor_1_ID:
			        {
			        	   CanManage_3508(rx_data , &m_CH3508_1_t.data);
								
			        }break;
			     case df_CHmotor_2_ID:
			         {
			           	 CanManage_3508(rx_data , &m_CH3508_2_t.data);
								 
			         }break;
			     case df_CHmotor_3_ID:
			         {
			           	 CanManage_3508(rx_data , &m_CH3508_3_t.data);
								 
			         }break;
			     case df_CHmotor_4_ID:
			          {
			           	 CanManage_3508(rx_data , &m_CH3508_4_t.data);
									
			          }break;
			     case df_SuperCap_ID:		//超级电容接收
			           {
			           	 CanManage_cap(rx_data , &capData_t.capGetDate);
									 
			           }break;
			     default:
			     {
			     	canBoll_t.my_can1.RxResolver = df_re_error;
			     }
			}
		}
		canBoll_t.my_can2.RxResolver = df_end;
	}

}

uint8_t my_CAN_Send(CAN_HandleTypeDef *hcan , uint32_t StdID , int16_t num1 , int16_t num2 , int16_t num3 , int16_t num4 , uint16_t len)
{  
	CAN_TxHeaderTypeDef  can_tx_message;//can发送头
	 uint32_t send_mail_box;
            can_tx_message.StdId = StdID;
            can_tx_message.IDE = CAN_ID_STD;
            can_tx_message.RTR = CAN_RTR_DATA;
            can_tx_message.DLC = 0x08;
            can_send_data[0] = (num1 >> 8);
            can_send_data[1] = num1;
            can_send_data[2] = (num2 >> 8);
            can_send_data[3] = num2;
            can_send_data[4] = (num3 >> 8);
            can_send_data[5] = num3;
            can_send_data[6] = (num4 >> 8);
            can_send_data[7] = num4;
     if (hcan == &hcan1){
           //CAN数据发送//顺便得到邮箱编号
		      HAL_CAN_AddTxMessage(&hcan1, &can_tx_message, can_send_data, &send_mail_box);     	 
		 }
			
	  else if (hcan == &hcan2){

          //CAN数据发送//顺便得到邮箱编号
           HAL_CAN_AddTxMessage(&hcan2, &can_tx_message, can_send_data, &send_mail_box);
	      }
		
    else{
		        return df_re_error;
       	}

	return df_re_ok;
}

//CAN发送函数,共用体发送格式
uint8_t my_CAN_Send_UNION(CAN_HandleTypeDef *hcan , uint32_t StdID , int16_t num1 , int16_t num2 , int16_t num3 , int16_t num4 , uint16_t len)
{   
	CAN_TxHeaderTypeDef  can_union_txmessage;//can发送头
  uint32_t send_mail_box;
	   if (hcan == &hcan1)
	   	   canBoll_t.my_can1.TxState = df_start;
	   else if (hcan == &hcan2)
	   	   canBoll_t.my_can2.TxState = df_start;
	   
//       设置标准标识符
	   can_union_txmessage.StdId = StdID;
//  		 设置拓展标识符//若使用标准帧这里就可以随便填
	   can_union_txmessage.ExtId = 0x000;
//       设置帧格式//标准还是拓展
	   can_union_txmessage.IDE = CAN_ID_STD;
//  	   设置帧的内容//遥控，停止，数据，错误帧
	   can_union_txmessage.RTR = CAN_RTR_DATA;
//   	   长度设置//数据位长度
	   can_union_txmessage.DLC = len;
//  	   数据接收
	   can_union_txdata[0]  =  (num1);
	   can_union_txdata[1]  =  ((num1)>>8);
	   can_union_txdata[2]  =  (num2);
	   can_union_txdata[3]  =  ((num2)>>8);
	   can_union_txdata[4]  =  (num3);
	   can_union_txdata[5]  =  ((num3)>>8);
	   can_union_txdata[6]  =  (num4);
	   can_union_txdata[7]  =  ((num4)>>8);
	   if (hcan == &hcan1)
	      {
	        	HAL_CAN_AddTxMessage(&hcan1, &can_union_txmessage, can_union_txdata, &send_mail_box);	     
	      }
	    else if (hcan == &hcan2)
	      {
	      	  HAL_CAN_AddTxMessage(&hcan2, &can_union_txmessage, can_union_txdata, &send_mail_box);
	      }
	    else
	      {
	      	return df_re_error;
	      }
	return df_re_ok;
}




/************************************************************万能分隔符**************************************************************
*	@author:			//赵澍
*	@performance:	//发送调用函数//底盘发送给云台的
*	@parameter:		//发送通道//CAN1//CAN2
*	@time:				//22-01-03
*	@ReadMe:			//调用该函数直接完成CAN发送
								//给云台的角度每次都会发送
								//其他的数据每执行十次发送一次，此时不发送角度
************************************************************************************************************************************/
uint8_t CANSendCHtoGM(CAN_HandleTypeDef *hcan)
{
	static uint8_t number = 1;		//记录执行次数	
	//执行次数累加
	++number;

	//数据发送部分
	if ((number%10) != 0)
	{
//先将要发送的数据解算出来
		ChassisTXResolve(0);
//				my_CAN_Send_UNION(hcan,df_CHControlAngle_ID, CanCommunit_t.chTOgm.sendData[0], CanCommunit_t.chTOgm.sendData[1], 
//																										 CanCommunit_t.chTOgm.sendData[2], CanCommunit_t.chTOgm.sendData[3], 8);		//发送角度

	}
	else if (number%10 == 0)
	{
		number = 1;
		//先将要发送的数据解算出来
		ChassisTXResolve(1);
		my_CAN_Send_UNION(hcan , df_CHControlData_ID , CanCommunit_t.chTOgm.sendData[0] , CanCommunit_t.chTOgm.sendData[1] ,
																								CanCommunit_t.chTOgm.sendData[2] , CanCommunit_t.chTOgm.sendData[3] , 8);			//发送数据
	}
	return df_re_ok;
}

