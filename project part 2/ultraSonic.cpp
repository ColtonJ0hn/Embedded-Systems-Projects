/*--------------------------------------------------------------------
Name:   <Colton Johnson>
Date:   <03/02/2022>
Course: CSCE 336 Embedded Systems (Spring 2022)
File:   ultraSonic.cpp
HW/Lab: Lab 3

Purp: This is an implemenation file that hold functions that are to be used with lab 3, or for the project. 

Doc:  <Falkinburg and his slides, as well as some external sources.>

Academic Integrity Statement: I certify that, while others may have
assisted me in brain storming, debugging and validating this program,
the program itself is my own work. I understand that submitting code
which is the work of other individuals is a violation of the honor
code.  I also understand that if I knowingly give my original work to
another individual is also a violation of the honor code.
--------------------------------------------------------------------*/

#include <Arduino.h>

#define sensorEcho PINB0
#define sensorTrigger PIND7
#define BLUE_LED PINB1
#define RED_LED PINB3
#define GREEN_LED PINB2


void servoRotate()
{
  _delay_ms(500);
  OCR0B = 36;
  _delay_ms(500);
  OCR0B = 20;
  _delay_ms(500);
  OCR0B = 5;
  _delay_ms(500);
  OCR0B = 20;
}

void sensorRight() {
    _delay_ms(500);
  OCR0B = 5;
  _delay_ms(500);
}

void sensorLeft() {
    _delay_ms(500);
  OCR0B = 36;
  _delay_ms(500);
}

double ultraSonic()  //reads the ultra sonic sensor and returns the value of how far away a wall is infront of the sensor.
{
  double distance;
  PORTD |= (1 << sensorTrigger);
  _delay_us(10);
  PORTD &= ~(1 << sensorTrigger);
  while (!(PINB & (1 << sensorEcho)))
  {
  }
  TCNT1 = 0;
  ICR1 = 0;
  _delay_ms(50);
  double time = double(ICR1) * double(64) * double(double(1)/double(16000000)) * 1000000;
  distance = time / double(148);
  return distance;
}



void ultraSonicLED() //Using ultraSonic(), if object is within 6 inches, light up independent LED.
{
double distance;
  _delay_ms(500);
  OCR0B = 36;
  _delay_ms(500);
distance = ultraSonic();
Serial.println(distance);
if(distance < 6.0) {
PORTB |= (1 << BLUE_LED);
delay(500);
PORTB &= ~(1 << BLUE_LED);
}

  _delay_ms(500);
  OCR0B = 20;
  _delay_ms(500);
distance = ultraSonic();
Serial.println(distance);
if(distance < 6.0) {
PORTB |= (1 << RED_LED);
delay(500);
PORTB &= ~(1 << RED_LED);
}
  _delay_ms(500);
  OCR0B = 5;
  _delay_ms(500);
  distance = ultraSonic();
  Serial.println(distance);
if(distance < 6.0) {
PORTB |= (1 << GREEN_LED);
delay(500);
PORTB &= ~(1 << GREEN_LED);
}
}