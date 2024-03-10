/*
 * main.c
 *
 *  Created on: Sep 10, 2023
 *      Author: sohai
 */
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/PORT/PORT_interface.h"
#include "../MCAL/GIE/GIE_interface.h"
#include "../MCAL/TIMERS/TIMERS_interface.h"
#include "../HAL/SSD/SSD_interface.h"
#include <util/delay.h>

SSD ssd = { SSD_CATHODE_TYPE, DIO_u8PORTC, DIO_u8PORTA, DIO_u8PIN0 };

void ISR();

int main() {
	PORT_voidInit();
	GIE_voidEnable();
	TIMER0_voidInit();
	TIMERS_u8SetCallBack(ISR, TIMER0_COMP_INDEX);

	SSD_u8EnableSsd(&ssd);
	SSD_u8SetNumber(1, &ssd);

	while (1);
	return 0;
}

void ISR() {
	static u16 overflowCounts = 0;
	static u8 seconds = 1;
	static u8 flag = 1;
	overflowCounts++;
	if (overflowCounts == 4000) {
		if (seconds == 20)
			seconds = 1;
		else
			seconds++;
		overflowCounts = 0;
	}
	if (overflowCounts % 40 == 0) {
		if (flag) {
			SSD_u8DisableSsd(&ssd);
			SSD_u8SetNumber((seconds / 10), &ssd);
			flag = 0;
		} else {
			SSD_u8EnableSsd(&ssd);
			SSD_u8SetNumber(seconds % 10, &ssd);
			flag = 1;
		}
	}
}
