#include <Arduino.h>
#include "StatusLed.h"

uint32_t timeToStartMainLoop = 0;
#define timeMainLoopMax 25  // время для сна
StatusLed statusLed(13);

void setup() {
    // put your setup code here, to run once:
}

void loop() {
    timeToStartMainLoop = millis();
    statusLed.update();
    // put your main code here, to run repeatedly
    timeToStartMainLoop = millis() - timeToStartMainLoop;
	if (timeToStartMainLoop<timeMainLoopMax) delay(timeMainLoopMax - timeToStartMainLoop);
}