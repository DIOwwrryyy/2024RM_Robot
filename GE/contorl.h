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

union remote_union_typdef		//ʹ�ù�������������
{
	struct {
		//ң������
		uint64_t ch0:11;
		uint64_t ch1:11;
		uint64_t ch2:11;
		uint64_t ch3:11;
		uint64_t s1:2;
		uint64_t s2:2;
		//�������
		int64_t	mouse_x:16;
		int64_t	mouse_y:16;
		int64_t	mouse_z:16;
		int64_t	mouse_r:8;
		int64_t	mouse_l:8;
		//��������
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
		//ң�ػ���
		uint64_t direction:11;
		uint64_t :0;
	}dataNeaten;
	//���յ�������
	uint8_t getData[18];
};
extern union remote_union_typdef remote_union_t;	

//���̿��ƺ���
uint8_t ControlCH(uint8_t mod);

#endif
