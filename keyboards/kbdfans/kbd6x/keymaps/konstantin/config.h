#pragma once

#define DYNAMIC_KEYMAP_LAYER_COUNT 4

#define LAYER_NUMPAD
#define LAYER_FN

#define RGB_INDICATORS                       \
    {                                        \
        .layer = L_NUMPAD,                   \
        .mode  = RGBLIGHT_MODE_STATIC_LIGHT, \
        .color = { SERIKA_YELLOW },          \
    },                                       \
    {                                        \
        .layer = L_FN,                       \
        .mode  = RGBLIGHT_MODE_STATIC_LIGHT, \
        .color = { MODERN_DOLCH_RED },       \
    },                                       \
    {                                        \
        .led   = LED_CAPS_LOCK,              \
        .mode  = RGBLIGHT_MODE_STATIC_LIGHT, \
        .color = { MODERN_DOLCH_CYAN },      \
    },
