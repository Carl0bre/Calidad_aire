#pragma once

#include <AHT10.h>
#include <Wire.h>

AHT10 myAHT10 (0X38);

double temp,humd;

void InitAHT()
{
	  while (myAHT10.begin() != true)
  {
    Serial.println(F("AHT10 not connected or fail to load calibration coefficient")); //(F()) save string to flash & keeps dynamic memory free
    delay(1000);
  }
  Serial.println(F("AHT10 OK"));
}

void Temperatura()
{
  uint8_t readStatus = 0;

  readStatus = myAHT10.readRawData(); //read 6 bytes from AHT10 over I2C
  
  if (readStatus != AHT10_ERROR)
  {   
    temp = ((int) (myAHT10.readTemperature(AHT10_USE_READ_DATA)*100))/100.0;
    humd = ((int) (myAHT10.readHumidity(AHT10_USE_READ_DATA)*100))/100.0;
    Serial.print(F("Temperature: ")); Serial.print(myAHT10.readTemperature(AHT10_USE_READ_DATA)); Serial.println(F(" +-0.3°C"));
    Serial.print(F("Humidity...: ")); Serial.print(myAHT10.readHumidity(AHT10_USE_READ_DATA));    Serial.println(F(" +-2 %"));
  }
  else
  {
    Serial.print(F("Failed to read - reset: ")); 
    Serial.println(myAHT10.softReset());         //reset 1-success, 0-failed
  }
}