//
// Created by sohai on 10/14/2023.
//

/****************************************************/
/**************** Name : Sohaib     *****************/
/**************** Date : 10/14/2023 *****************/
/**************** SWC  : TIMERS     *****************/
/**************** Version : 1.0     *****************/
/****************************************************/

#ifndef TIMERS_REGISTER_H
#define TIMERS_REGISTER_H


/************************************************************************/
/***********************	T I M E R 0		*****************************/
/************************************************************************/

#define TCCR0 *((volatile pu8) 0x53)  /* Timer/Counter Control */
#define TCCR0_CS00      0             /* Clock Select */
#define TCCR0_CS01      1
#define TCCR0_CS02      2
#define TCCR0_WGM01     3             /* Waveform Generation Mode */
#define TCCR0_COM00     4
#define TCCR0_COM01     5             /* Compare Match Output Mode */
#define TCCR0_WGM00     6
#define TCCR0_FOC0      7             /*  Force Output Compare */

/* Timer/Counter Preload value */
#define TCNT0 *((volatile pu8) 0x52)

/* Output Compare */
#define OCR0 *((volatile pu8) 0x5C)

#define  TIMSK *((volatile pu8) 0x59)  /* Timer/Counter Interrupt Mask */
#define  TIMSK_TOIE0    0              /* Timer/Counter0 Overflow Interrupt Enable */
#define  TIMSK_OCIE0    1              /* Timer/Counter0 Output Compare Match Interrupt Enable */


/************************************************************************/
/***********************	T I M E R 1		*****************************/
/************************************************************************/


#define TCCR1A *((volatile pu8) 0x4F)  /* Timer/Counter Control Register A  */
#define TCCR1A_WGM10      0            /* Waveform Generation Mode */
#define TCCR1A_WGM11      1
#define TCCR1A_FOC1B      2            /* Force Output Compare for Channel B */
#define TCCR1A_FOC1A      3            /* Force Output Compare for Channel A */
#define TCCR1A_COM1B0     4            /* Compare Output Mode for Channel B */
#define TCCR1A_COM1B1     5
#define TCCR1A_COM1A0     6            /*  Compare Output Mode for Channel A */
#define TCCR1A_COM1A1     7


#define TCCR1B *((volatile pu8) 0x4E)  /* Timer/Counter Control Register B  */
#define TCCR1B_CS10      0             /* Clock Select */
#define TCCR1B_CS11      1
#define TCCR1B_CS12      2
#define TCCR1B_WGM12     3             /* Waveform Generation Mode */
#define TCCR1B_WGM13     4
#define TCCR1B_ICES1     6             /* Input Capture Edge Select  */
#define TCCR1B_ICNC1     7             /* Input Capture Noise Canceler */


#define TCNT1H *((volatile pu8) 0x4D)   /*  Counter Register High Byte */
#define TCNT1L *((volatile pu8) 0x4C)   /*  Counter Register Low Byte */
#define TCNT1  *((volatile pu16) 0x4C)  /*  Counter Register */

#define OCR1AH *((volatile pu8) 0x4B)   /*  Output Compare Register A High Byte */
#define OCR1AL *((volatile pu8) 0x4A)   /*  Output Compare Register A Low Byte */
#define OCR1A  *((volatile pu16) 0x4A)  /*  Output Compare Register A  */

#define OCR1BH *((volatile pu8) 0x49)   /*  Output Compare Register B High Byte */
#define OCR1BL *((volatile pu8) 0x48)   /*  Output Compare Register B Low Byte */
#define OCR1B  *((volatile pu16) 0x48)  /*  Output Compare Register B  */

#define ICR1H *((volatile pu8) 0x47)    /*  Input Capture Register High Byte */
#define ICR1L *((volatile pu8) 0x46)    /*  Input Capture Register Low Byte */
#define ICR1  *((volatile pu16) 0x46)   /*  Input Capture Register */


#define TIMSK_TOIE1      2              /* Timer/Counter1, Overflow Interrupt Enable */
#define TIMSK_OCIE1B     3              /* Timer/Counter1, Output Compare B Match Interrupt Enable */
#define TIMSK_OCIE1A     4              /* Timer/Counter1, Output Compare A Match Interrupt Enable */
#define TIMSK_TICIE1     5              /* Timer/Counter1, Input Capture Interrupt Enable */


/************************************************************************/
/***********************	T I M E R 2		*****************************/
/************************************************************************/

#define TCCR2 *((volatile pu8) 0x45)  /* Timer/Counter Control Register  */
#define TCCR2_CS20       0            /* Clock Select */
#define TCCR2_CS21       1
#define TCCR2_CS22       2            /* Force Output Compare for Channel B */
#define TCCR2_WGM21      3            /* Waveform Generation Mode */
#define TCCR2_COM20      4            /* Compare Output Mode */
#define TCCR2_COM21      5            /* Compare Output Mode */
#define TCCR2_WGM20      6            /* Waveform Generation Mode */
#define TCCR2_FOC2       7            /* Force Output Compare */

#define TCNT2 *((volatile pu16) 0x44)  /* Counter Register */

#define OCR2  *((volatile pu16) 0x43)  /* Output Compare Register */

#define TIMSK_TOIE2      6              /* Timer/Counter2, Overflow Interrupt Enable */
#define TIMSK_OCIE2      7              /* Timer/Counter2, Output Compare Match Interrupt Enable */

#endif //TIMERS_REGISTER_H
