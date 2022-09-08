/*--------------------------------------------------------------------
Name:   Colton Johnson
Date:   24 April 22  
Course: CSCE 336 Embedded Systems (Spring 2022) 
File:   ir_decoder.h
HW/Lab: Lab 5/Project 2, Decoding an IR Packet

Purp: Uses counters and interrupts to decode an IR packet for a 
    remote. 

Doc:  <list the names of the people who you helped>
    <list the names of the people who assisted you>

Academic Integrity Statement: I certify that, while others may have 
assisted me in brain storming, debugging and validating this program, 
the program itself is my own work. I understand that submitting code 
which is the work of other individuals is a violation of the honor   
code.  I also understand that if I knowingly give my original work to 
another individual is also a violation of the honor code.
--------------------------------------------------------------------*/
#ifndef ultraSonic_FILE
#define ultraSonic_FILE

#include <Arduino.h>

void servoRotate();

double ultraSonic();

void ultraSonicLED();

void sensorRight();

void sensorLeft();

#endif
