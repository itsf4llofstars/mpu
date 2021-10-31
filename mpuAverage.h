#ifndef MPUAVERAGE_H
#define MPUAVERAGE_H

// TODO: Move print average to printMpu.h file

float takeAverage(float axis, float array[], int size, float *sum, int *index, float n) {
  axis *= n;
  int i = *index;

  *sum -= array[i];
  array[i] = axis;
  *sum += array[i];

  *index = (1 + *index) % size;

  return *sum / size;
}

void printAxisAverage(float axis, float average, bool both) {
  axis *= 10;

  if (both) {
    Serial.print(axis);
    Serial.print(" ");
    Serial.println(average);
  }
  else if (!both)
    Serial.println(average);
}

#endif
