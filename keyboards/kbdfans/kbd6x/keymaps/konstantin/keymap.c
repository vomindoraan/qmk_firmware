#include QMK_KEYBOARD_H
#include "konstantin.h"

enum layers_keymap {
    L_RCTRL = LAYERS_KEYMAP,
};

enum keycodes_keymap {
    RCTRL = RANGE_KEYMAP,
};

static void reset_light(void) {
    rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL);
    rgblight_sethsv(MODERN_DOLCH_RED);
}

static void fn_light(void) {
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_sethsv_noeeprom(modern_dolch_red.h, modern_dolch_red.s, rgblight_get_val());
}

static void numpad_light(void) {
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_sethsv_noeeprom(serika_yellow.h, serika_yellow.s, rgblight_get_val());
}

static void caps_light(void) {
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_sethsv_noeeprom(modern_dolch_cyan.h, modern_dolch_cyan.s, rgblight_get_val());
}

static void restore_light(void) {
    rgblight_config_t saved = { .raw = eeconfig_read_rgblight() };
    rgblight_mode_noeeprom(saved.mode);
    rgblight_sethsv_noeeprom(saved.hue, saved.sat, saved.val);
}

typedef enum {
    LH_CAPS = 1,
    LH_NUMPAD,
    LH_FN,

    LH__COUNT = LH_FN
} light_handler;

static light_handler light_handlers[LH__COUNT] = {0};

static void push_light_handler(light_handler lh) {
    light_handler prev = light_handlers[0];
    for (int i = 1; i < LH__COUNT; i++) {
        if (prev == lh) break;
        SWAP(light_handlers[i], prev);
    }
    light_handlers[0] = lh;
}

static void check_light(layer_state_t *pstate, led_t *pleds) {
    layer_state_t state = pstate ? *pstate : layer_state;
    led_t         leds  = pleds  ? *pleds  : host_keyboard_led_state();

    for (int i = 0; i < LH__COUNT && light_handlers[i]; i++) {
        switch (light_handlers[i]) {
        case LH_CAPS:
            if (leds.caps_lock) {
                caps_light();
                return;
            }
            break;
        case LH_NUMPAD:
            if (IS_LAYER_ON_STATE(state, L_NUMPAD)) {
                numpad_light();
                return;
            }
            break;
        case LH_FN:
            if (IS_LAYER_ON_STATE(state, L_FN)) {
                fn_light();
                return;
            }
            break;
        }
    }
    restore_light();
}

void eeconfig_init_keymap(void) {
    reset_light();
}

layer_state_t layer_state_set_keymap(layer_state_t state) {
    static layer_state_t prev_state = L_BASE;

    bool fn_changed =
        IS_LAYER_ON_STATE(state, L_FN)     != IS_LAYER_ON_STATE(prev_state, L_FN);
    bool numpad_changed =
        IS_LAYER_ON_STATE(state, L_NUMPAD) != IS_LAYER_ON_STATE(prev_state, L_NUMPAD);

    if (fn_changed || numpad_changed) {
        push_light_handler(LH_NUMPAD);
        push_light_handler(LH_FN);
        check_light(&state, NULL);
    }
    return prev_state = state;
}

