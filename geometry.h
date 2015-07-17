/*
 * config.h
 *
 *  Created on: Jul 9, 2015
 *      Author: Jacob
 */

#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include "AllegroStepper.h"

#define CABLE				1
#define CARTESIAN			0

#define TWO_AXIS			0
#define THREE_AXIS			1

#define A_STEPS_PER_MM		-8.488263
#define B_STEPS_PER_MM		-8.488263

#define AB_DISTANCE			1220

#define A_MIN_LENGTH		250
#define B_MIN_LENGTH		250
#define A_MAX_LENGTH		965
#define B_MAX_LENGTH		965

class Geometry{
	public:
		Geometry(AllegroStepper *aMot, AllegroStepper *bMot);
		void setOrigin(float aPos,float bPos);
		bool gotoPos(float x,float y,float vel);
		void hold();
		void move(int aSteps, int bSteps, long us);
		float getX();
		float getY();
		float getRealX();
		float getRealY();
	private:
		float a_orig, b_orig, a_pos, b_pos, x_pos, y_pos, x_offset, y_offset;
		AllegroStepper * a_mot;
		AllegroStepper * b_mot;
		bool isHomed;
};

float* xyToab(float x, float y, float d);
float* abToxy(float x, float b, float d);


#endif /* GEOMETRY_H_ */
