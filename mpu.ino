/*
 * An Arduino UNO/Nano sketch for the ITG/MPU gyro module. This takes
 * and save data from the x, y, z axis for a set number os milli-seconds.
 * Data collection will begin after a set number of n-length beeps from the
 * speaker module.
 */
#include "blink.h"
#include "mpu.h"

#define BAUD 9600

uint32_t ledClk = millis();
const uint32_t ledPer = 500;

void setup() {
  Serial.begin(BAUD);

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  flashLed(LED_BUILTIN, &ledClk, ledPer);
}
