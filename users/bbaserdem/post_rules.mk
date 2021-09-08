SRC += bbaserdem.c
EXTRAFLAGS += -flto			# Used to make code smaller

ifndef BLUETOOTH_ENABLE
	BLUETOOTH_ENABLE = no 	# No bluetooth
endif
