//
// Created by sohai on 9/12/2023.
//
#include "../../LIB//STD_TYPES.h"
#include "../../LIB//BIT_MATH.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "SSD_interface.h"
#include "SSD_config.h"
#include "SSD_private.h"


u8 SSD_u8SetNumber(u8 Copy_u8Number, SSD *Copy_SSDPtr) {
    if (Copy_u8Number > 9) return 1;
    u8 Locale_u8ErrorState = 0;
    u8 Locale_u8Number = Copy_SSDPtr->type == SSD_ANODE_TYPE ? ~SSD_ARR[Copy_u8Number] : SSD_ARR[Copy_u8Number];
    Locale_u8ErrorState += DIO_u8SetPortDirection(Copy_SSDPtr->port, DIO_u8PORT_HIGH);
    Locale_u8ErrorState += DIO_u8SetPortValue(Copy_SSDPtr->port, Locale_u8Number);
    if (Locale_u8ErrorState == 0) return 0;
    return 1;
};

u8 SSD_u8EnableSsd(SSD *Copy_SSDPtr) {
    u8 Locale_u8ErrorState = 0;
    u8 Locale_u8PinValue = Copy_SSDPtr->type == SSD_ANODE_TYPE ? DIO_u8PIN_HIGH : DIO_u8PIN_LOW;

    Locale_u8ErrorState += DIO_u8SetPinDirection(Copy_SSDPtr->enablePortport, Copy_SSDPtr->enablePin,
                                                 DIO_u8PIN_OUTPUT);

    Locale_u8ErrorState += DIO_u8SetPinValue(Copy_SSDPtr->enablePortport, Copy_SSDPtr->enablePin,
                                             Locale_u8PinValue);
    if (Locale_u8ErrorState == 0) return 0;
    return 1;
};

u8 SSD_u8DisableSsd(SSD *Copy_SSDPtr) {
//    u8 Locale_u8ErrorState = 0;
    u8 Locale_u8PinValue = Copy_SSDPtr->type == SSD_ANODE_TYPE ? DIO_u8PIN_LOW : DIO_u8PIN_HIGH;
    return DIO_u8SetPinValue(Copy_SSDPtr->enablePortport, Copy_SSDPtr->enablePin,
                             Locale_u8PinValue);
};


