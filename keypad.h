/**
 * @file keypad.h
 * @brief Keypad (4x4 matrix) interface for Raspberry Pi Pico
 *
 * Provides functions to initialize and scan a 4x4 matrix keypad.
 *
 * @author Luis Felipe Patrocinio
 * @date 2025
 */
#ifndef KEYPAD_H
#define KEYPAD_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Initializes the GPIO pins for the 4x4 matrix keypad.
 */
void initKeypad(void);

/**
 * @brief Scans the keypad and returns the row and column of the pressed key.
 *
 * @param[out] row Pointer to store the row index (0-3) of the pressed key.
 * @param[out] col Pointer to store the column index (0-3) of the pressed key.
 * @return true if a key is pressed, false otherwise.
 */
bool keypadScan(uint8_t *row, uint8_t *col);

/**
 * @brief Frequency map for each key in the 4x4 matrix (Hz).
 */
extern const int keypad_freq_map[4][4];

#endif // KEYPAD_H