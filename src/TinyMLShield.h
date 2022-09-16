#include "Arduino_OV767X_TinyMLx.h"
#define BUTTON_PIN 13

// Custom shield button pin setting
void nrf_gpio_cfg_out_with_input(uint32_t pin_number) {
  nrf_gpio_cfg(
    pin_number,
    NRF_GPIO_PIN_DIR_OUTPUT,
    NRF_GPIO_PIN_INPUT_CONNECT,
    NRF_GPIO_PIN_PULLUP,
    NRF_GPIO_PIN_S0S1,
    NRF_GPIO_PIN_NOSENSE);
}

// Variables for button debouncing
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
bool lastButtonState = HIGH;
bool buttonState;

// set the pin modes for the button
void initializeShield(){
  pinMode(BUTTON_PIN, OUTPUT);
  digitalWrite(BUTTON_PIN, HIGH);
  nrf_gpio_cfg_out_with_input(digitalPinToPinName(BUTTON_PIN));
}

// debounce the button and return true on new click
bool readShieldButton(){
  bool buttonRead = nrf_gpio_pin_read(digitalPinToPinName(BUTTON_PIN));
  
  if (buttonRead != lastButtonState) {
    lastDebounceTime = millis();
  }

  if (millis() - lastDebounceTime >= debounceDelay) {
    if (buttonRead != buttonState) {
      buttonState = buttonRead;

      if (!buttonState) {
        lastButtonState = buttonRead;
        return true;
      }
    }
  }

  lastButtonState = buttonRead;
  return false;
}