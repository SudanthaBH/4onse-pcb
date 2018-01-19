#ifndef SERVICE_H
#define SERVICE_H

#include <sim800.h>
#include "Settings.h"
#include "Log.h"
#include "Clocks.h"

// SIM800
extern Sim800 server ;

void ServiceBegin();
uint8_t executeRequest(double* externalHum,
    double *externalTemp,
    double *internalTemp,
    double *light_intensity,
    double *windSpeed,
    double *windDirection,
    double *rainFall,
    double *pressure,
    double *soilMoisture,
    double *waterlevel,
    double *altitude,
    double *battry,
    int type,
    String& TimeStamp,
    String& Guid);

uint8_t executePostRequest(char server[],char url[],String &data);
int readRSSI();

DateTime ntpUpdate();

#endif
