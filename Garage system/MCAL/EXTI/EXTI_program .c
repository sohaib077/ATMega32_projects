//
// Created by sohai on 10/6/2023.
//

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "EXTI_config.h"
#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_register.h"

static void (* EXTI_AfPtr[3])(void) = {NULL};

static u8 EXTI_u8Checker(u8 Copy_u8EXTIIndex, u8 Copy_u8EdgeIndex) {
    return (Copy_u8EXTIIndex < 3) && (Copy_u8EdgeIndex < 4);
}

u8 EXTI_u8EXTIEnable(u8 Copy_u8EXTIIndex, u8 Copy_u8EdgeIndex) {
    u8 Local_u8ErrorState = OK;
    if (EXTI_u8Checker(Copy_u8EXTIIndex, Copy_u8EdgeIndex)) {
        switch (Copy_u8EXTIIndex) {
            case EXTI_INT0:
                switch (Copy_u8EdgeIndex) {
                    case EXTI_LOW_LEVEL:
                        CLR_BIT(MCUCR, MCUCR_ISC00);
                        CLR_BIT(MCUCR, MCUCR_ISC01);
                        break;
                    case EXTI_ON_CHANGE:
                        SET_BIT(MCUCR, MCUCR_ISC00);
                        CLR_BIT(MCUCR, MCUCR_ISC01);
                        break;
                    case EXTI_FALLING_EDGE:
                        CLR_BIT(MCUCR, MCUCR_ISC00);
                        SET_BIT(MCUCR, MCUCR_ISC01);
                        break;
                    case EXTI_RISING_EDGE:
                        SET_BIT(MCUCR, MCUCR_ISC00);
                        SET_BIT(MCUCR, MCUCR_ISC01);
                        break;
                }
                /* Enable INT0 */
                SET_BIT(GICR, GICR_INT0);
                break;
            case EXTI_INT1:
                switch (Copy_u8EdgeIndex) {
                    case EXTI_LOW_LEVEL:
                        CLR_BIT(MCUCR, MCUCR_ISC10);
                        CLR_BIT(MCUCR, MCUCR_ISC11);
                        break;
                    case EXTI_ON_CHANGE:
                        SET_BIT(MCUCR, MCUCR_ISC10);
                        CLR_BIT(MCUCR, MCUCR_ISC11);
                        break;
                    case EXTI_FALLING_EDGE:
                        CLR_BIT(MCUCR, MCUCR_ISC10);
                        SET_BIT(MCUCR, MCUCR_ISC11);
                        break;
                    case EXTI_RISING_EDGE:
                        SET_BIT(MCUCR, MCUCR_ISC10);
                        SET_BIT(MCUCR, MCUCR_ISC11);
                        break;
                }
                /* Enable INT1 */
                SET_BIT(GICR, GICR_INT1);
                break;
            case EXTI_INT2:
                switch (Copy_u8EdgeIndex) {
                    case EXTI_FALLING_EDGE:
                        CLR_BIT(MCUCSR, MCUCSR_ISC2);
                        break;
                    case EXTI_RISING_EDGE:
                        SET_BIT(MCUCSR, MCUCSR_ISC2);
                        break;
                    default:
                        Local_u8ErrorState = NOT_OK;
                }
                /* Enable INT2 */
                SET_BIT(GICR, GICR_INT2);
                break;
        }
    } else {
        Local_u8ErrorState = NOT_OK;
    }
    return Local_u8ErrorState;
}

u8 EXTI_u8EXTIDisable(u8 Copy_u8EXTIIndex) {
    u8 Local_u8ErrorState = OK;
    if (EXTI_u8Checker(Copy_u8EXTIIndex, 0)) {
        switch (Copy_u8EXTIIndex) {
            case EXTI_INT0:
                CLR_BIT(GICR, GICR_INT0);
                break;
            case EXTI_INT1:
                CLR_BIT(GICR, GICR_INT1);
                break;
            case EXTI_INT2:
                CLR_BIT(GICR, GICR_INT2);
                break;
        }
    } else {
        Local_u8ErrorState = NOT_OK;
    }
    return Local_u8ErrorState;
}


