/*
 * AllegroStepper.cpp
 *
 *  Created on: Jul 9, 2015
 *      Author: Jacob
 */

#include "AllegroStepper.h"
#include <Arduino.h>

//Constructor: Set up pins
AllegroStepper::AllegroStepper(byte step_Pin, byte dir_Pin, byte enable_Pin) {
	stepPin = step_Pin;
	dirPin = dir_Pin;
	enablePin = enable_Pin;
}

//Initialize: set up pins for output
void AllegroStepper::initialize()
{
	pinMode(stepPin,OUTPUT);
	pinMode(dirPin,OUTPUT);
	pinMode(enablePin,OUTPUT);
	disable(); //start with motors disabled
	digitalWrite(stepPin, LOW); //actively keep step pin low
}

void AllegroStepper::enable() //enables stepper motor drive. Keeps enable pin low.
{
	digitalWrite(enablePin,LOW);
	enabled = true;
}

void AllegroStepper::disable() //disables stepper motor drive. Keeps enable pin high.
{
	digitalWrite(enablePin,HIGH);
	enabled = false;
}

void AllegroStepper::step(byte dir) //Executes a single step
{
	if (!enabled) //check if driver is enabled, and keep
		enable();
	digitalWrite(dirPin,dir); //set direction
	digitalWrite(stepPin,HIGH); //execute step
	delayMicroseconds(5); //wait before
	digitalWrite(stepPin,LOW); //put step pin low
}
