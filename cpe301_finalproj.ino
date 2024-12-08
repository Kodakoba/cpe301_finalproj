//it's the FI-NAL PRO-JEEECT
//by Lloyd C and Bailey E
//let's begin with some directives
#include "customPins.h"
#include "customSerial.h"
#include "customTimer.h"
#include "customPrintOverSerial.h"
//neccessary libs
#include <EduIntro.h> //for DHT11
#include <LiquidCrystal.h>
#include <Stepper.h>
#include <RTClib.h>
//handy fast-edit definitions in {register letter, position}
//buttons
#define B_ON_OFF {Register::C,7}
#define B_RESET {Register::C,6}
#define LIMIT_MAX {Register::C,5}
#define LIMIT_MIN {Register::C,4}
#define STEP_UP {Register::C,3}
#define STEP_DOWN {Register::C,2}

//leds
#define LED_R {Register::A,0}
#define LED_Y {Register::A,1}
#define LED_G {Register::A,2}
#define LED_B {Register::A,3}

//motors
#define FAN {Register::E,0}
#define STEPPER_P1 1 //E1
#define STEPPER_P2 2//E4
#define STEPPER_P3 3 //E5
#define STEPPER_P4 4 //G5 //who designed this

//sensors
#define DHT_PIN 5 //E3
#define WATER_LEVEL 1

//boundries
#define WATER_THRESH 320 //this is subject to change via actual measurements from the sensor.
#define TEMP_THRESH 50 //or 10 in C mode, i didn't check the doc at this time.

//I2C bus
#define SDA {Register::D,1}
#define SCL {Register::D,0}

//setup but global
LiquidCrystal lcd(6,7,8,9,10,11);
DHT11 dht11(DHT_PIN);
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
//state machine sh!t
State currentState = OFF;
State previousState = START;
bool OnState = true;
//test macro
#define BLINK {Register::B, 6}

//now we actually run a setup routine
void setup(){
    U0init(9600);
    //call digitalPinSetup
    digitalPinSetup(B_ON_OFF, PinMode::PIN_INPUT);
    digitalPinSetup(B_RESET, PinMode::PIN_INPUT);
    digitalPinSetup(LIMIT_MAX, PinMode::PIN_INPUT);
    digitalPinSetup(LIMIT_MIN, PinMode::PIN_INPUT);
    digitalPinSetup(STEP_UP, PinMode::PIN_INPUT);
    digitalPinSetup(STEP_DOWN, PinMode::PIN_INPUT);
    //
    digitalPinSetup(LED_R, PinMode::PIN_OUTPUT);
    digitalPinSetup(LED_Y, PinMode::PIN_OUTPUT);
    digitalPinSetup(LED_G, PinMode::PIN_OUTPUT);
    digitalPinSetup(LED_B, PinMode::PIN_OUTPUT);
    //
    digitalPinSetup(FAN, PinMode::PIN_OUTPUT);
    //
    digitalPinSetup(SDA, PinMode::PIN_INPUT);
    digitalPinSetup(SCL, PinMode::PIN_INPUT);
    //
    RTC.begin();
    DateTime now = DateTime(2024, 12, 12, 0, 0, 0);
    RTC.adjust(now);
    adc_init();
    initTimer();
    dht.begin(); // check library for this function, its a PITA.
    lcd.begin(16, 2);
    //sheesh
    attachInterrupt(digitalPinToInterrupt(30), powerChange, RISING);
}

void loop(){
    DateTime now = RTC.now();
    if(displayTemp){
        temp_F = dht.readTemperature();
        humidity = dht.readHumidity(); //may require casting to an integer. BOO.
    }
    if(digitalPinRead(B_ON_OFF)){
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
    if(stepperState){
        //determine direction the user wants, the limits it can go, then set that speed
        int stepperDirection = 2048 * (digitalPinRead(STEP_UP) ? 1 : digitalPinRead(STEP_DOWN) ? -1 : 0);
        //preform limit checks
        stepperDirection = (digitalPinRead(LIMIT_MAX) ? min(stepperDirection, 0) : (digitalPinRead(LIMIT_MIN) ? max(stepperDirection,0) : stepperDirection));
        if(stepperDirection != 0){
            U0putchar('S');
            U0putchar('T');
            U0putchar('E');
            U0putchar('P');
            U0putchar(' ');
            U0putchar(stepperDirection);
            DisplayTime(now); //hehe outbound library function
        }
        setStepperMotor(stepperDirection);
    }
    if(displayTemp && abs(lastTempPrint - now.minute()) >= 1){
        lcd.clear();
        lastTempPrint = now.minute(); //update prev
        temp_F = dht.readTemperature();
        humidity = dht.readHumidity();
        lcd.print("Temp F, Humidity"); //might be too wide
        delayFreq(1);
        lcd.clear();
        lcd.print(temp_F); // write temp in F to lcd
        lcd.print(humidity); // write humidity to lcd
    }
    previousState = currentState;
    if(Water){
        int waterLvl = adc_read(WATER_LEVEL); // calc water lvl
        if(waterLvl <= WATER_THRESH){
            currentState = ERROR;
        }
    }
    delayFreq(1); //1 second delay.
    }
}

void powerChange(){
    previousState = currentState;
    bool bPressed = digitalPinRead(B_ON_OFF); //implies you need to hold the button long enough to reach this state.
     if(OnState && bPressed){
        currentState = IDLE;
        OnState = false;
    }
    else if(bPressed) {
        currentState = OFF;
        OnState = true;
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
    else if(currentState == ERROR && digitalPinRead(B_RESET) && waterLvl > WATER_THRESH){
        state = IDLE;
    }
    else{
        state = currentState;
    }
    return state;
}

void setFan(int speed){
    if(speed){
        digitalPinWrite(FAN, true);
    }
    if(!speed){
        digitalPinWrite(FAN, false);
    }
}

void setStep(int distance){
    stepper.step(distance);
}