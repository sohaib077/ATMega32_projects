//
// Created by sohai on 10/14/2023.
//

/****************************************************/
/**************** Name : Sohaib     *****************/
/**************** Date : 10/14/2023 *****************/
/**************** SWC  : TIMERS     *****************/
/**************** Version : 1.0     *****************/
/****************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "TIMERS_config.h"
#include "TIMERS_private.h"
#include "TIMERS_interface.h"
#include "TIMERS_register.h"

/* There are 8 interrupts for timers */
static void (*TIMERS_pvCallBackFunc[8])(void) = {NULL};


/************************************************************************/
/***********************	T I M E R 0		*****************************/
/************************************************************************/

void TIMER0_voidInit() {
    /* Mode */
#if TIMER0_MODE == TIMER0_NORMAL_MODE
    CLR_BIT(TCCR0, TCCR0_WGM00);
    CLR_BIT(TCCR0, TCCR0_WGM01);

    /* Preload value */
    TCNT0 = TIMER0_PRELOAD_VALUE;

    /* Enable overflow Interrupt */
    SET_BIT(TIMSK, TIMSK_TOIE0);


#elif TIMER0_MODE == TIMER0_CTC_MODE
    CLR_BIT(TCCR0, TCCR0_WGM00);
    SET_BIT(TCCR0, TCCR0_WGM01);

    /* Set compare match value */
    OCR0 = TIMER0_CTC_COUNT;

    /* Enable Output Compare Match Interrupt */
    SET_BIT(TIMSK, TIMSK_OCIE0);

#elif TIMER0_MODE == TIMER0_PHASE_CORRECT_PWM_MODE
    SET_BIT(TCCR0 , TCCR0_WGM00);
    CLR_BIT(TCCR0 , TCCR0_WGM01);

/*  Compare Output Mode */
#if TIMER0_PHASE_CORRECT_PWM_COMPARE_OUT_MODE ==  TIMER0_PHASE_CORRECT_PWM_COMPARE_OUT_NORMAL_MODE
    CLR_BIT(TCCR0 , TCCR0_COM00);
    CLR_BIT(TCCR0 , TCCR0_COM01);

#elif TIMER0_PHASE_CORRECT_PWM_COMPARE_OUT_MODE ==  TIMER0_PHASE_CORRECT_PWM_COMPARE_OUT_INVERTING_MODE
    CLR_BIT(TCCR0 , TCCR0_COM00);
    SET_BIT(TCCR0 , TCCR0_COM01);

#elif TIMER0_PHASE_CORRECT_PWM_COMPARE_OUT_MODE ==  TIMER0_PHASE_CORRECT_PWM_COMPARE_OUT_NON_INVERTING_MODE
    SET_BIT(TCCR0 , TCCR0_COM00);
    SET_BIT(TCCR0 , TCCR0_COM01);
#else
#error " Wrong TIMER0_PHASE_CORRECT_PWM_MODE Compare Output Mode "
#endif

/* Set compare match value */
OCR0 = TIMER0_COMPARE_MATCH_VALUE;

/* Enable overflow Interrupt */
SET_BIT(TIMSK, TIMSK_TOIE0);


#elif TIMER0_MODE == TIMER0_FAST_PWM_MODE
    SET_BIT(TCCR0, TCCR0_WGM00);
    SET_BIT(TCCR0, TCCR0_WGM01);


    /*  Compare Output Mode */
#if TIMER0_FAST_PWM_COMPARE_OUT_MODE == TIMER0_PHASE_CORRECT_PWM_COMPARE_OUT_NORMAL_MODE
    CLR_BIT(TCCR0 , TCCR0_COM00);
    CLR_BIT(TCCR0 , TCCR0_COM01);

#elif TIMER0_FAST_PWM_COMPARE_OUT_MODE == TIMER0_FAST_PWM_COMPARE_OUT_NON_INVERTING_MODE
    CLR_BIT(TCCR0, TCCR0_COM00);
    SET_BIT(TCCR0, TCCR0_COM01);

#elif TIMER0_FAST_PWM_COMPARE_OUT_MODE == TIMER0_FAST_PWM_COMPARE_OUT_INVERTING_MODE
    SET_BIT(TCCR0 , TCCR0_COM00);
    SET_BIT(TCCR0 , TCCR0_COM01);

#else
#error " Wrong TIMER0_FAST_PWM_MODE Compare Output Mode "
#endif

    /* Set compare match value */
    OCR0 = TIMER0_COMPARE_MATCH_VALUE;

    /* Enable overflow Interrupt */
    SET_BIT(TIMSK, TIMSK_TOIE0);

#else
#error " Wrong TIMER0_MODE "
#endif


/* Select hardware action on OC0 pin when compare match in non PWM mode */
#if TIMER0_MODE == TIMER0_NORMAL_MODE || TIMER0_MODE == TIMER0_CTC_MODE
#if TIMER0_NON_PWM_COMPARE_OUT_MODE == TIMER0_NON_PWM_COMPARE_OUT_NORMAL_MODE
    CLR_BIT(TCCR0, TCCR0_COM00);
    CLR_BIT(TCCR0, TCCR0_COM01);

#elif TIMER0_NON_PWM_COMPARE_OUT_MODE == TIMER0_NON_PWM_COMPARE_OUT_TOGGLE_MODE
    SET_BIT(TCCR0, TCCR0_COM00);
    CLR_BIT(TCCR0, TCCR0_COM01);

#elif TIMER0_NON_PWM_COMPARE_OUT_MODE == TIMER0_NON_PWM_COMPARE_OUT_CLR_MODE
    CLR_BIT(TCCR0, TCCR0_COM00);
    SET_BIT(TCCR0, TCCR0_COM01);

#elif TIMER0_NON_PWM_COMPARE_OUT_MODE == TIMER0_NON_PWM_COMPARE_OUT_SET_MODE
    SET_BIT(TCCR0, TCCR0_COM00);
    SET_BIT(TCCR0, TCCR0_COM01);
#else
#error " Wrong TIMER0_NON_PWM_MODE Compare Output Mode"
#endif
#endif

    /* Prescaler Clock */
    TCCR0 &= 0b11111000;
    TCCR0 |= TIMER0_CLOCK;
}


