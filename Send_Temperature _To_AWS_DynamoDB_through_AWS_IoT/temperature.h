#include<arduino.h>

float readTemperatureInC();
int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
float temperatureInC = 0;
int i = 0;

/*Read the LM35 temperature sensor in NodeMCU*/
float readTemperatureInC() 
{
  sensorValue = analogRead(sensorPin);
    temperatureInC = ((3.3/1024.0)*sensorValue)*100;  //nodeMCU ADC reference voltage is 3.3v
  for(i=0;i<10;i++) //take average of ten readings
  {
    sensorValue = analogRead(sensorPin);
    temperatureInC = (temperatureInC + ((3.3/1024.0)*sensorValue)*100)/2;
  }
  return temperatureInC;
}
