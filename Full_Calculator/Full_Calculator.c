/*
 * main.c
 *
 *  Created on: Sep 10, 2023
 *      Author: sohai
 */
#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_interface.h"
#include "../HAL/LCD/LCD_config.h"
#include "../HAL/LCD/LCD_interface.h"
#include "../HAL/KeyPad/KEYPAD_config.h"
#include "../HAL/KeyPad/KEYPAD_interface.h"
#include <util/delay.h>

#define NOT_USED 0
#define USED 1
#define FALSE 0
#define TRUE 1


static u8 Global_pu8UpperSpecialStringData[][8] = {{
                                              0,
                                              0,
                                              0,
											  0,
                                              0,
                                              1,
											  2,
                                              0,
                                      },
                                      {
                                    		  0b00011111,
											  0b00011111,
											  0b00011111,
                                              0b00000100,
                                              0b00011100,
                                              0b00000110,
                                              0b00000101,
                                              0,
                                      },
                                      {
                                    		  0,
											  0,
                                              0,
											  4,
                                              8,
                                              0b00010000,
                                              0,
                                              0,
                                      },

};
static u8 Global_pu8LowerSpecialStringData[][8] = {
									  {
                                              0,
                                              0,
                                              0,
											  0,
                                              3,
                                              2,
											  0,
                                              0,
                                      },
                                      {
                                    		  0b00000100,
											  0b00000100,
											  0b00000100,
                                              0b00001010,
											  0b00010001,
                                              1,
                                              1,
                                              0,
                                      },
									  {
											  0
									  },

};


static u8 Global_pu8UpperSpecialStringData2[][8] = {{
										    0,
										    0,
											0,
											2,
											1,
										    0,
											0,
											0,
                                      },
                                      {
                                    		  0b00011111,
											  0b00011111,
											  0b00011111,
                                              0b00000100,
                                              0b00011111,
                                              0b00000100,
                                              0b00000100,
                                              0,
                                      },
                                      {
                                    		  0,
											  0,
											  0,
											  0,
											  0b00010000,
											  0b00001000,
											  0b00000100,
											  0,
                                     },

};
static u8 Global_pu8LowerSpecialStringData2[][8] = {{
                                    		  0,
											  0,
											  0,
                                              0,
                                              3,
                                              2,
											  0,
                                              0,
                                      },
                                      {
                                    		  0b00000100,
											  0b00000100,
											  0b00000100,
                                              0b00001010,
											  0b00010001,
                                              1,
                                              1,
                                              0,
                                      },
									  {
                                              0
									  },

};


s32 Global_u64Operand1 = NULL;
s32 Global_u64Operand2 = NULL;
f64 Global_u64Ans = NULL;
u8 Global_u8Operator = NULL;
u8 Global_u8DigitsNumber = 0;
u8 Global_u8IsAnswered = FALSE;
u8 Global_u8Operand1State = NOT_USED;
u8 Global_u8Operand2State = NOT_USED;
u8 Global_u8NegativeFlag = FALSE;
u8 Global_u8ModeFlag ;

void NormalCalculator(u8 Local_u8SwitchValue);
void DisplayIntro();
void ClearDisplay();
void ResetLcd(u8 Copy_u8ClearFlag , u8 Copy_u8DigitsNumber);
void DisplayDataWithShiftingIfNeeded(u8 Copy_u8Data);
void HandlingOperands(u8 Copy_u8Data);
void DisplayAnswer();
u8 GetDigitsNumber(s64 Copy_s64Number);

void BinCalculator(u8 Local_u8SwitchValue);
void DisplayDecToBinAns();
void DisplayBinToDecAns();
void main() {
	LCD_voidInit();
	KEYPAD_voidInit();
	u8 Local_u8SwitchValue;
	DisplayIntro();
	LCD_voidSendString("WELCOME");
	LCD_voidSetDDRAMAddress(1 , 0);
	LCD_voidSendString("1.NORMAL2.BINARY");
	while(Global_u8ModeFlag != '1' && Global_u8ModeFlag != '2')
		Global_u8ModeFlag = KEYPAD_u8GetSwitchValue();

	LCD_voidSendCommand(DISPLAY_CLEAR);

	if(Global_u8ModeFlag == '2'){
		LCD_voidSetDDRAMAddress(0,0);
		LCD_voidSendString("3. Dec -> Bin");
		LCD_voidSetDDRAMAddress(1,0);
		LCD_voidSendString("4. Bin -> Dec");
		while(Global_u8ModeFlag != '3' && Global_u8ModeFlag != '4')
		Global_u8ModeFlag = KEYPAD_u8GetSwitchValue();
	}
		ClearDisplay();

	while (1) {
			Local_u8SwitchValue = KEYPAD_u8GetSwitchValue();
		if(Global_u8ModeFlag == '1')
			NormalCalculator(Local_u8SwitchValue);
		else
			BinCalculator(Local_u8SwitchValue);

	}
}


