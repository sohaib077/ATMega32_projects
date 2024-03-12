#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include <avr/delay.h>
#include "LCD_config.h"
#include "LCD_interface.h"
#include "../../MCAL/DIO/DIO_interface.h"

void LCD_voidSendCommand(u8 Copy_u8Command) {
	DIO_u8SetPinValue(LCD_CTR_PORT, LCD_RS_PIN, DIO_u8PIN_LOW);
	DIO_u8SetPinValue(LCD_CTR_PORT, LCD_RW_PIN, DIO_u8PIN_LOW);
	DIO_u8SetPortValue(LCD_DATA_PORT, Copy_u8Command);
	DIO_u8SetPinValue(LCD_CTR_PORT, LCD_E_PIN, DIO_u8PIN_HIGH);
	_delay_ms(4);
	DIO_u8SetPinValue(LCD_CTR_PORT, LCD_E_PIN, DIO_u8PIN_LOW);

}
;

void LCD_voidSendData(u8 Copy_u8Data) {
	DIO_u8SetPinValue(LCD_CTR_PORT, LCD_RS_PIN, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(LCD_CTR_PORT, LCD_RW_PIN, DIO_u8PIN_LOW);
	DIO_u8SetPortValue(LCD_DATA_PORT, Copy_u8Data);
	DIO_u8SetPinValue(LCD_CTR_PORT, LCD_E_PIN, DIO_u8PIN_HIGH);
	_delay_ms(4);
	DIO_u8SetPinValue(LCD_CTR_PORT, LCD_E_PIN, DIO_u8PIN_LOW);

}
;

void LCD_voidSendString(pu8 Copy_pu8Data) {
	u8 i = 0;
	while (Copy_pu8Data[i] != '\0') {
		LCD_voidSendData(Copy_pu8Data[i]);
		i++;
	}
}
;

void LCD_voidInit() {
//	DIO_u8SetPortDirection(LCD_DATA_PORT, DIO_u8PORT_OUTPUT);
//	DIO_u8SetPinDirection(LCD_CTR_PORT, LCD_RW_PIN, DIO_u8PIN_OUTPUT);
//	DIO_u8SetPinDirection(LCD_CTR_PORT, LCD_RS_PIN, DIO_u8PIN_OUTPUT);
//	DIO_u8SetPinDirection(LCD_CTR_PORT, LCD_E_PIN, DIO_u8PIN_OUTPUT);

	_delay_ms(40);
	LCD_voidSendCommand(FUNC_SET_SMALL_TWO_LINE);
	LCD_voidSendCommand(DISPLAY_ON_NO_CURSOR);
	LCD_voidSendCommand(DISPLAY_CLEAR);
}
;

void LCD_voidShiftDisplayRight(u8 Copy_u8ShiftingNumber) {
	for (u8 i = 0; i < Copy_u8ShiftingNumber; i++) {
		_delay_ms(100);
		LCD_voidSendCommand(SHIFT_DISPLAY_RIGHT);
	}
}

void LCD_voidShiftDisplayLeft(u8 Copy_u8ShiftingNumber) {
	for (u8 i = 0; i < Copy_u8ShiftingNumber; i++) {
		_delay_ms(100);
		LCD_voidSendCommand(SHIFT_DISPLAY_LEFT);
	}
}

void LCD_voidSetDDRAMAddress(u8 Copy_u8Y, u8 Copy_u8X) {
	u8 Local_u8NewAddress = 0b10000000;
	Local_u8NewAddress += ((Copy_u8Y * 0x40) + Copy_u8X);
	LCD_voidSendCommand(Local_u8NewAddress);
}

void LCD_voidWriteSpecialCharacter(pu8 Copy_pu8Character,
		u8 Copy_u8CharacterPos, u8 Copy_u8X, u8 Copy_u8Y, u8 Copy_u8Direction) {
	u8 Local_u8NewAddress = 0b01000000;
	LCD_voidSendCommand(Local_u8NewAddress + (8 * Copy_u8CharacterPos));

	for (int i = 0; i < 8; ++i)
		LCD_voidSendData(Copy_pu8Character[i]);

	if (Copy_u8Direction == LCD_WRITE_FROM_LEFT)
		LCD_voidSetDDRAMAddress(Copy_u8Y, Copy_u8X);
	else
		LCD_voidSetDDRAMAddress(Copy_u8Y, 15 - Copy_u8X);
	LCD_voidSendData(Copy_u8CharacterPos);
}

void LCD_voidWriteSpecialString(u8 Copy_pu8String[][8],
		u8 Copy_u8NumberOfCharacters, u8 Copy_u8Direction, u8 Copy_u8X,
		u8 Copy_u8Y) {
	for (int i = 0; i < Copy_u8NumberOfCharacters; ++i) {
		LCD_voidWriteSpecialCharacter(Copy_pu8String[i], i, Copy_u8X + i,
				Copy_u8Y, Copy_u8Direction);
	}
}
void LCD_voidWriteNumber(f64 Copy_f64Number) {
	if (Copy_f64Number < 0) {
		LCD_voidSendData('-');
		Copy_f64Number *= -1;
	} else if (Copy_f64Number == 0) {
		LCD_voidSendData('0');
		return;
	}
	s64 Local_s64CopyNumber = (s64) Copy_f64Number;
	u8 Local_u8NumberDigits = 0;
	while (Local_s64CopyNumber != 0) {
		Local_u8NumberDigits++;
		Local_s64CopyNumber /= 10;
	}
	Local_s64CopyNumber = (s64) Copy_f64Number;
	u8 Local_u8arrStringData[Local_u8NumberDigits];
	if (Local_s64CopyNumber != 0) {
		while (Local_s64CopyNumber != 0) {
			Local_u8arrStringData[--Local_u8NumberDigits] = (Local_s64CopyNumber
					% 10) + '0';
			Local_s64CopyNumber /= 10;
		}
		LCD_voidSendString(Local_u8arrStringData);
	} else {
		LCD_voidSendData('0');
	}
	Local_s64CopyNumber = (s64) Copy_f64Number;
	if (Local_s64CopyNumber != Copy_f64Number) {
		LCD_voidSendData('.');
		Copy_f64Number *= 1000;
		Local_s64CopyNumber *= 1000;
		Local_s64CopyNumber = (s64) Copy_f64Number - Local_s64CopyNumber;
//		Copy_f64Number -= Local_s64CopyNumber;
//		Local_s64CopyNumber = ((s64)Copy_f64Number * 1000);
		u8 Local_u8FloatDigits = 4;
		s32 Local_u8Temp = 0;
		while (--Local_u8FloatDigits) {
			Local_u8Temp = (Local_u8Temp * 10) + (Local_s64CopyNumber % 10);
			Local_s64CopyNumber /= 10;
		}
		Local_u8FloatDigits = 4;
		while (--Local_u8FloatDigits) {
			LCD_voidSendData((Local_u8Temp % 10) + '0');
			Local_u8Temp /= 10;
		}
//		LCD_voidSendString(Local_u8arrStringData);
	}
}

