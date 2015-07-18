// Do not remove the include below
#include "simplepolargraph.h"
#include "pins.h"
#include <HardwareSerial.h>
#include "AllegroStepper.h"
#include "Geometry.h"

//set origin positions
float aPos=300;
float bPos=300;
//initialize stepper motor object
AllegroStepper a = AllegroStepper(A_STEP_PIN,A_DIR_PIN,A_ENABLE_PIN);
AllegroStepper b = AllegroStepper(B_STEP_PIN,B_DIR_PIN,B_ENABLE_PIN);
Geometry pos = Geometry(&a, &b);

//The setup function is called once at startup of the sketch
void setup()
{
// initialization commands
	Serial.begin(9600);
	a.initialize();
	b.initialize();
	pos.setOrigin(914.4,914.4);
}

void loop()
{
	char in;
	//execute commands if available
	if (Serial.available()>0)
	{
		 in = Serial.read();
		 //TODO: Add GCODE PARSER
		 switch (in) //TEST COMMANDS
		 {
		 	 case 'q':
		 		 a.disable();
		 		 b.disable();
		 		 break;
		 	 case 'e':
		 		 a.enable();
		 		 b.enable();
		 		 break;
		 	 case 'w':
		 		 pos.gotoPos(pos.getX(),pos.getY()+20,100);
		 		 Serial.print((double)pos.getX());
		 		 Serial.print(',');
		 		 Serial.println((double)pos.getY());
		 		 break;
		 	 case 'a':
		 		 pos.gotoPos(pos.getX()-20,pos.getY(),100);
		 		 Serial.print((double)pos.getX());
		 		 Serial.print(',');
		 		 Serial.println((double)pos.getY());
		 		 break;
		 	 case 's':
		 		 pos.gotoPos(pos.getX(),pos.getY()-20,100);
		 		 Serial.print((double)pos.getX());
		 		 Serial.print(',');
		 		 Serial.println((double)pos.getY());
		 		 break;
		 	 case 'd':
		 		 pos.gotoPos(pos.getX()+20,pos.getY(),100);
		 		 Serial.print((double)pos.getX());
		 		 Serial.print(',');
		 		 Serial.println((double)pos.getY());
		 		 break;
		 	 case 'p':
		 		 stepperTest(a,800,1);
		 		 stepperTest(a,800,0);
		 		 break;

		 }
	}
//Add your repeated code here

}

void stepperTest(AllegroStepper mot, int numSteps, byte direction)
{
	while (numSteps>0)
	{
		mot.step(direction);//step
		delayMicroseconds(1250);//wait for next step
		numSteps--;//decrease steps remaining
	}
}

void stepperTest(int numSteps, byte direction)
{
	while (numSteps>0)
	{
		a.step(direction);
		b.step(!direction);
		delayMicroseconds(1250);
		numSteps--;
	}
}
