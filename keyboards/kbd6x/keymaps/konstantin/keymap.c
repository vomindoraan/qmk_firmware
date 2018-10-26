#include QMK_KEYBOARD_H

#define LCT_CPS LCTL_T(KC_CAPS)
#define FN      MO(L_FN)        // Unused
#define FN_TOG  TD(TD_FN_TOG)
#define DESKTOP TD(TD_DESKTOP)

#define DESKT_L LCTL(LGUI(KC_LEFT))
#define DESKT_R LCTL(LGUI(KC_RGHT))
#define TOP     LCTL(KC_HOME)
#define BOTTOM  LCTL(KC_END)

enum layers {
  L_BASE,
  L_FN,
};

enum custom_keycodes {
  CLEAR = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case CLEAR:
    if (record->event.pressed) { SEND_STRING(SS_LCTRL("a") SS_TAP(X_DELETE)); }
    return false;

  default:
    return true;
  }
}

enum tap_dance {
  TD_FN_TOG,
  TD_DESKTOP,
};

bool td_fn_saved;
bool td_fn_started;

void td_fn_tog_each(qk_tap_dance_state_t *state, void *user_data) {
  if (!td_fn_started) {
    td_fn_saved = IS_LAYER_ON(L_FN);
    td_fn_started = true;
  }
  layer_on(L_FN);
}

void td_fn_tog_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {
    td_fn_saved ? layer_off(L_FN) : layer_on(L_FN);
  }
}

void td_fn_tog_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    layer_off(L_FN);
  }
  td_fn_started = false;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_FN_TOG] = ACTION_TAP_DANCE_FN_ADVANCED(td_fn_tog_each, td_fn_tog_finished, td_fn_tog_reset),
  [TD_DESKTOP] = ACTION_TAP_DANCE_DOUBLE(LCTL(LGUI(KC_D)), LCTL(LGUI(KC_F4))), // Add/close virtual desktop
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [L_BASE] = LAYOUT(
    KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,    KC_6,  KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSLS,KC_GRV,
    KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,    KC_Y,  KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSPC,
    LCT_CPS,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,    KC_H,  KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,KC_ENT,
    KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,    KC_N,  KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,FN_TOG,
    XXXXXXX,KC_LGUI,KC_LALT,                KC_SPACE,               KC_RALT,KC_RCTL,XXXXXXX
  ),

  [L_FN] = LAYOUT(
    _______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, KC_PSCR,CLEAR,
    _______,KC_HOME,KC_UP,  KC_END, KC_PGUP,TOP,    _______,_______,_______,KC_BTN1,KC_MS_U,KC_BTN2,KC_BTN3,KC_DEL,
    _______,KC_LEFT,KC_DOWN,KC_RGHT,KC_PGDN,BOTTOM, _______,_______,KC_WH_U,KC_MS_L,KC_MS_D,KC_MS_R,KC_INS,
    _______,KC_MUTE,KC_VOLD,KC_VOLU,KC_MPLY,KC_MPRV,KC_MNXT,KC_WH_L,KC_WH_R,KC_BTN4,KC_BTN5,_______,_______,
    _______,DESKTOP,DESKT_L,                KC_WH_D,                DESKT_R,KC_APP, _______
  ),
};