/****************************************************************
 * NodeMCU SPIFFS Tutorial Example
 * 
 * Example program to read file from SPIFFS in ESP8266
 * by https://nerdyelectronics.com
 * 
 * The ESP8266 SPIFFS File System – Complete Beginner Guide:
 * https://nerdyelectronics.com/iot/esp8266/esp8266-spiffs-file-system/
 * 
 * Upload Files to ESP8266 SPIFFS:
 * https://nerdyelectronics.com/iot/esp8266/upload-files-to-esp8266-spiffs/
 * 
 ***************************************************************/

#include "FS.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  if (!SPIFFS.begin()) //mount the file system
  {
    Serial.println("Failed to mount file system");
    return;
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  

  File configurations = SPIFFS.open("/config.txt", "r"); //open the config file
  if (!configurations) 
  {
    Serial.println("Failed to open config file");
    
  }
  else
  {
    Serial.println("Successfully opened config file");
    Serial.print("File size = ");
    Serial.println(configurations.size());  //read the file size here
    while (configurations.available())
    {
      Serial.write(configurations.read());
    }
    Serial.println("");
  }
  configurations.close();
  delay(5000);
}
