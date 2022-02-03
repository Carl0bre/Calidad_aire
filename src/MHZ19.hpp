#pragma once

#include <MHZ19.h>
#include <Wire.h>

MHZ19 myMHZ19;
int diox;
double temp1;
//void setRange(int range);

void InitMHZ()
{
    myMHZ19.begin(Serial2); 

    Serial.println(F("MHZ19 OK"));
}
void CO2()
{  
        diox = myMHZ19.getCO2();
       
        temp1 = myMHZ19.getTemperature();

   if(myMHZ19.errorCode == RESULT_OK)              // RESULT_OK is an alis for 1. Either can be used to confirm the response was OK.
        {
            Serial.print(F("CO2(ppm) ..: ")); Serial.print(diox);Serial.println(F(" ppm"));
            Serial.print(F("TEMPERATURA: "));Serial.print(temp1);Serial.println(F(" °C"));
        }

        else 
        {
            Serial.println("Failed to recieve CO2 value - Error");
            Serial.print("Response Code: ");
            Serial.println(myMHZ19.errorCode);          // Get the Error Code value
        }  
}
