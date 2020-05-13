SRC += konstantin.c
ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
    SRC += rgb.c
endif
RGB_MATRIX_ENABLE ?= no
ifneq ($(strip $(RGB_MATRIX_ENABLE)), no)
    SRC += rgb.c
endif
ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
    SRC += tap_dance.c
endif
ifneq (,$(filter yes,$(UNICODE_ENABLE) $(UNICODEMAP_ENABLE)))
    SRC += unicode.c
endif
# Context: The user konstantin has `BACKLIGHT_ENABLE = yes` in their userspace,
# and is trying to build `make maartenwut/wasdat:konstantin`, a keyboard that
# has `BACKLIGHT_SUPPORTED = no` declared.
# If everything works correctly, at this point in the build (post_keymap.mk),
# the supported flag will have overridden the enable flag and set it to no, so
# the .c file will NOT be included and the build will finish successfully.
# The keyboard's "backlight not supported" flag is respected by default,
# without requiring extra checks in the makefile.
ifeq ($(strip $(BACKLIGHT_ENABLE)), yes)
    SRC += my_backlight.c
endif
