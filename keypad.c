/**
 * @file keypad.c
 * @brief Implementation of 4x4 matrix keypad interface for Raspberry Pi Pico
 *
 * Handles GPIO initialization and scanning for key presses.
 *
 * @author Luis Felipe Patrocinio
 * @date 2025
 */
#include "keypad.h"
#include "pico/stdlib.h"

// Keypad line (row) GPIO pins
#define LINE1 4
#define LINE2 8
#define LINE3 9
#define LINE4 16

// Keypad column GPIO pins
#define COLUMN1 17
#define COLUMN2 18
#define COLUMN3 19
#define COLUMN4 20

const uint LINE_PINS[4] = {LINE1, LINE2, LINE3, LINE4};
const uint COLUMN_PINS[4] = {COLUMN1, COLUMN2, COLUMN3, COLUMN4};

const int keypad_freq_map[4][4] = {
    {262, 294, 330, 349},  // C4, D4, E4, F4
    {392, 440, 494, 523},  // G4, A4, B4, C5
    {587, 659, 698, 784},  // D5, E5, F5, G5
    {880, 988, 1047, 1175} // A5, B5, C6, D6
};

void initKeypad(void)
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

bool keypadScan(uint8_t *row, uint8_t *col)
{
  for (int r = 0; r < 4; r++)
  {
    gpio_put(LINE_PINS[r], 1);
    for (int c = 0; c < 4; c++)
    {
      if (gpio_get(COLUMN_PINS[c]))
      {
        if (row)
          *row = r;
        if (col)
          *col = c;
        // Wait for key release (debounce)
        while (gpio_get(COLUMN_PINS[c]))
        {
          tight_loop_contents();
        }
        gpio_put(LINE_PINS[r], 0);
        return true;
      }
    }
    gpio_put(LINE_PINS[r], 0);
  }
  return false;
}