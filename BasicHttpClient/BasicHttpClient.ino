/**
   BasicHTTPClient.ino

    Created on: 24.05.2015

*/


#include "HX711.h"

#include <Arduino.h>

#include <ESP8266WiFi.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 14;
const int LOADCELL_SCK_PIN = 2;

HX711 scale;


void setup() {

  Serial.begin(38400);

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  scale.set_scale(45.f);
  scale.tare();

//  for (uint8_t t = 4; t > 0; t--) {
//    Serial.printf("[SETUP] WAIT %d...\n", t);
//    Serial.flush();
//    delay(3000);
//  }

  WiFi.begin("ProbeNet", "h3jpasn0vfIJ");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  // wait for WiFi connection
  WiFiClient client;

  HTTPClient http;


  //scale.power_down();             // put the ADC in sleep mode
  //delay(1000);
  //scale.power_up();


  if (http.begin(client, String("http://192.168.1.87:8080/ajout/0/") + scale.get_units(10))) { // HTTP

    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = http.getString();
        Serial.println(payload);
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  } else {
    Serial.printf("[HTTP} Unable to connect\n");
  }


}

void loop() {
}
