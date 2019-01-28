#pragma once

#include "quantum.h"

#define DST_N_C TD(TD_DST_N_C)

#define RAL_LAL TD(TD_RAL_LAL)
#define RAL_RGU TD(TD_RAL_RGU)
#define RCT_RSF TD(TD_RCT_RSF)

#define FN_RCTL TD(TD_FN_RCTL)
#define LSFT_FN TD(TD_LSFT_FN)

enum tap_dance {
  TD_DST_N_C,

  TD_RAL_LAL,
  TD_RAL_RGU,
  TD_RCT_RSF,

  TD_FN_RCTL,
  TD_LSFT_FN,
};
