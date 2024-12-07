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

//test macro
#define BLINK {Register::B, 7}


//now we actually run a setup routine
void setup(){
    adc_init();
    initTimer();
    U0init(9600);
    //initialize LEDs because they're ezpz
    digitalPinSetup(LED_R, PinMode::PIN_OUTPUT);
    //time to initialize the RTC module
    digitalPinSetup(SDA, PinMode::PIN_INPUT);
    digitalPinSetup(SCL, PinMode::PIN_INPUT); //in or out? we'll find out!
    //setup RTC
    //RTC.begin();
    DateTime now = DateTime(2024, 12, 12, 0, 0, 0);
    //RTC.adjust(now); //why can it not use a passed in compile stamp >:/

    //dht11.begin();

    //test code
    digitalPinSetup(BLINK, PinMode::PIN_OUTPUT);
}

void loop(){
  /*dht11.update();
  temp_F = dht11.readFahrenheit(); 
  humidity = dht11.readHumidity();*/
  digitalPinWrite(BLINK, true);
  delay(1000);
  digitalPinWrite(BLINK, false);
  delay(1000);
}
