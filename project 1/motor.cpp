/*--------------------------------------------------------------------
Name:   <Colton Johnson>
Date:   <03/20/2022>
Course: CSCE 336 Embedded Systems (Spring 2022)
File:   Motor.cpp
HW/Lab: Project 1

Purp: This is an implemenation file that hold functions that are to used for the project. 

Doc:  <Falkinburg and his slides, as well as some external sources.>

Academic Integrity Statement: I certify that, while others may have
assisted me in brain storming, debugging and validating this program,
the program itself is my own work. I understand that submitting code
which is the work of other individuals is a violation of the honor
code.  I also understand that if I knowingly give my original work to
another individual is also a violation of the honor code.
--------------------------------------------------------------------*/
#include <arduino.h>
#include "ultraSonic.h"
#define motorLeftPWM PINB3
#define motorLeftBack PINB2
#define motorLeftForward PINB1
<<<<<<< HEAD
#define motorRightBack PIND6
=======
#define motorRightBack PIND2
>>>>>>> 855ecf72d88e2eeb916c96b7c95d2733a5ec2541
#define motorRightForward PIND4
#define motorRightPWM PIND3

void motorLeftFWD()
{
    PORTB = 1 << motorLeftForward;
}
void motorLeftBWRD()
{
    PORTB = 1 << motorLeftBack;
}
void motorRightFWD()
{
    PORTD = 1 << motorRightForward;
}
void motorRightBWRD()
{
    PORTD = 1 << motorRightBack;
}
void motorStopAll()
{
    PORTD &= ~(1 << motorRightForward);
    PORTD &= ~(1 << motorRightBack);
    PORTB &= ~(1 << motorLeftBack);
    PORTB &= ~(1 << motorLeftForward);
}
/* sets up reigsters and outputs needed for my robot to work and receive instructions.
*/
void motorSetup()
{
    DDRB |= (1 << motorLeftPWM);
    DDRB |= (1 << motorLeftBack);
    DDRB |= (1 << motorLeftForward);
    PORTB &= ~(1 << motorLeftPWM);
    PORTB &= ~(1 << motorLeftBack);
    PORTB &= ~(1 << motorLeftForward);
    DDRD |= (1 << motorRightPWM);
    DDRD |= (1 << motorRightBack);
    DDRD |= (1 << motorRightForward);
    PORTD &= ~(1 << motorRightPWM);
    PORTD &= ~(1 << motorRightForward);
    PORTD &= ~(1 << motorRightBack);

    TCCR2A = 1 << COM2A1 | 1 << COM2B1 | 1 << WGM21 | 1 << WGM20;
    TCCR2B = 1 << CS22;
    OCR2A = 255;
    OCR2B = 255;

}
/*
moves the robot forwards for 75ms, backwards for 75ms,
 than turns left less than 45 degrees, right less than 45 degrees, 
 left more than 90 degrees, and right more than 90 degrees.
 */
void robotDance()  
{
    delay(200);
    OCR2B = 255;
    motorLeftFWD();
    motorRightFWD();
    delay(75);
    OCR2B = 255;
    delay(10);
    motorLeftBWRD();
    motorRightBWRD();
    delay(75);
    motorStopAll();
    delay(50);
    motorRightFWD();
    delay(13);
    motorStopAll();
    delay(75);
    motorRightBWRD();
    motorLeftFWD();
    delay(10);
    motorStopAll();
    delay(100);
    motorRightFWD();
    delay(25);
    motorStopAll();
    delay(75);
    motorRightBWRD();
    motorLeftFWD();
    delay(20);
    motorStopAll();
}

/* tests wall following functionality. Is paired up with the ultrasonic sensor to determine
how far away a wall is, and tried to stay within a given range.
*/
void functionalityTest2()
{
   double distance = ultraSonic();
        OCR2B = 155;
        OCR2A = 147;
        motorRightFWD();
        motorLeftFWD();
        if ((distance > 0.1) && (distance < 5.0))
    {
        OCR2B = 200;
        OCR2A = 147;
        _delay_ms(100);
    }
    else if ((distance > 0.1) && (distance > 9.0)) // too close increase close one   too far increase far one
    {
        OCR2A = 200;
        OCR2B = 155;
        _delay_ms(75);
    }
    // too close increase close one   too far increase far one

}
