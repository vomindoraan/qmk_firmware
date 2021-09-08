SRC += xulkal.c \
    process_records.c \
    custom_tap_dance.c

ifneq ($(strip $(DISABLE_LTO)), yes)
  EXTRAFLAGS += -flto
  OPT_DEFS += -DNO_ACTION_MACRO
  OPT_DEFS += -DNO_ACTION_FUNCTION
endif

ifeq ($(strip $(ENCODER_ENABLE)), yes)
  SRC += custom_encoder.c
endif

ifneq ($(strip $(RGB_MATRIX_ENABLE)), no)
  OPT_DEFS += -DRGB_ENABLE
  SRC += custom_rgb.c
endif

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
  OPT_DEFS += -DRGB_ENABLE
  SRC += custom_rgb.c
endif

ifeq ($(strip $(OLED_ENABLE)), yes)
  SRC += custom_oled.c
endif
