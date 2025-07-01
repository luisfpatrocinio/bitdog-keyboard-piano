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

// Setup 4x4 Keyboard Pins
/**
 * @def LINE1
 * @brief GPIO pin for keyboard line 1
 */
#define LINE1 4
/**
 * @def LINE2
 * @brief GPIO pin for keyboard line 2
 */
#define LINE2 8
/**
 * @def LINE3
 * @brief GPIO pin for keyboard line 3
 */
#define LINE3 9
/**
 * @def LINE4
 * @brief GPIO pin for keyboard line 4
 */
#define LINE4 16

// Columns 1-4
/**
 * @def COLUMN1
 * @brief GPIO pin for keyboard column 1
 */
#define COLUMN1 17
/**
 * @def COLUMN2
 * @brief GPIO pin for keyboard column 2
 */
#define COLUMN2 18
/**
 * @def COLUMN3
 * @brief GPIO pin for keyboard column 3
 */
#define COLUMN3 19
/**
 * @def COLUMN4
 * @brief GPIO pin for keyboard column 4
 */
#define COLUMN4 20

/**
 * @var LINE_PINS
 * @brief Array of GPIO pins for keyboard lines.
 */
const uint LINE_PINS[4] = {LINE1, LINE2, LINE3, LINE4};
/**
 * @var COLUMN_PINS
 * @brief Array of GPIO pins for keyboard columns.
 */
const uint COLUMN_PINS[4] = {COLUMN1, COLUMN2, COLUMN3, COLUMN4};

/**
 * @var freq_map
 * @brief Frequency map for each key in the 4x4 matrix.
 *        Each entry corresponds to a musical note frequency in Hz.
 */
const int freq_map[4][4] = {
    {262, 294, 330, 349},  // C4, D4, E4, F4
    {392, 440, 494, 523},  // G4, A4, B4, C5
    {587, 659, 698, 784},  // D5, E5, F5, G5
    {880, 988, 1047, 1175} // A5, B5, C6, D6
};

/**
 * @brief Initializes the GPIO pins for the 4x4 matrix keyboard.
 *
 * Sets the line pins as outputs (initially low) and the column pins as inputs with pull-down resistors.
 */
void setup_keyboard()
{
  for (int i = 0; i < 4; i++)
  {
    gpio_init(LINE_PINS[i]);
    gpio_set_dir(LINE_PINS[i], GPIO_OUT);
    gpio_put(LINE_PINS[i], 0);

    gpio_init(COLUMN_PINS[i]);
    gpio_set_dir(COLUMN_PINS[i], GPIO_IN);
    gpio_pull_down(COLUMN_PINS[i]);
  }
}

/**
 * @brief Initializes the standard IO, buzzer, and keyboard.
 *
 * This function should be called once at the beginning of main().
 */
void setup()
{
  stdio_init_all();

  initBuzzerPWM();

  setup_keyboard();
}

/**
 * @brief Scans the 4x4 matrix keyboard for key presses.
 *
 * For each detected key press, plays the corresponding tone for 200 ms.
 * Waits for the key to be released before continuing (simple debouncing).
 */
void scan_keyboard()
{
  for (int row = 0; row < 4; row++)
  {
    // Activate the current row
    gpio_put(LINE_PINS[row], 1);
    for (int col = 0; col < 4; col++)
    {
      if (gpio_get(COLUMN_PINS[col]))
      {
        // Key pressed: play corresponding tone
        playTone(freq_map[row][col], 200); // 200ms
        // Wait for key release to avoid multiple triggers
        while (gpio_get(COLUMN_PINS[col]))
        {
          tight_loop_contents();
        }
      }
    }
    // Deactivate the current row
    gpio_put(LINE_PINS[row], 0);
  }
}

/**
 * @brief Main program entry point.
 *
 * Initializes peripherals and enters the main loop, scanning the keyboard and playing tones.
 * @return int Program exit status (never returns in embedded context).
 */
int main()
{
  setup();

  playTone(262, 200); // Play a welcome tone

  while (true)
  {
    scan_keyboard();
    sleep_ms(10); // Simple debounce
  }
}
