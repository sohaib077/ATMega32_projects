//
// Created by sohai on 10/7/2023.
//

#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

/* ACD CHANNELS */
#define ADC_CH0 0
#define ADC_CH1 1
#define ADC_CH2 2
#define ADC_CH3 3
#define ADC_CH4 4
#define ADC_CH5 5
#define ADC_CH6 6
#define ADC_CH7 7

/* Voltage Reference */
#define ADC_VREF_AREF      0
#define ADC_VREF_AVCC      1
#define ADC_VREF_INTERNAL  2

/* MODE */
#define  ADC_SINGLE_MODE           0
#define  ADC_FREE_RUNNING_MODE     1

/* RESOLUTION */
#define  ACD_8_BIT_RES   0
#define  ACD_10_BIT_RES  1

/* PRESCALER */
#define  ACD_PRESCALER_2    0
#define  ACD_PRESCALER_4    2
#define  ACD_PRESCALER_8    3
#define  ACD_PRESCALER_16   4
#define  ACD_PRESCALER_32   5
#define  ACD_PRESCALER_64   6
#define  ACD_PRESCALER_128  7


#define ADC_INITIAL_DIGITAL_VALUE 0xffff

void ADC_voidInit();

u8 ADC_u8ReadSynchronous(u8 Copy_u8ReadChannel,  u32 * Copy_pu16DigitalValue) ;
u8 ADC_u8ReadAsynchronous(u8 Copy_u8ReadChannel , void(*Copy_pfNotification)(u32));

void ADC_voidStartConversion(u8 Copy_u8ReadChannel);

void ADC_voidEnable();
void ADC_voidDisable();

void ADC_voidEnableInterrupt();
void ADC_voidDisableInterrupt();

#endif //ADC_INTERFACE_H
