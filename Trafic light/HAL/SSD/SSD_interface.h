//
// Created by sohai on 9/12/2023.
//

#ifndef SSD_INTERFACE_H
#define SSD_INTERFACE_H

#define SSD_ANODE_TYPE 1
#define SSD_CATHODE_TYPE 0


u8 static SSD_ARR[] =
        {
                0b00111111, /* 0 */
                0b00000110, /* 1 */
                0b01011011, /* 2 */
                0b01001111, /* 3 */
                0b01100110, /* 4 */
                0b01101101, /* 5 */
                0b01111101, /* 6 */
                0b00000111, /* 7 */
                0b01111111, /* 8 */
                0b01101111  /* 9 */
        };

typedef struct {
    u8 type;
    u8 port;
    u8 enablePort;
    u8 enablePin;
} SSD;

u8 SSD_u8SetNumber(u8 Copy_u8Number, SSD *Copy_SSDPtr);

u8 SSD_u8EnableSsd(SSD *Copy_SSDPtr);

u8 SSD_u8DisableSsd(SSD *Copy_SSDPtr);

#endif //DIO_INTERFACE_H_SSD_INTERFACE_H
