#include <Arduino.h>
#include "Temperature.h"
#include "DallasTemperature.h"

Temperature::Temperature(uint8_t TEMPERATURE_PIN){
	temperature_pin = TEMPERATURE_PIN;
	temperature_max = temperature_error;
	oneWire = new OneWire(temperature_pin);
	sensors = new DallasTemperature(oneWire);
	sensors->begin();
	temperature_sensors_count = sensors->getDS18Count();
	device_address = new DeviceAddress [temperature_sensors_count];
	//device_temperature = new float [temperature_sensors_count];
	device_temperature = new int16_t [temperature_sensors_count];
	for (uint8_t i = 0; i < temperature_sensors_count; i++)	{
		sensors->getAddress(device_address[i], i);
	};
	temperature_last_request_time = millis();
};

bool Temperature::update() {
	if ( (millis()>=(temperature_last_request_time + temperature_request_time)) ) {
		sensors->requestTemperatures();
		temperature_max = temperature_error;
		for (uint8_t i = 0; i < temperature_sensors_count; i++)	{
			//device_temperature[i] = sensors->getTempC(device_address[i]);
			device_temperature[i] = sensors->getTemp(device_address[i]);
			if (temperature_max < device_temperature[i]) temperature_max = device_temperature[i];
		};
		temperature_last_request_time = millis();
		return true;
	};
	return false;
};

int16_t Temperature::getMax() {
	return temperature_max;
};

void Temperature::print(){
	for (uint8_t i = 0; i < temperature_sensors_count; i++)	{
		Serial.print("D");
		Serial.print(i);
		Serial.print("-");
		printAddress(device_address[i]);
		Serial.print("=");
		Serial.print(device_temperature[i]);
		Serial.print("  ");
	};
	Serial.println("");
};
void Temperature::printAddress(DeviceAddress deviceAddress) {
	for (uint8_t i = 0; i < 8; i++)	{
		//Serial.print("0x");
		if (deviceAddress[i] < 16) Serial.print("0");
		Serial.print(deviceAddress[i], HEX);
		//if (i !=7) Serial.print(", ");
	};
};
