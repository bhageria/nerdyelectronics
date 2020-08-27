/*
This project is to do an analysis of the effect on room temperature because of white paint on roof

There will be 3 temperature sensors - 
1) Environment
2) Below the ceiling without white paint
3) Below the ceiling with white paint

All three sensors will be read simultaneously. Expectation is to see the value of sensor below the ehite topping to be less than the other two.

Let's see
*******/

#include"main.h"
String data;

RtcDateTime now;

void setup() 
{
  #ifdef DEBUG
    Serial.begin(9600);
    Serial.println("Serial Test");
  #endif
  
  Rtc.Begin();
  
  #ifdef DEBUG
    Serial.println("After RTC begin");
  #endif
  SDInit();
  
  #ifdef DEBUG
    Serial.println("after SD init");
  #endif
}
 

void loop()
{
  uint8_t temperature[3]={0};
  
  readTemperature(temperature);

  now = Rtc.GetDateTime();
  storeDataToSD(temperature,now);
}

void readTemperature(uint8_t *tempArrPtr)
{
  uint8_t i = 0;
  uint16_t tempData = 0;
  uint8_t temperature = 0;
  const int analogInPin[3] = {A0, A1, A2};

  for(i = 0; i<3; i++)
  {
    tempData = analogRead(analogInPin[i]);
    temperature = ((tempData*5)/1024)*100;
    *(tempArrPtr + i) = temperature;
    #ifdef DEBUG
      Serial.println(temperature);
    #endif
  }
  #ifdef DEBUG
    Serial.println("");
  #endif
 }
