#include QMK_KEYBOARD_H

/* LAYER 1
  * /-------+-------\
  * |RGB_TOG|RGB_MOD|
  * \-------+-------/
  */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(RGB_TOG, RGB_MOD) \
};

void encoder_update_user(uint8_t index, _Bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            rgblight_increase_val();
        } else {
            rgblight_decrease_val();
        }
    }
    else if (index == 1) {
        if (clockwise) {
            rgblight_increase_hue();
        } else {
            rgblight_decrease_hue();
        }
    }
}
