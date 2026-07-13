/*
  Arduino Nano 33 BLE Sense
  APDS9960 Color Sensor Example
*/

#include <Arduino_APDS9960.h>

void setup() {
  Serial.begin(9600);

  while (!Serial);

  // Initialize the APDS9960 sensor
  if (!APDS.begin()) {
    Serial.println("Error initializing APDS-9960 sensor!");
    while (1);
  }

  Serial.println("APDS9960 Color Sensor Started");
  Serial.println("-----------------------------");
}

void loop() {

  int r, g, b;

  // Wait until a color reading is available
  if (APDS.colorAvailable()) {

    // Read the RGB values
    APDS.readColor(r, g, b);

    // Print the RGB values
    Serial.print("R = ");
    Serial.println(r);

    Serial.print("G = ");
    Serial.println(g);

    Serial.print("B = ");
    Serial.println(b);

    Serial.println("-----------------------------");
  }

  delay(500);
}