/*
  Active Learning Labs
  Harvard University 
  tinyMLx - Built-in Microphone Test
*/

#include <PDM.h>

#define BUTTON_PIN 13

// PDM buffer
short sampleBuffer[256];
volatile int samplesRead;

// Variables for button debouncing
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
bool lastButtonState = HIGH;
bool buttonState;

bool record = false;

void setup() {
  Serial.begin(9600);
  while (!Serial);  

  pinMode(BUTTON_PIN, OUTPUT);
  digitalWrite(BUTTON_PIN, HIGH);
  nrf_gpio_cfg_out_with_input(digitalPinToPinName(BUTTON_PIN));

  PDM.onReceive(onPDMdata);
  // Initialize PDM microphone in mono mode with 16 kHz sample rate
  if (!PDM.begin(1, 16000)) {
    Serial.println("Failed to start PDM");
    while (1);
  }

  Serial.println("Welcome to the microphone test for the built-in microphone on the Nano 33 BLE Sense\n");
  Serial.println("Use the on-shield button to start and stop an audio recording");
  Serial.println("Open the Serial Plotter to view the corresponding waveform");
}

void loop() {
  bool buttonRead = nrf_gpio_pin_read(digitalPinToPinName(BUTTON_PIN));

  if (buttonRead != lastButtonState) {
    lastDebounceTime = millis();
  }

  if (millis() - lastDebounceTime >= debounceDelay) {
    if (buttonRead != buttonState) {
      buttonState = buttonRead;

      if (!buttonState) {
        record = !record;
      }
    }
  }

  lastButtonState = buttonRead;
  
  if (samplesRead) {

    // print samples to serial plotter
    if (record) {
      for (int i = 0; i < samplesRead; i++) {
        Serial.println(sampleBuffer[i]);
      }
    }

    // clear read count
    samplesRead = 0;
  } 
}

void onPDMdata() {
  // query the number of bytes available
  int bytesAvailable = PDM.available();

  // read data into the sample buffer
  PDM.read(sampleBuffer, bytesAvailable);

  samplesRead = bytesAvailable / 2;
}

void nrf_gpio_cfg_out_with_input(uint32_t pin_number) {
  nrf_gpio_cfg(
    pin_number,
    NRF_GPIO_PIN_DIR_OUTPUT,
    NRF_GPIO_PIN_INPUT_CONNECT,
    NRF_GPIO_PIN_PULLUP,
    NRF_GPIO_PIN_S0S1,
    NRF_GPIO_PIN_NOSENSE);
}