bool led_update_keymap(led_t leds) {
    static led_t prev_leds = { .raw = 0 };

    if (leds.caps_lock != prev_leds.caps_lock) {
        push_light_handler(LH_CAPS);
        check_light(NULL, &leds);
    }
    prev_leds = leds;
    return true;
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case RGB_TOG ... RGB_SPD:
        if (record->event.pressed) {
            // Shift+Toggle = reset RGB
            if (keycode == RGB_TOG && get_mods() & MOD_MASK_SHIFT) {
                reset_light();
                return false;
            }
            restore_light();
        } else {
            check_light(NULL, NULL);
        }
        break;

    // Combined RCtrl and layer
    // Cannot use LM(L_RCTRL, MOD_RCTL) because it sends LCtrl instead of RCtrl
    case RCTRL:
        if (record->event.pressed) {
            register_code(KC_RCTL);
            layer_on(L_RCTRL);
        } else {
            unregister_code(KC_RCTL);
            layer_off(L_RCTRL);
        }
        break;
    }

    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base layer
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Esc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ \ │ ` │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │Bspc │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │LCtCps│ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ Enter  │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
     * │LShiftFn│ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │RShift│FnF│
     * └─────┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴───┴┬───┬─┴───┘
     *       │LGu│LAlt │           Space           │RAlGu│RCt│
     *       └───┴─────┴───────────────────────────┴─────┴───┘
     */
    [L_BASE] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
        LCT_CPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        LSFT_FN, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, FN_FNLK,
        XXXXXXX, KC_LGUI, KC_LALT,                            KC_SPC,                             RAL_RGU, RCTRL,   XXXXXXX
    ),

    /* Numpad layer
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │   │   │   │   │   │   │   │P7 │P8 │P9 │P- │ − │ = │Num│   │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
     * │     │   │   │   │   │   │   │P4 │P5 │P6 │P+ │ ( │ ) │     │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │      │   │   │   │   │   │   │P1 │P2 │P3 │P* │ × │ PEnter │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
     * │        │   │   │   │   │   │P0 │P0 │ , │P. │P/ │  ÷   │   │
     * └─────┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴───┴┬───┬─┴───┘
     *       │   │     │                           │     │   │
     *       └───┴─────┴───────────────────────────┴─────┴───┘
     */
    [L_NUMPAD] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   KC_PMNS, MINUS,   EQUALS,  NUMPAD,  _______,
        _______, _______, _______, _______, _______, _______, _______, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, L_PAREN, R_PAREN, _______,
        _______, _______, _______, _______, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_PAST, TIMES,   KC_PENT,
        _______, _______, _______, _______, _______, _______, KC_P0,   KC_P0,   COMMA,   KC_PDOT, KC_PSLS, DIVIDE,  _______,
        XXXXXXX, _______, _______,                            _______,                            _______, _______, XXXXXXX
    ),

    /* Fn layer
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │   │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│PSc│Ins│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
     * │     │Hom│ ↑ │End│PgU│BrU│   │UCN│   │M1 │M↑ │М2 │M3 │ Del │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │      │ ← │ ↓ │ → │PgD│BrD│   │   │   │M← │M↓ │M→ │        │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
     * │        │Mut│Vo-│Vo+│Ply│Prv│Nxt│App│MW↑│M4 │М5 │      │   │
     * └─────┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴───┴┬───┬─┴───┘
     *       │   │     │            MW↓            │MAcl2│   │
     *       └───┴─────┴───────────────────────────┴─────┴───┘
     */
    [L_FN] = LAYOUT(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_INS,
        _______, KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_BRIU, _______, UC_NEXT, _______, KC_BTN1, KC_MS_U, KC_BTN2, KC_BTN3, KC_DEL,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_BRID, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______,
        _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY, KC_MPRV, KC_MNXT, KC_APP,  KC_WH_U, KC_BTN4, KC_BTN5, _______, _______,
        XXXXXXX, _______, _______,                            KC_WH_D,                            KC_ACL2, _______, XXXXXXX
    ),

    /* RCtrl layer
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │   │   │   │   │   │   │   │   │   │   │   │   │   │Num│Clr│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
     * │     │Top│Mv↑│Btm│TPr│   │   │   │   │   │   │   │   │DelNx│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │      │Mv←│Mv↓│Mv→│TNx│   │   │   │   │   │   │   │        │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
     * │        │RTg│RV-│RV+│RMd│   │   │   │   │   │   │      │   │
     * └─────┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴───┴┬───┬─┴───┘
     *       │DPR│DstNA│                           │RGui │   │
     *       └───┴─────┴───────────────────────────┴─────┴───┘
     */
    [L_RCTRL] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, NUMPAD,  CLEAR,
        _______, TOP,     MV_UP,   BOTTOM,  TAB_PRV, _______, _______, _______, _______, _______, _______, _______, _______, DEL_NXT,
        _______, MV_LEFT, MV_DOWN, MV_RGHT, TAB_NXT, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, RGB_TOG, RGB_VAD, RGB_VAI, RGB_MOD, _______, _______, _______, _______, _______, _______, _______, _______,
        XXXXXXX, DST_P_R, DST_N_A,                            _______,                            KC_RGUI, _______, XXXXXXX
    ),
};