void TIMER0_voidSetCompareMatch(u8 Copy_u8OCR0Value) {
    OCR0 = Copy_u8OCR0Value;
}

void TIMER0_voidSetPreload(u8 Copy_u8PreloadValue) {
    TCNT0 = Copy_u8PreloadValue;
}

u8 TIMER0_u8ReadTimer() {
    return TCNT0;
}

u8 TIMER0_voidChangeOutCompareMatchInterruptState(enum INTERRUPT_STATE enum_CopyState) {
    if (enum_CopyState == DISABLE) CLR_BIT(TIMSK, TIMSK_OCIE0);
    else if (enum_CopyState == ENABLE) SET_BIT(TIMSK, TIMSK_OCIE0);
    else return NOT_OK;
    return OK;
}

u8 TIMER0_voidChangeOverFlowInterruptState(enum INTERRUPT_STATE enum_CopyState) {
    if (enum_CopyState == DISABLE) CLR_BIT(TIMSK, TIMSK_TOIE0);
    else if (enum_CopyState == ENABLE) SET_BIT(TIMSK, TIMSK_TOIE0);
    else return NOT_OK;
    return OK;
}


/************************************************************************/
/***********************	T I M E R 1		*****************************/
/************************************************************************/

void TIMER1_voidInit() {

/* SET MODE */
#if TIMER1_MODE == TIMER1_NORMAL_MODE
    CLR_BIT(TCCR1A, TCCR1A_WGM10);
    CLR_BIT(TCCR1A, TCCR1A_WGM11);
    CLR_BIT(TCCR1B, TCCR1B_WGM12);
    CLR_BIT(TCCR1B, TCCR1B_WGM13);

    /* Set preload value */
    TCNT1 = TIMER1_PRELOAD_VALUE;

    /* Enable Overflow interrupt */
    SET_BIT(TIMSK, TIMSK_TOIE1);

#elif TIMER1_MODE == TIMER1_PWM_8_BIT_MODE
    SET_BIT(TCCR1A, TCCR1A_WGM10);
    CLR_BIT(TCCR1A, TCCR1A_WGM11);
    CLR_BIT(TCCR1B, TCCR1B_WGM12);
    CLR_BIT(TCCR1B, TCCR1B_WGM13);

#elif TIMER1_MODE == TIMER1_PWM_9_BIT_MODE
    CLR_BIT(TCCR1A, TCCR1A_WGM10);
    SET_BIT(TCCR1A, TCCR1A_WGM11);
    CLR_BIT(TCCR1B, TCCR1B_WGM12);
    CLR_BIT(TCCR1B, TCCR1B_WGM13);

#elif TIMER1_MODE == TIMER1_PWM_10_BIT_MODE
    SET_BIT(TCCR1A, TCCR1A_WGM10);
    SET_BIT(TCCR1A, TCCR1A_WGM11);
    CLR_BIT(TCCR1B, TCCR1B_WGM12);
    CLR_BIT(TCCR1B, TCCR1B_WGM13);

#elif TIMER1_MODE == TIMER1_CTC_OCR1A_MODE
    CLR_BIT(TCCR1A, TCCR1A_WGM10);
    CLR_BIT(TCCR1A, TCCR1A_WGM11);
    SET_BIT(TCCR1B, TCCR1B_WGM12);
    CLR_BIT(TCCR1B, TCCR1B_WGM13);

    /* CTC channel A/B value */
    OCR1A = TIMER1_CHANNEL_A_CTC_VALUE;
    OCR1B = TIMER1_CHANNEL_B_CTC_VALUE;

    /* Enable Output Compare A/B Match Interrupt */
    SET_BIT(TIMSK, TIMSK_OCIE1A);
    SET_BIT(TIMSK, TIMSK_OCIE1B);

#elif TIMER1_MODE == TIMER1_FAST_PWM_8_BIT_MODE
    SET_BIT(TCCR1A, TCCR1A_WGM10);
    CLR_BIT(TCCR1A, TCCR1A_WGM11);
    SET_BIT(TCCR1B, TCCR1B_WGM12);
    CLR_BIT(TCCR1B, TCCR1B_WGM13);

#elif TIMER1_MODE == TIMER1_FAST_PWM_9_BIT_MODE
    CLR_BIT(TCCR1A, TCCR1A_WGM10);
    SET_BIT(TCCR1A, TCCR1A_WGM11);
    SET_BIT(TCCR1B, TCCR1B_WGM12);
    CLR_BIT(TCCR1B, TCCR1B_WGM13);

#elif TIMER1_MODE == TIMER1_FAST_PWM_10_BIT_MODE
    SET_BIT(TCCR1A, TCCR1A_WGM10);
    SET_BIT(TCCR1A, TCCR1A_WGM11);
    SET_BIT(TCCR1B, TCCR1B_WGM12);
    CLR_BIT(TCCR1B, TCCR1B_WGM13);

#elif TIMER1_MODE == TIMER1_PWM_PHASE_AND_FREQ_CORRECT_ICR1_MODE
    CLR_BIT(TCCR1A, TCCR1A_WGM10);
    CLR_BIT(TCCR1A, TCCR1A_WGM11);
    CLR_BIT(TCCR1B, TCCR1B_WGM12);
    SET_BIT(TCCR1B, TCCR1B_WGM13);

#elif TIMER1_MODE == TIMER1_PWM_PHASE_AND_FREQ_CORRECT_OCR1A_MODE
    SET_BIT(TCCR1A, TCCR1A_WGM10);
    CLR_BIT(TCCR1A, TCCR1A_WGM11);
    CLR_BIT(TCCR1B, TCCR1B_WGM12);
    SET_BIT(TCCR1B, TCCR1B_WGM13);

#elif TIMER1_MODE == TIMER1_PWM_PHASE_CORRECT_ICR1_MODE
    CLR_BIT(TCCR1A, TCCR1A_WGM10);
    SET_BIT(TCCR1A, TCCR1A_WGM11);
    CLR_BIT(TCCR1B, TCCR1B_WGM12);
    SET_BIT(TCCR1B, TCCR1B_WGM13);

#elif TIMER1_MODE == TIMER1_PWM_PHASE_CORRECT_OCR1A_MODE
    SET_BIT(TCCR1A, TCCR1A_WGM10);
    SET_BIT(TCCR1A, TCCR1A_WGM11);
    CLR_BIT(TCCR1B, TCCR1B_WGM12);
    SET_BIT(TCCR1B, TCCR1B_WGM13);

#elif TIMER1_MODE == TIMER1_CTC_ICR1_MODE
    CLR_BIT(TCCR1A, TCCR1A_WGM10);
    CLR_BIT(TCCR1A, TCCR1A_WGM11);
    SET_BIT(TCCR1B, TCCR1B_WGM12);
    SET_BIT(TCCR1B, TCCR1B_WGM13);

#elif TIMER1_MODE == TIMER1_FAST_PWM_ICR1_MODE
    CLR_BIT(TCCR1A, TCCR1A_WGM10);
    SET_BIT(TCCR1A, TCCR1A_WGM11);
    SET_BIT(TCCR1B, TCCR1B_WGM12);
    SET_BIT(TCCR1B, TCCR1B_WGM13);

#elif TIMER1_MODE == TIMER1_FAST_PWM_OCR1A_MODE
    SET_BIT(TCCR1A, TCCR1A_WGM10);
    SET_BIT(TCCR1A, TCCR1A_WGM11);
    SET_BIT(TCCR1B, TCCR1B_WGM12);
    SET_BIT(TCCR1B, TCCR1B_WGM13);

#else
#error " Wrong TIMER1_MODE config "
#endif



/* NON PWM Compare Output Mode */
#if TIMER1_MODE == TIMER1_CTC_OCR1A_MODE || TIMER1_MODE == TIMER1_CTC_ICR1_MODE

    /* Channel A */
#if TIMER1_CHANNEL_A_NON_PWM_COMPARE_OUT_MODE == TIMER1_NON_PWM_COMPARE_OUT_NORMAL_MODE
    CLR_BIT(TCCR1A, TCCR1A_COM1A0);
    CLR_BIT(TCCR1A, TCCR1A_COM1A1);
#elif TIMER1_CHANNEL_A_NON_PWM_COMPARE_OUT_MODE == TIMER1_NON_PWM_COMPARE_OUT_TOGGLE_MODE
    SET_BIT(TCCR1A , TCCR1A_COM1A0);
    CLR_BIT(TCCR1A , TCCR1A_COM1A1);
#elif TIMER1_CHANNEL_A_NON_PWM_COMPARE_OUT_MODE ==  TIMER1_NON_PWM_COMPARE_OUT_CLR_MODE
    CLR_BIT(TCCR1A , TCCR1A_COM1A0);
    SET_BIT(TCCR1A , TCCR1A_COM1A1);
#elif TIMER1_CHANNEL_A_NON_PWM_COMPARE_OUT_MODE ==  TIMER1_NON_PWM_COMPARE_OUT_SET_MODE
    SET_BIT(TCCR1A , TCCR1A_COM1A0);
    SET_BIT(TCCR1A , TCCR1A_COM1A1);
#else
#error " Wrong TIMER1_CHANNEL_A_NON_PWM_COMPARE_OUT_MODE config "
#endif

    /* Channel B */
#if TIMER1_CHANNEL_B_NON_PWM_COMPARE_OUT_MODE == TIMER1_NON_PWM_COMPARE_OUT_NORMAL_MODE
    CLR_BIT(TCCR1A, TCCR1A_COM1B0);
    CLR_BIT(TCCR1A, TCCR1A_COM1B1);
#elif TIMER1_CHANNEL_B_NON_PWM_COMPARE_OUT_MODE == TIMER1_NON_PWM_COMPARE_OUT_TOGGLE_MODE
    SET_BIT(TCCR1A , TCCR1A_COM1B0);
    CLR_BIT(TCCR1A , TCCR1A_COM1B1);
#elif TIMER1_CHANNEL_B_NON_PWM_COMPARE_OUT_MODE ==  TIMER1_NON_PWM_COMPARE_OUT_CLR_MODE
    CLR_BIT(TCCR1A , TCCR1A_COM1B0);
    SET_BIT(TCCR1A , TCCR1A_COM1B1);
#elif TIMER1_CHANNEL_B_NON_PWM_COMPARE_OUT_MODE ==  TIMER1_NON_PWM_COMPARE_OUT_SET_MODE
    SET_BIT(TCCR1A , TCCR1A_COM1B0);
    SET_BIT(TCCR1A , TCCR1A_COM1B1);
#else
#error " Wrong TIMER1_CHANNEL_B_NON_PWM_COMPARE_OUT_MODE config "
#endif

#endif


/* FAST PWM Compare Output Mode */
#if TIMER1_MODE == TIMER1_FAST_PWM_8_BIT_MODE || TIMER1_MODE == TIMER1_FAST_PWM_9_BIT_MODE || TIMER1_MODE == TIMER1_FAST_PWM_10_BIT_MODE || TIMER1_MODE == TIMER1_FAST_PWM_ICR1_MODE || TIMER1_MODE == TIMER1_FAST_PWM_OCR1A_MODE

    /* Channel A */
#if TIMER1_CHANNEL_A_FAST_PWM_COMPARE_OUT_MODE ==  TIMER1_FAST_PWM_COMPARE_OUT_NORMAL_MODE
                CLR_BIT(TCCR1A , TCCR1A_COM1A0);
                CLR_BIT(TCCR1A , TCCR1A_COM1A1);
#elif TIMER1_CHANNEL_A_FAST_PWM_COMPARE_OUT_MODE ==  TIMER1_FAST_PWM_COMPARE_OUT_TOGGLE_MODE
                SET_BIT(TCCR1A , TCCR1A_COM1A0);
                CLR_BIT(TCCR1A , TCCR1A_COM1A1);
#elif TIMER1_CHANNEL_A_FAST_PWM_COMPARE_OUT_MODE ==  TIMER1_FAST_PWM_COMPARE_OUT_NON_INVERTING_MODE
                CLR_BIT(TCCR1A , TCCR1A_COM1A0);
                SET_BIT(TCCR1A , TCCR1A_COM1A1);
#elif TIMER1_CHANNEL_A_FAST_PWM_COMPARE_OUT_MODE ==  TIMER1_FAST_PWM_COMPARE_OUT_INVERTING_MODE
                SET_BIT(TCCR1A , TCCR1A_COM1A0);
                SET_BIT(TCCR1A , TCCR1A_COM1A1);
#else
#error " Wrong TIMER1_CHANNEL_A_FAST_PWM_COMPARE_OUT_MODE config "
#endif

    /* Channel B */
#if TIMER1_CHANNEL_B_FAST_PWM_COMPARE_OUT_MODE ==  TIMER1_FAST_PWM_COMPARE_OUT_NORMAL_MODE
                CLR_BIT(TCCR1A , TCCR1A_COM1B0);
                CLR_BIT(TCCR1A , TCCR1A_COM1B1);
#elif TIMER1_CHANNEL_B_FAST_PWM_COMPARE_OUT_MODE ==  TIMER1_FAST_PWM_COMPARE_OUT_NON_INVERTING_MODE
                CLR_BIT(TCCR1A , TCCR1A_COM1B0);
                SET_BIT(TCCR1A , TCCR1A_COM1B1);
#elif TIMER1_CHANNEL_B_FAST_PWM_COMPARE_OUT_MODE ==  TIMER1_FAST_PWM_COMPARE_OUT_INVERTING_MODE
                SET_BIT(TCCR1A , TCCR1A_COM1B0);
                SET_BIT(TCCR1A , TCCR1A_COM1B1);
#else
#error " Wrong TIMER1_CHANNEL_B_FAST_PWM_COMPARE_OUT_MODE config "
#endif

    /* CTC channel A/B value */
    OCR1A = TIMER1_CHANNEL_A_CTC_VALUE;
    OCR1B = TIMER1_CHANNEL_B_CTC_VALUE;

    /* Enable Overflow interrupt */
    SET_BIT(TIMSK, TIMSK_TOIE1);

    /* Enable Output Compare A/B Match Interrupt */
    SET_BIT(TIMSK , TIMSK_OCIE1A);
    SET_BIT(TIMSK , TIMSK_OCIE1B);

#endif


/* Phase Correct and Phase and Frequency Correct PWM Compare Output Mode */
#if TIMER1_MODE == TIMER1_PWM_8_BIT_MODE || TIMER1_MODE == TIMER1_PWM_9_BIT_MODE || TIMER1_MODE == TIMER1_PWM_10_BIT_MODE || TIMER1_MODE == TIMER1_PWM_PHASE_AND_FREQ_CORRECT_ICR1_MODE || TIMER1_MODE == TIMER1_PWM_PHASE_AND_FREQ_CORRECT_OCR1A_MODE || TIMER1_MODE == TIMER1_PWM_PHASE_CORRECT_ICR1_MODE || TIMER1_MODE == TIMER1_PWM_PHASE_CORRECT_OCR1A_MODE

    /* Channel A */
#if TIMER1_CHANNEL_A_PHASE_FREQ_CORRECT_PWM_COMPARE_OUT_MODE ==  TIMER1_PHASE_FREQ_CORRECT_PWM_COMPARE_OUT_NORMAL_MODE
                CLR_BIT(TCCR1A , TCCR1A_COM1A0);
                CLR_BIT(TCCR1A , TCCR1A_COM1A1);
#elif TIMER1_CHANNEL_A_PHASE_FREQ_CORRECT_PWM_COMPARE_OUT_MODE ==  TIMER1_PHASE_FREQ_CORRECT_PWM_COMPARE_OUT_TOGGLE_MODE
                SET_BIT(TCCR1A , TCCR1A_COM1A0);
                CLR_BIT(TCCR1A , TCCR1A_COM1A1);
#elif TIMER1_CHANNEL_A_PHASE_FREQ_CORRECT_PWM_COMPARE_OUT_MODE ==  TIMER1_PHASE_FREQ_CORRECT_PWM_COMPARE_OUT_INVERTING_MODE
                CLR_BIT(TCCR1A , TCCR1A_COM1A0);
                SET_BIT(TCCR1A , TCCR1A_COM1A1);
#elif TIMER1_CHANNEL_A_PHASE_FREQ_CORRECT_PWM_COMPARE_OUT_MODE ==  TIMER1_PHASE_FREQ_CORRECT_PWM_COMPARE_OUT_NON_INVERTING_MODE
                SET_BIT(TCCR1A , TCCR1A_COM1A0);
                SET_BIT(TCCR1A , TCCR1A_COM1A1);
#else
#error " Wrong TIMER1_CHANNEL_A_PHASE_FREQ_CORRECT_PWM_COMPARE_OUT_MODE config "
#endif

    /* Channel B */
#if TIMER1_CHANNEL_B_PHASE_FREQ_CORRECT_PWM_COMPARE_OUT_MODE ==  TIMER1_PHASE_FREQ_CORRECT_PWM_COMPARE_OUT_NORMAL_MODE
                CLR_BIT(TCCR1A , TCCR1A_COM1B0);
                CLR_BIT(TCCR1A , TCCR1A_COM1B1);
#elif TIMER1_CHANNEL_B_PHASE_FREQ_CORRECT_PWM_COMPARE_OUT_MODE ==  TIMER1_PHASE_FREQ_CORRECT_PWM_COMPARE_OUT_INVERTING_MODE
                CLR_BIT(TCCR1A , TCCR1A_COM1B0);
                SET_BIT(TCCR1A , TCCR1A_COM1B1);
#elif TIMER1_CHANNEL_B_PHASE_FREQ_CORRECT_PWM_COMPARE_OUT_MODE ==  TIMER1_PHASE_FREQ_CORRECT_PWM_COMPARE_OUT_NON_INVERTING_MODE
                SET_BIT(TCCR1A , TCCR1A_COM1B0);
                SET_BIT(TCCR1A , TCCR1A_COM1B1);
#else
#error " Wrong TIMER1_CHANNEL_B_PHASE_CORRECT_FREQ_PWM_COMPARE_OUT_MODE config "
#endif

    /* CTC channel A/B value */
    OCR1A = TIMER1_CHANNEL_A_CTC_VALUE;
    OCR1B = TIMER1_CHANNEL_B_CTC_VALUE;

    /* Enable Overflow interrupt */
    SET_BIT(TIMSK, TIMSK_TOIE1);

    /* Enable Output Compare A/B Match Interrupt */
    SET_BIT(TIMSK , TIMSK_OCIE1A);
    SET_BIT(TIMSK , TIMSK_OCIE1B);
#endif

/* Setting ICR modes */
#if TIMER1_MODE == TIMER1_CTC_ICR1_MODE || TIMER1_MODE == TIMER1_FAST_PWM_ICR1_MODE || TIMER1_MODE == TIMER1_PWM_PHASE_CORRECT_ICR1_MODE || TIMER1_MODE == TIMER1_PWM_PHASE_AND_FREQ_CORRECT_ICR1_MODE

    ICR1 = TIMER1_ICR1_VALUE;

    /* Enable Input Capture Interrupt */
    SET_BIT(TIMSK , TIMSK_TICIE1);

#if TIMER1_ITIMER1_ICR_EDGE == TIMER1_ICR_FALLING_EDGE
        CLR_BIT(TCCR1B,TCCR1B_ICES1);
#elif TIMER1_ITIMER1_ICR_EDGE == TIMER1_ICR_RISING_EDGE
        SET_BIT(TCCR1B,TCCR1B_ICES1);
#else
#error " Wrong TIMER1_ITIMER1_ICR_EDGE config "
#endif

#endif

    /* Prescaler Clock */
    TCCR1B &= 0b11111000;
    TCCR1B |= TIMER1_CLOCK;
}


