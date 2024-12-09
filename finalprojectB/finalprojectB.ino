//this should be used ONLY in the case i can't figure out headers or dreaded arduino bullshit since they don't include a debugger.
//it is a MONO FILE design, and aside from being a pain to debug it will be VERY LARGE.
#include <EduIntro.h> //for DHT11 - refer to eduintro library for implementation.
#include <LiquidCrystal.h>
#include <Stepper.h>
#include <RTClib.h>

/*buttons:
ON_OFF - D30
RESET - D31
LIMITERS - D32/33
STEPPER U/D - D34/35

motors:
FAN - D0
STEPPER - D1-4

sensors/other dout:
DHT - D5
LCD - D6-11
RTC - D20/21 (i2c)

leds:
R - D22
Y - D23
G - D24
B - D25*/

#define RDA 0x80
#define TBE 0x20

//the megalist of register cause YAY
volatile unsigned char* port_a = (unsigned char*) 0x22;
volatile unsigned char* ddr_a = (unsigned char*) 0x21;
volatile unsigned char* pin_a = (unsigned char*) 0x20;
volatile unsigned char* port_b = (unsigned char*) 0x25;
volatile unsigned char* ddr_b = (unsigned char*) 0x24;
volatile unsigned char* pin_b = (unsigned char*) 0x23;
volatile unsigned char* port_c = (unsigned char*) 0x28;
volatile unsigned char* ddr_c = (unsigned char*) 0x27;
volatile unsigned char* pin_c = (unsigned char*) 0x26;
volatile unsigned char* port_d = (unsigned char*) 0x2B;
volatile unsigned char* ddr_d = (unsigned char*) 0x2A;
volatile unsigned char* pin_d = (unsigned char*) 0x29;
volatile unsigned char* port_e = (unsigned char*) 0x2E;
volatile unsigned char* ddr_e = (unsigned char*) 0x2D;
volatile unsigned char* pin_e = (unsigned char*) 0x2C;
volatile unsigned char* port_f = (unsigned char*) 0x31;
volatile unsigned char* ddr_f = (unsigned char*) 0x30;
volatile unsigned char* pin_f = (unsigned char*) 0x2F;
volatile unsigned char* port_g = (unsigned char*) 0x34;
volatile unsigned char* ddr_g = (unsigned char*) 0x33;
volatile unsigned char* pin_g = (unsigned char*) 0x32;
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
//additional define magic
#define WRITE_LOW_PA(pin_num)  *port_a &= ~(0x01 << pin_num);
#define WRITE_HIGH_PA(pin_num) *port_a |= (0x01 << pin_num);
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

volatile unsigned char *newUCSR0A = (unsigned char *)0x00C0;
volatile unsigned char *newUCSR0B = (unsigned char *)0x00C1;
volatile unsigned char *newUCSR0C = (unsigned char *)0x00C2;
volatile unsigned int  *newUBRR0  = (unsigned int *) 0x00C4;
volatile unsigned char *newUDR0   = (unsigned char *)0x00C6;

volatile unsigned char *newTCCR1A = (unsigned char *) 0x80;
volatile unsigned char *newTCCR1B = (unsigned char *) 0x81;
volatile unsigned char *newTCCR1C = (unsigned char *) 0x82;
volatile unsigned char *newTIMSK1 = (unsigned char *) 0x6F;
volatile unsigned int  *newTCNT1  = (unsigned  int *) 0x84;
volatile unsigned char *newTIFR1 =  (unsigned char *) 0x36;

volatile unsigned char* a_ADMUX = (unsigned char*) 0x7C;
volatile unsigned char* a_ADCSRB = (unsigned char*) 0x7B;
volatile unsigned char* a_ADCSRA = (unsigned char*) 0x7A;
volatile unsigned int* a_ADC_DATA = (unsigned int*) 0x78;

#define B_ON_OFF 7 //C7
#define B_RESET 6 //C6
#define B_LIM_MAX 5 //C5
#define B_LIM_MIN 4 //C4
#define B_STEP_U 3 //C3
#define B_STEP_D 2 //C2

#define FAN_P 0 //E0

#define STEPPER_P1 1 //E1
#define STEPPER_P2 2//E4
#define STEPPER_P3 3 //E5
#define STEPPER_P4 4 //G5 //who designed this
#define DHT_PIN 5 //E3
#define WATER_LEVEL 6

//boundries
#define WATER_THRESH 320 //this is subject to change via actual measurements from the sensor.
#define TEMP_THRESH 50 //or 10 in C mode, i didn't check the doc at this time.

//setup but global
LiquidCrystal lcd(7,8,9,10,11,12);
DHT11 dht(D5);
RTC_DS1307 rtc;
Stepper stepper(2048, STEPPER_P1, STEPPER_P2, STEPPER_P3, STEPPER_P4);

