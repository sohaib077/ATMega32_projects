//
// Created by sohai on 10/6/2023.
//

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "GIE_config.h"
#include "GIE_private.h"
#include "GIE_interface.h"
#include "GIE_register.h"

void GIE_voidEnable() {
    SET_BIT(SREG, SREG_I);
}

void GIE_voidDisable() {
    CLR_BIT(SREG, SREG_I);
}
