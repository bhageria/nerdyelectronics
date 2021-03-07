#ifndef __WIFI_H_INCLUDED__
#define __WIFI_H_INCLUDED__

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include<arduino.h>

const char* ssid = "xxxxxxx";   //Edit this line and put in your Wifi Name
const char* password = "xxxxxxxxxxxxx";   //Edit this line and put in your Wifi Password

const char* AWS_endpoint = "xxxxxxxxxxxxxxxxxxxxxx.iot.us-east-1.amazonaws.com"; // Edit your AWS Endpoint here

void callback(char* topic, byte* payload, unsigned int length) ;
void setup_wifi();
void reconnect() ;

WiFiClientSecure espClient;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");
PubSubClient client(AWS_endpoint, 8883, callback, espClient);

void callback(char* topic, byte* payload, unsigned int length) 
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  Serial.println(*payload); //print the data received in the inTopic
}

void setup_wifi() 
{
  
  delay(10);
  // We start by connecting to a WiFi network
  espClient.setBufferSizes(512, 512);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  timeClient.begin(); // read about time keeping using NTP https://nerdyelectronics.com/iot/getting-time-from-internet-using-esp8266-ntp/
  timeClient.setTimeOffset(19800);
  while (!timeClient.update()) {
    timeClient.forceUpdate();
  }
  
  espClient.setX509Time(timeClient.getEpochTime());
  
}

void reconnect() 
{
  // Loop until we're reconnected
  while (!client.connected()) 
  {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESPthing")) 
    {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } 
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
  
      char buf[256];
      espClient.getLastSSLError(buf, 256);
      Serial.print("WiFiClientSecure SSL error: ");
      Serial.println(buf);
  
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

#endif
