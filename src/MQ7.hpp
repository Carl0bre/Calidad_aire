#pragma once

MQ7 mq7(35,5.0);

double monox;

void CO()
{  
    monox = roundf(mq7.getPPM());
    
    Serial.print(F("CO(ppm) ...: ")); Serial.print(monox); Serial.println(F(" ppm"));  
}