float temp_F;
int humidity; //don't know if i actually need this bjorgen
int lastTempPrint = 0;

// state machine flags 
bool fanOn = false;
int ledH = -1;
bool displayTemp = false;
bool stepperState = false;
bool Water = false;
//the state machine
enum State {
  IDLE,
  OFF,
  RUNNING, //or just run?
  ERROR,
  START,
};
//other state machine sh!t
State currentState = OFF;
State previousState = START;
bool OnState = true;

//did i mention i spent my whole weekend doing this and im becoming derranged

void setup(){
    U0init(9600);
    //initialize port, ddr, pin here later on my laptop.
    //and set mode
    //*ddrc &= ~(0x01 << B_ON_OFF | 0x01 << B_RESET | ...)
    pinSetup();
    rtc.begin();
    DateTime now = DateTime(2024, 12, 12, 0, 0, 0);
    rtc.adjust(now);
    adc_init();
    initTimer();
    //dht.begin(); // check library for this function, its a PITA.
    lcd.begin(16, 2);
    //sheesh
    attachInterrupt(digitalPinToInterrupt(30), powerChange, RISING);
}

void loop(){
    DateTime now = rtc.now();
    if(displayTemp){
        temp_F = dht.readFahrenheit();
        humidity = dht.readHumidity(); //may require casting to an integer. BOO.
    }
    if(neoPinRead(7, 'C')){
        powerChange();
    }
    currentState = newMachineState(humidity,temp_F,currentState);
    if(currentState != previousState){
        //print the time
        //then do state matic stuff.
        switch (currentState) {
        case OFF:
            fanOn = false;
            ledH = 3;
            displayTemp = false;
            stepperState = true;
            Water = false;
            break; //always forget you >:/
        case IDLE:
            fanOn = false;
            ledH = 2;
            displayTemp = true;
            stepperState = true;
            Water = true;
            break;
        case RUNNING:
            fanOn = true;
            ledH = 1;
            displayTemp = true;
            stepperState = true;
            Water = true;
            break;
        case ERROR:
            lcd.clear();
            lcd.print("ERROR WATER LOW");
            fanOn = false;
            ledH = 0;
            displayTemp = true;
            stepperState = false;
            Water = true;
            break;
        case START: 
            //should do start things.
        default: //needed or else it breaks and im gonna break a computer.
            break;
    }
    setFan(fanOn);
    //turn leds on here too using *ddrA.
    if(ledH = 0){
      WRITE_HIGH_PA(0);
      WRITE_LOW_PA(1);
      WRITE_LOW_PA(2);
      WRITE_LOW_PA(3);
    }
    else if(ledH = 1){
      WRITE_HIGH_PA(1);
      WRITE_LOW_PA(0);
      WRITE_LOW_PA(2);
      WRITE_LOW_PA(3);
    }
    else if(ledH = 2){
      WRITE_HIGH_PA(2);
      WRITE_LOW_PA(1);
      WRITE_LOW_PA(0);
      WRITE_LOW_PA(3);
    }
    else if(ledH = 3){
      WRITE_HIGH_PA(3);
      WRITE_LOW_PA(1);
      WRITE_LOW_PA(2);
      WRITE_LOW_PA(0);
    }

    if(stepperState){
        int previous = 0;
        int stepperDirection = 2048 * (neoPinRead(3, 'C') ? 1 : neoPinRead(2, 'C') ? -1 : 0);
        //preform a limit check
        stepperDirection = (neoPinRead(5, 'C') ? min(stepperDirection, 0) : (neoPinRead(4, 'C') ? max(stepperDirection,0) : stepperDirection));
        if(stepperDirection != 0){
            U0putchar('S');
            U0putchar('T');
            U0putchar('E');
            U0putchar('P');
            U0putchar(' ');
            U0putchar(stepperDirection);
            DisplayTime(now);
        }
        stepper.step(stepperDirection - previous);
        previous = stepperDirection;
    }
    if(displayTemp && abs(lastTempPrint - now.minute()) >= 1){
        lcd.clear();
        lastTempPrint = now.minute(); //update prev
        temp_F = dht.readFahrenheit();
        humidity = dht.readHumidity();
        lcd.print("Temp F, Humidity"); //might be too wide
        delayFreq(1); //originally was gonna CALL THE TIME FUNCTION AT 1 HZ. but cmon, functional programming 
        lcd.clear();
        lcd.print(temp_F); //write temp in F to lcd
        lcd.print(humidity); //write humidity to lcd
    }
    previousState = currentState;
    if(Water){
        int waterLvl = adc_read(WATER_LEVEL); //calc water lvl
        if(waterLvl <= WATER_THRESH){
            currentState = ERROR;
        }
    }
    delayFreq(1); //1 second delay.
    }
}

