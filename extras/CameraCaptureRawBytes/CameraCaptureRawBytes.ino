/*
  OV767X - Camera Capture Raw Bytes

  This sketch reads a frame from the OmniVision OV7675 camera
  and writes the bytes to the Serial port. Use the Procesing
  sketch in the extras folder to visualize the camera output.

  This example code is in the public domain.
*/

#include <Arduino_OV767X.h>

int bytesPerFrame;

byte data[176 * 144 * 2]; // QVGA: 320x240 X 2 bytes per pixel (RGB565)

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!Camera.begin(QVGA, RGB565, 1, OV7675)) {
    Serial.println("Failed to initialize camera!");
    while (1);
  }

  bytesPerFrame = Camera.width() * Camera.height() * Camera.bytesPerPixel();

  // Optionally, enable the test pattern for testing
  // Camera.testPattern();
}

void loop() {
  Camera.readFrame(data);

  Serial.write(data, bytesPerFrame);
}
