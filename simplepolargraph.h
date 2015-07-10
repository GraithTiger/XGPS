// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef simplepolargraph_H_
#define simplepolargraph_H_
#include "Arduino.h"
#include "AllegroStepper.h"

//typedef byte uint8_t;
//add your includes for the project simplepolargraph here

//extern HardwareSerial Serial;

//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
#ifdef __cplusplus
} // extern "C"
#endif

//add your function definitions for the project simplepolargraph here

void enable();
void disable();
void stepperTest(AllegroStepper mot, int numSteps, byte direction);
void stepperTest(int numSteps, byte direction);


//Do not add code below this line
#endif /* simplepolargraph_H_ */
