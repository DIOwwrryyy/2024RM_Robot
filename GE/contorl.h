#ifndef CONTROL__H
#define CONTROL__H

#include "stdint.h"
#include "chassis.h"
#include "can.h"
#include "gpio.h"
#include "root.h"

#ifndef df_re_error
	#define df_re_ok 1
	#define df_re_error 0
#endif

union remote_union_typdef		//使用共用体整合数据
{
	struct {
		//遥控数据
		uint64_t ch0:11;
		uint64_t ch1:11;
		uint64_t ch2:11;
		uint64_t ch3:11;
		uint64_t s1:2;
		uint64_t s2:2;
		//鼠标数据
		int64_t	mouse_x:16;
		int64_t	mouse_y:16;
		int64_t	mouse_z:16;
		int64_t	mouse_r:8;
		int64_t	mouse_l:8;
		//键盘数据
		uint64_t keyboard_w:1;
		uint64_t keyboard_s:1;
		uint64_t keyboard_a:1;
		uint64_t keyboard_d:1;
		uint64_t keyboard_shift:1;
		uint64_t keyboard_ctrl:1;
		uint64_t keyboard_q:1;
		uint64_t keyboard_e:1;
		uint64_t keyboard_r:1;
		uint64_t keyboard_f:1;
		uint64_t keyboard_g:1;
		uint64_t keyboard_z:1;
		uint64_t keyboard_x:1;
		uint64_t keyboard_c:1;
		uint64_t keyboard_v:1;
		uint64_t keyboard_b:1;
		//遥控滑轮
		uint64_t direction:11;
		uint64_t :0;
	}dataNeaten;
	//接收到的数组
	uint8_t getData[18];
};
extern union remote_union_typdef remote_union_t;	

//底盘控制函数
uint8_t ControlCH(uint8_t mod);

#endif
