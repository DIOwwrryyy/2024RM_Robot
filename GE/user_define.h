#ifndef USER_DEFINE__H
#define USER_DEFINE__H
/*
所有有关灵敏度的赋值  大小不可以超过 1  最小为0.01
											大小不可以超过 1  最小为0.01
											大小不可以超过 1  最小为0.01
*/
//鼠标灵敏度
#define user_Sensitivity_yaw 0.6f		//yaw轴基础灵敏度
#define user_Sensitivity_pitch 0.8f		//pitch轴基础灵敏度//虽然澍哥注释给的p轴但实际控制的yaw



//按键式触发//按键式触发//按键式触发//重要的事情说三遍
#define user_SuperCapPower	300			//超级电容放电功率//不可以超过350W


//操作手自定义按键区域
#define user_WindmillKey KeyBoard_qLock				//风车模式	
#define user_SupercapKey KeyBoard_r		//超级电容
#define user_CarSpinKey KeyBoard_shift		//小陀螺



//操作手自定义 
#define user_SuperCap (KeyBoard_ctrl)		//电容开关
#endif

#define SBUS_RX_BUF_NUM 36u

#define RC_FRAME_LENGTH 18u

#define RC_CH_VALUE_MIN         ((uint16_t)364)
#define RC_CH_VALUE_OFFSET      ((uint16_t)1024)
#define RC_CH_VALUE_MAX         ((uint16_t)1684)

/* ----------------------- RC Switch Definition----------------------------- */
#define KeyboardBoll (rc_ctrl.control.s1_u8 == CarKeyboard)		//键盘模式检测
#define KeyWindmillBoll rc_ctrl.control.s1_u8	//打符模式检测
#define Mouse_VX rc_ctrl.mouse.x_filter		//鼠标横向速度
#define Mouse_VY rc_ctrl.mouse.y_filter		//鼠标纵向速度
#define Mouse_R rc_ctrl.mouse.r_state	  //鼠标横向速度
#define Mouse_L rc_ctrl.mouse.l_state		//鼠标纵向速度
//按键式触发开关
#define KeyBoard_ctrl rc_ctrl.key_board.ctrl		//Ctrl键调用
#define KeyBoard_a rc_ctrl.key_board.a		//a键调用
#define KeyBoard_s rc_ctrl.key_board.s		//s键调用
#define KeyBoard_d rc_ctrl.key_board.d		//d键调用
#define KeyBoard_w rc_ctrl.key_board.w		//w键调用
#define KeyBoard_q rc_ctrl.key_board.q		//q键调用
#define KeyBoard_e rc_ctrl.key_board.e		//e键调用
#define KeyBoard_r rc_ctrl.key_board.r		//r键调用
#define KeyBoard_t rc_ctrl.key_board.t		//t键调用
#define KeyBoard_g rc_ctrl.key_board.g		//g键调用
#define KeyBoard_z rc_ctrl.key_board.z		//z键调用
#define KeyBoard_x rc_ctrl.key_board.x		//x键调用
#define KeyBoard_c rc_ctrl.key_board.c		//c键调用
#define KeyBoard_v rc_ctrl.key_board.v		//v键调用
#define KeyBoard_b rc_ctrl.key_board.b		//b键调用
#define KeyBoard_shift rc_ctrl.key_board.shift		//shift键调用
//按键式触发开关
#define KeyBoard_qLock rc_ctrl.key_board.q_preeNumber 
#define KeyBoard_eLock rc_ctrl.key_board.e_preeNumber 
#define KeyBoard_rLock rc_ctrl.key_board.r_preeNumber 
#define KeyBoard_fLock rc_ctrl.key_board.f_preeNumber
#define KeyBoard_gLock rc_ctrl.key_board.g_preeNumber 
#define KeyBoard_zLock rc_ctrl.key_board.z_preeNumber 	
#define KeyBoard_xLock rc_ctrl.key_board.x_preeNumber 	
#define KeyBoard_cLock rc_ctrl.key_board.c_preeNumber 
#define KeyBoard_vLock rc_ctrl.key_board.v_preeNumber
#define KeyBoard_bLock rc_ctrl.key_board.b_preeNumber 
#define KeyBoard_shiftLock rc_ctrl.key_board.shift_preeNumber 
#define KeyBoard_ctrlLock rc_ctrl.key_board.ctrl_preeNumber 


