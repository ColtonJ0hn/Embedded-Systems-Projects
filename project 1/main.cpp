/*--------------------------------------------------------------------
Name:   <Colton Johnson>
Date:   <03/02/2022>
Course: CSCE 336 Embedded Systems (Spring 2022)
File:   main.cpp
HW/Lab: Lab 3

Purp: This is an implemenation file that is the main file for lab 3, used for testing functions.

Doc:  <Falkinburg and his slides, as well as some external sources.>

Academic Integrity Statement: I certify that, while others may have
assisted me in brain storming, debugging and validating this program,
the program itself is my own work. I understand that submitting code
which is the work of other individuals is a violation of the honor
code.  I also understand that if I knowingly give my original work to
another individual is also a violation of the honor code.
--------------------------------------------------------------------*/

#include <Arduino.h>
#include "ultraSonic.h"
#include "motor.h"
#define servo PIND5
#define sensorEcho PINB0
#define sensorTrigger PIND7

void setup()
{

  Serial.begin(9600);


  DDRD |= (1 << servo);
  DDRB |= ~(1 << sensorEcho);
  DDRD |= (1 << sensorTrigger);
  


  TCCR1A = 0x00;                  //normal mode
  TCCR1B = (1<<CS11) | (1<<CS10); //use clk/64
  TCCR1C = 0x00;                  //no forced compare 
  

  TCCR0A = (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
  TCCR0B = (1 << WGM02) | (1 << CS00) | (1 << CS02);
  OCR0A = 255;
  OCR0B = 0;
  TCNT1 = 57723;

  motorSetup();
}







void loop() {
functionalityTest2();
}