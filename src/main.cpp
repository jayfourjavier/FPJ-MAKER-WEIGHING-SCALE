#include <Arduino.h>
#include "HX711.h"

#define DOUT  4
#define CLK  5

HX711 scale;

void setup() {
  Serial.begin(115200);
  scale.begin(DOUT, CLK);
  scale.set_scale(23.0);  // Set the calibration factor you just calculated
  Serial.println("Ready to weigh! Type 'TARE' to tare the scale.");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readString();  // Read input from serial monitor
    input.trim();  // Remove any leading or trailing whitespace

    // If the input is "TARE", tare the scale
    if (input == "TARE") {
      scale.tare();  // Reset the scale to zero
      Serial.println("TARED");
    }
    // If the input is "WEIGHT", display the current weight
    else if (input == "WEIGHT") {
      float weight = scale.get_units(20); // Get the average weight (20 samples)
      Serial.printf("WT, %.2f\n", weight);  // Display weight with 2 decimal places
    }
    // If the input is neither "TARE" nor "WEIGHT", prompt the user
    else {
      Serial.println("Invalid input. Type 'TARE' to tare or 'WEIGHT' to get the weight.");
    }
  }
}
