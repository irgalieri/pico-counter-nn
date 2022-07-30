#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"

#define PICO_SERIAL_PIN 0
#define PICO_SR_CLOCK_PIN 1
#define PICO_STR_CLOCK_PIN 2

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


/**
 * @brief Send One Bit to HC595
 * 
 * @param sr ShiftRegister Pointer
 * @param bit bit to transfer
 * @return true Ok
 * @return false Fail
 */
bool hc595_shift_bit(bool bit);

/**
 * @brief Out register to parallel output
 * 
 * @param sr ShiftRegister Pointer
 * @return true Ok
 * @return false Fail
 */
bool hc595_out_shift_register(void);

/**
 * @brief Send Number to HC595
 * 
 * @param sr ShiftRegister Pointer
 * @param data Number to Transfer
 * @return true Ok
 * @return false Fail
 */
bool hc595_shift(uint data);

/**
 * @brief Send Segment Number to HC595
 * 
 * @param sr ShiftRegister Pointer
 * @param segment Number to represent in 7 segment display
 * @return true Ok
 * @return false Fail
 */
bool hc595_shift_segment(uint segment);
/**
 * @brief Init GPIO Led Pin
 * 
 * @param led Pin Led
 */
void init_gpio_led(uint led);

/**
 * @brief Blink Onboard Led
 * 
 */
void blinking(void);

/**
 * @brief Change State Of Pin
 * 
 * @param pin Pin
 */
void toggle(uint pin);

/**
 * @brief Main Function
 * 
 * @return int 
 */
int main() {
    uint8_t counter = 0;

    stdio_init_all();

    // Define Pins Layout
    bi_decl(bi_1pin_with_name(PICO_SERIAL_PIN, "Serial Pin."));
    bi_decl(bi_1pin_with_name(PICO_SR_CLOCK_PIN, "Shift Register Clock Pin."));
    bi_decl(bi_1pin_with_name(PICO_STR_CLOCK_PIN, "Storage Register Clock Pin."));
    bi_decl(bi_1pin_with_name(PICO_DEFAULT_LED_PIN, "On-Board LED"));

    // init onboard led
    init_gpio_led(PICO_DEFAULT_LED_PIN);

    // launch thread to control onboard led
    multicore_launch_core1(blinking);

    // Init Shit Regsiter Pins
    gpio_init(PICO_SERIAL_PIN);
    gpio_set_dir(PICO_SERIAL_PIN, GPIO_OUT);
    
    gpio_init(PICO_SR_CLOCK_PIN);
    gpio_set_dir(PICO_SR_CLOCK_PIN, GPIO_OUT);
    
    gpio_init(PICO_STR_CLOCK_PIN);
    gpio_set_dir(PICO_STR_CLOCK_PIN, GPIO_OUT);

    
    while (1) {
        if (counter > 9) counter = 0;
        // counter in seven segment display
        hc595_shift_segment(counter);
        sleep_ms(1000);
        counter++;
    }
    
    return 0;
}

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

void init_gpio_led(uint led) {
    gpio_init(led);
    gpio_set_dir(led, GPIO_OUT);
}

void toggle(uint pin) {
    gpio_put(pin, !gpio_get(pin));
}

void blinking() {
    while (1) {
        toggle(PICO_DEFAULT_LED_PIN);
        sleep_ms(1000);
    }
}