void NormalCalculator(u8 Local_u8SwitchValue) {
	if (Local_u8SwitchValue != KEYPAD_NOT_PRESSED_VALUE) {
		if (Local_u8SwitchValue == '=')
			DisplayAnswer();
		else if (Local_u8SwitchValue == '%')
			ResetLcd(1, 0);
		else {
			DisplayDataWithShiftingIfNeeded(Local_u8SwitchValue);
			HandlingOperands(Local_u8SwitchValue);
		}
	}
	//			LCD_voidSendData(Local_u8SwitchValue);
}

void BinCalculator(u8 Local_u8SwitchValue){
	if (Local_u8SwitchValue != KEYPAD_NOT_PRESSED_VALUE) {
			if (Local_u8SwitchValue == '=')
				if(Global_u8ModeFlag == '3')
					DisplayDecToBinAns();
				else
					DisplayBinToDecAns();
			else if (Local_u8SwitchValue == '%')
				ResetLcd(1, 0);
			else {
				DisplayDataWithShiftingIfNeeded(Local_u8SwitchValue);
				HandlingOperands(Local_u8SwitchValue);
			}
		}
}

void DisplayDecToBinAns(){
	if(Global_u8Operator != NULL){
		ClearDisplay();
		LCD_voidSendString("INVALID INPUT");
		_delay_ms(70);
		ResetLcd(1 , 13);
		return ;
	}

	u8 Local_u8DigitsNumber = 0;
	s32 Local_s32CopyOperand1 = Global_u64Operand1;
	u8 Local_u8Flag = 0;
	while(Local_s32CopyOperand1 != 0 || Local_u8Flag == 0){
		Local_u8Flag = 1;
		Local_s32CopyOperand1 /= 2;
		Local_u8DigitsNumber++;
	}
	Local_u8Flag = 0;
	u8 Local_u8ABinaryNumber [Local_u8DigitsNumber+1];
	u8 Local_u8Counter = Local_u8DigitsNumber-1;
	while(Global_u64Operand1 > 0 || Local_u8Flag == 0){
		Local_u8Flag = 1;
		Local_u8ABinaryNumber[Local_u8Counter--] = (Global_u64Operand1%2 + '0');
		Global_u64Operand1 /= 2;
	}
	Local_u8ABinaryNumber[Local_u8DigitsNumber+1] = '\0';
	ClearDisplay();
	LCD_voidSendString(Local_u8ABinaryNumber);
	ResetLcd(0 , Local_u8DigitsNumber);
	Global_u8IsAnswered = 1;
//	ResetLcd(0 , Local_u8DigitsNumber);
}

u8 BinaryNumberChecker(s32 Copy_s32Number){
	if(Copy_s32Number < 0) return 0;
	while(Copy_s32Number > 0){
		if(Copy_s32Number % 10 > 1) return 0;
		Copy_s32Number /= 10;
	}
	return 1;
}

void DisplayBinToDecAns(){
	if(Global_u8Operator != NULL || ! BinaryNumberChecker(Global_u64Operand1) ){
		ClearDisplay();
		LCD_voidSendString("INVALID INPUT");
		_delay_ms(70);
		ResetLcd(1 , 13);
		return ;
	}

	u8 Local_u8DigitsNumber = 0;
	s32 Local_s32CopyOperand1 = Global_u64Operand1;
	u32 Local_u32Base = 1;
	u32 Local_s32DecNumber = 0;
	while(Local_s32CopyOperand1 != 0 ){
		Local_s32DecNumber += ((Local_s32CopyOperand1 % 10 )* Local_u32Base) ;
		Local_u32Base *= 2;
		Local_s32CopyOperand1 /= 10;
		Local_u8DigitsNumber++;
	}
	ClearDisplay();
	LCD_voidWriteNumber(Local_s32DecNumber);
	ResetLcd(0 , Local_u8DigitsNumber);
	Global_u8IsAnswered = 1;
//	ResetLcd(0 , Local_u8DigitsNumber);
}

