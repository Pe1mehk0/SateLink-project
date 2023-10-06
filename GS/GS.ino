#include <nRF905.h>
#include <SPI.h>

#define BASE_STATION_ADDR	0xE7E7E7E7

float receivedData;
nRF905 reciever = nRF905();

void setup() {
  Serial.begin(9600);
  reciever.begin(SPI, 10000000, 6, NRF905_PIN_UNUSED, NRF905_PIN_UNUSED, 8, NRF905_PIN_UNUSED, NRF905_PIN_UNUSED, NRF905_PIN_UNUSED, NULL, NULL);
  reciever.setChannel(106);
}
void loop() {
  Serial.println(receivedData);
  if(reciever.receiveBusy())
  {
    reciever.read(&receivedData, sizeof(receivedData));
  }
  else
  {
    Serial.println("Packets are not accepted");
  }
  Serial.println(receivedData);
}
