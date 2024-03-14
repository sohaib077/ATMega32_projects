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
#include "../MCAL/EXTI/EXTI_interface.h"
#include "../MCAL/TIMERS/TIMERS_interface.h"
#include "../HAL/LCD/LCD_interface.h"
#include <util/delay.h>
#include <string.h>

u8 Global_u8CarsInGarage;
void INT0_voidCallBack();
void INT1_voidCallBack();
void main() {
	PORT_voidInit();
	LCD_voidInit();
	EXTI_u8EXTIEnable(0, EXTI_ON_CHANGE);
	EXTI_u8EXTIEnable(1, EXTI_ON_CHANGE);
	EXTI_u8EXTISetCallBack(0, INT0_voidCallBack);
	EXTI_u8EXTISetCallBack(1, INT1_voidCallBack);
	TIMER1_voidInit();
	LCD_voidSendString("There're 0 car");
	LCD_voidSetDDRAMAddress(1, 0);
	LCD_voidSendString("garage has space");
	GIE_voidEnable();
	while (1);
}

/* It's for entering the garage */
void INT0_voidCallBack() {
	static u8 flag = 0;
	if(Global_u8CarsInGarage < 3){
		if (!flag) {
			TIMER1_u8SetCompareMatch(TIMER1_CHANNEL_A , 1499);
			flag = 1;
		} else {
			TIMER1_u8SetCompareMatch(TIMER1_CHANNEL_A , 999);
			LCD_voidSetDDRAMAddress(0, 9);
			LCD_voidWriteNumber(++Global_u8CarsInGarage);
			if(Global_u8CarsInGarage == 3){
				LCD_voidSetDDRAMAddress(1, 7);
				LCD_voidSendString("is full  ");
			}
			flag = 0;
		}
	}
}

/* It's for exiting the garage */
void INT1_voidCallBack() {
	static u8 flag = 0;
	if(Global_u8CarsInGarage > 0){
		if (!flag) {
			TIMER1_u8SetCompareMatch(TIMER1_CHANNEL_A , 1499);
			flag = 1;
		} else {
			TIMER1_u8SetCompareMatch(TIMER1_CHANNEL_A , 999);
			LCD_voidSetDDRAMAddress(0, 9);
			LCD_voidWriteNumber(--Global_u8CarsInGarage);
			if(Global_u8CarsInGarage == 2){
				LCD_voidSetDDRAMAddress(1, 7);
				LCD_voidSendString("has space");
			}
			flag = 0;
		}
	}
}

