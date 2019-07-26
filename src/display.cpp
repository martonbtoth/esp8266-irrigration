#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>

#include "state.hpp"
#include "display.hpp"
#include <Ticker.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Ticker timer;

unsigned long debounceTimer;

void handleTimerInterrupt() {
    state.displayDimmed = true;
    state.dirty = true;
}

void handleButtonPress() {
    if ((millis() - debounceTimer) < 200) {
        return;
    }
    debounceTimer = millis();
    if (state.displayDimmed) {
        state.displayDimmed = false;
        timer.once(5, handleTimerInterrupt);
    } else {
        state.displayDimmed = true;
    }
    state.dirty = true;
}

void initDisplay() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();

  pinMode(D6, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(D6), handleButtonPress, FALLING);

  delay(2000);

  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(F("Starting up..."));
  display.display();
  timer.once(5, handleTimerInterrupt);
}

void displayData() {
  display.dim(state.displayDimmed);
  display.clearDisplay();

  display.setTextSize(1);             
  display.setTextColor(WHITE);        
  display.setCursor(0,0);             
  display.println(F("Wifi connected."));
  display.println(F("IP Address:\n"));
  display.setTextSize(1, 2);
  display.println(WiFi.localIP());
  display.setTextSize(1);
  display.println();
  display.setTextSize(1, 2);        
  display.printf("State: %s", state.valveOpen ? "on" : "off");

  display.display();
}
