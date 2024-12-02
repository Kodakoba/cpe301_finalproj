#ifndef CUSTOM_SERIAL_H
#define CUSTOM_SERIAL_H
//customSerial.h - a crude serial library :catjamcry:
#define RDA 0x80
#define TBE 0x20

volatile unsigned char *newUCSR0A = (unsigned char *)0x00C0;
volatile unsigned char *newUCSR0B = (unsigned char *)0x00C1;
volatile unsigned char *newUCSR0C = (unsigned char *)0x00C2;
volatile unsigned int  *newUBRR0  = (unsigned int *) 0x00C4;
volatile unsigned char *newUDR0   = (unsigned char *)0x00C6;

void U0init(int U0baud){
 unsigned long FCPU = 16000000;
 unsigned int tbaud;
 tbaud = (FCPU / 16 / U0baud - 1);
 //equal to (FCPU / (16 * U0baud)) - 1;
 *newUCSR0A = 0x20;
 *newUCSR0B = 0x18;
 *newUCSR0C = 0x06;
 *newUBRR0  = tbaud;
}
unsigned char U0kbhit(){
  return *newUCSR0A & RDA;
}
unsigned char U0getchar(){
  return *newUDR0;
}
void U0putchar(unsigned char U0pdata){
  while((*newUCSR0A & TBE)==0);
  *newUDR0 = U0pdata;
}
#endif