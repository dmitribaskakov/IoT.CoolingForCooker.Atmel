#ifndef TEMPERATURE_H_
#define TEMPERATURE_H_

#include <Arduino.h>
#include "DallasTemperature.h"

const uint16_t temperature_request_time = 2000;
const int16_t temperature_error = -32000;

class Temperature {
	public:
	Temperature(uint8_t TEMPERATURE_PIN=2);
	bool update();
	void print();
	void printAddress(DeviceAddress deviceAddress);
	int16_t getMax();
	private:
	OneWire *oneWire;
	DallasTemperature *sensors;
	DeviceAddress *device_address;
	//float *device_temperature;
	int16_t *device_temperature;	// ToCelsius * 0,0078125
	int16_t temperature_max;
	uint8_t temperature_pin;		
	uint8_t temperature_sensors_count;

	uint32_t temperature_last_request_time;		//Время последнего изменения
};

#endif /* STATUS_H_ */
