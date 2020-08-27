#include <SPI.h>
#include <SD.h>
#include <RtcDS3231.h>
#include<arduino.h>
#include<Wire.h>

#define __SDCONTROL 1


#define CS_PIN 4 //change the pin correctly


void SDInit();
int storeDataToSD(uint8_t *temperaturePtr, RtcDateTime now);


