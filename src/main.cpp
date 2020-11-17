#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "login.hpp";

const int oneWireBus = 4;
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);
WiFiServer server(80);

void setup()
{
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  int counter = 0;
  while (WiFi.status() != WL_CONNECTED && counter < 10)
  {
    delay(500);
    counter++;
    Serial.print(".");
  }
  if(WiFi.status() != WL_CONNECTED){
    ESP.restart();
  }
  sensors.begin();
  server.begin();
}

void loop()
{
  server.
  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0);
  Serial.print(temperature);
  Serial.println("ºC");
  delay(5000);
}