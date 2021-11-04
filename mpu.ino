#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
/*
 * An Arduino UNO/Nano sketch for the ITG/MPU6050 gyro module.
 * Based from the Adafruit basic reading sketch included in their
 * mpu library.
 */

#define BAUD 115200

uint8_t led = 13;

Adafruit_MPU6050 mpu;
sensors_event_t a, g, temp;

void setup() {
  Serial.begin(BAUD);

  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);

  if (mpu.begin()) {
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G); // 2, 4, 8, 16 G's
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);      // 250, 500, 1000, 2000 rads/s
    mpu.setFilterBandwidth(MPU6050_BAND_10_HZ);   // 5, 10, 21, 44, 94, 184, 260
  }
  else {
    digitalWrie(led, !digitalRead(led));
    delay(50);
  }

  delay(1000);
  digitalWrite(led, !HIGH);
}

void loop() {
  mpu.getEvent(&a, &g, &temp);

  Serial.print(a.acceleration.x);
  Serial.print(a.acceleration.y);
  Serial.println(a.acceleration.z);
}
