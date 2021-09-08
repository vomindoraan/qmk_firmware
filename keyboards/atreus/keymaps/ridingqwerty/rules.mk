# MCU name
MCU = STM32F303
BOARD = QMK_PROTON_C

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
#   comment out to disable the options.
#
BACKLIGHT_ENABLE = no
# MAINTAINERS' NOTE: The following flag has been disabled because it clashes with the default value set in your userspace rules.mk (see that file for more info).
#                    If you're sure you want to change the behavior that your keymap has had thus far, you may uncomment the following line and delete this note.
#BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no # Mouse keys
EXTRAKEY_ENABLE = yes # Audio control and System control
CONSOLE_ENABLE = no  # Console for debug
COMMAND_ENABLE = no    # Commands for debug and configuration
NKRO_ENABLE = yes     # USB Nkey Rollover
AUDIO_ENABLE = yes   # Doot
RGBLIGHT_ENABLE = no
# MAINTAINERS' NOTE: The following flag has been disabled because it clashes with the default value set in your userspace rules.mk (see that file for more info).
#                    If you're sure you want to change the behavior that your keymap has had thus far, you may uncomment the following line and delete this note.
#TAP_DANCE_ENABLE = no
UNICODE_ENABLE = no
UNICODEMAP_ENABLE = yes
