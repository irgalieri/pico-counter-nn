#include <h595-shift-register-nn.h>
#include "pico/stdlib.h"

const uint SEGCODE[] = {
    0b111111010,
    0b011000010,
    0b110110110,
    0b111100110,
    0b011001110,
    0b101101110,
    0b101111110,
    0b111000010,
    0b111111110,
    0b111001110
};

bool hc595_out_shift_register(void) {
    gpio_put(PICO_STR_CLOCK_PIN, true);
    gpio_put(PICO_STR_CLOCK_PIN, false);
    return true;
}

bool hc595_shift_bit(bool bit) {
    gpio_put(PICO_SERIAL_PIN, bit);
    gpio_put(PICO_SR_CLOCK_PIN, true);
    gpio_put(PICO_SR_CLOCK_PIN, false);
    gpio_put(PICO_SERIAL_PIN, false);
}

bool hc595_shift(uint data) {
    int b = 0b0000001;
    while (b <= 128) {
        ((b <<= 1) & data) ? hc595_shift_bit(true) : hc595_shift_bit(false);
    }
    hc595_out_shift_register();
    return true;
}

bool hc595_shift_segment(uint segment) {
    uint base = 0b111111100;
    if (segment > 9) return false;
    if (segment % 2) base = 0b111111110;
    return hc595_shift(SEGCODE[segment] & base);
}