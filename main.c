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

#define LED_RED_PIN 13

/**
 * @brief Frequency map for each key in the 4x4 matrix (Hz).
 */
const int keypad_freq_map[4][4] = {
    {262, 294, 330, 349},  // C4, D4, E4, F4
    {392, 440, 494, 523},  // G4, A4, B4, C5
    {587, 659, 698, 784},  // D5, E5, F5, G5
    {880, 988, 1047, 1175} // A5, B5, C6, D6
};

/**
 * @brief Pisca o LED vermelho conectado ao pino 13.
 * @param times Quantas vezes piscar
 * @param delay_ms Delay em ms entre liga/desliga
 */
void blink_led_red(int times, int delay_ms)
{
  for (int i = 0; i < times; i++)
  {
    gpio_put(LED_RED_PIN, 1);
    sleep_ms(delay_ms);
    gpio_put(LED_RED_PIN, 0);
    sleep_ms(delay_ms);
  }
}

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
  gpio_init(LED_RED_PIN);
  gpio_set_dir(LED_RED_PIN, GPIO_OUT);
}

uint8_t row, col;

/**
 * @brief Main program entry point.
 *
 * Initializes peripherals and enters the main loop, scanning the keypad and playing tones.
 * @return int Program exit status (never returns in embedded context).
 */
int main()
{
  setup();

  blink_led_red(1, 100);
  playWelcomeTones();

  while (true)
  {
    if (keypadScan(&row, &col))
    {
      blink_led_red(1, 50);
      playTone(keypad_freq_map[row][col], 200); // 200ms
    }
    sleep_ms(10); // Simple debounce
  }
}
