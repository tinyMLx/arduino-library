/*
  Active Learning Labs
  Harvard University 
  tinyMLx - Sensor Test

  Requires the Arduino_LSM9DS1 library library
*/

#include <Arduino_LSM9DS1.h>

int imuIndex = 0; // 0 - accelerometer, 1 - gyroscope, 2 - magnetometer
bool commandRecv = false; // flag used for indicating receipt of commands from serial port
bool startStream = false;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // Initialize IMU
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU");
    while (1);
  }

  Serial.println("Welcome to the IMU test for the built-in IMU on the Nano 33 BLE Sense\n");
  Serial.println("Available commands:");
  Serial.println("a - display accelerometer readings in g's in x, y, and z directions");
  Serial.println("g - display gyroscope readings in deg/s in x, y, and z directions");
  Serial.println("m - display magnetometer readings in uT in x, y, and z directions");
}

void loop() {
  String command;

  // Read incoming commands from serial monitor
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

  // Command interpretation
  if (commandRecv) {
    commandRecv = false;
    if (command == "a") {
      imuIndex = 0;
      if (!startStream) {
        startStream = true;
      } 
      delay(3000);
    }
    else if (command == "g") {
      imuIndex = 1;
      if (!startStream) {
        startStream = true;
      }
      delay(3000);
    }
    else if (command == "m") {
      imuIndex = 2;
      if (!startStream) {
        startStream = true;
      }
      delay(3000);
    }
  }


  float x, y, z;
  if (startStream) {
    if (imuIndex == 0) { // testing accelerometer
      if (IMU.accelerationAvailable()) {
        IMU.readAcceleration(x, y, z);
  
        Serial.print("Ax:");
        Serial.print(x);
        Serial.print(' ');
        Serial.print("Ay:");
        Serial.print(y);
        Serial.print(' ');
        Serial.print("Az:");
        Serial.println(z);
      }
    }
    else if (imuIndex == 1) { // testing gyroscope
      if (IMU.gyroscopeAvailable()) {
        IMU.readGyroscope(x, y, z);
  
        Serial.print("wx:");
        Serial.print(x);
        Serial.print(' ');
        Serial.print("wy:");
        Serial.print(y);
        Serial.print(' ');
        Serial.print("wz:");
        Serial.println(z);
      }
    }
    else if (imuIndex == 2) { // testing magnetometer
      if (IMU.magneticFieldAvailable()) {
        IMU.readMagneticField(x, y, z);
  
        Serial.print("Bx:");
        Serial.print(x);
        Serial.print(' ');
        Serial.print("By:");
        Serial.print(y);
        Serial.print(' ');
        Serial.print("Bz:");
        Serial.println(z);
      }
    }
  }
}
