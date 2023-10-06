#include <LoRa.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include <SPI.h>


Adafruit_BMP280 bmp280;


float measurement;

void setup() {
  if(!bmp280.begin(0x76))
  {
    Serial.println("Sensor does not working. Error: 13"); //To do tests easier, in the future it is going to be sent to the gs
  }
  if (!LoRa.begin(433E6)) 
  {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
} 

void loop() {
  for(int i = 0; i < 100; ++i)
  {
    measurement += bmp280.readAltitude();
  }
  measurement /= 100;
  if(isnan(measurement))
  {
    Serial.println("Altitude is not found. Error: 29"); //To do tests easier, in the future it is going to be sent to the gs
    return;
  }
  Serial.println("Altitude: ");
  Serial.println(measurement);
  LoRa.beginPacket();
  LoRa.print(measurement);
  LoRa.endPacket();
}

