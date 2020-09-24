#pragma once

#include "config_common.h"

#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x3003
#define DEVICE_VER      0x0001
#define MANUFACTURER    Harry Harrison
#define PRODUCT         StripLamp
#define DESCRIPTION     Lamp

#define MATRIX_ROWS 1
#define MATRIX_COLS 2

#define DIODE_DIRECTION COL2ROW

#define MATRIX_ROW_PINS { B0 }
#define MATRIX_COL_PINS { F4, F5 }
#define ENCODERS_PAD_A { D1, D4 }
#define ENCODERS_PAD_B { D0, C6 }

#define DEBOUNCE 5

#define RGB_DI_PIN D3
#define UNUSED_PINS

// #define RGBLIGHT_ANIMATIONS
#undef RGBLED_NUM
#define RGBLED_NUM 93
#define RGBLIGHT_LIMIT_VAL 255
// 5 steps for saturation control
#define RGBLIGHT_HUE_STEP 10
// 5 steps for saturation control
#define RGBLIGHT_SAT_STEP 51
// 5 Steps for brightness control
#define RGBLIGHT_VAL_STEP 51
