#pragma once

#include "AHT.hpp"
#include "MHZ19.hpp"
#include "MQ7.hpp"
#include "PMS.hpp"

const IPAddress MQTT_HOST(192, 168, 1, 150);
const int MQTT_PORT = 1883;


AsyncMqttClient mqttClient;

String GetPayloadContent(char* data, size_t len)
{
	String content = "";
	for(size_t i = 0; i < len; i++)
	{
		content.concat(data[i]);
	}
	return content;
}

void SuscribeMqtt()
{
	uint16_t packetIdSub = mqttClient.subscribe("aire/1C", 0);
	Serial.print("Subscribing at QoS 2, packetId: ");
	Serial.println(packetIdSub);
}

void PublishMqtt()
{
	String payload = "";
    

	StaticJsonDocument<128> jsonDoc;
	jsonDoc["CO2"] = diox;
	jsonDoc["CO"] = monox;
	jsonDoc["Part1"] = part1;
	jsonDoc["Part25"] = part25;
	jsonDoc["Part10"] = part10;
	jsonDoc["Humedad"] = humd;
	jsonDoc["Temperatura"] = temp;
	serializeJson(jsonDoc, payload);

	mqttClient.publish("aire/1C", 0, true, (char*)payload.c_str());
}

void OnMqttReceived(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
{
	//Serial.print("Received on ");
	//Serial.print(topic);
	//Serial.print(": ");

	String content = GetPayloadContent(payload, len);

	StaticJsonDocument<200> doc;
	DeserializationError error = deserializeJson(doc, content);
	if(error) return;

	unsigned long data = doc["CO2"];
	//Serial.print("diox:");
	//Serial.println(data);
}