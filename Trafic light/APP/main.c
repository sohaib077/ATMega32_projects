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
#include "../HAL/LCD/LCD_interface.h"
#include <util/delay.h>

u8 Global_u8Seconds ;
u8 Global_u8RedStateEndTime = 7;
u8 Global_u8YellowStateEndTime = 10;	/* 7 + 3 */
u8 Global_u8GreenStateEndTime = 20; 	/* 7 + 3 + 10 */

#define RED_STATE		0
#define YELLOW_STATE	1
#define GREEN_STATE		2

u8 Global_u8TrafficState = RED_STATE;

u8 RemainigSeconds();
void ISR();
void main() {
	PORT_voidInit();
	LCD_voidInit();
	TIMER0_voidInit();
	GIE_voidEnable();
	LCD_voidSendString("Rem seconds = ");
	LCD_voidSetDDRAMAddress(0,14);
	LCD_voidWriteNumber(7);
	TIMERS_u8SetCallBack(ISR,TIMER0_COMP_INDEX);
	while (1) ;
}

void ISR(){
	static u16 overflowCounts = 0;
	overflowCounts++;
	if(overflowCounts == 4000){

		Global_u8Seconds++;

		/* changing traffic light status */
		if(Global_u8Seconds == Global_u8RedStateEndTime){
			/* Yellow state  on */
			DIO_u8SetPinValue(DIO_u8PORTD , DIO_u8PIN0 , DIO_u8PIN_LOW);
			DIO_u8SetPinValue(DIO_u8PORTD , DIO_u8PIN1 , DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(DIO_u8PORTD , DIO_u8PIN2 , DIO_u8PIN_LOW);

			Global_u8TrafficState = YELLOW_STATE;

		}else if(Global_u8Seconds == Global_u8YellowStateEndTime){
			/* Green state  on */
			DIO_u8SetPinValue(DIO_u8PORTD , DIO_u8PIN0 , DIO_u8PIN_LOW);
			DIO_u8SetPinValue(DIO_u8PORTD , DIO_u8PIN1 , DIO_u8PIN_LOW);
			DIO_u8SetPinValue(DIO_u8PORTD , DIO_u8PIN2 , DIO_u8PIN_HIGH);

			Global_u8TrafficState = GREEN_STATE;

		}else if(Global_u8Seconds == Global_u8GreenStateEndTime){
			/* Red state  on */
			DIO_u8SetPinValue(DIO_u8PORTD , DIO_u8PIN0 , DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(DIO_u8PORTD , DIO_u8PIN1 , DIO_u8PIN_LOW);
			DIO_u8SetPinValue(DIO_u8PORTD , DIO_u8PIN2 , DIO_u8PIN_LOW);

			Global_u8TrafficState = RED_STATE;

			/* reseting seconds */
			Global_u8Seconds = 0;
		}

		/* Removing 0 from LCD */
		if(Global_u8Seconds == 11){
			LCD_voidSetDDRAMAddress(0,15);
			LCD_voidSendData(' ');
		}

		LCD_voidSetDDRAMAddress(0,14);
		LCD_voidWriteNumber(RemainigSeconds());
		overflowCounts = 0;

	}
}

u8 RemainigSeconds(){

	if(Global_u8TrafficState == RED_STATE)
		return Global_u8RedStateEndTime - Global_u8Seconds;

	else if(Global_u8TrafficState == YELLOW_STATE)
		return Global_u8YellowStateEndTime - Global_u8Seconds;

	else
		return Global_u8GreenStateEndTime - Global_u8Seconds;

}




