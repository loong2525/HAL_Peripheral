/**
 ****************************************************************************************************
 * @file        tpl0401a.c
 * @author      科一电子
 * @version     V1.0
 * @date        2020-04-21
 * @brief       TPL0401A驱动程序
 ****************************************************************************************************
 */
#ifndef __TPL0401A_H
#define __TPL0401A_H
#include "include.h"

extern uint8_t Step;
extern float RWH, RWL;
//step:0-127
//RWH = (128 - Step) *78.125;
//RWL = Step * 78.125;

/*********************************设备地址*********************************************/  
#define TPL0401A_ADDRESS_W	0x5C	// 写地址
#define TPL0401A_ADDRESS_R	0x5D	// 读地址

/*******************************外部函数声明*******************************************/  													  
extern void tpl0401a_init(void);
extern void tpl0401a_write_reg(uint8_t Data);
extern uint8_t tpl0401a_read_reg(void);
		 
#endif
