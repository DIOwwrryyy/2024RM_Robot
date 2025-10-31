/**
  ****************************(C) COPYRIGHT 2019 DJI****************************
  * @file       can_receive.c/h
  * @brief      there is CAN interrupt function  to receive motor data,
  *             and CAN send function to send motor current to control motor.
  *             ������CAN�жϽ��պ��������յ������,CAN���ͺ������͵���������Ƶ��.
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

	CAN_RxHeaderTypeDef rx_header;//can����ͷ
  uint8_t rx_data[8];//can���������ݴ�		
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef* hcan)
{

//    HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, rx_data);
	if (hcan == &hcan1)
	{     HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &rx_header, rx_data);

		 if (root_t.Init_t.positionInit == df_chassisControl)
		{				//����CAN1����
			switch (rx_header.StdId)
			{
			   case df_GMmotor_y_ID:		//yaw����
			       {
			      	 CanManage_6020(rx_data , &m_GM6020_y_t.data);
			        }break;
						 
			   case df_GMmotor_p_ID:		//pitch���� 
			       {
			      	 CanManage_6020(rx_data , &m_GM6020_p_t.data);
			        }break;
						 
			    case df_GMControl_ID:	//��̨����������
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
	{	//CAN2�����ж�	
		    HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO0, &rx_header, rx_data);

		 if (root_t.Init_t.positionInit == df_chassisControl)
		{		//����CAN2����
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
			     case df_SuperCap_ID:		//�������ݽ���
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
	CAN_TxHeaderTypeDef  can_tx_message;//can����ͷ
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
           //CAN���ݷ���//˳��õ�������
		      HAL_CAN_AddTxMessage(&hcan1, &can_tx_message, can_send_data, &send_mail_box);     	 
		 }
			
	  else if (hcan == &hcan2){

          //CAN���ݷ���//˳��õ�������
           HAL_CAN_AddTxMessage(&hcan2, &can_tx_message, can_send_data, &send_mail_box);
	      }
		
    else{
		        return df_re_error;
       	}

	return df_re_ok;
}

//CAN���ͺ���,�����巢�͸�ʽ
uint8_t my_CAN_Send_UNION(CAN_HandleTypeDef *hcan , uint32_t StdID , int16_t num1 , int16_t num2 , int16_t num3 , int16_t num4 , uint16_t len)
{   
	CAN_TxHeaderTypeDef  can_union_txmessage;//can����ͷ
  uint32_t send_mail_box;
	   if (hcan == &hcan1)
	   	   canBoll_t.my_can1.TxState = df_start;
	   else if (hcan == &hcan2)
	   	   canBoll_t.my_can2.TxState = df_start;
	   
//       ���ñ�׼��ʶ��
	   can_union_txmessage.StdId = StdID;
//  		 ������չ��ʶ��//��ʹ�ñ�׼֡����Ϳ��������
	   can_union_txmessage.ExtId = 0x000;
//       ����֡��ʽ//��׼������չ
	   can_union_txmessage.IDE = CAN_ID_STD;
//  	   ����֡������//ң�أ�ֹͣ�����ݣ�����֡
	   can_union_txmessage.RTR = CAN_RTR_DATA;
//   	   ��������//����λ����
	   can_union_txmessage.DLC = len;
//  	   ���ݽ���
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




/************************************************************���ָܷ���**************************************************************
*	@author:			//����
*	@performance:	//���͵��ú���//���̷��͸���̨��
*	@parameter:		//����ͨ��//CAN1//CAN2
*	@time:				//22-01-03
*	@ReadMe:			//���øú���ֱ�����CAN����
								//����̨�ĽǶ�ÿ�ζ��ᷢ��
								//����������ÿִ��ʮ�η���һ�Σ���ʱ�����ͽǶ�
************************************************************************************************************************************/
uint8_t CANSendCHtoGM(CAN_HandleTypeDef *hcan)
{
	static uint8_t number = 1;		//��¼ִ�д���	
	//ִ�д����ۼ�
	++number;

	//���ݷ��Ͳ���
	if ((number%10) != 0)
	{
//�Ƚ�Ҫ���͵����ݽ������
		ChassisTXResolve(0);
//				my_CAN_Send_UNION(hcan,df_CHControlAngle_ID, CanCommunit_t.chTOgm.sendData[0], CanCommunit_t.chTOgm.sendData[1], 
//																										 CanCommunit_t.chTOgm.sendData[2], CanCommunit_t.chTOgm.sendData[3], 8);		//���ͽǶ�

	}
	else if (number%10 == 0)
	{
		number = 1;
		//�Ƚ�Ҫ���͵����ݽ������
		ChassisTXResolve(1);
		my_CAN_Send_UNION(hcan , df_CHControlData_ID , CanCommunit_t.chTOgm.sendData[0] , CanCommunit_t.chTOgm.sendData[1] ,
																								CanCommunit_t.chTOgm.sendData[2] , CanCommunit_t.chTOgm.sendData[3] , 8);			//��������
	}
	return df_re_ok;
}

