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

ShiftRegister shift_register_new(PicoPinConfig config) {
    ShiftRegister *reg = malloc(sizeof(ShiftRegister));

    reg->serial = config.Serial;
    reg->registerClock = config.RegisterClock;
    reg->StorageClock = config.StorageClock;

    // Init Shit Regsiter Pins
    gpio_init(reg->serial);
    gpio_set_dir(reg->serial, GPIO_OUT);
    
    gpio_init(reg->registerClock);
    gpio_set_dir(reg->registerClock, GPIO_OUT);
    
    gpio_init(reg->StorageClock);
    gpio_set_dir(reg->StorageClock, GPIO_OUT);

    return *reg;
}

bool hc595_out_shift_register(ShiftRegister* sr) {
    gpio_put(sr->StorageClock, true);
    gpio_put(sr->StorageClock, false);
    return true;
}

bool hc595_shift_bit(ShiftRegister* sr, bool bit) {
    gpio_put(sr->serial, bit);
    gpio_put(sr->registerClock, true);
    gpio_put(sr->registerClock, false);
    gpio_put(sr->serial, false);
}

bool hc595_shift(ShiftRegister* sr, uint data) {
    int b = 0b0000001;
    while (b <= 128) {
        ((b <<= 1) & data) ? hc595_shift_bit(sr, true) : hc595_shift_bit(sr, false);
    }
    hc595_out_shift_register(sr);
    return true;
}

bool hc595_shift_segment(ShiftRegister* sr, uint segment) {
    uint base = 0b111111100;
    if (segment > 9) return false;
    if (segment % 2) base = 0b111111110;
    return hc595_shift(sr, SEGCODE[segment] & base);
}