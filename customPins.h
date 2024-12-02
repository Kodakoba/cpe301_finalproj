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
int ERROR_STATE = 0; //might auto extern idfk tbh


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

volatile unsigned char* a_ADMUX = (unsigned char*) 0x7C;
volatile unsigned char* a_ADCSRB = (unsigned char*) 0x7B;
volatile unsigned char* a_ADCSRA = (unsigned char*) 0x7A;
volatile unsigned int* a_ADC_DATA = (unsigned int*) 0x78;

void digitalPinSetup(int pin,char reg,char mode){
  //digital setup should refer pin by some digital pin number (i.e. D2 references PE1)
  //because the ATmega is a nonlinear platform, our digital library will be super truncated!
  //
   if(mode == 'O'){
     switch(reg){
       case 'A':
         *ddr_a |= (0x01 << pin);
       break;
       case 'B':
         *ddr_b |= (0x01 << pin);
       break;
       case 'C':
         *ddr_c |= (0x01 << pin);
       break;
       case 'D':
         *ddr_d |= (0x01 << pin);
       break;
       case 'E':
         *ddr_e |= (0x01 << pin);
       break;
       case 'F':
         *ddr_f |= (0x01 << pin);
       break;
       case 'G':
         *ddr_g |= (0x01 << pin);
       break;
       case 'H':
         *ddr_h |= (0x01 << pin);
       break;
       case 'J':
         *ddr_j |= (0x01 << pin);
       break;
       case 'K':
         *ddr_k |= (0x01 << pin);
       break;
       case 'L':
         *ddr_l |= (0x01 << pin);
       break;
       default:
         //ok arduino sucks so much for this. there's NO DEFAULT OUTPUT ASIDE FROM SERIAL. WHY??
         ERROR_STATE + 1; //so we can check in the actual serial library if this is incremented for some reason.
       break;
     }
   }
   else if (mode == 'I'){
     switch(reg){
       case 'A':
         *ddr_a &= ~(0x01 << pin);
         *port_a |= (0x01 << pin);
         break;
       case 'B':
         *ddr_b &= ~(0x01 << pin);
         *port_b |= (0x01 << pin);
         break;
       case 'C':
         *ddr_c &= ~(0x01 << pin);
         *port_c |= (0x01 << pin);
         break;
       case 'D':
           *ddr_d &= ~(0x01 << pin);
           *port_d |= (0x01 << pin);
           break;
       case 'E':
           *ddr_e &= ~(0x01 << pin);
           *port_e |= (0x01 << pin);
           break;
       case 'F':
           *ddr_f &= ~(0x01 << pin);
           *port_f |= (0x01 << pin);
           break;
       case 'G':
           *ddr_g &= ~(0x01 << pin);
           *port_g |= (0x01 << pin);
           break;
       case 'H':
           *ddr_h &= ~(0x01 << pin);
           *port_h |= (0x01 << pin);
           break;
       case 'J':
           *ddr_j &= ~(0x01 << pin);
           *port_j |= (0x01 << pin);
           break;
       case 'K':
           *ddr_k &= ~(0x01 << pin);
           *port_k |= (0x01 << pin);
           break;
       case 'L':
           *ddr_l &= ~(0x01 << pin);
           *port_l |= (0x01 << pin);
       default:
           ERROR_STATE + 100; 
     }
   }
}

