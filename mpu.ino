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
#include "blink.h"
#include "mpu.h"

#define BAUD 9600

const int8_t sensPin = A5;

int16_t sensVal = 0;
int16_t count = 0;

uint32_t ledClk = millis();
const uint32_t ledPer = 100;

void setup() {
  Serial.begin(BAUD);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(sensPin, INPUT);

  for (int i = 0; i < 6; ++i) {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(500);
  }

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  delay(500);
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

void loop() {
  while (count < 1024) {
    sensVal = analogRead(sensPin);
    // Serial.println(sensVal);
    ++count;
    delay(5);
  }

  flashLed(LED_BUILTIN, &ledClk, ledPer);
  delay(1); // A-D converter limit delay
}
