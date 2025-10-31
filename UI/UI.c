#include "main.h"
#include "Write_Data.h"
#include "stdint.h"
#include "string.h"

ALL_TX_Typdef ALL_TX;
graphic_data_Typdef graphic_data;
uint8_t dau8[255];

void UI_TX_Write_graphics_One_gky(graphic_data_Typdef *graphic_data_1)
{
	graphic_data_1->color = 0;
	graphic_data_1->details_a = 0;
	graphic_data_1->details_b = 0;
	graphic_data_1->details_c = 0;
	graphic_data_1->graphic_name[0] = 0;
	graphic_data_1->graphic_tpye = 0;
	graphic_data_1->layer = 0;
	graphic_data_1->operate_tpye = 0;
	graphic_data_1->details_d = 0;
	graphic_data_1->details_e = 0;
	graphic_data_1->start_x = 0;
	graphic_data_1->start_y = 0;
	graphic_data_1->width = 0;
	
	UI_TX_Write_graphics_One(&ALL_TX , 0x0001 , 0x0101 ,graphic_data_1 , dau8);
	
//	HAL_UART_Trans;
}