void DisplayIntro(){
	u8 welcome[] = {' ' ,'W' , 'E' , 'L' , 'C' , 'O' , 'M' , 'E'};
	u8 empty[] = {0};
	u8 rope[] = {0 , 0 , 0b00011111 , 0b00011111 , 0   , 0 ,0 , 0};
	for(u8 i = 0 , flag = 0; i < 19 ; i++ , flag++){
		if(flag % 2 != 0){
			LCD_voidWriteSpecialCharacter(Global_pu8UpperSpecialStringData[0],
					0, i, 0, LCD_WRITE_FROM_LEFT);
			LCD_voidWriteSpecialCharacter(Global_pu8UpperSpecialStringData[1],
					1, i + 1, 0, LCD_WRITE_FROM_LEFT);
			LCD_voidWriteSpecialCharacter(Global_pu8UpperSpecialStringData[2],
					2, i + 2, 0, LCD_WRITE_FROM_LEFT);

			LCD_voidWriteSpecialCharacter(Global_pu8LowerSpecialStringData[0],
					3, i, 1, LCD_WRITE_FROM_LEFT);
			LCD_voidWriteSpecialCharacter(Global_pu8LowerSpecialStringData[1],
					4, i + 1, 1, LCD_WRITE_FROM_LEFT);
			LCD_voidWriteSpecialCharacter(Global_pu8LowerSpecialStringData[2],
					5, i + 2, 1, LCD_WRITE_FROM_LEFT);

		} else {
			LCD_voidWriteSpecialCharacter(Global_pu8UpperSpecialStringData2[0],
					0, i, 0, LCD_WRITE_FROM_LEFT);
			LCD_voidWriteSpecialCharacter(Global_pu8UpperSpecialStringData2[1],
					1, i + 1, 0, LCD_WRITE_FROM_LEFT);
			LCD_voidWriteSpecialCharacter(Global_pu8UpperSpecialStringData2[2],
					2, i + 2, 0, LCD_WRITE_FROM_LEFT);

			LCD_voidWriteSpecialCharacter(Global_pu8LowerSpecialStringData2[0],
					3, i, 1, LCD_WRITE_FROM_LEFT);
			LCD_voidWriteSpecialCharacter(Global_pu8LowerSpecialStringData2[1],
					4, i + 1, 1, LCD_WRITE_FROM_LEFT);
			LCD_voidWriteSpecialCharacter(Global_pu8LowerSpecialStringData2[2],
					5, i + 2, 1, LCD_WRITE_FROM_LEFT);
		}

		_delay_ms(5);
		LCD_voidSetDDRAMAddress(0, i);
		LCD_voidSendData(' ');
		LCD_voidSetDDRAMAddress(0, i + 2);
		LCD_voidSendData(' ');
		LCD_voidSetDDRAMAddress(1, i);
		LCD_voidSendData(' ');
		LCD_voidSetDDRAMAddress(1, i + 2);
		LCD_voidSendData(' ');

		if (i < 14) {
			LCD_voidWriteSpecialCharacter(rope, 6, i - 1, 0,
					LCD_WRITE_FROM_LEFT);
			LCD_voidWriteSpecialCharacter(rope, 6, i - 2, 0,
					LCD_WRITE_FROM_LEFT);
		} else {
			LCD_voidSetDDRAMAddress(0, i - 2);
			LCD_voidSendData(' ');
			LCD_voidSetDDRAMAddress(0, i - 3);
			LCD_voidSendData(' ');
			LCD_voidWriteSpecialCharacter(rope, 6, i - 1, 0,
					LCD_WRITE_FROM_LEFT);
			LCD_voidWriteSpecialCharacter(rope, 6, i - 2, 0,
					LCD_WRITE_FROM_LEFT);
		}

		if (i < 14)
			for (u8 j = 8; j > 0; j--) {
				LCD_voidSetDDRAMAddress(0, i - 10 + j - 1);
				LCD_voidSendData(welcome[j - 1]);
			}
		else {

		}
	}
	LCD_voidSetDDRAMAddress(1 , 0);
	LCD_voidSendString("1.NORMAL2.BINARY");
}
//
//void DisplayIntro2(){
//	u8 welcome[] = {'W' , 'E' , 'L' , 'C' , 'O' , 'M' , 'E'};
//	u8 empty[] = {0};
//	u8 rope[] = {0 , 0 , 0b00011111 , 0b00011111 , 0   , 0 ,0 , 0};
//	for(u8 i = 0 , flag = 0; i < 25 ; i+=2 , flag++){
//		if(flag % 2 == 0){
//			LCD_voidWriteSpecialCharacter(Global_pu8UpperSpecialStringData[0] , 0 , i , 0 ,LCD_WRITE_FROM_LEFT);
//			LCD_voidWriteSpecialCharacter(Global_pu8UpperSpecialStringData[1] , 1 , i+1 , 0 ,LCD_WRITE_FROM_LEFT);
//			LCD_voidWriteSpecialCharacter(Global_pu8UpperSpecialStringData[2] , 2 , i+2 , 0 ,LCD_WRITE_FROM_LEFT);
//
//			LCD_voidWriteSpecialCharacter(Global_pu8LowerSpecialStringData[0] , 3 , i , 1 ,LCD_WRITE_FROM_LEFT);
//			LCD_voidWriteSpecialCharacter(Global_pu8LowerSpecialStringData[1] , 4 , i+1 , 1 ,LCD_WRITE_FROM_LEFT);
//			LCD_voidWriteSpecialCharacter(Global_pu8LowerSpecialStringData[2] , 5 , i+2 , 1 ,LCD_WRITE_FROM_LEFT);
//
//		}else{
//			LCD_voidWriteSpecialCharacter(Global_pu8UpperSpecialStringData2[0] , 0 ,i , 0 ,LCD_WRITE_FROM_LEFT);
//			LCD_voidWriteSpecialCharacter(Global_pu8UpperSpecialStringData2[1] , 1 ,i+1 , 0 ,LCD_WRITE_FROM_LEFT);
//			LCD_voidWriteSpecialCharacter(Global_pu8UpperSpecialStringData2[2] , 2 ,i+2 , 0 ,LCD_WRITE_FROM_LEFT);
//
//			LCD_voidWriteSpecialCharacter(Global_pu8LowerSpecialStringData2[0] , 3 ,i, 1 ,LCD_WRITE_FROM_LEFT);
//			LCD_voidWriteSpecialCharacter(Global_pu8LowerSpecialStringData2[1] , 4 ,i+1 , 1 ,LCD_WRITE_FROM_LEFT);
//			LCD_voidWriteSpecialCharacter(Global_pu8LowerSpecialStringData2[2] , 5 ,i+2 , 1 ,LCD_WRITE_FROM_LEFT);
//		}
//
//		LCD_voidWriteSpecialCharacter(rope , 6 , i-1 , 0 ,LCD_WRITE_FROM_LEFT);
//		LCD_voidWriteSpecialCharacter(rope , 6 , i-2 , 0 ,LCD_WRITE_FROM_LEFT);
//
//	for (u8 j = 7; j > 0 ; j--){
//		LCD_voidSetDDRAMAddress(0 , i-10+j-1);
//		LCD_voidSendData(welcome[j-1]);
//	}
//
//
//		_delay_ms(5);
//		LCD_voidSendCommand(DISPLAY_CLEAR);
////		LCD_voidWriteSpecialCharacter(empty[0] , 0 ,i , 0 ,LCD_WRITE_FROM_LEFT);
////		LCD_voidWriteSpecialCharacter(empty[0] , 1 ,i+1 , 0 ,LCD_WRITE_FROM_LEFT);
////		LCD_voidWriteSpecialCharacter(empty[0] , 2 ,i+2 , 0 ,LCD_WRITE_FROM_LEFT);
////		LCD_voidWriteSpecialCharacter(empty[0] , 3 ,i, 1 ,LCD_WRITE_FROM_LEFT);
////		LCD_voidWriteSpecialCharacter(empty[0] , 4 ,i+1 , 1 ,LCD_WRITE_FROM_LEFT);
////		LCD_voidWriteSpecialCharacter(empty[0] , 5 ,i+2 , 1 ,LCD_WRITE_FROM_LEFT);
////		if(flag < 7){
////			LCD_voidSetDDRAMAddress(0,flag);
////			LCD_voidSendData(welcome[flag]);
////		}
//	}
//
//}

