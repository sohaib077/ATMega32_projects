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
#include "../HAL/SSD/SSD_interface.h"
#include <util/delay.h>

u8 SSD_u8SetNumber(u8 Copy_u8Number, SSD *Copy_SSDPtr) {
	if (Copy_u8Number > 9)
		return 1;
	u8 Locale_u8ErrorState = 0;
	u8 Locale_u8Number =
			Copy_SSDPtr->type == SSD_ANODE_TYPE ?
					~SSD_ARR[Copy_u8Number] : SSD_ARR[Copy_u8Number];
	Locale_u8ErrorState += DIO_u8SetPortDirection(Copy_SSDPtr->port,
	DIO_u8PORT_HIGH);
	Locale_u8ErrorState += DIO_u8SetPortValue(Copy_SSDPtr->port,
			Locale_u8Number);
	if (Locale_u8ErrorState == 0)
		return 0;
	return 1;
}

u8 SSD_u8EnableSsd(SSD *Copy_SSDPtr) {
	u8 Locale_u8ErrorState = 0;
	u8 Locale_u8PinValue =
			Copy_SSDPtr->type == SSD_ANODE_TYPE ?
			DIO_u8PIN_HIGH :DIO_u8PIN_LOW;

	Locale_u8ErrorState += DIO_u8SetPinDirection(Copy_SSDPtr->enablePort,
			Copy_SSDPtr->enablePin,
			DIO_u8PIN_OUTPUT);

	Locale_u8ErrorState += DIO_u8SetPinValue(Copy_SSDPtr->enablePort,
			Copy_SSDPtr->enablePin, Locale_u8PinValue);
	if (Locale_u8ErrorState == 0)
		return 0;
	return 1;
}

u8 SSD_u8DisableSsd(SSD *Copy_SSDPtr) {
//    u8 Locale_u8ErrorState = 0;
	u8 Locale_u8PinValue =
			Copy_SSDPtr->type == SSD_ANODE_TYPE ?
			DIO_u8PIN_LOW :DIO_u8PIN_HIGH;
	return DIO_u8SetPinValue(Copy_SSDPtr->enablePort, Copy_SSDPtr->enablePin,
			Locale_u8PinValue);
}

int main() {
	PORT_voidInit();
	SSD ssd = { SSD_CATHODE_TYPE, DIO_u8PORTC, DIO_u8PORTA, DIO_u8PIN0 };
	SSD_u8EnableSsd(&ssd);

	while (1) {
		for (int i = 1; i <= 20; ++i) {
			for (int j = 0; j < 50; ++j) {
				SSD_u8EnableSsd(&ssd);
				SSD_u8SetNumber(i % 10, &ssd);
				_delay_ms(10);

				SSD_u8DisableSsd(&ssd);
				SSD_u8SetNumber((i / 10), &ssd);
				_delay_ms(10);

			}
		}
	}
	return 0;
}

