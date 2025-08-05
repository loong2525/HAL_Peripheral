/**
 ****************************************************************************************************
 * @file        tpl0401a.c
 * @author      ��һ����
 * @version     V1.0
 * @date        2020-04-21
 * @brief       TPL0401A��������
 ****************************************************************************************************
 */


#include "tpl0401a.h"

uint8_t Step = 0;	// TPL0401A???,???0~127
float RWH, RWL;		// RWH?RWL????,???????
/**
 * @brief       TPL0401A��ʼ��
 * @param       ��
 * @retval      ��
 */
void tpl0401a_init(void)
{
	iic_init();
	HAL_Delay(10);

	tpl0401a_write_reg(0x40);
}   

/**
 * @brief       TPL0401Aд�Ĵ���
 * @param       Data������
 * @retval      ��
 */
void tpl0401a_write_reg(uint8_t Data)
{	
	iic_start();
	iic_send_byte(TPL0401A_ADDRESS_W);
	iic_wait_ack();
	iic_send_byte(0x00);
	iic_wait_ack();
	iic_send_byte(Data);
	iic_wait_ack();
	iic_stop();
}

/**
 * @brief       TPL0401A���Ĵ���
 * @param       ��
 * @retval      ���յ�������(1�ֽ�)
 */
uint8_t tpl0401a_read_reg(void)
{
	uint8_t data = 0;
	
	iic_start();
	iic_send_byte(TPL0401A_ADDRESS_W);
	iic_wait_ack();
	iic_send_byte(0x00);
	iic_wait_ack();
	
	iic_start();
	iic_send_byte(TPL0401A_ADDRESS_R);
	iic_wait_ack();
	data = iic_read_byte(0);
	iic_stop();

	return data;
}