void ClearDisplay() {
	LCD_voidSendCommand(DISPLAY_CLEAR);
	LCD_voidSetDDRAMAddress(0,5);
	if(Global_u8ModeFlag == '1')
		LCD_voidSendString("NORMAL");
	else if(Global_u8ModeFlag == '2')
		LCD_voidSendString("BINARY");
	else if(Global_u8ModeFlag == '3'){
		LCD_voidSetDDRAMAddress(0,2);
		LCD_voidSendString("Dec -> Bin");
	}
	else if(Global_u8ModeFlag == '4')
	{
		LCD_voidSetDDRAMAddress(0,2);
		LCD_voidSendString("Bin -> Dec");
	}
	LCD_voidSetDDRAMAddress(1,0);
}
void ResetLcd(u8 Copy_u8ClearFlag, u8 Copy_u8DigitsNumber) {
	if (Copy_u8ClearFlag != 0)
		ClearDisplay();
	Global_u64Operand1 = NULL;
	Global_u64Operand2 = NULL;
	Global_u64Ans = NULL;
	Global_u8Operator = NULL;
	Global_u8DigitsNumber = Copy_u8DigitsNumber;
	Global_u8IsAnswered = FALSE;
	Global_u8Operand1State = NOT_USED;
	Global_u8Operand2State = NOT_USED;
	Global_u8NegativeFlag = FALSE;

}

