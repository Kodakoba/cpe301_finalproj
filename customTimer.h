#ifndef CUSTOM_TIMER_H
#define CUSTOM_TIMER_H
//customTimer.h - funny timer library v3
//do you think this might actually make main look good? no
volatile unsigned char *newTCCR1A = (unsigned char *) 0x80;
volatile unsigned char *newTCCR1B = (unsigned char *) 0x81;
volatile unsigned char *newTCCR1C = (unsigned char *) 0x82;
volatile unsigned char *newTIMSK1 = (unsigned char *) 0x6F;
volatile unsigned int  *newTCNT1  = (unsigned  int *) 0x84;
volatile unsigned char *newTIFR1 =  (unsigned char *) 0x36;

void initTimer(){
  //run this ONLY ONCE.
  *newTCCR1A = 0x00;
  *newTCCR1B = 0x00;
  *newTCCR1C = 0x00;
  *newTIFR1 = 0x01;
}

void delayFreq(double freq){
  //1000hz = 1ms
  double period = 1.0/double(freq);
  double half_period = period/ 2.0f;
  double clk_period = 1.0 / 16000000;
  unsigned int ticks = half_period/clk_period;
  *newTCNT1 = (unsigned int) (65536 - ticks);
  *newTCCR1A = 0x0;
  *newTCCR1B = 0x01; //wait?
  while((*newTIFR1 & 0x01)==0); 
  *newTCCR1B = 0x00;           
  *newTIFR1 = 0x01;
}

void delayMS(int delay){ //my brain hurts right now, ill come back to this.

}

void delaySeconds(){

}


#endif