u8 TIMER1_u8SetCompareMatch(u8 Copy_u8Channel, u16 Copy_u16OCR1xValue) {
    if (Copy_u8Channel == TIMER1_CHANNEL_A)
        OCR1A = Copy_u16OCR1xValue;
    else if (Copy_u8Channel == TIMER1_CHANNEL_B)
        OCR1B = Copy_u16OCR1xValue;
    else return NOT_OK;
    return OK;
}

void TIMER1_voidSetPreload(u8 Copy_u8PreloadValue) {
    TCNT1 = Copy_u8PreloadValue;
}

u16 TIMER1_u16ReadTimer() {
    return TCNT1;
}


u8 TIMER1_voidChangeOverFlowInterruptState(enum INTERRUPT_STATE enum_CopyState) {
    if (enum_CopyState == DISABLE) CLR_BIT(TIMSK, TIMSK_TOIE1);
    else if (enum_CopyState == ENABLE) SET_BIT(TIMSK, TIMSK_TOIE1);
    else return NOT_OK;
    return OK;
}


u8 TIMER1_voidChangeOutCompareMatchInterruptState(u8 Copy_u8Channel, enum INTERRUPT_STATE enum_CopyState) {
    if (Copy_u8Channel != TIMER1_CHANNEL_A && Copy_u8Channel != TIMER1_CHANNEL_B) return NOT_OK;
    if (enum_CopyState != DISABLE && enum_CopyState != ENABLE) return NOT_OK;

    if (Copy_u8Channel == TIMER1_CHANNEL_A) {
        if (enum_CopyState == DISABLE) CLR_BIT(TIMSK, TIMSK_OCIE1A);
        else
            SET_BIT(TIMSK, TIMSK_OCIE1A);
    } else {
        if (enum_CopyState == DISABLE) CLR_BIT(TIMSK, TIMSK_OCIE1B);
        else
            SET_BIT(TIMSK, TIMSK_OCIE1B);
    }
    return OK;
}


