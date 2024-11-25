#ifndef CUSTOM_PINS_H
#define CUSTOM_PINS_H
//customPins.h - a fun custom pin library
#define WRITE_HIGH_PA(pin_num)  *port_a |= (0x01 << pin_num);
#define WRITE_LOW_PA(pin_num)  *port_a &= ~(0x01 << pin_num);
#define WRITE_HIGH_PB(pin_num)  *port_b |= (0x01 << pin_num);
#define WRITE_LOW_PB(pin_num)  *port_b &= ~(0x01 << pin_num);
#define WRITE_HIGH_PC(pin_num)  *port_c |= (0x01 << pin_num);
#define WRITE_LOW_PC(pin_num)  *port_c &= ~(0x01 << pin_num);
#define WRITE_HIGH_PD(pin_num)  *port_d |= (0x01 << pin_num);
#define WRITE_LOW_PD(pin_num)  *port_d &= ~(0x01 << pin_num);
#define WRITE_HIGH_PE(pin_num)  *port_e |= (0x01 << pin_num);
#define WRITE_LOW_PE(pin_num)  *port_e &= ~(0x01 << pin_num);
#define WRITE_HIGH_PF(pin_num)  *port_f |= (0x01 << pin_num);
#define WRITE_LOW_PF(pin_num)  *port_f &= ~(0x01 << pin_num);
#define WRITE_HIGH_PG(pin_num)  *port_g |= (0x01 << pin_num);
#define WRITE_LOW_PG(pin_num)  *port_g &= ~(0x01 << pin_num);
#define WRITE_HIGH_PH(pin_num)  *port_h |= (0x01 << pin_num);
#define WRITE_LOW_PH(pin_num)  *port_h &= ~(0x01 << pin_num);
#define WRITE_HIGH_PJ(pin_num)  *port_j |= (0x01 << pin_num);
#define WRITE_LOW_PJ(pin_num)  *port_j &= ~(0x01 << pin_num);
#define WRITE_HIGH_PK(pin_num)  *port_k |= (0x01 << pin_num);
#define WRITE_LOW_PK(pin_num)  *port_k &= ~(0x01 << pin_num);
#define WRITE_HIGH_PL(pin_num)  *port_l |= (0x01 << pin_num);
#define WRITE_LOW_PL(pin_num)  *port_l &= ~(0x01 << pin_num);

volatile unsigned char* port_a = (unsigned char*) 0x22;
volatile unsigned char* ddr_a  = (unsigned char*) 0x21;
volatile unsigned char* pin_a  = (unsigned char*) 0x20;

volatile unsigned char* port_b = (unsigned char*) 0x25;
volatile unsigned char* ddr_b  = (unsigned char*) 0x24;
volatile unsigned char* pin_b  = (unsigned char*) 0x23;

volatile unsigned char* port_c = (unsigned char*) 0x28;
volatile unsigned char* ddr_c  = (unsigned char*) 0x27;
volatile unsigned char* pin_c  = (unsigned char*) 0x26;

volatile unsigned char* port_d = (unsigned char*) 0x2B;
volatile unsigned char* ddr_d  = (unsigned char*) 0x2A;
volatile unsigned char* pin_d  = (unsigned char*) 0x29;

volatile unsigned char* port_e = (unsigned char*) 0x2E;
volatile unsigned char* ddr_e  = (unsigned char*) 0x2D;
volatile unsigned char* pin_e  = (unsigned char*) 0x2C;

volatile unsigned char* port_f = (unsigned char*) 0x31;
volatile unsigned char* ddr_f  = (unsigned char*) 0x30;
volatile unsigned char* pin_f  = (unsigned char*) 0x2F;

volatile unsigned char* port_g = (unsigned char*) 0x34;
volatile unsigned char* ddr_g  = (unsigned char*) 0x33;
volatile unsigned char* pin_g  = (unsigned char*) 0x32;

volatile unsigned char* port_h = (unsigned char*) 0x102;
volatile unsigned char* ddr_h  = (unsigned char*) 0x101;
volatile unsigned char* pin_h  = (unsigned char*) 0x100;

volatile unsigned char* port_j = (unsigned char*) 0x105;
volatile unsigned char* ddr_j  = (unsigned char*) 0x104;
volatile unsigned char* pin_j  = (unsigned char*) 0x103;

volatile unsigned char* port_k = (unsigned char*) 0x108;
volatile unsigned char* ddr_k  = (unsigned char*) 0x107;
volatile unsigned char* pin_k  = (unsigned char*) 0x106;

volatile unsigned char* port_l = (unsigned char*) 0x10B;
volatile unsigned char* ddr_l  = (unsigned char*) 0x10A;
volatile unsigned char* pin_l  = (unsigned char*) 0x109;

void digitalPinSetup(int pin, char mode){
  //digital setup should refer pin by some digital pin number (i.e. D2 references PE1)
  //because the ATmega is a nonlinear platform, our digital library will be super truncated!
  //
  switch(pin){
    case 0:
      *ddr_e |= 0x01;

    case 1:
      *ddr_e |= 0x02;

    case 2:
      *ddr_e |= 0x10;
    //pickup here -L

  }
}



#endif