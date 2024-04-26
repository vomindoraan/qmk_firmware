/* Copyright 2019-2024 Konstantin Đorđević <vomindoraan@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "quantum.h"

#define GODSPEED_BLUE     198,  68, 255
#define GODSPEED_YELLOW    27, 153, 255
#define MODERN_DOLCH_CYAN 110, 255, 108
#define MODERN_DOLCH_RED  253, 255, 108
#define SERIKA_YELLOW      18, 255, 128

#ifdef RGB_INDICATORS

#define LED_NUM_LOCK    (1 << 0)
#define LED_CAPS_LOCK   (1 << 1)
#define LED_SCROLL_LOCK (1 << 2)
#define LED_COMPOSE     (1 << 3)
#define LED_KANA        (1 << 4)

typedef struct {
    uint8_t layer;
    uint8_t led;
    uint8_t mode;
    HSV     color;
} rgb_indicator_t;

extern const rgb_indicator_t rgb_indicators[];

void rgb_indicator_reset(void);
void rgb_indicator_action(void);
void rgb_indicator_update_layer(layer_state_t state);
void rgb_indicator_update_led(led_t led_state);
bool rgb_indicator_process_record(uint16_t keycode, keyrecord_t *record);

#endif  // RGB_INDICATORS
