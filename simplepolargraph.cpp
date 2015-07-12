// Do not remove the include below
#include "simplepolargraph.h"
#include "pins.h"
#include <HardwareSerial.h>
#include "AllegroStepper.h"

//set origin positions
float aPos=300;
float bPos=300;
//initialize stepper motor object
AllegroStepper a = AllegroStepper(A_STEP_PIN,A_DIR_PIN,A_ENABLE_PIN);
AllegroStepper b = AllegroStepper(B_STEP_PIN,B_DIR_PIN,B_ENABLE_PIN);

//The setup function is called once at startup of the sketch
void setup()
{
// initialization commands
	Serial.begin(9600);
	a.initialize();
	b.initialize();
}

void loop()
{
	char in;
	//execute commands if available
	if (Serial.available())
	{
		 in = Serial.read();
		 //TODO: Add GCODE PARSER
		 switch (in) //TEST COMMANDS
		 {
		 	 case 'd':
		 		 a.disable();
		 		 b.disable();
		 		 break;
		 	 case 'e':
		 		 a.enable();
		 		 b.enable();
		 		 break;
		 	 case 'a':
		 		 stepperTest(a,800,CW); //spin a-axis motor and reverse
				 stepperTest(a,800,CCW);
		 		 break;
		 	 case 'b':
		 		stepperTest(b,800,CW); //spin b-axis motor and reverse
		 		stepperTest(b,800,CCW);
		 		break;
		 	 case 'c':
		 		stepperTest(800,CW); //spin both motors and reverse
		 		stepperTest(800,CCW);
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
