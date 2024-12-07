#ifndef CUSTOM_PINS_H
#define CUSTOM_PINS_H
//customPins.h - a fun custom pin library

enum class PinMode {
  PIN_OUTPUT = 0,
  PIN_INPUT
};

enum class Register {
  A = 1,
  B = 2,
  C = 3,
  D = 4,
  E = 5,
  F = 6,
  G = 7,
  H = 8,
  J = 9,
  K = 10,
  L = 11
};

struct PinSampler {
  Register reg;
  int pin;
};


int ERROR_STATE = 0; //might auto extern idfk tbh

volatile unsigned char* ddr_base = (unsigned char*) 0x1E;
volatile unsigned char* port_base = (unsigned char*) 0x1F;
volatile unsigned char* pin_base = (unsigned char*) 0x1D;

// Conversion funcs to turn a Register into a proper int
unsigned char *ddrb(Register reg) {
  return *(ddr_base + 0x3 * static_cast<int>(reg));
}

unsigned char *port(Register reg) {
  return *(port_base + 0x3 * static_cast<int>(reg));
}

unsigned char *pinb(Register reg) {
  return *(pin_base + 0x3 * static_cast<int>(reg));
}

//until here
volatile unsigned char* a_ADMUX = (unsigned char*) 0x7C;
volatile unsigned char* a_ADCSRB = (unsigned char*) 0x7B;
volatile unsigned char* a_ADCSRA = (unsigned char*) 0x7A;
volatile unsigned int* a_ADC_DATA = (unsigned int*) 0x78;

void digitalPinSetup(Register reg, int pin, PinMode mode) {
  switch( mode ) {
    case PinMode::PIN_OUTPUT:
      *ddrb(reg) |= (0x01 << pin);
      break;

    case PinMode::PIN_INPUT:
      *ddrb(reg) &= ~(0x01 << pin);
      *port(reg) |= ~(0x01 << pin);
      break;
  }
}

void digitalPinWrite(Register reg, int pin, bool state) {
  switch(state) {
    case false:
      *port(reg) &= ~(0x01 << pin);
      break;
    case true:
      *port(reg) |= (0x01 << pin);
      break;
  }
}

bool digitalPinRead(Register reg) {
  return *pinb(reg) & 0x10;
}

void digitalPinSetup(PinSampler p, PinMode mode) {
  digitalPinSetup(p.reg, p.pin, mode);
}

void digitalPinWrite(PinSampler p, bool mode) {
  digitalPinWrite(p.reg, p.pin, mode);
}

//begin ADC <bruh>
void adc_init()
{
  // setup the A register
  *a_ADCSRA |= 0x80; // set bit   7 to 1 to enable the ADC
  *a_ADCSRA &= 0xDF; // clear bit 6 to 0 to disable the ADC trigger mode
  *a_ADCSRA &= 0xF7; // clear bit 5 to 0 to disable the ADC interrupt
  *a_ADCSRA &= 0xF8; // clear bit 0-2 to 0 to set prescaler selection to slow reading
  // setup the B register
  *a_ADCSRB &= 0xF7; // clear bit 3 to 0 to reset the channel and gain bits
  *a_ADCSRB &= 0xF8; // clear bit 2-0 to 0 to set free running mode
  // setup the MUX Register
  *a_ADMUX  &= 0x7F; // clear bit 7 to 0 for AVCC analog reference
  *a_ADMUX  |= 0x40; // set bit   6 to 1 for AVCC analog reference
  *a_ADMUX  &= 0xDF; // clear bit 5 to 0 for right adjust result
  *a_ADMUX  &= 0xE0; // clear bit 4-0 to 0 to reset the channel and gain bits
}

unsigned int adc_read(unsigned char adc_channel_num)
{
  // clear the channel selection bits (MUX 4:0)
  *a_ADMUX  &= 0xE0;
  // clear the channel selection bits (MUX 5)
  *a_ADCSRB &= 0xF7;
  if(adc_channel_num > 7)
  {
    adc_channel_num -= 8;
    *a_ADCSRB |= 0x08;
  }
  *a_ADMUX  += adc_channel_num;
  *a_ADCSRA |= 0x40;
  while((*a_ADCSRA & 0x40) != 0);
  return *a_ADC_DATA;
}

#endif