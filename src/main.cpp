#include <Arduino.h>
#include "HX711.h"

#define DOUT  4
#define CLK   5

HX711 scale;

unsigned long lastWeightSent = 0;
const unsigned long sendInterval = 50;  // 200 milliseconds

void setup() {
  Serial.begin(115200);
  scale.begin(DOUT, CLK);
  scale.set_scale(22.1f);  // Calculate Calibration factor READING 5130.00 WT 5000
  Serial.println("Ready to weight! Type 'TARE' or 'T' to tare the scale.");
}

void loop() {
  // Handle serial input
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');  // Read until newline
    input.trim();
    if (input.equalsIgnoreCase("TARE") || input.equalsIgnoreCase("T")) {
      scale.tare();
      Serial.println("TARED");
    } else if (input.equalsIgnoreCase("WEIGHT") || input.equalsIgnoreCase("W")) {
      float raw = scale.get_units(20);
      Serial.printf("WT, %.2f\n", raw);
    } else {
      Serial.println("Invalid input. Type 'TARE' or 'WEIGHT'.");
    }
  }

  // Periodically send weight
  if (millis() - lastWeightSent >= sendInterval) {
    lastWeightSent = millis();
    float weight = scale.get_units(20);
    Serial.printf("WT, %.2f\n", weight);
  }
}
