/*
 * AllegroStepper.cpp
 *
 *  Created on: Jul 9, 2015
 *      Author: Jacob
 */

#include "AllegroStepper.h"
#include <Arduino.h>


AllegroStepper::AllegroStepper(byte step_Pin, byte dir_Pin, byte enable_Pin) {
	// TODO Auto-generated constructor stub
	stepPin = step_Pin;
	dirPin = dir_Pin;
	enablePin = enable_Pin;
}

void AllegroStepper::initialize()
{
	pinMode(stepPin,OUTPUT);
	pinMode(dirPin,OUTPUT);
	pinMode(enablePin,OUTPUT);
	disable();
	digitalWrite(stepPin, LOW); //actively keep step pin low
}

void AllegroStepper::enable()
{
	digitalWrite(enablePin,LOW);
	enabled = true;
}

void AllegroStepper::disable()
{
	digitalWrite(enablePin,HIGH);
	enabled = false;
}

void AllegroStepper::step(byte dir)
{
	if (!enabled)
		enable();
	digitalWrite(dirPin,dir);
	digitalWrite(stepPin,HIGH);
	delayMicroseconds(2);
	digitalWrite(stepPin,LOW);
}
