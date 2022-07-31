#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"

typedef struct PicoPinConfig {
    uint Serial;
    uint RegisterClock;
    uint StorageClock;
} PicoPinConfig;

typedef struct ShiftRegister {
    uint serial;
    uint registerClock;
    uint StorageClock;
} ShiftRegister;

/**
 * @brief Construct and init Shift Register
 * 
 * @param config Pico Pins Config
 * @return ShiftRegister 
 */
ShiftRegister shift_register_new(PicoPinConfig config);

/**
 * @brief Send One Bit to HC595
 * 
 * @param sr ShiftRegister Pointer
 * @param bit bit to transfer
 * @return true Ok
 * @return false Fail
 */
bool hc595_shift_bit(ShiftRegister* sr, bool bit);

/**
 * @brief Out register to parallel output
 * 
 * @param sr ShiftRegister Pointer
 * @return true Ok
 * @return false Fail
 */
bool hc595_out_shift_register(ShiftRegister* sr);

/**
 * @brief Send Number to HC595
 * 
 * @param sr ShiftRegister Pointer
 * @param data Number to Transfer
 * @return true Ok
 * @return false Fail
 */
bool hc595_shift(ShiftRegister* sr, uint data);

/**
 * @brief Send Segment Number to HC595
 * 
 * @param sr ShiftRegister Pointer
 * @param segment Number to represent in 7 segment display
 * @return true Ok
 * @return false Fail
 */
bool hc595_shift_segment(ShiftRegister* sr, uint segment);