void powerChange(){
    previousState = currentState;
    bool bPressed = neoPinRead(7, 'C'); //implies you need to hold the button long enough to reach this state.
     if(OnState && bPressed){
        currentState = IDLE;
        OnState = false;
    }
    else if(bPressed) {
        currentState = OFF;
        OnState = true;
    }
}

int neoPinRead(int pin, char bank){
    //needs bull fallthrough statement
    switch(bank){
      case 'A':
        return *pin_a & (0x01 << pin);
        break;
      case 'B':
        return *pin_b & (0x01 << pin);
        break;
      case 'C':
        return *pin_c & (0x01 << pin);
        break;
      case 'D':
        return *pin_d & (0x01 << pin);
        break;
      case 'E':
        return *pin_e & (0x01 << pin);
        break;
      case 'F':
        return *pin_f & (0x01 << pin);
        break;
      case 'G':
        return *pin_g & (0x01 << pin);
        break;
      case 'H':
        return *pin_h & (0x01 << pin);
        break;
      case 'J':
        return *pin_j & (0x01 << pin);
        break;
      case 'K':
        return *pin_k & (0x01 << pin);
        break;
      case 'L':
        return *pin_l & (0x01 << pin);
        break;
    }
}

State newMachineState(int waterLvl , float temp, State currentState){
    State state;
    if(temp <= TEMP_THRESH && currentState == RUNNING){
        state = IDLE;
    }
    else if(temp > TEMP_THRESH && currentState == IDLE){
        state = RUNNING;
    }
    else if(currentState == ERROR && neoPinRead(6,'C') && waterLvl > WATER_THRESH){
        state = IDLE;
    }
    else{
        state = currentState;
    }
    return state;
}

void setFan(int speed){
    if(speed){
        WRITE_HIGH_PE(0);
    }
    if(!speed){
        //do not that.
        WRITE_LOW_PE(0);
    }
}

void setStep(int distance){
    stepper.step(distance); //should do bounds checking.
}

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

char numbers[10] = {'0','1','2','3','4','5','6','7','8','9'};

void DisplayTime(DateTime now){
//date stuff
    int year = now.year();
    int month = now.month();
    int day = now.day();
    int hour = now.hour();
    int minute = now.minute();
    int second = now.second(); 
//more conversion sh!t i kept out of main (lol)
    int place_ones_Year = year % 10;
    int place_tens_Year = year / 10 % 10;
    int place_ones_Month = month % 10;
    int place_tens_Month = month / 10 % 10;
    int place_ones_Day = day % 10;
    int place_tens_Day = day / 10 % 10;
    int place_ones_Hour = hour % 10;
    int place_tens_Hour = hour / 10 % 10;
    int place_ones_Minute = minute % 10;
    int place_tens_Minute = minute / 10 % 10;
    int place_ones_Second = second % 10;
    int place_tens_Second = second / 10 % 10;
//now let's write it!!!
    U0putchar('M'); //the temptation to put this all on one line is real.
    U0putchar(':');
    U0putchar('D');
    U0putchar(':');
    U0putchar('Y');
    U0putchar(' ');
    U0putchar('H');
    U0putchar(':');
    U0putchar('M');
    U0putchar(':');
    U0putchar('S');
    U0putchar(' ');
    U0putchar(numbers[place_tens_Month]);
    U0putchar(numbers[place_ones_Month]);
    U0putchar(':');
    U0putchar(numbers[place_tens_Day]);
    U0putchar(numbers[place_ones_Day]);
    U0putchar(':');
    U0putchar(numbers[place_tens_Year]);
    U0putchar(numbers[place_ones_Year]);
    U0putchar(' ');
    U0putchar(numbers[place_tens_Hour]);
    U0putchar(numbers[place_ones_Hour]);
    U0putchar(':');
    U0putchar(numbers[place_tens_Minute]);
    U0putchar(numbers[place_ones_Minute]);
    U0putchar(':');
    U0putchar(numbers[place_tens_Second]);
    U0putchar(numbers[place_ones_Second]);
    U0putchar('\n');
}


void pinSetup(){
    //*ddrc &= ~(0x01 << B_ON_OFF | 0x01 << B_RESET | ...)
    //LEDs
    *ddr_a |= 0b00001111; //cheesy >:)
    //buttons
    *ddr_c &= ~(0b11111100);
    *port_c |= 0b11111100;
    //the fan since stepper already has a routine
    *ddr_e |= 0x01; //because 0x01 = 0b00000001
    //DHT
    *ddr_e &= ~(0b00001000);
    *port_e |= 0b00001000;
    //RTC (i2c in)
    *ddr_d &= ~(0b00000011);
    *port_d |= 0b00000011;
    //water sensor
    *ddr_h &= ~(0b00001000);
    *port_h |= (0b00001000);
    //should be it? lets find out :trollge: 


}
