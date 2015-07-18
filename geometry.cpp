/*
 * geometry.cpp
 *
 *  Created on: Jul 15, 2015
 *      Author: Jacob
 */

#include "geometry.h"

Geometry::Geometry(AllegroStepper *aMot, AllegroStepper *bMot) //initialize position system
{
	a_pos=b_pos=x_pos=y_pos=a_orig=b_orig=x_offset=y_offset=0;
	a_mot = aMot;
	b_mot = bMot;
	isHomed = false;
}

//TODO: Automatic homing

void Geometry::setOrigin(float aPos, float bPos) //sets home position to specified position, also allows positioning
{
	a_orig = a_pos = aPos;
	b_orig = b_pos = bPos;
	isHomed = true;
	float* xy = abToxy(a_pos,b_pos,AB_DISTANCE);
	x_pos = xy[0];
	y_pos = xy[1];
	x_offset = y_offset = 0;
	//x_pos = y_pos = 0;
	Serial.print(getRealX());
	Serial.print('#');
	Serial.println(getRealY());
}

bool Geometry::gotoPos(float x, float y, float vel) //go to specified position in millimeters, at specified velocity in mm/s
{
	if (!isHomed) //do nothing if system not homed
		return false;
	//Serial.print(a_pos);
	//Serial.print('-');
	//Serial.println(b_pos);
	float delta_x = x-x_pos;
	float delta_y = y-y_pos;
	float length = sqrt(delta_x*delta_x+delta_y*delta_y); //get length of path in mm
	float* newAB = xyToab(x+x_offset,y+y_offset, AB_DISTANCE);
	float delta_a = newAB[0]-a_pos;
	float delta_b = newAB[1]-b_pos;
	/*if (delta_a>A_MAX_LENGTH)
		delta_a = A_MAX_LENGTH;
	else if (delta_a<A_MIN_LENGTH)
		delta_a = A_MIN_LENGTH;
	else if (delta_b>B_MAX_LENGTH)
		delta_b = B_MAX_LENGTH;
	else if (delta_b<B_MIN_LENGTH)
		delta_b = B_MIN_LENGTH;*/
	int steps_a = delta_a * A_STEPS_PER_MM;
	int steps_b = delta_b * B_STEPS_PER_MM;
	long time = 1000000L*(length/vel);
	//Serial.print(steps_a);
	//Serial.print(':');
	//Serial.print(steps_b);
	//Serial.print(':');
	//Serial.println(time);
	move(steps_a, steps_b, time);
	x_pos = x;
	y_pos = y;
	a_pos = newAB[0];
	b_pos = newAB[1];
	return true;
}

float Geometry::getX() {return x_pos;}
float Geometry::getY() {return y_pos;}
float Geometry::getRealX() {return x_pos+x_offset;}
float Geometry::getRealY() {return y_pos+y_offset;}

void Geometry::move(int aSteps,int bSteps, long us)
{
	bool aDir = aSteps>0;
	bool bDir = bSteps>0;
	aSteps = abs(aSteps);
	bSteps = abs(bSteps);
	long aInt = us/aSteps;
	long bInt = us/bSteps;
	long curTime = micros();
	long nextA = curTime+aInt;
	long nextB = curTime+bInt;
	while(aSteps>0 || bSteps>0)
	{
		curTime = micros();
		if (curTime>nextA && aSteps>0)
		{
			a_mot->step(aDir);
			nextA = curTime+aInt;
			aSteps--;
			//Serial.print("a:");
			//Serial.println(aSteps);
		}
		if (curTime>nextB && bSteps>0)
		{
			b_mot->step(bDir);
			nextB = curTime+aInt;
			bSteps--;
			//Serial.print("b:");
			//Serial.println(bSteps);
		}
	}

}

void Geometry::hold()
{
	a_mot->enable();
	b_mot->enable();
}

float * xyToab(float x, float y, float d) //converts absolute (x,y) coordinates into (a,b) coordinates with (a=0,b=d) being the xy origin, and d being the distance between a and b
{
	float* ab = new float[2];
	ab[0] = sqrt(x*x+y*y);
	ab[1] = sqrt((d-x)*(d-x)+y*y);
	return ab;
}

float* abToxy(float a, float b, float d) //converts (a,b) coordinates into absolute (x,y) coordinates with (a=0,b=d) being the xy origin, and d being the distance between a and b
{
	float* xy = new float[2];
	xy[0] = (a*a-b*b+d*d)/(2*d); // find x
	xy[1] = -a*sqrt(1-pow((a*a-b*b+d*d)/(2*a*d),2)); //find y
	return xy;
}
