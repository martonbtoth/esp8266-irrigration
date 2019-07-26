#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncTCP.h>

#include "request_handlers.hpp"
#include "state.hpp"
#include "display.hpp"

const char* PARAM_MESSAGE = "message";

void notFound(AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/404.html", "text/html");
}

void registerHandlers(AsyncWebServer& server) {
    server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

    // Send a GET request to <IP>/get?message=<message>
    server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
        String message;
        if (request->hasParam(PARAM_MESSAGE)) {
            message = request->getParam(PARAM_MESSAGE)->value();
        } else {
            message = "No message sent";
        }
        request->send(200, "text/plain", "Hello, GET: " + message);
    });

    server.on("/status", HTTP_GET, [] (AsyncWebServerRequest *request) {
        int status = digitalRead(valvePin);
        if (state.valveOpen) {
            request->send(200, "text/plain", "on");
        } else {
            request->send(200, "text/plain", "off");
        }
    });

    server.on("/on", HTTP_POST, [] (AsyncWebServerRequest *request) {
        digitalWrite(valvePin, LOW);
        state.valveOpen = true;
        state.dirty = true;
        request->send(200, "text/plain", "On yo");
    });

    server.on("/off", HTTP_POST, [] (AsyncWebServerRequest *request) {
        digitalWrite(valvePin, HIGH);
        state.valveOpen = false;
        state.dirty = true;
        request->send(200, "text/plain", "Off yo");
    });

    // Send a POST request to <IP>/post with a form field message set to <message>
    server.on("/post", HTTP_POST, [](AsyncWebServerRequest *request) {
        String message;
        if (request->hasParam(PARAM_MESSAGE, true)) {
            message = request->getParam(PARAM_MESSAGE, true)->value();
        } else {
            message = "No message sent";
        }
        request->send(200, "text/plain", "Hello, POST: " + message);
    });

    server.onNotFound(notFound);

}