/*--------------------------------------------------------------------
Name:   Colton Johnson
Date:   24 Apr 22
Course: CSCE 336 Embedded Systems (Spring 2022) 
File:   ir_decoder.cpp
HW/Lab: Project 2, Decoding an IR Packet

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
#include <avr/io.h>
#include <Arduino.h>
#include "ir_decoder.h"


// -----------------------------------------------------------------------
// In order to decode IR packets, the Arduino needs to be configured to
// tell time and generate interrupts on positive going edges.  The
// edge sensitivity is used to detect the first incoming IR packet.
// The PinD2 (i.e. INT0) pin change ISR will then toggle the edge sensitivity of
// the interrupt in order to measure the times of the high and low
// pulses arriving from the IR decoder.
//
// Timer 1 must be enabled so that we can tell how long the pulses
// last.  In some degenerate cases, we will need to generate a interrupt
// when the timer rolls over.  This will indicate the end of a packet
// and will be used to alert main that we have a new packet.
// -----------------------------------------------------------------------
void IR_Decoder_Setup() {

  TCCR1A = 0x0;
  TCCR1B = 0x0;
  TCCR1A = (1<<WGM12);
  TCCR1B = (1<<CS11) | (1<<CS10);
  /* Configure OCR1A (the counter top) to generate an interrupt every 65ms. */
  OCR1A = 16250; 
  TCCR1C = 0x0;


  DDRD &= ~(1 << IR_PIN);
  PORTD |= (1 << IR_PIN);


  HIGH_2_LOW;				  /* check the header out.  INT0 edge select has changed */
  EIMSK |= (1 << INT0);       /* Enable External Interrupt Mask 0*/

}