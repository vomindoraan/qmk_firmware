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

#include "rgb.h"
#include "konstantin.h"

#ifdef RGBLIGHT_EFFECT_BREATHING
const uint8_t PROGMEM RGBLED_BREATHING_INTERVALS[] = { 20, 30, 5, 10 };
#endif

#ifdef RGBLIGHT_EFFECT_RAINBOW_MOOD
const uint8_t PROGMEM RGBLED_RAINBOW_MOOD_INTERVALS[] = { 20, 50, 100 };
#endif

#ifdef RGBLIGHT_EFFECT_RAINBOW_SWIRL
const uint8_t PROGMEM RGBLED_RAINBOW_SWIRL_INTERVALS[] = { 20, 50, 100 };
#endif

#ifdef RGBLIGHT_EFFECT_SNAKE
const uint8_t PROGMEM RGBLED_SNAKE_INTERVALS[] = { 20, 50, 100 };
#endif

#ifdef RGBLIGHT_EFFECT_KNIGHT
const uint8_t PROGMEM RGBLED_KNIGHT_INTERVALS[] = { 20, 50, 100 };
#endif

#ifdef RGB_INDICATORS

const rgb_indicator_t rgb_indicators[] = { RGB_INDICATORS };

#define COUNT ARRAY_SIZE(rgb_indicators)
typedef const rgb_indicator_t *handler_t;
static handler_t handlers[COUNT];

void rgb_indicator_reset(void) {
    rgblight_mode(RGBLIGHT_DEFAULT_MODE);
    rgblight_sethsv(RGBLIGHT_DEFAULT_HUE, RGBLIGHT_DEFAULT_SAT, RGBLIGHT_DEFAULT_VAL);
}

void rgb_indicator_action(void) {
    if (handlers[0]) {
        HSV color = handlers[0]->color;
        rgblight_mode_noeeprom(handlers[0]->mode);
        rgblight_sethsv_noeeprom(color.h, color.s, rgblight_get_val());
    } else {
        rgblight_config_t saved = { .raw = eeconfig_read_rgblight() };
        rgblight_mode_noeeprom(saved.mode);
        rgblight_sethsv_noeeprom(saved.hue, saved.sat, saved.val);
    }
}

static void update_handlers(handler_t handler, bool turned_on) {
    if (!handler || handler < rgb_indicators || handler >= rgb_indicators + COUNT) {
        return;
    }
    if (turned_on) {
        // Prepend handler
        handler_t tmp = handler;
        for (int i = 0; i < COUNT; i++) {
            SWAP(handlers[i], tmp);
            if (tmp == handler) break;
        }
    } else {
        // Remove handler
        int i = 0;
        for (int j = 0; j < COUNT; j++) {
            handlers[i] = handlers[j];
            if (handlers[j] != handler) i++;
        }
        handlers[i] = NULL;
    }
}

static void reshuffle_handlers(void) {
    // TODO
}

#define GET_LAYER(h)      (h)->layer
#define CHECK_LAYER(s, l) IS_LAYER_ON_STATE(s, l)
#define GET_LED(h)        (h)->led
#define CHECK_LED(s, l)   ((s).raw & l)

// TODO: Refactor into a function
#define RGB_INDICATOR_UPDATE(name, type, getter, checker)     \
    void rgb_indicator_update_##name(type state) {            \
        static type prev_state;                               \
        bool changed = false;                                 \
        for (int i = 0; i < COUNT; i++) {                     \
            handler_t h = &rgb_indicators[i];                 \
            if (!h || !getter(h)) continue;                   \
            bool is_on      = checker(state,      getter(h)); \
            bool is_on_prev = checker(prev_state, getter(h)); \
            if (is_on != is_on_prev) {                        \
                update_handlers(h, is_on);                    \
                changed = true;                               \
            }                                                 \
        }                                                     \
        if (changed) rgb_indicator_action();                  \
        prev_state = state;                                   \
    }

RGB_INDICATOR_UPDATE(layer, layer_state_t, GET_LAYER, CHECK_LAYER)

RGB_INDICATOR_UPDATE(led, led_t, GET_LED, CHECK_LED)

bool rgb_indicator_process_record(uint16_t keycode, keyrecord_t *record) {
    if (IS_RGB_KEYCODE(keycode)) {
        // Requires RGB_TRIGGER_ON_KEYDOWN
        if (record->event.pressed) {
            // Shift+Toggle = reset RGB
            if (keycode == RGB_TOG && get_mods() & MOD_MASK_SHIFT) {
                rgb_indicator_reset();
                return false;
            }
            rgb_indicator_action();
        } else {
            reshuffle_handlers();
        }
    }
    return true;
}

#endif  // RGB_INDICATORS
