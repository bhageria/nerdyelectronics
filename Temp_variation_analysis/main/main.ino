/*
  
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

/******* 
 *  Version Control
 *  25-Feb-2020  Srinivas
 *  -------------------------
 *  main.h
 *  CALLED LoadMotorState in main - setup to power mtr after power cut
 *  CALLED loadLocalMotorState in main - loop to power mtr after power cut
 *  --------------------------
 *  motor_control.h
 *  ADDED eeprom.h to write and read motor sts
 *  ADDED checkMotorState, LoadMotorState, loadLocalMotorState to satisy mtr power state after powercut 
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

