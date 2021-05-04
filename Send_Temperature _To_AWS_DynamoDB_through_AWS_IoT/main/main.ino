/***************************NerdyElectronics.com******************************

Code to send temperature data to AWS DynamoDB 
The code sends Temperature and timestamp of the reading to AWS IoT
AWS IoT Rule then pushes the data to a table in DynamoDB
Temperature sensor - LM35
*****************************************************************************/
#include "FS.h"
#include "config.h"

#include <string.h>
#include "wifi.h"
#include "temperature.h"


void setup()
{
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  setup_wifi();
  delay(100);
  loadCerts();
}
  
void loop() 
{
  if (!client.connected()) 
  {
    reconnect();
  }
  client.loop();

    formMSGToTransmit();
    client.publish("terraceTemp",data );  
    Serial.print("Heap: "); 
    Serial.println(ESP.getFreeHeap()); //Low heap can cause problems
    memset(data,0,100);
    //ESP.deepSleep(1000e6); 
    //client.disconnect();
    delay(10000);
}

String getDate(unsigned long epochTime)
{
  struct tm *ptm = gmtime ((time_t *)&epochTime); 

  int monthDay = ptm->tm_mday;
  int currentMonth = ptm->tm_mon+1;
  int currentYear = ptm->tm_year+1900;
  String currentDate = String(currentYear) + "-" + String(currentMonth) + "-" + String(monthDay);
  return currentDate;
}

void loadCerts()
{
  int certCount = 0;
  if (!SPIFFS.begin()) 
  {
    Serial.println("Failed to mount file system");
    return;
  }
  
  Serial.print("Heap: "); Serial.println(ESP.getFreeHeap());
  
  // Load certificate file
  File cert = SPIFFS.open("/cert.der", "r"); //replace cert.crt with your uploaded file name
  if (!cert) 
  {
    Serial.println("Failed to open cert file");
  }
  else
    Serial.println("Successfully opened cert file");
  
  delay(100);
  
  if (espClient.loadCertificate(cert)) // add the thing certificate to the client
    Serial.println("cert loaded");
  else
    Serial.println("cert not loaded");
  
  // Load private key file
  File private_key = SPIFFS.open("/private.der", "r"); //replace private with your uploaded file name
  if (!private_key) 
  {
    Serial.println("Failed to open private cert file");
  }
  else
    Serial.println("Successfully opened private cert file");
  
  delay(100);
  
  if (espClient.loadPrivateKey(private_key))  // add the private key to the client
    Serial.println("private key loaded");
  else
    Serial.println("private key not loaded");
  
  // Load CA file
  File ca = SPIFFS.open("/ca.der", "r"); //replace ca with your uploaded file name
  if (!ca) 
  {
    Serial.println("Failed to open ca ");
  }
  else
    Serial.println("Successfully opened open ca");
  
  delay(100);
  
  if (espClient.loadCACert(ca))   // add the AWS root certificate to the client
    Serial.println("ca loaded");
  else
    Serial.println("ca failed");
  
  Serial.print("Heap: "); Serial.println(ESP.getFreeHeap());
}

/* Form the message that should be transmitted*/
void formMSGToTransmit()
{
    String msg;
    
    timeClient.update();
    unsigned long epochTime = timeClient.getEpochTime();
    String formattedTime = timeClient.getFormattedTime();
    String formattedDate = getDate(epochTime);

    msg = "{\"Date\": \"" + formattedDate + "\",\n\"Time\":\"" + formattedTime + "\",\n\"Temperature\":\"";
    msg = msg + String(readTemperatureInC()) + "\"\n}";

    msg.toCharArray(data,100);

    Serial.print("Publish message: ");
    Serial.println(data);
}
