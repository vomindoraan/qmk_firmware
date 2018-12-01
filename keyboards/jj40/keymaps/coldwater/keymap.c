#include QMK_KEYBOARD_H

enum jj40_layers {
  _QWERTY,
  _LOWER,
  _RAISE
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE
};

// enum {
//   TD_QUOTE_SCLN = 0,
//   TD_ESC_GRAVE
// };

// qk_tap_dance_action_t tap_dance_actions[] = {
//   //Tap once for quote, twice for semicolon
//   [TD_QUOTE_SCLN]  = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_QUOTE),
//   [TD_ESC_GRAVE]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_GRAVE),
// };


#define _______ KC_TRNS
#define LOWER_SHIFT LT(_LOWER, KC_DELETE)
#define RAISE_ENTER LT(_RAISE, KC_ENT)
#define SHT_BSP LSFT_T(KC_BSPC)
#define CMD_SPC LGUI_T(KC_SPC)
#define DIVVY LALT(LGUI(LSFT(KC_D)))
#define F_CHR LALT(LSFT(KC_E))
#define F_WIN LALT(LGUI(LSFT(KC_W)))


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT_ortho_4x12( \
  KC_TAB,         KC_Q,    KC_W,    KC_E,    KC_R,         KC_T,     KC_Y,     KC_U,        KC_I,       KC_O,    KC_P,    _______, \
  LCTL_T(KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,         KC_G,     KC_H,     KC_J,        KC_K,       KC_L,    KC_SCLN, KC_QUOTE, \
  _______,        KC_Z,    KC_X,    KC_C,    KC_V,         KC_B,     KC_N,     KC_M,        KC_COMM,    KC_DOT,  KC_SLSH, KC_BSLASH, \
  _______,        _______, KC_LGUI, KC_LALT, LOWER_SHIFT,  SHT_BSP,  CMD_SPC,  RAISE_ENTER, KC_LEFT,    KC_DOWN, KC_UP,   KC_RGHT \
),

[_LOWER] = LAYOUT_ortho_4x12( \
  _______,  _______,  _______,  _______,  KC_GRAVE,   _______,      _______,      KC_7,     KC_8, KC_9,   KC_MINUS, KC_HOME, \
  _______,  _______,  DIVVY,    F_CHR,    F_WIN,      KC_LPRN,      KC_RPRN,      KC_4,     KC_5, KC_6,   KC_EQUAL, KC_PGUP, \
  _______,  _______,  _______,  _______,  KC_PSCREEN, KC_LBRACKET,  KC_RBRACKET,  KC_1,     KC_2, KC_3,   KC_SLSH,  KC_PGDOWN, \
  _______,  _______,  _______,  _______,  _______,    _______,      _______,      _______,  KC_0, KC_DOT, _______,  KC_END \
),

[_RAISE] = LAYOUT_ortho_4x12( \
	KC_F1,	  KC_F2,	  KC_F3,	        KC_F4,	    KC_F5,	        KC_F6,	        KC_F7,	  KC_F8,	              KC_F9,	              KC_F10,	            KC_F11,	              KC_F12	,	\
	RGB_TOG,	RGB_MOD,	KC_MS_WH_LEFT,  KC_MS_UP,   KC_MS_WH_RIGHT, KC_MS_WH_UP,    _______,	KC_MS_BTN1,           KC_MS_BTN3,           KC_MS_BTN2,         LALT(LSFT(KC_UP)),    KC_MS_ACCEL2,	\
	BL_TOGG,	BL_STEP,	KC_MS_LEFT,     KC_MS_DOWN, KC_MS_RIGHT,    KC_MS_WH_DOWN,	_______,	KC_MEDIA_PLAY_PAUSE,  KC_MEDIA_STOP,        KC_APPLICATION,     LALT(LSFT(KC_DOWN)),  KC_MS_ACCEL0,	\
	_______,	_______,	_______,	      _______,	  _______,	      _______,        _______,	_______,	            KC_MEDIA_PREV_TRACK,  KC_AUDIO_VOL_DOWN,  KC_AUDIO_VOL_UP,      KC_MEDIA_NEXT_TRACK	\
)
};

// Loop
void matrix_scan_user(void) {
  // Empty
};

