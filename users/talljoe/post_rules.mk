SRC += talljoe.c macros.c $(wildcard users/talljoe/tapdance/*.c)
ifeq ($(strip $(VISUALIZER_ENABLE)), yes)
  SRC += visualizer.c
endif

ifeq ($(strip $(FLASH_BOOTLOADER)), yes)
    OPT_DEFS += -DFLASH_BOOTLOADER
endif

EXTRAFLAGS+=-flto
