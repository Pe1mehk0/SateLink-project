#include <nRF905.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include <SPI.h>

#define BASE_STATION_ADDR 0xE7E7E7E7

nRF905 transceiver = nRF905();
Adafruit_BMP280 bmp280;


float measurement;

void setup() {
  SPI.begin();
  Serial.begin(9600);
  if(!bmp280.begin(0x76))
  {
    Serial.println("Sensor does not working. Error: 13"); //To do tests easier, in the future it is going to be sent to the gs
  }
  transceiver.begin(SPI, 10000000, 10, NRF905_PIN_UNUSED, 9, 8, 4, 3, 2, NULL, NULL);
  transceiver.setChannel(106);
  transceiver.setPayloadSize(sizeof(float), sizeof(float));
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
  transceiver.write(BASE_STATION_ADDR, &measurement, sizeof(measurement));
  delay(100);
  transceiver.TX(NRF905_NEXTMODE_RX, true);
}

