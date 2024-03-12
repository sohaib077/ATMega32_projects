//
// Created by sohai on 10/7/2023.
//

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "ADC_register.h"
#include "ADC_config.h"
#include "ADC_private.h"
#include "ADC_interface.h"

#define BUSY 0
#define NOT_BUSY 1

static void(*ADC_pfNotification)(u32) = NULL;

/* ADC busy flag */
static u8 ADC_u8BusyFlag = NOT_BUSY;

void ADC_voidInit() {

    /* Voltage reference */
#if ADC_VREF == ADC_VREF_AVCC
    SET_BIT(ADMUX, ADMUX_REFS0);
    CLR_BIT(ADMUX, ADMUX_REFS1);

#elif ADC_VREF == ADC_VREF_AREF
    CLR_BIT(ADMUX , ADMUX_REFS0);
    CLR_BIT(ADMUX , ADMUX_REFS1);

#elif ADC_VREF == ADC_VREF_ADC_VREF_INTERNAL
    SET_BIT(ADMUX , ADMUX_REFS0);
    SET_BIT(ADMUX , ADMUX_REFS1);
#endif

    /* Mode */
#if ADC_MODE == ADC_SINGLE_MODE
    CLR_BIT(ADCSRA, ADCSRA_ADATE);

#elif ADC_MODE == ADC_FREE_RUNNING_MODE
    SET_BIT(ADCSRA, ADCSRA_ADATE);
    CLR_BIT(SFIOR, SFIOR_ADTS0);
    CLR_BIT(SFIOR, SFIOR_ADTS1);
    CLR_BIT(SFIOR, SFIOR_ADTS2);
#endif

    /* Resolution */
#if ADC_RESOLUTION == ACD_10_BIT_RES
    CLR_BIT(ADMUX, ADMUX_ADLAR);
#elif ADC_RESOLUTION == ACD_8_BIT_RES
    SET_BIT(ADMUX, ADMUX_ADLAR);
#endif

    /* Prescaler */
    ADCSRA &= 0b11111000;
    ADCSRA |= ADC_PRESCALER;

    /* Enable */
    ADC_voidEnable();
}

void ADC_voidEnable() {
    SET_BIT(ADCSRA, ADCSRA_ADEN);
}

void ADC_voidDisable() {
    CLR_BIT(ADCSRA, ADCSRA_ADEN);
}

void ADC_voidEnableInterrupt() {
    SET_BIT(ADCSRA, ADCSRA_ADIE);
}

void ADC_voidDisableInterrupt() {
    CLR_BIT(ADCSRA, ADCSRA_ADIE);
}

void ADC_voidStartConversion(u8 Copy_u8ReadChannel) {
    ADMUX &= 0b11100000;
    ADMUX |= Copy_u8ReadChannel;

    SET_BIT(ADCSRA, ADCSRA_ADSC);
}

u8 ADC_u8ReadSynchronous(u8 Copy_u8ReadChannel,  u32 * Copy_pu16ReadValue) {
    u8 Local_u8ErrorState = OK;
    if(Copy_u8ReadChannel > ADC_CH7 || Copy_pu16ReadValue == NULL)
        return  NOT_OK;


    ADC_voidStartConversion(Copy_u8ReadChannel);
    /* Polling until the conversion complete */
    u32 Local_u8Timer = 5000;
    while (!GET_BIT(ADCSRA, ADCSRA_ADIF) && Local_u8Timer--);

    if (Local_u8Timer > 0 || GET_BIT(ADCSRA, ADCSRA_ADIF)) {
        /* Clearing the interrupt flag */
        SET_BIT(ADCSRA, ADCSRA_ADIF);

#if ADC_RESOLUTION == ACD_10_BIT_RES
        *Copy_pu16ReadValue = ADCL;
        *Copy_pu16ReadValue |= (ADCH << 8);
#elif ADC_RESOLUTION == ACD_8_BIT_RES
        *Copy_pu16ReadValue = ADCH;
#endif
    }else{
        return  TIMEOUT_STATE;
    }
    return OK;
}

u8 ADC_u8ReadAsynchronous(u8 Copy_u8ReadChannel , void(*Copy_pfNotification)(u32)) {
    if(Copy_u8ReadChannel > ADC_CH7 || Copy_pfNotification == NULL || ADC_u8BusyFlag == BUSY){
        return NOT_OK;
    }
    ADC_u8BusyFlag = BUSY;
    ADC_pfNotification = Copy_pfNotification ;
    /* Enable ADC Interrupt */
    SET_BIT(ADCSRA,ADCSRA_ADIE);
    ADC_voidStartConversion(Copy_u8ReadChannel);
    return OK;
}

void __vector_16(void)     __attribute__((signal));
void __vector_16(void)
{
    if(ADC_pfNotification != NULL)
    {
        /* Clear Flag */
        ADC_u8BusyFlag = NOT_BUSY;
        /* Clear PIE of ADC */
        CLR_BIT(ADCSRA,ADCSRA_ADIE);

        u32 Local_u32ADCRead;
#if ADC_RESOLUTION == ACD_10_BIT_RES
        Local_u32ADCRead= ADCL;
        Local_u32ADCRead |= (ADCH << 8);
#elif ADC_RESOLUTION == ACD_8_BIT_RES
        Local_u32ADCRead = ADCH;
#endif

        /* Calling Notification function */
        ADC_pfNotification(Local_u32ADCRead);
    }
}
