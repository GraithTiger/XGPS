// Do not remove the include below
#include "simplepolargraph.h"
#include "pins.h"
#include <HardwareSerial.h>
#include "AllegroStepper.h"

float aPos=300;
float bPos=300;
AllegroStepper a = AllegroStepper(A_STEP_PIN,A_DIR_PIN,A_ENABLE_PIN);
AllegroStepper b = AllegroStepper(B_STEP_PIN,B_DIR_PIN,B_ENABLE_PIN);

//The setup function is called once at startup of the sketch
void setup()
{
// Add your initialization code here
	Serial.begin(9600);
	a.initialize();
	b.initialize();
}

// The loop function is called in an endless loop
void loop()
{
	char in;
	if (Serial.available())
	{
		 in = Serial.read();
		 switch (in)
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
		 		 stepperTest(a,800,CW);
				 stepperTest(a,800,CCW);
		 		 break;
		 	 case 'b':
		 		stepperTest(b,800,CW);
		 		stepperTest(b,800,CCW);
		 		break;
		 	 case 'c':
		 		stepperTest(800,CW);
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
		mot.step(direction);
		delay(5);
		numSteps--;
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
