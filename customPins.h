#ifndef CUSTOM_PINS_H
#define CUSTOM_PINS_H
//customPins.h - a fun custom pin library
#define WRITE_HIGH_PA(pin_num)  *port_a |= (0x01 << pin_num);
#define WRITE_LOW_PA(pin_num)  *port_a &= ~(0x01 << pin_num);
#define WRITE_HIGH_PB(pin_num)  *port_b |= (0x01 << pin_num);
#define WRITE_LOW_PB(pin_num)  *port_b &= ~(0x01 << pin_num);



#endif