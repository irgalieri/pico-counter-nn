#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"

#ifndef PICO_SERIAL_PIN
#define PICO_SERIAL_PIN 0
#endif

#ifndef PICO_SR_CLOCK_PIN
#define PICO_SR_CLOCK_PIN 1
#endif

#ifndef PICO_STR_CLOCK_PIN
#define PICO_STR_CLOCK_PIN 2
#endif

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