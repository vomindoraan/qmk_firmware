#pragma once

#include "config_common.h"

/* USB Device descriptor parameters */
#define VENDOR_ID    0xFEED
#define PRODUCT_ID   0x6060
#define DEVICE_VER   0x0001
#define MANUFACTURER Greenwald Designs
#define PRODUCT      Waldo
#define DESCRIPTION  A custom 60% board

/* Key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

/* Key matrix pins */
#define MATRIX_ROW_PINS { F0, F1, F4, F5, F6 }
#define MATRIX_COL_PINS { F7, D5, D3, D2, B3, B2, C7, C6, B6, B5, B4, D7, D6, D4, B1 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Backlight parameters */
#define BACKLIGHT_PIN    B7
#define BACKLIGHT_LEVELS 3

// RGB parameters
#define RGB_DI_PIN B0  // The pin the LED strip is connected to
#define RGBLED_NUM 10  // Number of LEDs in your strip

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
