SRC += sigul.c

ifneq ($(strip $(NO_SECRETS)), yes)
    ifneq ("$(wildcard $(USER_PATH)/secrets.c)","")
        SRC += secrets.c
    endif
endif
