SRC += d4mation.c \
  tap-hold.c \
  macros.c

ifeq ($(strip $(UNICODE_ENABLE)), yes)
  SRC += zalgo.c
endif

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
  SRC += tap-dance.c
endif
