//
// Created by sohai on 10/7/2023.
//

#ifndef ADC_REGISTER_H
#define ADC_REGISTER_H

#define ADMUX *((volatile pu8) 0x27)
#define ADMUX_MUX0  0
#define ADMUX_MUX1  1
#define ADMUX_MUX2  2
#define ADMUX_MUX3  3
#define ADMUX_MUX4  4

/* ADC Left Adjust Result */
#define ADMUX_ADLAR  5

/* Voltage Reference Selections for ADC */
#define ADMUX_REFS0 6
#define ADMUX_REFS1 7

#define ADCSRA *((volatile pu8) 0x26)
#define ADCSRA_ADEN     7   /* Enable */
#define ADCSRA_ADSC     6   /* Start Conversion */
#define ADCSRA_ADATE    5   /* Auto Trigger Enable */
#define ADCSRA_ADIF     4   /* Interrupt Flag */
#define ADCSRA_ADIE     3   /* Interrupt Enable */

/* ADC Prescaler Select Bits */
#define ADCSRA_ADPS2    2
#define ADCSRA_ADPS1    1
#define ADCSRA_ADPS0    0

/* Special FunctionIO Registe */
#define SFIOR *((volatile pu8) 0x50)
#define SFIOR_ADTS0 5   /* Auto Trigger Source */
#define SFIOR_ADTS1 6
#define SFIOR_ADTS2 7

#define ADCH *((volatile pu8) 0x25)
#define ADCL *((volatile pu8) 0x24)

#endif //ADC_REGISTER_H