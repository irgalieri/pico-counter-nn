#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"
#include "h595-shift-register-nn.h"

#define PICO_SERIAL_PIN 6
#define PICO_SR_CLOCK_PIN 7
#define PICO_STR_CLOCK_PIN 8

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

    //  Init Shift Register
    ShiftRegister sr = shift_register_new((PicoPinConfig){
        .Serial = PICO_SERIAL_PIN,
        .RegisterClock = PICO_SR_CLOCK_PIN,
        .StorageClock = PICO_STR_CLOCK_PIN
    });

    while (1) {
        if (counter > 9) counter = 0;
        // counter in seven segment display
        hc595_shift_segment(&sr, counter);
        sleep_ms(1000);
        counter++;
    }
    
    return 0;
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