u8 TIMER1_voidChangeICR1InterruptState(enum INTERRUPT_STATE enum_CopyState) {
    if (enum_CopyState == DISABLE) CLR_BIT(TIMSK, TIMSK_TICIE1);
    else if (enum_CopyState == ENABLE) SET_BIT(TIMSK, TIMSK_TICIE1);
    else return NOT_OK;
    return OK;
}


/************************************************************************/
/***********************	T I M E R 2		*****************************/
/************************************************************************/


void TIMER2_voidInit() {
    /* Mode */
#if TIMER2_MODE == TIMER0_NORMAL_MODE
    CLR_BIT(TCCR2, TCCR2_WGM20);
    CLR_BIT(TCCR2, TCCR2_WGM21);

    /* Preload value */
    TCNT2 = TIMER2_PRELOAD_VALUE;

    /* Enable overflow Interrupt */
    SET_BIT(TIMSK, TIMSK_TOIE2);


#elif TIMER2_MODE == TIMER0_CTC_MODE
    CLR_BIT(TCCR2, TCCR2_WGM20);
    SET_BIT(TCCR2, TCCR2_WGM21);

    /* Set compare match value */
    OCR2 = TIMER2_CTC_COUNT;

    /* Enable Output Compare Match Interrupt */
    SET_BIT(TIMSK, TIMSK_OCIE2);

#elif TIMER2_MODE == TIMER0_PHASE_CORRECT_PWM_MODE
    SET_BIT(TCCR2 , TCCR2_WGM20);
    CLR_BIT(TCCR2 , TCCR2_WGM21);

    /*  Compare Output Mode */
#if TIMER2_PHASE_CORRECT_PWM_COMPARE_OUT_MODE ==  TIMER0_PHASE_CORRECT_PWM_COMPARE_OUT_NORMAL_MODE
            CLR_BIT(TCCR2 , TCCR2_COM20);
            CLR_BIT(TCCR2 , TCCR2_COM21);

#elif TIMER2_PHASE_CORRECT_PWM_COMPARE_OUT_MODE ==  TIMER0_PHASE_CORRECT_PWM_COMPARE_OUT_INVERTING_MODE
            CLR_BIT(TCCR2 , TCCR2_COM20);
            SET_BIT(TCCR2 , TCCR2_COM21);

#elif TIMER2_PHASE_CORRECT_PWM_COMPARE_OUT_MODE ==  TIMER0_PHASE_CORRECT_PWM_COMPARE_OUT_NON_INVERTING_MODE
            SET_BIT(TCCR2 , TCCR2_COM20);
            SET_BIT(TCCR2 , TCCR2_COM21);
#else
#error " Wrong TIMER2_PHASE_CORRECT_PWM_MODE Compare Output Mode "
#endif

    /* Set compare match value */
    OCR2 = TIMER2_COMPARE_MATCH_VALUE;

    /* Enable overflow Interrupt */
    SET_BIT(TIMSK, TIMSK_TOIE2);


#elif TIMER2_MODE == TIMER0_FAST_PWM_MODE
    SET_BIT(TCCR2, TCCR2_WGM20);
    SET_BIT(TCCR2, TCCR2_WGM21);


    /*  Compare Output Mode */
#if TIMER2_FAST_PWM_COMPARE_OUT_MODE == TIMER0_PHASE_CORRECT_PWM_COMPARE_OUT_NORMAL_MODE
        CLR_BIT(TCCR2 , TCCR2_COM20);
        CLR_BIT(TCCR2 , TCCR2_COM21);

#elif TIMER2_FAST_PWM_COMPARE_OUT_MODE == TIMER0_FAST_PWM_COMPARE_OUT_NON_INVERTING_MODE
        CLR_BIT(TCCR2, TCCR2_COM20);
        SET_BIT(TCCR2, TCCR2_COM21);

#elif TIMER2_FAST_PWM_COMPARE_OUT_MODE == TIMER0_FAST_PWM_COMPARE_OUT_INVERTING_MODE
        SET_BIT(TCCR2 , TCCR2_COM20);
        SET_BIT(TCCR2 , TCCR2_COM21);

#else
#error " Wrong TIMER2_FAST_PWM_MODE Compare Output Mode "
#endif

    /* Set compare match value */
    OCR2 = TIMER2_COMPARE_MATCH_VALUE;

    /* Enable overflow Interrupt */
    SET_BIT(TIMSK, TIMSK_TOIE2);

#else
#error " Wrong TIMER2_MODE config "
#endif


/* Select hardware action on OC2 pin when compare match in non PWM mode */
#if TIMER0_MODE == TIMER0_NORMAL_MODE || TIMER0_MODE == TIMER0_CTC_MODE

#if TIMER0_NON_PWM_COMPARE_OUT_MODE == TIMER0_NON_PWM_COMPARE_OUT_NORMAL_MODE
    CLR_BIT(TCCR2, TCCR2_COM20);
    CLR_BIT(TCCR2, TCCR2_COM21);

#elif TIMER0_NON_PWM_COMPARE_OUT_MODE == TIMER0_NON_PWM_COMPARE_OUT_TOGGLE_MODE
    SET_BIT(TCCR2, TCCR2_COM20);
    CLR_BIT(TCCR2, TCCR2_COM21);

#elif TIMER0_NON_PWM_COMPARE_OUT_MODE == TIMER0_NON_PWM_COMPARE_OUT_CLR_MODE
    CLR_BIT(TCCR2, TCCR2_COM20);
    SET_BIT(TCCR2, TCCR2_COM21);

#elif TIMER0_NON_PWM_COMPARE_OUT_MODE == TIMER0_NON_PWM_COMPARE_OUT_SET_MODE
    SET_BIT(TCCR2, TCCR2_COM20);
    SET_BIT(TCCR2, TCCR2_COM21);
#else
#error " Wrong TIMER2_NON_PWM_MODE Compare Output Mode"
#endif

#endif

    /* Prescaler Clock */
    TCCR2 &= 0b11111000;
    TCCR2 |= TIMER0_CLOCK;
}


