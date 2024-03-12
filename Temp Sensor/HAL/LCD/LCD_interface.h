//
// Created by sohai on 9/13/2023.
//

#ifndef LCD_PROGRAM_C_LCD_INTERFACE_H
#define LCD_PROGRAM_C_LCD_INTERFACE_H

#define LCD_CHARACTERS_PER_LINE


/* Defining some commands */

// Function Set
#define FUNC_SET_SMALL_ONE_LINE 0b00110000
#define FUNC_SET_BIG_ONE_LINE   0b00110100
#define FUNC_SET_SMALL_TWO_LINE 0b00111000
#define FUNC_SET_BIG_TWO_LINE   0b00111100

// DISPLAY ON/OFF
#define DISPLAY_ON_NO_CURSOR 0b00001100
#define DISPLAY_ON_CURSOR 0b00001110
#define DISPLAY_ON_BLINK 0b00001101
#define DISPLAY_OFF 0b00001000

//DISPLAY CLEAR
#define DISPLAY_CLEAR 1

//ENTRY MODE SET
#define MODE_SET_INC_SHIFTING 7
#define MODE_SET_INC_NO_SHIFTING 6
#define MODE_SET_DEC_SHIFTING 5
#define MODE_SET_DEC_NO_SHIFTING 4

// CURSOR AND DISPLAY SHIFTING
#define SHIFT_CURSOR_LEFT 0b00010000
#define SHIFT_CURSOR_RIGHT 0b00010100
#define SHIFT_DISPLAY_LEFT 0b00011000
#define SHIFT_DISPLAY_RIGHT 0b00011100

//RETURN HOME
#define RETURN_HOME 2

#define LCD_WRITE_FROM_LEFT 0
#define LCD_WRITE_FROM_RIGHT 1




void LCD_voidSendCommand(u8 Copy_u8Command);

void LCD_voidSendData(u8 Copy_u8Data);

void LCD_voidSendString(pu8 Copy_pu8Data);

void LCD_voidInit();

void LCD_voidShiftDisplayRight(u8 Copy_u8ShiftingNumber);

void LCD_voidShiftDisplayLeft(u8 Copy_u8ShiftingNumber);

void LCD_voidSetDDRAMAddress(u8 x, u8 y);

void LCD_voidWriteSpecialCharacter(pu8 Copy_pu8Character, u8 Copy_u8CharacterPos, u8 Copy_u8X, u8 Copy_u8Y, u8 Copy_u8Direction);

void LCD_voidWriteSpecialString(u8 Copy_pu8String[][8], u8 Copy_u8NumberOfCharacters, u8 Copy_u8Direction, u8 Copy_u8X, u8 Copy_u8Y);

void LCD_voidWriteNumber(f64 Copy_s64Number);

#endif //LCD_PROGRAM_C_LCD_INTERFACE_H
