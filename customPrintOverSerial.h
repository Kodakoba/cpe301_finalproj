#ifndef CUSTOM_PRINT_OVER_SERIAL_H
#define CUSTOM_PRINT_OVER_SERIAL_H
#pragma once
//customPrintOverSerial.h - because what the fuck is Serial.print() am i right?
//------
//it is a serial library afterall.
#include "customSerial.h"
#include <RTClib.h> //for a DateTime instance to pass.
char numbers[10] = {'0','1','2','3','4','5','6','7','8','9'};

void DisplayTime(DateTime now){
//date stuff
    int year = now.year();
    int month = now.month();
    int day = now.day();
    int hour = now.hour();
    int minute = now.minute();
    int second = now.second(); 
//more conversion sh!t i kept out of main
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
  U0putchar('M');
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

#endif