void digitalPinWrite(char reg,int pin,bool state){
  //we're not gonna make initialize flags cause we're using this all of once!!!!
  switch(reg){
    case 'A':
      if(state){
        WRITE_HIGH_PA(pin);
      }  
      if(state == false){
        WRITE_LOW_PA(pin);
      }  
      break;
    case 'B':
      if(state){
        WRITE_HIGH_PB(pin);
      }  
      if(state == false){
        WRITE_LOW_PB(pin);
      }  
      break;
    case 'C':
      if(state){
        WRITE_HIGH_PC(pin);
      }  
      if(state == false){
        WRITE_LOW_PC(pin);
      }  
      break;
    case 'D':
      if(state){
        WRITE_HIGH_PD(pin);
      }  
      if(state == false){
        WRITE_LOW_PD(pin);
      }  
      break;
    case 'E':
      if(state){
        WRITE_HIGH_PE(pin);
      }  
      if(state == false){
        WRITE_LOW_PE(pin);
      }  
      break;
    case 'F':
      if(state){
        WRITE_HIGH_PF(pin);
      }  
      if(state == false){
        WRITE_LOW_PF(pin);
      }  
      break;
    case 'G':
      if(state){
        WRITE_HIGH_PG(pin);
      }  
      if(state == false){
        WRITE_LOW_PG(pin);
      }  
      break;
    case 'H':
      if(state){
        WRITE_HIGH_PH(pin);
      }  
      if(state == false){
        WRITE_LOW_PH(pin);
      }  
      break;
    case 'J':
      if(state){
        WRITE_HIGH_PJ(pin);
      }  
      if(state == false){
        WRITE_LOW_PJ(pin);
      }  
      break;
    case 'K':
      if(state){
        WRITE_HIGH_PK(pin);
      }  
      if(state == false){
        WRITE_LOW_PK(pin);
      }  
      break;
    case 'L':
      if(state){
        WRITE_HIGH_PL(pin);
      }  
      if(state == false){
        WRITE_LOW_PL(pin);
      }  
      break;
    default:
      ERROR_STATE + 10000;
      break;
    }
}
//oop land command pattern would come in handy for this logic to be honest.
bool digitalPinRead(char reg,int pin){
  switch(reg){
    case 'A':
      if(*pin_a & 0x10){
        return true;
      }
      else{
        return false;
      }
      break;
    case 'B':
      if(*pin_b & 0x10){
        return true;
      }
      else{
        return false;
      }
      break;
    case 'C':
      if(*pin_c & 0x10){
        return true;
      }
      else{
        return false;
      }
      break;
    case 'D':
      if(*pin_d & 0x10){
        return true;
      }
      else{
        return false;
      }
      break;
    case 'E':
      if(*pin_e & 0x10){
        return true;
      }
      else{
        return false;
      }
      break;
    case 'F':
      if(*pin_f & 0x10){
        return true;
      }
      else{
        return false;
      }
      break;
    case 'G':
      if(*pin_g & 0x10){
        return true;
      }
      else{
        return false;
      }
      break;
    case 'H':
      if(*pin_h & 0x10){
        return true;
      }
      else{
        return false;
      }
      break;
    case 'J':
      if(*pin_j & 0x10){
        return true;
      }
      else{
        return false;
      }
      break;
    case 'K':
      if(*pin_k & 0x10){
        return true;
      }
      else{
        return false;
      }
      break;
    case 'L':
      if(*pin_l & 0x10){
        return true;
      }
      else{
        return false;
      }
      break;
    default:
      ERROR_STATE + 1000000; //i love fall through programming!!111!!!!
      break;
  }
}
//begin ADC <bruh>
void adc_init()
{
  // setup the A register
  *a_ADCSRA |= 0b10000000; // set bit   7 to 1 to enable the ADC
  *a_ADCSRA &= 0b11011111; // clear bit 6 to 0 to disable the ADC trigger mode
  *a_ADCSRA &= 0b11110111; // clear bit 5 to 0 to disable the ADC interrupt
  *a_ADCSRA &= 0b11111000; // clear bit 0-2 to 0 to set prescaler selection to slow reading
  // setup the B register
  *a_ADCSRB &= 0b11110111; // clear bit 3 to 0 to reset the channel and gain bits
  *a_ADCSRB &= 0b11111000; // clear bit 2-0 to 0 to set free running mode
  // setup the MUX Register
  *a_ADMUX  &= 0b01111111; // clear bit 7 to 0 for AVCC analog reference
  *a_ADMUX  |= 0b01000000; // set bit   6 to 1 for AVCC analog reference
  *a_ADMUX  &= 0b11011111; // clear bit 5 to 0 for right adjust result
  *a_ADMUX  &= 0b11100000; // clear bit 4-0 to 0 to reset the channel and gain bits
}

unsigned int adc_read(unsigned char adc_channel_num)
{
  // clear the channel selection bits (MUX 4:0)
  *a_ADMUX  &= 0b11100000;
  // clear the channel selection bits (MUX 5)
  *a_ADCSRB &= 0b11110111;
  if(adc_channel_num > 7)
  {
    adc_channel_num -= 8;
    *a_ADCSRB |= 0b00001000;
  }
  *a_ADMUX  += adc_channel_num;
  *a_ADCSRA |= 0x40;
  while((*a_ADCSRA & 0x40) != 0);
  return *a_ADC_DATA;
}

#endif