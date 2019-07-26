#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>
#include "request_handlers.hpp"
#include "display.hpp"
#include "state.hpp"

AsyncWebServer server(80);

const char* ssid = "Ciclak";
const char* password = "wifijelszo";

void setup() {
  pinMode(valvePin, OUTPUT);

  Serial.begin(9600);
  delay(200);
  Serial.println();
  Serial.println("Starting up");

  Serial.println("Initializing display");
  initDisplay();

  Serial.println("Starting SPIFFS");
  SPIFFS.begin();
  FSInfo fsInfo = FSInfo();
  SPIFFS.info(fsInfo);
  Serial.printf("SPIFFS initialized. Total bytes: %d used bytes: %d\n", fsInfo.totalBytes, fsInfo.usedBytes);

  Serial.println("Starting WiFi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
      Serial.printf("WiFi Failed!\n");
      return;
  }

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  displayData();

  if (!MDNS.begin("esp8266-dev", WiFi.localIP(), 1800)) {
    Serial.println("Error setting up MDNS responder!");
  }
  Serial.println("mDNS responder started");

  registerHandlers(server);
  Serial.println("Registered http handlers");
  digitalWrite(valvePin, HIGH);
  server.begin();
}

void loop() {
  if (state.dirty) {
    state.dirty = false;
    displayData();
  }
  delay(200);
}