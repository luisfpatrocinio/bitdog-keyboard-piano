/**
 * @file main.c
 * @brief 4x4 Matrix Keyboard with Buzzer Example for Raspberry Pi Pico
 * @author Luis Felipe Patrocinio (https://github.com/luisfpatrocinio/)
 *
 * This program scans a 4x4 matrix keyboard and plays a tone on a buzzer corresponding to the pressed key.
 *
 * - Keyboard lines and columns are mapped to GPIO pins.
 * - Each key press triggers a specific frequency.
 * - Uses PWM for buzzer control.
 *
 * @version 0.1
 * @date 07-01-2025
 * @copyright Copyright (c) 2025 Luis Felipe Patrocinio
 * @license This project is released under the MIT License.
 * See LICENSE file for full license text.
 * https://github.com/luisfpatrocinio/bitdog-patroLibs/blob/main/LICENSE
 */
#include <stdio.h>
#include "pico/stdlib.h"
#include "buzzer.h"
#include "keypad.h"

/**
 * @brief Initializes the standard IO, buzzer, and keypad.
 *
 * This function should be called once at the beginning of main().
 */
void setup()
{
  stdio_init_all();
  initBuzzerPWM();
  initKeypad();
}

/**
 * @brief Main program entry point.
 *
 * Initializes peripherals and enters the main loop, scanning the keypad and playing tones.
 * @return int Program exit status (never returns in embedded context).
 */
int main()
{
  setup();
  // Play a sequence of 5 short welcome tones
  int welcome_notes[5] = {262, 294, 330, 349, 392}; // C4, D4, E4, F4, G4
  for (int i = 0; i < 5; i++)
  {
    playTone(welcome_notes[i], 50); // 50ms per note
    sleep_ms(30);                   // Short pause between notes
  }

  while (true)
  {
    uint8_t row, col;
    if (keypadScan(&row, &col))
    {
      playTone(keypad_freq_map[row][col], 200); // 200ms
    }
    sleep_ms(10); // Simple debounce
  }
}