void TIMER2_voidSetCompareMatch(u8 Copy_u8OCR2Value) {
    OCR2 = Copy_u8OCR2Value;
}

void TIMER2_voidSetPreload(u8 Copy_u8PreloadValue) {
    TCNT2 = Copy_u8PreloadValue;
}

u8 TIMER2_u8ReadTimer() {
    return TCNT2;
}

u8 TIMER2_voidChangeOutCompareMatchInterruptState(enum INTERRUPT_STATE enum_CopyState) {
    if (enum_CopyState == DISABLE) CLR_BIT(TIMSK, TIMSK_OCIE2);
    else if (enum_CopyState == ENABLE) SET_BIT(TIMSK, TIMSK_OCIE2);
    else return NOT_OK;
    return OK;
}

u8 TIMER2_voidChangeOverFlowInterruptState(enum INTERRUPT_STATE enum_CopyState) {
    if (enum_CopyState == DISABLE) CLR_BIT(TIMSK, TIMSK_TOIE2);
    else if (enum_CopyState == ENABLE) SET_BIT(TIMSK, TIMSK_TOIE2);
    else return NOT_OK;
    return OK;
}

/************************************************************************/
/*******************    INPUT CAPTURE UNIT	*****************************/
/************************************************************************/


void TIMER_voidICUInitEnable(void) {

    /* Set trigger edge  */
    #if (TIMER1_ICR_EDGE == TIMER1_ICR_RISING_EDGE)
    SET_BIT(TCCR1B,TCCR1B_ICES1);
    #elif(TIMER1_ICR_EDGE == TIMER1_ICR_FALLING_EDGE)
    CLR_BIT(TCCR1B, TCCR1B_ICES1);
    #endif

    /* Enable Interrupt of ICU */
    SET_BIT(TIMSK, TIMSK_TICIE1);
}