#ifndef df_now
	#define df_now 0
	#define df_last 1
	#define df_llast 2
#endif
/****************键鼠状态定义***************/
#ifndef df_passState
	//鼠标状态
	#define df_click 1	//点按
	#define df_uplift 3		//松开
	#define df_press 2	//长按
	//键盘状态
	#define df_click 1	//点按
	#define df_keyuplift 0		//松开
	#define df_press 2	//长按
#endif
#include "main.h"
/***********************************云台数据转移到底盘******************************************/
typedef  struct
{
      struct
	      {	
	        	int16_t ch0_int16;
	        	int16_t ch1_int16;
	        	int16_t ch2_int16;
	        	int16_t ch3_int16;
	        	uint8_t s1_u8;
	        	uint8_t s2_u8;
	        	int16_t direction;
	        	int8_t Bool_i8;			//当数据产生错误处理时的计数器
	       } __attribute__ ((__packed__))control; 
				
      struct
        {
                int16_t x;
                int16_t y;
                int16_t z;
                uint8_t press_l;
                uint8_t press_r;
					
					float x_flt;
		      float x_filter;		//处理后使用的鼠标值
		      float x_max;	//记录鼠标的最大值用来校准鼠标		
		      float y_flt;
		      float y_filter;		//处理后使用的鼠标值
		      float y_max;	//记录鼠标的最大值用来校准鼠标
		      uint8_t r_state:4;
		      uint8_t l_state:4;
		      uint8_t r_pressTime;
		      uint8_t l_pressTime;
        } __attribute__ ((__packed__))mouse;
       struct
	      {
		       uint8_t w:4;
		       uint8_t s:4;
		       uint8_t a:4;
		       uint8_t d:4;
		       uint8_t shift:4;		//小陀螺
		       uint8_t ctrl:4;		//电容
		       uint8_t q:4;
		       uint8_t e:4;
		       uint8_t r:4;
		       uint8_t f:4;
		       uint8_t g:4;
		       uint8_t z:4;
		       uint8_t x:4;
		       uint8_t c:4;
		       uint8_t v:4;
		       uint8_t b:4;
		       uint8_t w_pressTime;
		       uint8_t s_pressTime;
		       uint8_t a_pressTime;
		       uint8_t d_pressTime;
		       uint8_t q_preeNumber:1;		//风车模式
		       uint8_t e_preeNumber:1;		//爬坡状态
		       uint8_t r_preeNumber:1;		
		       uint8_t f_preeNumber:1;
		       uint8_t g_preeNumber:1;
		       uint8_t z_preeNumber:1;
		       uint8_t x_preeNumber:1;
		       uint8_t c_preeNumber:1;//V和B键被占用不做调整
		       uint8_t shift_preeNumber:1;
		       uint8_t ctrl_preeNumber:1;
	    } __attribute__ ((__packed__))key_board;

} __attribute__ ((__packed__))RC_ctrl_t;

extern RC_ctrl_t rc_ctrl;
/**************************************视觉传递***********************************/
struct ConToVis_Typdef
{
	float pitchAngle;
	float yawAngle;
	uint32_t time;		//电控的系统时间
	uint8_t state;		//请求的状态
	uint8_t bullet;		//子弹射速
};

struct visionData_typdef
{
	struct
	{
		float pitchAngle[2];
		float pitchSpeed;
		float yawAngle[2];
		float yawSpeed;
		uint32_t visionTime;
		uint8_t visionState : 3;			//反陀螺
		uint8_t shootBoll : 1;		//射击
		uint8_t target : 1;			//识别成功的标志位(1是有目标，0是无目标)
		uint8_t : 0;
//				uint8_t yawchangeTime;		//尖峰滤波使用
//				uint8_t pitchchangeTime;
		uint8_t resolveState;		//数据解算的状态
		uint16_t FPS;	//视觉的帧率显示
	}receive;
	struct ConToVis_Typdef transmit;
};
extern struct visionData_typdef visionData_t;



