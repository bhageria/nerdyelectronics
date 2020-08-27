
#include"SD_control.h"
#include"config.h"

void SDInit()
{

  #ifdef DEBUG
    while (!Serial); // wait for serial port to connect. Needed for native USB port only
    Serial.println("Initializing SD card...");
  #endif
    // see if the card is present and can be initialized:
  if (!SD.begin(CS_PIN))
  {
    #ifdef DEBUG
      Serial.println("INSIDE SERIAL INIT");
    #endif
    #ifdef DEBUG
      Serial.println("Card failed, or not present");
    #endif
      // don't do anything more:
      while (1);
  }
  else
  {
    #ifdef DEBUG
      Serial.print("SD card initialized...");
    #endif
  }

}


int storeDataToSD(uint8_t *temperaturePtr, RtcDateTime now)
{
  String fileName = "";
  
  fileName = (String(now.Day(), DEC))+'_'+(String(now.Month(), DEC))+'_'+(String(now.Year(), DEC)[2])+(String(now.Year(), DEC)[3])+'.'+"csv"; //create or open a file with the current date as the name

  #ifdef DEBUG
    Serial.println(fileName);
  #endif
  // if the file is available, write to it:
    File dataFile = SD.open(fileName, FILE_WRITE);
    if(dataFile) //print only if the file is open and if the level has changed
    {

      #ifdef DEBUG
        Serial.println("New reading");
        Serial.print("Data = ");
        Serial.println(*temperaturePtr);
        Serial.println("");
      #endif
      dataFile.println("{");
      dataFile.print("\"Date\":");
      dataFile.print("\"");
      dataFile.print(now.Day(), DEC);
      dataFile.print('/');
      dataFile.print(now.Month(), DEC);
      dataFile.print('/');
      dataFile.print(now.Year(), DEC);
      dataFile.print("\"");
      dataFile.println(',');
      dataFile.print("\"Time\":");
      dataFile.print("\"");
      dataFile.print(now.Hour(), DEC);
      dataFile.print('/');
      dataFile.print(now.Minute(), DEC);
      dataFile.print('/');
      dataFile.print(now.Second(), DEC);
      dataFile.print("\"");
      dataFile.println(',');
      dataFile.print("\"Status\":");
      dataFile.println(*data);   
      dataFile.println("}");
      //*previousLevelPTR = *currentLevelPTR;

      
    }
    else {
      #ifdef DEBUG
        Serial.print("error opening ");
        Serial.println("error opening fileName");
      #endif
    }
      dataFile.flush();
      dataFile.close(); // close the file
  
}
