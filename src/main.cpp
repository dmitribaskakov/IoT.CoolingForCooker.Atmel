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
	pinMode(cooler_pin, OUTPUT);
	digitalWrite(cooler_pin, LOW);
	//Serial.begin(Serial_baud_count);
}

void loop() {
    timeToStartMainLoop = millis();
	statusLed.update();		//мигнем светодиодом что контроллер жив
	if (temperature.update()) {
		//temperature.print();
		if (temperature.getMax() > temperature_error) {
			if (temperature.getMax() > temperature_high) {
				digitalWrite(cooler_pin, HIGH);
			} else if (temperature.getMax() < temperature_low) {
				digitalWrite(cooler_pin, LOW);
			};
		};
	};
    timeToStartMainLoop = millis() - timeToStartMainLoop;
	if (timeToStartMainLoop<timeMainLoopMax) delay(timeMainLoopMax - timeToStartMainLoop);
}