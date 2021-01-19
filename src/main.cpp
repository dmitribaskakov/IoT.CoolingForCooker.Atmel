#include <Arduino.h>

#include "Temperature.h"
const uint8_t temperature_pin = 2;
Temperature temperature(temperature_pin);
//const int16_t temperature_low = 3840; //30c
//const int16_t temperature_high = 4096; //32c
const int16_t temperature_low = 5120; //40c
const int16_t temperature_high = 5760; //45c
const uint8_t cooler_pin = 6;

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