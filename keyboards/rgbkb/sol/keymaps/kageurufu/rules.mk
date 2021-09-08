# Overridden build options from rev1 & rev2

# Debug Options
CONSOLE_ENABLE          = yes       # Console for debug(+400)
COMMAND_ENABLE          = yes       # Commands for debug and configuration

# RGB Options
RGBLIGHT_ENABLE         = no        # Enable global lighting effects. Do not enable with RGB Matrix
# MAINTAINERS' NOTE: The following flag has been disabled because it clashes with the default value set in your userspace rules.mk (see that file for more info).
#                    If you're sure you want to change the behavior that your keymap has had thus far, you may uncomment the following line and delete this note.
#RGBLIGHT_ANIMATIONS     = no        # LED animations
LED_MIRRORED            = no        # Mirror LEDs across halves (enable DIP 1 on slave, and DIP 2 and 3 on master)
RGB_MATRIX_ENABLE       = yes       # Enable per-key coordinate based RGB effects. Do not enable with RGBlight

# Userspace implements their own LTO
LTO_ENABLE = no



# Do not edit past here

include keyboards/$(KEYBOARD)/post_rules.mk
