/*--------------------------------------------------------------------
Name:   <Colton Johnson>
Date:   <03/20/2022>
Course: CSCE 336 Embedded Systems (Spring 2022)
File:   Motor.h
HW/Lab: Project 1

Purp: This is a header file that hold functions that are to used for the project.

Doc:  <Falkinburg and his slides, as well as some external sources.>

Academic Integrity Statement: I certify that, while others may have
assisted me in brain storming, debugging and validating this program,
the program itself is my own work. I understand that submitting code
which is the work of other individuals is a violation of the honor
code.  I also understand that if I knowingly give my original work to
another individual is also a violation of the honor code.
--------------------------------------------------------------------*/
#ifndef motor_FILE
#define motor_FILE

#include <Arduino.h>

void motorSetup();

void robotDance();

void motorStopAll();


void functionalityTest2();

void obstacleAvoidance();

void forwardMotor(int time);

void turnLeft(int time);

void turnRight(int time);

#endif