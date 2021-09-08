RGB_MATRIX_ENABLE = yes
# MAINTAINERS' NOTE: The following flag has been disabled because it clashes with the default value set in your userspace rules.mk (see that file for more info).
#                    If you're sure you want to change the behavior that your keymap has had thus far, you may uncomment the following line and delete this note.
#MOUSEKEY_ENABLE = no
OLED_ENABLE = yes
OLED_DRIVER = SSD1306
LTO_ENABLE = yes

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no    # Breathing sleep LED during USB suspend
