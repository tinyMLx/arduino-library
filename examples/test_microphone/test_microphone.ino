/*
  Active Learning Labs
  Harvard University 
  tinyMLx - Built-in Microphone Test
*/

#include <PDM.h>
#include <TinyMLShield.h>

// PDM buffer
short sampleBuffer[256];
volatile int samplesRead;

bool record = false;
bool commandRecv = false;

void setup() {
  Serial.begin(9600);
  while (!Serial);  

  // Initialize the TinyML Shield
  initializeShield();

  PDM.onReceive(onPDMdata);
  // Initialize PDM microphone in mono mode with 16 kHz sample rate
  if (!PDM.begin(1, 16000)) {
    Serial.println("Failed to start PDM");
    while (1);
  }

  Serial.println("Welcome to the microphone test for the built-in microphone on the Nano 33 BLE Sense\n");
  Serial.println("Use the on-shield button or send the command 'click' to start and stop an audio recording");
  Serial.println("Open the Serial Plotter to view the corresponding waveform");
}

void loop() {
  // see if the button is pressed and turn off or on recording accordingly
  bool clicked = readShieldButton();
  if (clicked){
    record = !record;
  }
  
  // see if a command was sent over the serial monitor and record it if so
  String command;
  while (Serial.available()) {
    char c = Serial.read();
    if ((c != '\n') && (c != '\r')) {
      command.concat(c);
    } 
    else if (c == '\r') {
      commandRecv = true;
      command.toLowerCase();
    }
  }

  // parse the command if applicable
  if (commandRecv && command == "click") {
    commandRecv = false;
    record = !record;
  }

  // display the audio if applicable
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
