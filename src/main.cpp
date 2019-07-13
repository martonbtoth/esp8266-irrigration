#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESP8266mDNS.h>
#include "request_handlers.hpp"

AsyncWebServer server(80);

const char* ssid = "Ciclak";
const char* password = "wifijelszo";

void setup() {
  Serial.begin(9600);
  delay(10);

  Serial.printf("Starting up");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.printf("WiFi Failed!\n");
        return;
    }

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

  if (!MDNS.begin("esp8266")) {
    Serial.println("Error setting up MDNS responder!");
  }
  Serial.println("mDNS responder started");

  registerHandlers(server);

  server.begin();
}

void loop() {
}