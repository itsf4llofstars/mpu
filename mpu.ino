#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
/*
 * An Arduino UNO/Nano sketch for the ITG/MPU6050 gyro module.
 * Based from the Adafruit basic reading sketch included in their
 * mpu library.
 */

#define BAUD 115200
#define PER 500

Adafruit_MPU6050 mpu;
sensors_event_t a, g, temp;

byte led = 13;
bool printAccel = false;

unsigned long int ledClk = millis();

void setup() {
  Serial.begin(BAUD);

  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);

  if (mpu.begin()) {
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G); // 2, 4, 8*, 16* G's
    mpu.setGyroRange(MPU6050_RANGE_2000_DEG);      // 250, 500, 1000, 2000 rads/s
    mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);    // 5*, 10*, 21, 44, 94, 184, 260
  }
  else {
    do {
      digitalWrite(led, !digitalRead(led));
      delay(50);
    } while (true);
  }

  delay(1000);
  digitalWrite(led, !HIGH);
}

void loop() {
  mpu.getEvent(&a, &g, &temp);

  if (printAccel) {
    Serial.print(a.acceleration.x);
    Serial.print(" ");
    Serial.print(a.acceleration.y);
    Serial.print(" ");
    Serial.println(a.acceleration.z);
  }
  else if (!printAccel) {
    Serial.print(g.gyro.x);
    Serial.print(" ");
    Serial.print(g.gyro.y);
    Serial.print(" ");
    Serial.println(g.gyro.z);
  }

  if (millis() - ledClk >= PER) {
    digitalWrite(led, !digitalRead(led));
    ledClk = millis();
  }
}
