#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "login.hpp"
#include <WebOTA.h>
//https://github.com/scottchiefbaker/ESP-WebOTA

const int oneWireBus = 4;
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);
ESP8266WebServer server(80);

void handleRoot() {
  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0);
  String s = "" + (String) temperature + " C";
  server.send(200, "text/plain", s);
}

void setup()
{
  Serial.begin(9600);
  WiFi.hostname("keller-test-esp");
  WiFi.begin(ssid, password);
  int counter = 0;
  while (WiFi.status() != WL_CONNECTED && counter < 15)
  {
    delay(500);
    counter++;
    Serial.print(".");
  }
  if(WiFi.status() != WL_CONNECTED){
    ESP.restart();
  }
  Serial.println(WiFi.localIP());
  sensors.begin();
  server.on("/",handleRoot);
  server.begin();
}

void loop()
{
  webota.handle();
  server.handleClient();
}