/*--------------------------------------------------------------------
Name:   Colton Johnson
Date:   24 Apr 22
Course: CSCE 336 Embedded Systems (Spring 2022) 
File:   project2.iso
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
#include "motor.h"

#define SAMPLE_SIZE       34
#define   BIT0            0x00000001
volatile uint32_t irPacket;
volatile uint8_t  newIrPacket = FALSE;
volatile uint16_t packetData[34];
volatile uint8_t  packetIndex = 0;

void setup() {
  Serial.begin(9600);
  Serial.print("Starting up...");
  IR_Decoder_Setup();
  motorSetup();
  sei(); /* Enable Global Interrupts*/
}

/*
 * main loop
 */
void loop() {

for(int i=0; i<34; i++) {


                    // reset timer and
      while(IR_DECODER_PIN==0 && newIrPacket == FALSE);        
      TCNT1 = 0;       
      while(IR_DECODER_PIN != 0 && newIrPacket == FALSE); // wait while IR is logic 1
      if(TCNT1 > averageLogic1Pulse - 75) {
        packetData[i] = 1;
      }
      if( TCNT1 < averageLogic0Pulse + 75) {
        packetData[i] = 0; 
      }
    irPacket = (irPacket << 1) + packetData[i];
    } // end for
	  Serial.println(irPacket, HEX);
    newIrPacket = FALSE; //end if newIrPacket
  
  /* Do something with new IR packet */ 
  if(irPacket == Up_Button){    
    motorLeftFWD();
    motorRightFWD();
    delay(1000);
    motorStopAll();
    Serial.println("Up_Button");
    irPacket = 0;     // Clear irPacket
  } //end if
    if (irPacket == Down_Button){    
    motorLeftBWRD();
    motorRightBWRD();
        delay(1000);
    motorStopAll();
    Serial.println("Down_Button");
    irPacket = 0;     // Clear irPacket
  }
    if (irPacket == Left_Button){    
    motorLeftFWD();
    motorRightBWRD();
        delay(500);
    motorStopAll();
    Serial.println("Left_Button");
    irPacket = 0;     // Clear irPacket
  }
    if (irPacket == Right_Button){    
    motorLeftBWRD();
    motorRightFWD();
        delay(500);
    motorStopAll();
    Serial.println("Right_Button");
    irPacket = 0;     // Clear irPacket
  }
    if (irPacket == VolUp_Button){    
    OCR2A += 75;
    OCR2B += 75;
    Serial.println("Vol+_Button");
    irPacket = 0;     // Clear irPacket
  }
    if (irPacket == VolDown_Button){    
    OCR2A -= 75;
    OCR2B -= 75;
    Serial.println("Vol-_Button");
    irPacket = 0;     // Clear irPacket
  }
}// end loop

// -----------------------------------------------------------------------
// Since the IR decoder is connected to INT0, we want an interrupt
// to occur every time that the pin changes - this will occur on
// a positive edge and a negative edge.
//
// Negative Edge:
// The negative edge is associated with end of the logic 1 half-bit and
// the start of the logic 0 half of the bit.  The timer contains the
// duration of the logic 1 pulse, so we'll pull that out, process it
// and store the bit in the global irPacket variable. Going forward there
// is really nothing interesting that happens in this period, because all
// the logic 0 half-bits have the same period.  So we will turn off
// the timer interrupts and wait for the next (positive) edge on INT0
//
// Positive Edge:
// The positive edge is associated with the end of the logic 0 half-bit
// and the start of the logic 1 half-bit.  There is nothing to do in
// terms of the logic 0 half bit because it does not encode any useful
// information.  On the other hand, we are going into the logic 1 half bit
// and the portion which determines the bit value, the start of the
// packet, or if the timer rolls over, the end of the ir packet.
// Since the duration of this half-bit determines the outcome
// we will turn on the timer and its associated interrupt.
// -----------------------------------------------------------------------

ISR(INT0_vect){

  uint8_t   pin;
  uint16_t  pulseDuration;      // The timer is 16-bits

  if (IR_DECODER_PIN)   pin=1;  else pin=0;

  switch (pin) {          // read the current pin level
    case 0:           // !!!!!!!!!NEGATIVE EDGE!!!!!!!!!!

      pulseDuration = TCNT1;    //**Note** Timer Count register is 16-bits
      packetData[packetIndex++] = pulseDuration;
			TIMSK1 &= ~(1 << 0x1);						//Disable interrupt on match with OCR1A
      LOW_2_HIGH;               // Set up pin INT0 on positive edge

      
      break;

    case 1:             // !!!!!!!!POSITIVE EDGE!!!!!!!!!!!
      TCNT1 = 0x0000;
                 // time measurements are based at time 
                
			OCR1A =	0x0;				// Clear Timer/Counter1, Output Compare A Match Flag by writing 1 
			TIMSK1 |= (1 << 0x1);						// Enable interrupt on match with OCR1A
      HIGH_2_LOW;               // Set up pin INT0 on falling edge
      break;
  } // end switch

} // end pinChange ISR

// -----------------------------------------------------------------------
//            0 half-bit  1 half-bit    TIMER 1 COUNTS    TIMER 1 COUNTS
//  Logic 0   xxx
//  Logic 1
//  Start
//  End
//
// -----------------------------------------------------------------------
/**
 * This function is called whenever the timer 1 output compare match OCR1A
 * is generated.
 **/
ISR(TIMER1_COMPA_vect){
TIMSK1 &= ~(1 << 0x1);					// Disable interrupt on match with OCR1A
packetIndex = 0;
newIrPacket = TRUE;

}