//
// Created by sohai on 10/6/2023.
//

#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

#define EXTI_INT0 0
#define EXTI_INT1 1
#define EXTI_INT2 2

/* Edge Source */
#define EXTI_RISING_EDGE    0
#define EXTI_FALLING_EDGE   1
#define EXTI_ON_CHANGE      2
#define EXTI_LOW_LEVEL      3

u8 EXTI_u8EXTIEnable(u8 Copy_u8EXTIIndex , u8 Copy_u8EdgeIndex);
u8 EXTI_u8EXTIDisable(u8 Copy_u8EXTIIndex);
u8 EXTI_u8SetSenceControl(u8 Copy_u8EXTIIndex, u8 Copy_u8EdgeIndex);
u8 EXTI_u8EXTISetCallBack(u8 Copy_u8EXTIIndex , void (*Copy_fPtr) (void));
#endif //EXTI_INTERFACE_H