u8 TIMER_voidICUSetTriggerEdge(u8 Copy_u8Edge) {
    if (Copy_u8Edge == TIMER1_ICR_RISING_EDGE)
        SET_BIT(TCCR1B, TCCR1B_ICES1);
    else if (Copy_u8Edge == TIMER1_ICR_FALLING_EDGE)
        CLR_BIT(TCCR1B, TCCR1B_ICES1);
    else return NOT_OK;
    return OK;
}

u8 TIMER_u8ChangeICUInterruptState(enum INTERRUPT_STATE enum_CopyState) {
    if (enum_CopyState == DISABLE)
        CLR_BIT(TIMSK, TIMSK_TICIE1);
    else if (enum_CopyState == ENABLE)
        SET_BIT(TIMSK, TIMSK_TICIE1);
    else return NOT_OK;
    return OK;
}

u16 TIMER_u16ReadICR(void) {
    return ICR1;
}



/************************************************************************/
/***********************	 I S R s		*****************************/
/************************************************************************/

u8 TIMERS_u8SetCallBack(void (*Copy_pf)(void), u8 Copy_Index) {
    if (Copy_pf == NULL) return NULL_POINTER;
    if (Copy_Index > TIMER2_COMP_INDEX) return NOT_OK;

    TIMERS_pvCallBackFunc[Copy_Index] = Copy_pf;
    return OK;
}


