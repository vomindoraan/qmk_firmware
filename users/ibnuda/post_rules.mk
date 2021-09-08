SRC += ibnuda.c

ifeq ($(strip $(COMBO_ENABLE)), yes)
	SRC += combo.c
endif
