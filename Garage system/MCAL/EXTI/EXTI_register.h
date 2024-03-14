//
// Created by sohai on 10/6/2023.
//

#ifndef EXTI_REGISTER_H
#define EXTI_REGISTER_H


/* The MCU Control Register contains control bits for interrupt sense control and general MCU functions  */
#define MCUCR *((volatile pu8) 0x55)
#define MCUCR_ISC00 0
#define MCUCR_ISC01 1
#define MCUCR_ISC10 2
#define MCUCR_ISC11 3

/* General Interrupt Control Register */
#define GICR *((volatile pu8) 0x5B)
#define GICR_INT2 5
#define GICR_INT0 6
#define GICR_INT1 7

/* General Interrupt Flag Register */
#define GIFR *((volatile pu8) 0x5A)
#define GIFR_INTF2 5
#define GIFR_INTF0 6
#define GIFR_INTF1 7

/* MCU Control and Status Register  */
#define MCUCSR *((volatile pu8) 0x54)
#define MCUCSR_ISC2 6

#endif //EXTI_REGISTER_H