#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

#ifdef RGBLIGHT_ENABLE
    // Following line allows macro to read current RGB settings
    extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

// Set those keymaps!
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT( \
        KC_GESC, KC_1, KC_2, KC_3, KC_4, KC_5,                         KC_6, KC_7, KC_8,    KC_9,   KC_0,    KC_EQUAL, \
        KC_TAB,  KC_Q, KC_W, KC_E, KC_R, KC_T,                         KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_MINUS, \
        KC_BSLS, KC_A, KC_S, KC_D, KC_F, KC_G,                         KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_QUOT, \
        KC_LSPO, KC_Z, KC_X, KC_C, KC_V, KC_B, MO(_LOWER), MO(_RAISE), KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSPC, \
                   KC_LCTRL, KC_LALT, KC_LGUI, KC_SPC,         KC_ENT, KC_BSPC, KC_LBRC, KC_RBRC \
    ),
    [_LOWER] = LAYOUT( \
        KC_F1,     KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, \
        XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F12, \
        XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, KC_GRAVE, \
        KC_LSHIFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, KC_MPLY, KC_MPRV, KC_MNXT, XXXXXXX, KC_RSHIFT, \
                    KC_LCTRL, KC_LALT, KC_LGUI, MO(_ADJUST),           KC_ENT, KC_DEL,  KC_BRID, KC_BRIU \
    ),
    [_RAISE] = LAYOUT( \
        KC_F1,     KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6, KC_F7, KC_F8, KC_F9,   KC_F10,  KC_F11, \
        XXXXXXX,   XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX, XXXXXXX,                   KC_P1, KC_P1, KC_P1, XXXXXXX, XXXXXXX, KC_F12, \
        XXXXXXX,   KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX,                   KC_P1, KC_P1, KC_P1, XXXXXXX, XXXXXXX, XXXXXXX, \
        KC_LSHIFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, KC_P1, KC_P2, KC_P3, XXXXXXX, XXXXXXX, KC_RSHIFT, \
                                     KC_LCTRL, KC_LALT, KC_LGUI, KC_SPC,  KC_ENT, KC_BSPC, KC_LBRC, KC_RBRC \
    ),
    [_ADJUST] = LAYOUT( \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K, \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   RGB_M_X, RGB_M_G, RGB_M_T, XXXXXXX,  XXXXXXX,  XXXXXXX, \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, RGB_HUD, RGB_HUI,  XXXXXXX,  XXXXXXX, \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, RGB_TOG, XXXXXXX, XXXXXXX, RGB_SAD, RGB_SAI,  XXXXXXX,  XXXXXXX,\
                                   XXXXXXX, XXXXXXX, XXXXXXX, _______, RGB_MOD, _______, RGB_VAD, RGB_VAI \
    )
};

int RGB_current_mode;

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
    if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
        layer_on(layer3);
    } else {
        layer_off(layer3);
    }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
        RGB_current_mode = rgblight_config.mode;
    #endif
}

#ifdef OLED_DRIVER_ENABLE
    oled_rotation_t oled_init_user(oled_rotation_t rotation) {
        if (!is_keyboard_master()) {
            // Flips the display 180 degrees if not master side
            return OLED_ROTATION_180;
        }
        return rotation;
    }

    // When you add source files to SRC in rules.mk, you can use functions.
    const char *read_layer_state(void);
    const char *read_logo(void);
    void set_keylog(uint16_t keycode, keyrecord_t *record);
    const char *read_keylog(void);
    const char *read_keylogs(void);
    // const char *read_mode_icon(bool swap);
    // const char *read_host_led_state(void);
    // void set_timelog(void);
    // const char *read_timelog(void);

    void oled_task_user(void) {
        if (is_keyboard_master()) {
            // If you want to change the display of OLED, you need to change here
            oled_write_ln(read_layer_state(), false);
            oled_write_ln(read_keylog(), false);
            oled_write_ln(read_keylogs(), false);
            // oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
            // oled_write_ln(read_host_led_state(), false);
            // oled_write_ln(read_timelog(), false);
        } else {
            oled_write(read_logo(), false);
        }
    }

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        #ifdef OLED_DRIVER_ENABLE
            set_keylog(keycode, record);
        #endif
        // set_timelog();
    }

    switch (keycode) {
        case _LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case _RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case _ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
            break;
        }
    return true;
}
