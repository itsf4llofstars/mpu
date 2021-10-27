/*
 * A simple blink header file to flash the passed led and
 * update the current time for delay purposes
 */

void flashLed(int8_t led, uint32_t *clk, uint32_t per) {
    if (millis() - *clk >= per) {
        digitalWrite(led, !digitalRead(led));
        *clk = millis();
    }
}