/* TIMER0_OVF */
void __vector_11() __attribute__((signal));

void __vector_11() {
    if (TIMERS_pvCallBackFunc[TIMER0_OVF_INDEX] != NULL) TIMERS_pvCallBackFunc[TIMER0_OVF_INDEX]();
}

/* TIMER0_COMP */
void __vector_10() __attribute__((signal));

void __vector_10() {
    if (TIMERS_pvCallBackFunc[TIMER0_COMP_INDEX] != NULL) TIMERS_pvCallBackFunc[TIMER0_COMP_INDEX]();
}

/* TIMER1_OVF */
void __vector_9() __attribute__((signal));

void __vector_9() {
    if (TIMERS_pvCallBackFunc[TIMER1_OVF_INDEX] != NULL) TIMERS_pvCallBackFunc[TIMER1_OVF_INDEX]();
}

/* TIMER1_COMPB */
void __vector_8() __attribute__((signal));

void __vector_8() {
    if (TIMERS_pvCallBackFunc[TIMER1_COMPB_INDEX] != NULL) TIMERS_pvCallBackFunc[TIMER1_COMPB_INDEX]();
}

/* TIMER1_COMPA */
void __vector_7() __attribute__((signal));

void __vector_7() {
    if (TIMERS_pvCallBackFunc[TIMER1_COMPA_INDEX] != NULL) TIMERS_pvCallBackFunc[TIMER1_COMPA_INDEX]();
}

/* TIMER1_CAPT */
void __vector_6() __attribute__((signal));

void __vector_6() {
    if (TIMERS_pvCallBackFunc[TIMER1_CAPT_INDEX] != NULL) TIMERS_pvCallBackFunc[TIMER1_CAPT_INDEX]();
}

/* TIMER2_OVF */
void __vector_5() __attribute__((signal));

void __vector_5() {
    if (TIMERS_pvCallBackFunc[TIMER2_OVF_INDEX] != NULL) TIMERS_pvCallBackFunc[TIMER2_OVF_INDEX]();
}

/* TIMER2_COMP */
void __vector_4() __attribute__((signal));

void __vector_4() {
    if (TIMERS_pvCallBackFunc[TIMER2_COMP_INDEX] != NULL) TIMERS_pvCallBackFunc[TIMER2_COMP_INDEX]();
}
