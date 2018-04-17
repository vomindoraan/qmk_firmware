/*
Copyright 2018 Konstantin Đorđević <vomindoraan@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "whitefox.h"

#define _______ KC_TRNS

#define FN_TT   TT(1)
#define FN_CAPS LT(1, KC_CAPS)
#define FN_PLAY LT(2, KC_MPLY)

#define CTL_HOM LCTL(KC_HOME)
#define CTL_END LCTL(KC_END)

enum custom_keycodes {
    M_CLEAR = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    if (!record->event.pressed) return true;
    switch (keycode) {
    case M_CLEAR:
        SEND_STRING(SS_LCTRL("a") SS_TAP(X_DELETE));
        return false;
    default:
        return true;
    }
}

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Default layer
     * ,---------------------------------------------------------------.
     * |Esc| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = | \ | ` |FnP|
     * |---------------------------------------------------------------|
     * | Tab | Q | W | E | R | T | Y | U | I | O | P | [ | ] |Bspc |Del|
     * |---------------------------------------------------------------|
     * |FnCaps| A | S | D | F | G | H | J | K | L | ; | ' | Enter  |PgU|
     * |---------------------------------------------------------------|
     * | LShift | Z | X | C | V | B | N | M | , | . | / |RShift| ↑ |PgD|
     * |---------------------------------------------------------------|
     * |LCtl|LGui|LAlt|         Space          |RAlt|FnTT| | ← | ↓ | → |
     * `---------------------------------------------------------------'
     */
    [0] = KEYMAP_TRUEFOX( \
        KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSLS,KC_GRV, FN_PLAY, \
        KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSPC,        KC_DEL,  \
        FN_CAPS,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,        KC_ENT,         KC_PGUP, \
        KC_LSFT,        KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,        KC_UP,  KC_PGDN, \
        KC_LCTL,KC_LGUI,KC_LALT,                        KC_SPC,                 KC_RALT,FN_TT,                  KC_LEFT,KC_DOWN,KC_RGHT  \
    ),

    /* Function layer 1
     * ,---------------------------------------------------------------.
     * |   |F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|PSc|SLk|Pau|
     * |---------------------------------------------------------------|
     * | M4  |M2 |M↑ |M1 |M3 |M5 |   |   |   |   |   |   |   |Clear|Ins|
     * |---------------------------------------------------------------|
     * |      |M← |M↓ |M→ |MW↑|   |   |   |   |   |   |   |        |^Hm|
     * |---------------------------------------------------------------|
     * |        |   |   |MW←|MW→|   |   |   |   |   |   |      |PgU|^En|
     * |---------------------------------------------------------------|
     * |    |    |    |          MW↓           |App |    | |Hom|PgD|End|
     * `---------------------------------------------------------------'
     */
    [1] = KEYMAP_TRUEFOX( \
        _______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, KC_PSCR,KC_SLCK,KC_PAUS, \
        KC_BTN4,KC_BTN2,KC_MS_U,KC_BTN1,KC_BTN3,KC_BTN5,_______,_______,_______,_______,_______,_______,_______,M_CLEAR,        KC_INS,  \
        _______,KC_MS_L,KC_MS_D,KC_MS_R,KC_WH_U,_______,_______,_______,_______,_______,_______,_______,        _______,        CTL_HOM, \
        _______,        _______,_______,KC_WH_L,KC_WH_R,_______,_______,_______,_______,_______,_______,_______,        KC_PGUP,CTL_END, \
        _______,_______,_______,                        KC_WH_D,                KC_APP, _______,                KC_HOME,KC_PGDN,KC_END   \
    ),

    /* Function layer 2
     * ,---------------------------------------------------------------.
     * |Pwr|Slp|   |   |   |   |   |   |   |   |Mut|Vo-|Vo+|Prv|Nxt|   |
     * |---------------------------------------------------------------|
     * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |   |
     * |---------------------------------------------------------------|
     * |      |   |   |   |   |   |   |   |   |   |   |   |        |   |
     * |---------------------------------------------------------------|
     * |        |   |   |   |   |   |   |   |   |   |   |      |   |   |
     * |---------------------------------------------------------------|
     * |    |    |    |                        |    |    | |   |   |   |
     * `---------------------------------------------------------------'
     */
    [2] = KEYMAP_TRUEFOX( \
        KC_PWR, KC_SLEP,_______,_______,_______,_______,_______,_______,_______,_______,KC_MUTE,KC_VOLD,KC_VOLU,KC_MPRV,KC_MNXT,_______, \
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______, \
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,        _______, \
        _______,        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,_______, \
        _______,_______,_______,                        _______,                _______,_______,                _______,_______,_______  \
    ),
};

const uint16_t fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(1),
    [1] = ACTION_LAYER_MOMENTARY(2),
};
