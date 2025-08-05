#ifndef __MENU_H
#define __MENU_H

#include <include.h>

typedef struct MENU
{
	//本级菜单动作控制
	uint16_t return_flag;
	uint16_t confirm_flag;
	uint16_t previous_item_flag;
	uint16_t next_item_flag;
}MENU;

extern MENU menu;
extern uint16_t MenuIndex;
void Menu_switch(MENU* menu);
void Menu_show(void);





#endif
