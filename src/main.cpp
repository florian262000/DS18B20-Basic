#include <DallasTemperature.h>

const int oneWireBus = 4;     
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  sensors.begin();
}

void loop() {
  sensors.requestTemperatures(); 
  float temperature = sensors.getTempCByIndex(0);
  Serial.print(temperature);
  Serial.println("ºC");
  delay(5000);
}