#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
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

uint32_t ledClk = millis();
uint32_t ledPer = 500;


void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  // Initial Setup print
  Serial.println("MPU6050 Setup test.");

  // Initialize the MPU6050
  if (!mpu.begin())
    Serial.println("Failed to find MPU6050.");
  else
    Serial.println("MPU6050 found");

  Serial.println("DEBUG");

  // Setup Accelerometer Range
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
    case MPU6050_RANGE_2_G:
      Serial.println("+-2G");
      break;
    case MPU6050_RANGE_4_G:
      Serial.println("+-4G");
      break;
    case MPU6050_RANGE_8_G:
      Serial.println("+-8G");
      break;
    case MPU6050_RANGE_16_G:
      Serial.println("+-16G");
      break;
  }

  Serial.println("MPU Accelerometer Range set.");

  // Setup Gyro Range
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
    case MPU6050_RANGE_250_DEG:
      Serial.println("+- 250 deg/s");
      break;
    case MPU6050_RANGE_500_DEG:
      Serial.println("+- 500 deg/s");
      break;
    case MPU6050_RANGE_1000_DEG:
      Serial.println("+- 1000 deg/s");
      break;
    case MPU6050_RANGE_2000_DEG:
      Serial.println("+- 2000 deg/s");
      break;
  }

  Serial.println("MPU Gyro Range set.");

  // Setup Filter Bandwidth
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
    case MPU6050_BAND_260_HZ:
      Serial.println("260 Hz");
      break;
    case MPU6050_BAND_184_HZ:
      Serial.println("184 Hz");
      break;
    case MPU6050_BAND_94_HZ:
      Serial.println("94 Hz");
      break;
    case MPU6050_BAND_44_HZ:
      Serial.println("44 Hz");
      break;
    case MPU6050_BAND_21_HZ:
      Serial.println("21 Hz");
      break;
    case MPU6050_BAND_10_HZ:
      Serial.println("10 Hz");
      break;
    case MPU6050_BAND_5_HZ:
      Serial.println("5 Hz");
      break;
    }

  Serial.println("MPU Filter Bandwidth set.");

    Serial.println("Setup Complete.");
    delay(100);
} // END SETUP

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  Serial.print("Ax ");
  Serial.print(a.acceleration.x);
  Serial.print("Ay ");
  Serial.print(a.acceleration.y);
  Serial.print("Az ");
  Serial.println(a.acceleration.z);

  Serial.print("Rx ");
  Serial.print(g.gyro.x);
  Serial.print("Ry ");
  Serial.print(g.gyro.y);
  Serial.print("Rz ");
  Serial.println(g.gyro.z);

  Serial.print("T ");
  Serial.println(temp.temperature);

  Serial.println();
  delay(500);

  flashLed();
} // END LOOP

void flashLed() {
  if (millis() - ledClk >= ledPer) {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    ledClk = millis();
  }
}
