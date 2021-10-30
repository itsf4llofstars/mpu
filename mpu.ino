#include "printMpu.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#define DEBUG
#ifdef DEBUG
#define bug(x) Serial.print(x)
#define bugln(x) Serial.println(x)
#else
#define bug(x)
#define bugln(x)
#endif
/*
 * An Arduino UNO/Nano sketch for the ITG/MPU gyro module. This takes
 * and save data from the x, y, z axis for a set number os milli-seconds.
 * Data collection will begin after a set number of n-length beeps from the
 * speaker module.
 * Each A/D converter needs 100us (1ms is OK) between analog readings. A
 * delay is needed between reading of all analog pins, this delay does not
 * need to be for each individual pin but can be done as a whole as long as
 * you can confirm each analog pin will not be read 2 or more times within
 * 100us.
 */

Adafruit_MPU6050 mpu;

float accelMax = 0;
float rotMax = 0;

uint32_t ledClk = millis();
uint32_t ledPer = 500;


void setup() {
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);

  // Initial Setup print
  bugln("MPU6050 Setup test.");

  // Initialize the MPU6050
  if (!mpu.begin())
    bugln("Failed to find MPU6050.");
  else
    bugln("MPU6050 found");

  // Setup Accelerometer Range
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  bug("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
    case MPU6050_RANGE_2_G:
      bugln("+-2G");
      break;
    case MPU6050_RANGE_4_G:
      bugln("+-4G");
      break;
    case MPU6050_RANGE_8_G:
      bugln("+-8G");
      break;
    case MPU6050_RANGE_16_G:
      bugln("+-16G");
      break;
  }

  bugln("MPU Accelerometer Range set.");

  // Setup Gyro Range
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  bug("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
    case MPU6050_RANGE_250_DEG:
      bugln("+- 250 deg/s");
      break;
    case MPU6050_RANGE_500_DEG:
      bugln("+- 500 deg/s");
      break;
    case MPU6050_RANGE_1000_DEG:
      bugln("+- 1000 deg/s");
      break;
    case MPU6050_RANGE_2000_DEG:
      bugln("+- 2000 deg/s");
      break;
  }

  bugln("MPU Gyro Range set.");

  // Setup Filter Bandwidth
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  bug("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
    case MPU6050_BAND_260_HZ:
      bugln("260 Hz");
      break;
    case MPU6050_BAND_184_HZ:
      bugln("184 Hz");
      break;
    case MPU6050_BAND_94_HZ:
      bugln("94 Hz");
      break;
    case MPU6050_BAND_44_HZ:
      bugln("44 Hz");
      break;
    case MPU6050_BAND_21_HZ:
      bugln("21 Hz");
      break;
    case MPU6050_BAND_10_HZ:
      bugln("10 Hz");
      break;
    case MPU6050_BAND_5_HZ:
      bugln("5 Hz");
      break;
    }

  bugln("MPU Filter Bandwidth set.");

    bugln("Setup Complete.");
    delay(3000);
} // END SETUP

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  if (a.acceleration.z > accelMax) {
    accelMax = a.acceleration.z;
  }

  if (g.gyro.x > rotMax) {
    rotMax = g.gyro.x;
  }

  printAll(a.acceleration.x, a.acceleration.y, a.acceleration.z, g.gyro.x, g.gyro.y, g.gyro.z, temp.temperature);

  delay(10);

  flashLed();
} // END LOOP

void flashLed() {
  if (millis() - ledClk >= ledPer) {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    ledClk = millis();
  }
}
