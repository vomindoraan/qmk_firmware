#include QMK_KEYBOARD_H

enum jj40_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _FUNC
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  FUNC
};

// enum {
//   TD_SCLN_QUOTE = 0,
//   TD_ESC_GRAVE
// };

// qk_tap_dance_action_t tap_dance_actions[] = {
//   //Tap once for Esc, twice for Caps Lock
//   [TD_SCLN_QUOTE]  = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_QUOTE),
//   [TD_ESC_GRAVE]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_GRAVE),
// };


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Ctrl | Alt  | GUI  |Lower |   B  |   N  |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_4x12( \
  KC_GESC, KC_Q,      KC_W,    KC_E,    KC_R,       KC_T,             KC_Y,    KC_U,      KC_I,       KC_O,    KC_P,    KC_BSPC, \
  KC_TAB,  KC_A,      KC_S,    KC_D,    KC_F,       KC_G,             KC_H,    KC_J,      KC_K,       KC_L,    KC_SCLN, KC_ENT, \
  _______, KC_Z,      KC_X,    KC_C,    KC_V,       KC_B,             KC_N,    KC_M,      KC_COMM,    KC_DOT,  KC_SLSH, _______, \
  KC_LCTL, MO(_FUNC),KC_LGUI, KC_LALT, MO(_LOWER), LSFT_T(KC_BSPC),  KC_SPC,  MO(_RAISE), KC_LEFT,    KC_DOWN, KC_UP,   KC_RGHT \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |     |    \  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | |      |      |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_4x12( \
  KC_GRAVE,   KC_EXLM,  KC_AT,      KC_HASH,          KC_DLR,                 KC_PERC,          KC_CIRC,  KC_AMPR,    KC_ASTR,  KC_LPRN,      KC_RPRN,      _______, \
  KC_PSCREEN, _______,  _______,    LALT(LSFT(KC_E)), LALT(LGUI(LSFT(KC_W))), LCTL(LSFT(KC_Z)), _______,  KC_MINUS,   KC_EQUAL, KC_LBRACKET,  KC_RBRACKET,  KC_QUOTE, \
  _______,    _______,  LCTL(KC_X), LCTL(KC_C),       LCTL(KC_V),             LCTL(KC_Z),       KC_INSERT,KC_DELETE,  _______,  _______,      _______,      KC_BSLASH, \
  _______,    _______,  _______,    _______,          _______,                _______,          _______,  _______,    KC_HOME,  KC_PGDOWN,    KC_PGUP,      KC_END \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |     |    \  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | |      |      |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_FUNC] = LAYOUT_ortho_4x12( \
  _______,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7, KC_8,   KC_9,   KC_0,     _______, \
  _______,  RGB_TOG,  RGB_MOD,  _______,  _______,  _______,  _______,  KC_4, KC_5,   KC_6,   KC_MINUS, _______, \
  _______,  BL_TOGG,  BL_INC,   BL_DEC,   BL_STEP,  _______,  _______,  KC_1, KC_2,   KC_3,   KC_SLASH, _______, \
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_0, _______,KC_DOT, KC_ASTR,  _______ \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |      |      |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_4x12( \
	KC_F1,	  KC_F2,	  KC_F3,	        KC_F4,	    KC_F5,	        KC_F6,	        KC_F7,	  KC_F8,	              KC_F9,	              KC_F10,	            KC_F11,	              KC_F12	,	\
	_______,	_______,	KC_MS_WH_LEFT,  KC_MS_UP,   KC_MS_WH_RIGHT, KC_MS_WH_UP,    _______,	KC_MS_BTN1,           KC_MS_BTN3,           KC_MS_BTN2,         LALT(LSFT(KC_UP)),    KC_MS_ACCEL2,	\
	_______,	_______,	KC_MS_LEFT,     KC_MS_DOWN, KC_MS_RIGHT,    KC_MS_WH_DOWN,	_______,	KC_MEDIA_PLAY_PAUSE,  KC_MEDIA_STOP,        KC_APPLICATION,     LALT(LSFT(KC_DOWN)),  KC_MS_ACCEL0,	\
	_______,	_______,	_______,	      _______,	  _______,	      _______,        _______,	_______,	            KC_MEDIA_PREV_TRACK,  KC_AUDIO_VOL_DOWN,  KC_AUDIO_VOL_UP,      KC_MEDIA_NEXT_TRACK	\
)
};

// Loop
void matrix_scan_user(void) {
  // Empty
};

