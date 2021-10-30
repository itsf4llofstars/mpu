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
#include <Wire.h>

#define PRINT 1
#if PRINT == 1
#define bug(x) Serial.print(x)
#define bugln(x) Serial.println(x)
#else
#define bug(x)
#define bugln(x)
#endif

#if PRINT == 1
#define BAUD 9600
#endif

const int8_t sensPin = A5;

int16_t sensVal = 0;
int16_t count = 0;

uint32_t ledClk = millis();
const uint32_t ledPer = 100;

void setup() {
#if PRINT == 1
    Serial.begin(BAUD);
#endif

    initMpu();
    setMpuAccelRange();
    setMpuGyroRange();
    setfilterBandwidth();

    Serial.println("");
    delay(100);
}

void loop() {

}

