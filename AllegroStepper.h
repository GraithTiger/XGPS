/*
 * AllegroStepper.h
 *
 *  Created on: Jul 9, 2015
 *      Author: Jacob
 */

#ifndef ALLEGROSTEPPER_H_
#define ALLEGROSTEPPER_H_
#include <Arduino.h>

//Defining constants
#define CW 1
#define CCW 0

class AllegroStepper {
private:
	byte stepPin, dirPin, enablePin;
	bool enabled;
public:
	AllegroStepper(byte step_Pin, byte dir_Pin, byte enable_Pin);
	void initialize();
	void enable();
	void step(byte dir);
	void disable();
};


#endif /* ALLEGROSTEPPER_H_ */