u8 EXTI_u8SetSenceControl(u8 Copy_u8EXTIIndex, u8 Copy_u8EdgeIndex) {
    u8 Local_u8ErrorState = OK;
    if (EXTI_u8Checker(Copy_u8EXTIIndex, Copy_u8EdgeIndex)) {
        switch (Copy_u8EXTIIndex) {
            case EXTI_INT0:
                switch (Copy_u8EdgeIndex) {
                    case EXTI_LOW_LEVEL:
                        CLR_BIT(MCUCR, MCUCR_ISC00);
                        CLR_BIT(MCUCR, MCUCR_ISC01);
                        break;
                    case EXTI_ON_CHANGE:
                        SET_BIT(MCUCR, MCUCR_ISC00);
                        CLR_BIT(MCUCR, MCUCR_ISC01);
                        break;
                    case EXTI_FALLING_EDGE:
                        CLR_BIT(MCUCR, MCUCR_ISC00);
                        SET_BIT(MCUCR, MCUCR_ISC01);
                        break;
                    case EXTI_RISING_EDGE:
                        SET_BIT(MCUCR, MCUCR_ISC00);
                        SET_BIT(MCUCR, MCUCR_ISC01);
                        break;
                }
                break;
            case EXTI_INT1:
                switch (Copy_u8EdgeIndex) {
                    case EXTI_LOW_LEVEL:
                        CLR_BIT(MCUCR, MCUCR_ISC10);
                        CLR_BIT(MCUCR, MCUCR_ISC11);
                        break;
                    case EXTI_ON_CHANGE:
                        SET_BIT(MCUCR, MCUCR_ISC10);
                        CLR_BIT(MCUCR, MCUCR_ISC11);
                        break;
                    case EXTI_FALLING_EDGE:
                        CLR_BIT(MCUCR, MCUCR_ISC10);
                        SET_BIT(MCUCR, MCUCR_ISC11);
                        break;
                    case EXTI_RISING_EDGE:
                        SET_BIT(MCUCR, MCUCR_ISC10);
                        SET_BIT(MCUCR, MCUCR_ISC11);
                        break;
                }
                break;
            case EXTI_INT2:
                switch (Copy_u8EdgeIndex) {
                    case EXTI_FALLING_EDGE:
                        CLR_BIT(MCUCSR, MCUCSR_ISC2);
                        break;
                    case EXTI_RISING_EDGE:
                        SET_BIT(MCUCSR, MCUCSR_ISC2);
                        break;
                    default:
                        Local_u8ErrorState = NOT_OK;
                }
                break;
        }
    } else {
        Local_u8ErrorState = NOT_OK;
    }
    return Local_u8ErrorState;
}


u8 EXTI_u8EXTISetCallBack(u8 Copy_u8EXTIIndex, void (*Copy_fPtr)(void)) {
    u8 Local_u8ErrorState = OK;
    if (EXTI_u8Checker(Copy_u8EXTIIndex, 0) && (Copy_fPtr != NULL)) {
    	EXTI_AfPtr[Copy_u8EXTIIndex] = Copy_fPtr;
    } else {
        Local_u8ErrorState = NOT_OK;
    }
    return Local_u8ErrorState;
}

void __vector_1() __attribute__((signal));
void __vector_1() {
   if(EXTI_AfPtr[EXTI_INT0] != NULL) EXTI_AfPtr[EXTI_INT0]();
}

void __vector_2() __attribute__((signal));
void __vector_2() {
   if(EXTI_AfPtr[EXTI_INT1] != NULL) EXTI_AfPtr[EXTI_INT1]();
}

void __vector_3() __attribute__((signal));
void __vector_3() {
   if(EXTI_AfPtr[EXTI_INT2] != NULL) EXTI_AfPtr[EXTI_INT2]();
}

