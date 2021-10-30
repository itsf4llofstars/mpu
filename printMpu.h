#ifndef PRINTMPU_H
#define PRINTMPU_H

void printAll(float aX, float aY, float aZ, float gX, float gY, float gZ, float temp) {
  Serial.println("\nAccelerations:");
  Serial.print(" Accel X: ");
  Serial.print(aX);
  Serial.print(" Accel Y: ");
  Serial.print(aY);
  Serial.print(" Accel Z: ");
  Serial.print(aZ);
  Serial.print(" Temp: ");
  Serial.println(temp);
}

#endif
