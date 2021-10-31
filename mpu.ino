#include "blink.h"
#include "mpuAverage.h"
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
 * An Arduino UNO/Nano sketch for the ITG/MPU6050 gyro module. This takes
 * and save data from the x, y, z axis for a set number of milli-seconds.
 * Data collection will begin after a set number of n-length beeps from the
 * speaker module.
 * Each A/D converter needs 100us (1ms is OK) between analog readings. A
 * delay is needed between reading of all analog pins, this delay does not
 * need to be for each individual pin but can be done as a whole as long as
 * you can confirm each analog pin will not be read 2 or more times within
 * 100us.
 */

// TODO: Change (experiment with) setup parameters
// TODO: Move print average to printMpu.h file
// TODO: Re-Write main comment to match this example/test sketch

// Adafruit mpu variable
Adafruit_MPU6050 mpu;

#define BAUD 115200

// Average Variables
const int avgSize = 10;
float avgArray[avgSize];
float avgSum = 0;
float avgAvg = 0;
int avgIndex = 0;
bool takeAvg = false;

// Axis Variables
float aX, aY, aZ;
float gX, gY, gZ;
float mpuTemp;

// millis Function Clocks
uint32_t ledClk = millis();
uint32_t mpuClk = millis();
uint32_t printClk = millis();
uint32_t avgClk = millis();

// millis Function delay times
uint32_t ledPer = 100;
uint32_t mpuPer = 10;
uint32_t printPer = 5;
uint32_t avgPer = 5;

void setup() {
  Serial.begin(BAUD);

  pinMode(LED_BUILTIN, OUTPUT);

  // initiate the avgArray with zeros
  for (int i = 0; i < avgSize; ++i)
    avgArray[i] = 0;

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

    bugln("Setup Complete.");
    delay(3000);
} // END SETUP

void loop() {
  if (millis() - mpuClk >= mpuPer) {
    mpuClk = millis();

    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    aX = a.acceleration.x;
    aY = a.acceleration.y;
    aZ = a.acceleration.z;

    gX = g.gyro.x;
    gY = g.gyro.y;
    gZ = g.gyro.z;

    mpuTemp = temp.temperature;

    takeAvg = true;
  }

/*
  if ((millis() - avgClk >= avgPer) && (takeAvg)) {
    float multiplier = 1.0;

    avgAvg = takeAverage(aZ, avgArray, avgSize, &avgSum, &avgIndex, multiplier);
    printAxisAverage(aZ, avgAvg, false);
    takeAvg = false;

    avgClk = millis();
  }
*/

  if ((millis() - printClk >= printPer) && (takeAvg)) {
    printAll(aX, aY, aZ, gX, gY, gZ, mpuTemp);
    printClk = millis();
  }

  flashLed(LED_BUILTIN, &ledClk, ledPer);
} // END LOOP

