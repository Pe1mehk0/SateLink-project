#include <LoRa.h>
#include <SPI.h>


void setup() 
{
  Serial.begin(9600);
  if (!LoRa.begin(433E6)) 
  {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}
void loop() 
{
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) 
  {
    while (LoRa.available()) 
    {
      Serial.print((float)LoRa.read());
    }
  }
}

