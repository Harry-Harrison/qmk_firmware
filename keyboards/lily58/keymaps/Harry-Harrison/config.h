#pragma once

#define MASTER_LEFT
#define SSD1306OLED
#define USE_SERIAL_PD2

#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_SLEEP
#define RGBLIGHT_SPLIT
#define RGBLED_NUM 4
#define RGBLIGHT_LIMIT_VAL 255
// 5 steps for saturation control
#define RGBLIGHT_HUE_STEP 10
// 5 steps for saturation control
#define RGBLIGHT_SAT_STEP 51
// 5 Steps for brightness control
#define RGBLIGHT_VAL_STEP 51

#undef OLED_FONT_H
#define OLED_FONT_H "keymaps/Harry-Harrison/font.c"
