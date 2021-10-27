#ifndef MPU_H
#define MPU_H

// #include <MPU_LIB>

void readMpu(uint16_t *data, uint32_t *clk, uint32_t per) {
    if (millis() - *clk >= per) {
        // *data = analogRead(pin);
        *clk = millis();
    }
}
#endif

