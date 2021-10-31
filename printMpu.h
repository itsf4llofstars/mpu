#ifndef PRINTMPU_H
#define PRINTMPU_H

// TODO: Move print average to here

void printAll(float aX, float aY, float aZ, float gX, float gY, float gZ, float temp) {
  Serial.println("\nAccelerations:");
  Serial.print("Accel X: ");
  Serial.print(aX);
  Serial.print(" Accel Y: ");
  Serial.print(aY);
  Serial.print(" Accel Z: ");
  Serial.println(aZ);

  Serial.println("Gyroscopic:");
  Serial.print("Gyro X: ");
  Serial.print(gX);
  Serial.print(" Gyro Y: ");
  Serial.print(gY);
  Serial.print(" Gyro Z: ");
  Serial.println(gZ);

  Serial.print("Temp: ");
  Serial.println(temp);
}

void printAccel(float aX, float aY, float aZ) {
  Serial.println(aX);
  Serial.println(aY);
  Serial.println(aZ);

}

void printGyro(float gX, float gY, float gZ) {
  Serial.println(gX);
  Serial.println(gY);
  Serial.println(gZ);
}

void printTemp(float temp) {
  Serial.print("Temp: ");
  Serial.println(temp);
}

void singleAxis(float axis) {
  Serial.println(axis);
}

void multiplesSingleAxis(float axis, float n1, float n2) {
  Serial.print(axis);
  Serial.print(" ");
  Serial.print(axis * n1);
  Serial.print(" ");
  Serial.println(axis * n2);
}

void accelGyro(float accelAxis, float gyroAxis, bool first) {
  if (first) {
    Serial.print(accelAxis);
    Serial.print(" ");
    Serial.println(gyroAxis);
  }
  else if (!first) {
    Serial.print(gyroAxis);
    Serial.print(" ");
    Serial.println(accelAxis);
  }
}
#endif
