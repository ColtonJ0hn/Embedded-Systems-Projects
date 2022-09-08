/*--------------------------------------------------------------------
Name:   <Colton Johnson>
Date:   <03/28/2022>
Course: CSCE 336 Embedded Systems (Spring 2022)
File:   README.txt
HW/Lab: Project 1

Purp: This is a text file that contains information about my functions for the project.

Doc:  <Falkinburg and his slides, as well as some external sources.>

Academic Integrity Statement: I certify that, while others may have
assisted me in brain storming, debugging and validating this program,
the program itself is my own work. I understand that submitting code
which is the work of other individuals is a violation of the honor
code.  I also understand that if I knowingly give my original work to
another individual is also a violation of the honor code.
--------------------------------------------------------------------*/

There are two library files that contain all the functions used in the first stage of the project.
These files being ultraSonic.cpp and motor.cpp. Each of these files have functions that control their
respective parts. 

robotDance() :   
moves the robot forwards for 75ms, backwards for 75ms,
than turns left less than 45 degrees, right less than 45 degrees, 
left more than 90 degrees, and right more than 90 degrees.

motorSetup() : 
sets up registers and outputs needed for my robot to work and receive instructions.

TestFunctionality() :
tests wall following functionality. Is paired up with the ultrasonic sensor to determine
how far away a wall is, and tried to stay within a given range.

ultraSonic() : 
reads the ultra sonic sensor and returns the value of how far away a wall is infront of the sensor.