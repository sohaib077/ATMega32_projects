//
// Created by sohai on 10/14/2023.
//

/****************************************************/
/**************** Name : Sohaib     *****************/
/**************** Date : 10/14/2023 *****************/
/**************** SWC  : TIMERS     *****************/
/**************** Version : 1.0     *****************/
/****************************************************/


#ifndef TIMERS_CONFIG_H
#define TIMERS_CONFIG_H

#define TIMER0_MODE  TIMER0_CTC_MODE

#define TIMER0_CLOCK  TIMERS_8_PRESCALER_CLOCK

#define TIMER0_PRELOAD_VALUE               192
#define TIMER0_OVERFLOW_COUNT              10000
#define TIMER0_CTC_COUNT                   250
#define TIMER0_COMPARE_MATCH_VALUE         64

#define TIMER0_NON_PWM_COMPARE_OUT_MODE              TIMER0_NON_PWM_COMPARE_OUT_NORMAL_MODE

#define TIMER0_FAST_PWM_COMPARE_OUT_MODE             TIMER0_FAST_PWM_COMPARE_OUT_NON_INVERTING_MODE

#define TIMER0_PHASE_CORRECT_PWM_COMPARE_OUT_MODE    TIMER0_PHASE_CORRECT_PWM_COMPARE_OUT_INVERTING_MODE


/************************************************************************/
/***********************	T I M E R 1		*****************************/
/************************************************************************/

#define TIMER1_CLOCK  TIMERS_8_PRESCALER_CLOCK

#define TIMER1_MODE         TIMER1_FAST_PWM_ICR1_MODE

#define TIMER1_CHANNEL_A_NON_PWM_COMPARE_OUT_MODE              TIMER1_NON_PWM_COMPARE_OUT_NORMAL_MODE
#define TIMER1_CHANNEL_B_NON_PWM_COMPARE_OUT_MODE              TIMER1_NON_PWM_COMPARE_OUT_NORMAL_MODE

/* TIMER1_FAST_PWM_COMPARE_OUT_TOGGLE_MODE is available for Channel A only */
#define TIMER1_CHANNEL_A_FAST_PWM_COMPARE_OUT_MODE             TIMER1_FAST_PWM_COMPARE_OUT_NON_INVERTING_MODE
#define TIMER1_CHANNEL_B_FAST_PWM_COMPARE_OUT_MODE             TIMER1_FAST_PWM_COMPARE_OUT_NON_INVERTING_MODE

/* TIMER1_FAST_PWM_COMPARE_OUT_TOGGLE_MODE is available for Channel A only */
#define TIMER1_CHANNEL_A_PHASE_FREQ_CORRECT_PWM_COMPARE_OUT_MODE             TIMER1_NON_PWM_COMPARE_OUT_NORMAL_MODE
#define TIMER1_CHANNEL_B_PHASE_FREQ_CORRECT_PWM_COMPARE_OUT_MODE             TIMER1_NON_PWM_COMPARE_OUT_NORMAL_MODE

#define TIMER1_ICR_EDGE                    TIMER1_ICR_FALLING_EDGE

#define TIMER1_PRELOAD_VALUE               192  /* TCNT1 value */

#define TIMER1_CHANNEL_A_CTC_VALUE         999  /* OCR1A value */
#define TIMER1_CHANNEL_B_CTC_VALUE         192  /* OCR1B value */

#define TIMER1_ICR1_VALUE                  20000   /* ICR1 value */




/************************************************************************/
/***********************	T I M E R 2		*****************************/
/************************************************************************/

#define TIMER2_CLOCK        TIMER2_8_PRESCALER_CLOCK

/* Use Timer0 options */
#define TIMER2_MODE         TIMER0_NORMAL_MODE

/* Use Timer0 options */
#define TIMER2_NON_PWM_COMPARE_OUT_MODE              TIMER0_NON_PWM_COMPARE_OUT_NORMAL_MODE

/* Use Timer0 options */
#define TIMER2_FAST_PWM_COMPARE_OUT_MODE             TIMER0_FAST_PWM_COMPARE_OUT_NON_INVERTING_MODE

/* Use Timer0 options */
#define TIMER2_PHASE_CORRECT_PWM_COMPARE_OUT_MODE    TIMER0_PHASE_CORRECT_PWM_COMPARE_OUT_INVERTING_MODE

#define TIMER2_PRELOAD_VALUE               192
#define TIMER2_OVERFLOW_COUNT              10000
#define TIMER2_CTC_COUNT                   99
#define TIMER2_COMPARE_MATCH_VALUE         64


#endif //TIMERS_CONFIG_H
