# Unconditionally disable features that a keyboard advertises it doesn't support

FEATURE_NAMES :=
FEATURE_NAMES += ADAFRUIT_BLE
FEATURE_NAMES += AUDIO
FEATURE_NAMES += BACKLIGHT
FEATURE_NAMES += BLUETOOTH
FEATURE_NAMES += DIP_SWITCH
FEATURE_NAMES += DYNAMIC_KEYMAP
FEATURE_NAMES += ENCODER
FEATURE_NAMES += HAPTIC
FEATURE_NAMES += HD44780
FEATURE_NAMES += IOS_DEVICE
FEATURE_NAMES += LCD_BACKLIGHT
FEATURE_NAMES += LCD
FEATURE_NAMES += OLED
FEATURE_NAMES += PRINTING
FEATURE_NAMES += PS2_MOUSE
FEATURE_NAMES += RGBLIGHT
FEATURE_NAMES += RGB_MATRIX
FEATURE_NAMES += STENO
FEATURE_NAMES += SWAP_HANDS
FEATURE_NAMES += VISUALIZER
FEATURE_NAMES += WATCHDOG
FEATURE_NAMES += XT

$(foreach AFEATURE,$(FEATURE_NAMES),\
	 $(if $(filter $($(AFEATURE)_SUPPORTED),no),$(eval $(AFEATURE)_ENABLE=no)))