u8 CheckIfNumber(u8 Copy_u8Data) {
	return !(Copy_u8Data > '9' || Copy_u8Data < '0');
}

void DisplayDataWithShiftingIfNeeded(u8 Copy_u8Data) {
	if (++Global_u8DigitsNumber > 16)
		LCD_voidSendCommand(SHIFT_DISPLAY_LEFT);

	if (Global_u8IsAnswered != NULL
			&& CheckIfNumber(Copy_u8Data) && Global_u8Operator == NULL)
		ResetLcd(1, 0);

	LCD_voidSendData(Copy_u8Data);
}

void HandlingOperands(u8 Copy_u8Data) {
	if ((Global_u8DigitsNumber == 1
			|| (Global_u8Operator != NULL && Global_u8Operand2State == NOT_USED))
			&& Copy_u8Data == '-') {
		Global_u8NegativeFlag = TRUE;
		return;
	}

	if (Global_u8Operator == NULL && !CheckIfNumber(Copy_u8Data))
		Global_u8Operator = Copy_u8Data;
	else if (Global_u8Operator == NULL) {
		Global_u64Operand1 =
				Global_u64Operand1 == NULL ?
						(Global_u64Operand1 + (Copy_u8Data - '0')) :
						Global_u64Operand1 * 10 + (Copy_u8Data - '0');
		Global_u8Operand1State = USED;
	} else {
		Global_u64Operand2 =
				Global_u64Operand2 == NULL ?
						(Global_u64Operand2 + (Copy_u8Data - '0')) :
						Global_u64Operand2 * 10 + (Copy_u8Data - '0');
		Global_u8Operand2State = USED;
	}
	if (Global_u8NegativeFlag == TRUE) {
		if (Global_u8DigitsNumber == 2)
			Global_u64Operand1 *= -1;
		else
			Global_u64Operand2 *= -1;
		Global_u8NegativeFlag = FALSE;
	}
}
void DisplayAnswer() {
	if (Global_u8Operator == '/' && Global_u64Operand2 == 0) {
		ResetLcd(1, 5);
		LCD_voidSendString("ERROR");
		Global_u8IsAnswered = 1;
		return;
	}
	switch (Global_u8Operator) {
	case '+':
		Global_u64Ans = Global_u64Operand1 + Global_u64Operand2;
		break;
	case '-':
		Global_u64Ans = Global_u64Operand1 - Global_u64Operand2;
		break;
	case '/':
		Global_u64Ans = (f32)Global_u64Operand1 / (f32)Global_u64Operand2;
		break;
	case '*':
		Global_u64Ans = Global_u64Operand1 * Global_u64Operand2;
		break;
	default:
		Global_u64Ans = Global_u64Operand1;
	}
	ClearDisplay();

	LCD_voidWriteNumber(Global_u64Ans);
	s64 Local_u64Temp = Global_u64Ans;
	ResetLcd(0 , GetDigitsNumber(Local_u64Temp));
	Global_u64Operand1 = Local_u64Temp;
	Global_u8IsAnswered = 1;
}

u8 GetDigitsNumber(s64 Copy_s64Number) {
	u8 Local_digitsNumber = 1 * (Copy_s64Number == 0);
	while (Copy_s64Number != 0) {
		Local_digitsNumber++;
		Copy_s64Number /= 10;
	}
	return Local_digitsNumber;
}
