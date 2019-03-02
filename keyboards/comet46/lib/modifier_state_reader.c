#include <stdio.h>
#include "comet46.h"

char modifier_state_str[22];

const char *read_modifier_state(void) {
  uint8_t mods = get_all_mods();

  snprintf(modifier_state_str, sizeof(modifier_state_str), "Mods: %s %s %s %s",
    (mods & MOD_MASK_CTRL ) ? "CTL" : "   ",
    (mods & MOD_MASK_GUI  ) ? "GUI" : "   ",
    (mods & MOD_MASK_ALT  ) ? "ALT" : "   ",
    (mods & MOD_MASK_SHIFT) ? "SFT" : "   "
  );

  return modifier_state_str;
}
