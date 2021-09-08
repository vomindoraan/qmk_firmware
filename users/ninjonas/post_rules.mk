SRC += ninjonas.c \
       process_records.c \
       tap_dances.c \
       oled.c \
       encoder.c \
       combos.c

ifneq ("$(wildcard $(USER_PATH)/secrets.c)","")
    SRC += secrets.c
endif
