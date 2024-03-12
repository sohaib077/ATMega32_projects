//
// Created by sohai on 10/4/2023.
//

#ifndef PORT_REGISTER_H
#define PORT_REGISTER_H

#define DDRA    *((volatile pu8) 0x3A)
#define DDRB    *((volatile pu8) 0x37)
#define DDRC    *((volatile pu8) 0x34)
#define DDRD    *((volatile pu8) 0x31)

#define PORTA    *((volatile pu8) 0x3B)
#define PORTB    *((volatile pu8) 0x38)
#define PORTC    *((volatile pu8) 0x35)
#define PORTD    *((volatile pu8) 0x32)

#endif //PORT_REGISTER_H
