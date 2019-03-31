#include QMK_KEYBOARD_H
#include "konstantin.h"

#define TAP_CODE(code, delay)  (register_code(code), wait_ms(delay), unregister_code(code))
#define TAP_CODE_NODELAY(code) (register_code(code), unregister_code(code))

#define TAP_CODE16(code, delay)  (register_code16(code), wait_ms(delay), unregister_code16(code))
#define TAP_CODE16_NODELAY(code) (register_code16(code), unregister_code16(code))

#define TEST(macro, code) ( \
  macro ## _NODELAY(code),  \
  macro(code, 5),           \
  macro(code, 10),          \
  macro(code, 20),          \
  macro(code, 50),          \
  wait_ms(1000)             \
)

enum keycodes_keymap {
  TAPTEST = RANGE_KEYMAP,
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case TAPTEST:
    TEST(TAP_CODE,   KC_A);
    TEST(TAP_CODE16, KC_VOLU);
    // TEST(TAP_CODE16, KC_MS_U);
    // TEST(TAP_CODE16, KC_BTN1);
    TEST(TAP_CODE16, KC_HASH);
    return false;

  default:
    return true;
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Base layer
   * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
   * │Esc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ \ │ ` │PSc│
   * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┼───┤
   * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │Bspc │Del│
   * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
   * │FnCaps│ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ Enter  │PgU│
   * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
   * │ LShift │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │RCtRSf│ ↑ │PgD│
   * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
   * │LCtl│LGui│LAlt│         Space          │RAlG│FnLk│ │ ← │ ↓ │ → │
   * └────┴────┴────┴────────────────────────┴────┴────┘ └───┴───┴───┘
   */
  [L_BASE] = LAYOUT_truefox( \
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,  KC_PSCR, \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,          KC_DEL,  \
    FN_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGUP, \
    KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RCT_RSF,          KC_UP,   KC_PGDN, \
    KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                    RAL_RGU, FN_FNLK,                   KC_LEFT, KC_DOWN, KC_RGHT  \
  ),

  /* Function layer
   * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
   * │   │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│Num│SLk│Pau│
   * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┼───┤
   * │ M4  │M2 │M↑ │M1 │M3 │M5 │   │UCM│   │Stp│Ply│Prv│Nxt│Clear│Ins│
   * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
   * │      │M← │M↓ │M→ │MW↑│   │   │   │   │   │   │   │TapTest │Top│
   * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
   * │        │MA0│MA2│MW←│MW→│   │   │   │Vo-│Vo+│Mut│ App  │PgU│Btm│
   * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
   * │    │DtPR│DtNA│          MW↓           │    │    │ │Hom│PgD│End│
   * └────┴────┴────┴────────────────────────┴────┴────┘ └───┴───┴───┘
   */
  [L_FN] = LAYOUT_truefox( \
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  NUMPAD,  KC_SLCK, KC_PAUS, \
    KC_BTN4, KC_BTN2, KC_MS_U, KC_BTN1, KC_BTN3, KC_BTN5, _______, UC_MOD,  _______, KC_MSTP, KC_MPLY, KC_MPRV, KC_MNXT, CLEAR,            KC_INS,  \
    _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_U, _______, _______, _______, _______, _______, _______, _______,          TAPTEST,          TOP,     \
    _______,          KC_ACL0, KC_ACL2, KC_WH_L, KC_WH_R, _______, _______, _______, KC_VOLD, KC_VOLU, KC_MUTE, KC_APP,           KC_PGUP, BOTTOM,  \
    _______, DST_P_R, DST_N_A,                            KC_WH_D,                   _______, _______,                   KC_HOME, KC_PGDN, KC_END   \
  ),

  /* Numpad layer
   * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
   * │   │   │   │   │   │   │   │P7 │P8 │P9 │P- │ − │ = │Num│   │   │
   * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┼───┤
   * │     │   │   │   │   │   │   │P4 │P5 │P6 │P+ │ ( │ ) │     │   │
   * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
   * │      │   │   │   │   │   │   │P1 │P2 │P3 │P* │ × │ PEnter │   │
   * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
   * │        │   │   │   │   │   │P0 │P0 │ , │P. │P/ │  ÷   │   │   │
   * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
   * │    │    │    │                        │    │    │ │   │   │   │
   * └────┴────┴────┴────────────────────────┴────┴────┘ └───┴───┴───┘
   */
  [L_NUMPAD] = LAYOUT_truefox( \
    _______, _______, _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   KC_PMNS, MINUS,   EQUALS,  NUMPAD,  _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, L_PAREN, R_PAREN, _______,          _______, \
    _______, _______, _______, _______, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_PAST, TIMES,            KC_PENT,          _______, \
    _______,          _______, _______, _______, _______, _______, KC_P0,   KC_P0,   COMMA,   KC_PDOT, KC_PSLS, DIVIDE,           _______, _______, \
    _______, _______, _______,                            _______,                   _______, _______,                   _______, _______, _______  \
  ),
};
