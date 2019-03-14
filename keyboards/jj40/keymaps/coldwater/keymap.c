#include QMK_KEYBOARD_H

enum jj40_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _FUNCT,
  _MOUSE
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  FUNCT,
  MOUSE
};

enum {
  TD_Q_MIN = 0,
  TD_S_BSL,
  TD_PL_NX,
  TD_ST_PR,
  TD_LC_CA,
  TD_F4_ALTF4,
  TD_C_SCL,
  TD_D_CL
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_Q_MIN]  = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_MINS),
  [TD_S_BSL]  = ACTION_TAP_DANCE_DOUBLE(KC_SLASH, KC_BSLASH),
  [TD_PL_NX]  = ACTION_TAP_DANCE_DOUBLE(KC_MPLY, KC_MNXT),
  [TD_ST_PR]  = ACTION_TAP_DANCE_DOUBLE(KC_MSTP, KC_MPRV),
  [TD_LC_CA]  = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, LCTL(KC_A)),
  [TD_C_SCL]  = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_SCLN),
  [TD_D_CL]  = ACTION_TAP_DANCE_DOUBLE(KC_DOT, LSFT(KC_SCLN)),
  [TD_F4_ALTF4]  = ACTION_TAP_DANCE_DOUBLE(KC_F4, LALT(KC_F4))
// Other declarations would go here, separated by commas, if you have them
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define FUNCT MO(_FUNCT)
#define MOUSE MO(_MOUSE)
#define LOWDEL LT(_LOWER, KC_DELETE)
#define RAISENT LT(_RAISE, KC_ENT)
#define MSESC LT(_MOUSE, KC_ESC)
#define FNTAB LT(_FUNCT, KC_TAB)
#define SHT_BSP LSFT_T(KC_BSPC)
#define CMD_BSP LGUI_T(KC_BSPC)
#define CMD_SPC LGUI_T(KC_SPC)  // unused atm
#define CMD_LEFT LGUI_T(KC_LEFT)
#define SHT_SPC LSFT_T(KC_SPC)
#define DIVVY LALT(LGUI(LSFT(KC_D)))
#define F_CHR LALT(LSFT(KC_E))
#define F_WIN LALT(LGUI(LSFT(KC_W)))
#define CTLA CTL_T(KC_A)
#define CTLO CTL_T(KC_O)
#define GUIR GUI_T(KC_R)
#define GUII GUI_T(KC_I)
#define ALTS ALT_T(KC_S)
#define ALTE ALT_T(KC_E)
#define SFTT SFT_T(KC_T)
#define SFTN SFT_T(KC_N)

#define ALLP ALT_T(KC_LBRC)
#define SFRP SFT_T(KC_RBRC)

#define SF4 SFT_T(KC_4)
#define AL5 ALT_T(KC_5)
#define GUI6 GUI_T(KC_6)
#define CMIN CTL_T(KC_MINUS)
#define CZ LCTL(KC_Z)
#define CX LCTL(KC_X)
#define CC LCTL(KC_C)
#define CV LCTL(KC_V)
#define TDQMIN TD(TD_Q_MIN)
#define TDSLBS TD(TD_S_BSL)
#define TDPLNX TD(TD_PL_NX)
#define TDSTPR TD(TD_ST_PR)
#define TDLCCA TD(TD_LC_CA)
#define TDF4AF4 TD(TD_F4_ALTF4)
#define TDCSCL TD(TD_C_SCL)
#define TDDCL TD(TD_D_CL)
#define xxxxx KC_NO





const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_ortho_4x12(
  KC_Q,     KC_W,     KC_F,     KC_P,     KC_B,     TDSTPR,   TDPLNX,   KC_J,    KC_L,      KC_U,     KC_Y,     TDQMIN, \
  CTLA,     GUIR,     ALTS,     SFTT,     KC_G,     KC_BRID,  KC_BRIU,  KC_M,    SFTN,      ALTE,     GUII,     CTLO, \
  KC_Z,     KC_X,     KC_C,     KC_D,     KC_V,     KC_VOLD,  KC_VOLU,  KC_K,    KC_H,      TDCSCL,   TDDCL,    TDSLBS, \
  xxxxx,    xxxxx,    MSESC,    LOWDEL,   SHT_BSP,  KC_TAB,   xxxxx,    KC_SPC,  RAISENT,   FNTAB,    xxxxx,    xxxxx \
),

[_LOWER] = LAYOUT_ortho_4x12(
  KC_GRV,   xxxxx,    KC_LPRN,  KC_RPRN,  xxxxx,    xxxxx,    xxxxx,    xxxxx,    KC_7,     KC_8,     KC_9,     KC_EQL, \
  TDLCCA, 	KC_LWIN,  ALLP,     SFRP,     KC_TAB,   xxxxx,    xxxxx,    xxxxx,    SF4,      AL5,      GUI6,     CMIN, \
  CZ,       CX,       CC,       KC_PSCR,  CV,       xxxxx,    xxxxx,    xxxxx,    KC_1,     KC_2,     KC_3,     KC_SLSH,  \
  xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,    KC_0,     xxxxx,    KC_DOT,   xxxxx  \
),

[_RAISE] = LAYOUT_ortho_4x12(
	DIVVY,    F_CHR,    F_WIN,    xxxxx,    xxxxx,    xxxxx,    xxxxx,    KC_PGUP,	KC_HOME,  KC_UP,    KC_END,   xxxxx,  \
	KC_LCTL,	KC_LWIN,  KC_LALT,  KC_LSFT,  xxxxx,    xxxxx,    xxxxx,    KC_PGDN,  KC_LEFT,  KC_DOWN,  KC_RGHT,	KC_INS,  \
	xxxxx,  	KC_X,     xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,  	xxxxx,    xxxxx,    xxxxx,    xxxxx,   	xxxxx,    \
	xxxxx,  	xxxxx,    _______,  _______,  xxxxx,    xxxxx,    xxxxx,  	xxxxx,    xxxxx,    xxxxx,    xxxxx,  	xxxxx  \
),

[_FUNCT] = LAYOUT_ortho_4x12(
	xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,    KC_F7,    KC_F8,    KC_F9,    KC_F10,	\
	KC_LCTL,	KC_LWIN,  KC_LALT,  KC_LSFT,  xxxxx,    xxxxx,  	xxxxx,    xxxxx,    TDF4AF4,  KC_F5,    KC_F6,    KC_F11,	\
	xxxxx,  	xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,  	xxxxx,    xxxxx,    KC_F1,    KC_F2,    KC_F3,    KC_F12,	\
	xxxxx,  	xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,  	xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx	\
),

[_MOUSE] = LAYOUT_ortho_4x12(
	xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,  	KC_WH_U,  KC_WH_L,  KC_MS_U,  KC_WH_R,  xxxxx,   \
	KC_LCTL,	KC_LWIN,  KC_LALT,  KC_LSFT,  xxxxx,    xxxxx,    xxxxx,  	KC_WH_D,  KC_MS_L,  KC_MS_D,  KC_MS_R,  KC_LCTL, \
	xxxxx,  	xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,  	xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,   \
	xxxxx,  	xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,    xxxxx,    KC_BTN1,  KC_BTN2,  xxxxx,    xxxxx,    xxxxx \
)
};

// Loop
void matrix_scan_user(void) {
  // Empty
};

