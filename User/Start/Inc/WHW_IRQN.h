#ifndef __WHW_IRQN_H
#define __WHW_IRQN_H

#include "All_Init.h"

extern void BSP_TIM_IRQHandler(TIM_HandleTypeDef *htim);
extern void BSP_UART_IRQHandler(UART_HandleTypeDef *huart);

#endif
