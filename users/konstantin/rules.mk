# Generic features
BOOTMAGIC_ENABLE   = no
COMMAND_ENABLE     = yes
CONSOLE_ENABLE     = yes
EXTRAKEY_ENABLE    = yes
MOUSEKEY_ENABLE    = yes
NKRO_ENABLE        = yes
TAP_DANCE_ENABLE   = yes
UNICODEMAP_ENABLE  = yes

# Keyboard-specific feature defaults
BACKLIGHT_ENABLE   = no
RGBLIGHT_ENABLE    = no
RGB_MATRIX_ENABLE  = no

# Firmware size reduction
GRAVE_ESC_ENABLE   = no
MAGIC_ENABLE       = no
SPACE_CADET_ENABLE = no
ifneq ($(PLATFORM),CHIBIOS)
    LTO_ENABLE     = yes
endif
