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
#include "../MCAL/ADC/ADC_interface.h"
#include "../HAL/LCD/LCD_interface.h"
#include <util/delay.h>
#include <string.h>

void ADC_voidCallBack(u32 Copy_u32CopyDigitalValue);
void main() {
	PORT_voidInit();
	GIE_voidEnable();
	ADC_voidInit();
	LCD_voidInit();
	LCD_voidSendString("Temperature = ");
	while (1) {
		ADC_u8ReadAsynchronous(ADC_CH0, ADC_voidCallBack);
	}
}

void ADC_voidCallBack(u32 Copy_u32CopyDigitalValue) {
	static u32 Local_u32Flag;
	static u32 Local_u32AnalogValue;
	static u32 Local_u32TempValue;
	Local_u32AnalogValue = (Copy_u32CopyDigitalValue * 5000) / 1024;
	Local_u32TempValue = Local_u32AnalogValue / 10;

	if (Local_u32Flag != Local_u32TempValue) {
		Local_u32Flag = Local_u32TempValue;
		LCD_voidSetDDRAMAddress(0, 14);
		LCD_voidWriteNumber(Local_u32TempValue);
		if(Local_u32TempValue > 30) {
			/* turn on air conditioner and turn off heater */
			DIO_u8SetPinValue(DIO_u8PORTD , DIO_u8PIN1 , DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(DIO_u8PORTD , DIO_u8PIN0 , DIO_u8PIN_LOW);
		}else if(Local_u32TempValue >= 20){
			/* turn off air conditioner and turn off heater */
			DIO_u8SetPinValue(DIO_u8PORTD , DIO_u8PIN1 , DIO_u8PIN_LOW);
			DIO_u8SetPinValue(DIO_u8PORTD , DIO_u8PIN0 , DIO_u8PIN_LOW);
		}else{
			/* turn off air conditioner and turn on heater */
			DIO_u8SetPinValue(DIO_u8PORTD , DIO_u8PIN1 , DIO_u8PIN_LOW);
			DIO_u8SetPinValue(DIO_u8PORTD , DIO_u8PIN0 , DIO_u8PIN_HIGH);
		}
	}
}

