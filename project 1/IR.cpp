/*--------------------------------------------------------------------
Name:   Jeffrey Falkinburg
Date:   24 Mar 19  
Course: CSCE 336 Embedded Systems (Spring 2022) 
File:   test.ino
HW/Lab: Lab 5/Project 2, Measure IR Pulses

Purp: Uses counters and interrupts to measure IR Pulses for a 
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

#define SAMPLE_SIZE    34
#define IR_DECODER_PIN    (PIND & (1 << PIND2)) // (i.e. Digital Pin 2)
#define IR_PIN    (PIND2)
#define   TRUE        1
#define   FALSE       0

volatile uint8_t  newIrPacket = FALSE;
uint16_t time1[SAMPLE_SIZE], time0[SAMPLE_SIZE];
uint8_t  i;

/*
 * main loop
 */
void loop() {
  
    Serial.println("Waiting for IR input");

    while(IR_DECODER_PIN != 0); // IR input is nominally logic 1
    TCNT1 = 0;                  // reset timer  
    newIrPacket = FALSE;
	//write line of code		// Clear Timer/Counter1, Output Compare A Match Flag by writing 1 
	//write line of code		// Enable interrupt on match with OCR1A

    for(i=0; i<SAMPLE_SIZE; i++) {

      TCNT1 = 0;                  // reset timer and 
      while(IR_DECODER_PIN==0 && newIrPacket == FALSE);   // wait while IR is logic 0
      time0[i] = TCNT1;           // and store timer 1 count 

      TCNT1 = 0;                  // reset timer and
      while(IR_DECODER_PIN != 0 && newIrPacket == FALSE); // wait while IR is logic 1
      time1[i] = TCNT1;           // and store timer 1 count 

    } // end for

    Serial.println("Time Logic 1");
    for(i=0; i<SAMPLE_SIZE; i++) {
        Serial.print("time1["); Serial.print(i,DEC); Serial.print("] = ");Serial.println(time1[i],DEC);
    }        
    Serial.println("Time Logic 0");
    for(i=0; i<SAMPLE_SIZE; i++) {
        Serial.print("time0["); Serial.print(i,DEC); Serial.print("] = ");Serial.println(time0[i],DEC);
    }        
} // end main loop


// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void setup() {
  /* Turn off WDT */ 
  WDTCSR = 0x00; 
  
  Serial.begin(9600);
  Serial.println("Starting up.");

  //Init Timer 1
  TCCR1A = 0x0;
  TCCR1B = 0x0;
  TCCR1A = (1<<WGM12);
  TCCR1B = (1<<CS11) | (1<<CS10);
  //write line of code      /* Reset TCCR1A & TCCR1B to defaults  DONE */  
  //write line of code	   	/* Set Timer 1 to CTC with OCR1A as top  DONE */
  //write line of code	    /* Set clock prescaler to clk/64   DONE */
  /* Configure OCR1A (the counter top) to generate an interrupt every 65ms.  DONE */
  OCR1A = 16250; 
  TCCR1C = 0x0;
  //write line of code     	/* Clear timer 1 counter register high byte first*  DONE?/
  //write line of code 

  /* Configure IR input on Port D, Pin 2 using registers and (1 << IR_PIN) value */
  DDRD &= ~(1 << IR_PIN);
  PORTD |= (1 << IR_PIN);

  //write line of code		/* Input IR on Port D, Pin 2  DONE */
  //write line of code		/* Enable Pullup on Port D, Pin 2   DONE */

} // end setup

/**
 * This function is called whenever the timer 1 output compare match OCR1A
 * is generated.
 **/
ISR(TIMER1_COMPA_vect){
	//write line of code	// Disable interrupt on match with OCR1A
  newIrPacket = TRUE;
}