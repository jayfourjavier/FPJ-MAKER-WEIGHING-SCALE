#include <Arduino.h>
#include "HX711.h"

#define DOUT  4
#define CLK  5

HX711 scale;

void setup() {
  Serial.begin(115200);
  scale.begin(DOUT, CLK);
  scale.set_scale(13.0713333333);  // Set the calibration factor you just calculated
  //scale.set_gain(100);
  Serial.println("Ready to weight! Type 'TARE' to tare the scale.");
}

//WT, 532.13, 1000g
//WT, 1154.57, 2000g
//WT, 1814.65, 3000g
//WT, 2147.70, 4000g
//WT, 2881.00, 5000g, 
//WT, 3509.78, 6000g,

void loop() {
  if (Serial.available()) {
    String input = Serial.readString();  // Read input from serial monitor
    input.trim();  // Remove any leading or trailing whitespace

    if (input == "TARE" || input == "T") {
      scale.tare();  // Reset the scale to zero
      Serial.println("TARED");
    }
    else if (input == "WEIGHT" || input == "W") {
      float raw = scale.get_units(20);
      Serial.printf("WT, %.2f \n", raw);
    }
    // If the input is neither "TARE" nor "WEIGHT", prompt the user
    else {
      Serial.println("Invalid input. Type 'TARE' to tare or 'WEIGHT' to get the weight.");
    }
  }
}