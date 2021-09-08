SRC += dshields.c

ifeq ($(strip $(KEYBOARD)), planck/rev3)
	AUDIO_ENABLE	  = no
	BACKLIGHT_ENABLE  = yes
	RGB_MATRIX_ENABLE = no
endif
ifeq ($(strip $(KEYBOARD)), planck/rev6)
	CFLAGS           += -Wno-error=deprecated
	EXTRALDFLAGS	  = -Wl,--build-id=none
	AUDIO_ENABLE	  = no
	BACKLIGHT_ENABLE  = no
	RGB_MATRIX_ENABLE = no
endif
ifeq ($(strip $(KEYBOARD)), planck/light)
	AUDIO_ENABLE	  = yes
	BACKLIGHT_ENABLE  = no
	RGB_MATRIX_ENABLE = yes
endif
