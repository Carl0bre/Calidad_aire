#include <WiFi.h>
#include <AsyncMqttClient.h>
#include <ArduinoJson.h>
#include <AHT10.h>
#include <MHZ19.h>
#include <Wire.h>
#include <MQ7.h>
#include <PMserial.h>

#include "config.h"  // Sustituir con datos de vuestra red
#include "MQTT.hpp"
#include "ESP32_Utils.hpp"
#include "ESP32_Utils_MQTT_Async.hpp"
#include "AHT.hpp"
#include "MQ7.hpp"
#include "PMS.hpp"




void setup(void)
{
	Serial.begin(115200);
	Serial1.begin(9600, SERIAL_8N1, 33, 32);
	Serial2.begin(9600);
	
    pinMode(MQTT_LED,OUTPUT);
	pinMode(WIFI_LED,OUTPUT);
	
	delay(500);

	WiFi.onEvent(WiFiEvent);
	InitMqtt();

	ConnectWiFi_STA();
	
	InitAHT();
	InitMHZ();
	InitPMS();
	
}
void loop()
{
	Temperatura();
	CO2();
	CO();
	Particulas();
	
	PublishMqtt();

	delay(2000);
}