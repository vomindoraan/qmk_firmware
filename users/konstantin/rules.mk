SRC += konstantin.c
ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
    SRC += features/rgb.c
endif
RGB_MATRIX_ENABLE ?= no
ifneq ($(strip $(RGB_MATRIX_ENABLE)), no)
    SRC += features/rgb.c
endif
ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
    SRC += features/tap_dance.c
endif
ifneq (,$(filter yes,$(UNICODE_ENABLE) $(UNICODEMAP_ENABLE)))
    SRC += features/unicode.c
endif

ifneq ($(PLATFORM),CHIBIOS)
    LTO_ENABLE = yes
endif
