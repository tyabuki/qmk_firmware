/* Copyright 2018 Eucalyn
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

enum custom_keycodes {
  RGBRST = SAFE_RANGE
};

// Layer Declarations
enum {
    _QUWERTY = 0,
    _FN1 = 1,
    _FN2 = 2,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,--------------------------------------------------------------------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  ||   6  |   7  |   8  |   9  |   0  |   -  |   =  | Bksp |
 * |------+------+------+------+------+------++------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  ||   Y  |   U  |   I  |   O  |   P  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------++------+------+------+------+------+------+------+------|
 * | Caps |   A  |   S  |   D  |   F  |   G  ||   H  |   J  |   K  |   L  |   ;  |   '  |    Enter    |
 * |------+------+------+------+------+------++------+------+------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  ||   N  |   M  |   ,  |   .  |   /  | Fn2  |  Up  |RShift|
 * |-----------------------------------------++-------------------------------------------------------|
 * | Fn1 | LCtrl |  Win  |  LAlt |   Space   ||    Space       | RAlt   | Fn1    | Left | Down |Right |
 * `--------------------------------------------------------------------------------------------------'
*/
  [_QUWERTY] = LAYOUT( \
    KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,   KC_5,        KC_6,    KC_7,     KC_8,    KC_9,     KC_0,    KC_MINS,  KC_EQL,  KC_BSPC,  \
    KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,        KC_Y,    KC_U,     KC_I,    KC_O,     KC_P,    KC_LBRC,  KC_RBRC, KC_BSLS,  \
    KC_CAPS,  KC_A,    KC_S,    KC_D,    KC_F,   KC_G,        KC_H,    KC_J,     KC_K,    KC_L,     KC_SCLN, KC_QUOT,  KC_ENT,  \
    KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,        KC_N,    KC_M,     KC_COMM, KC_DOT,   KC_SLSH, MO(_FN2), KC_UP,   KC_RSFT,   \
    MO(_FN1), KC_LCTL, KC_LWIN, KC_LALT, KC_SPC,              KC_SPC,            KC_RALT, MO(_FN1),          KC_LEFT,  KC_DOWN, KC_RGHT \
  ),
/*
 * Fn1
 * ,--------------------------------------------------------------------------------------------------.
 * | Esc  |  F1  |  F2  |  F3  |  F4  |  F5  ||  F6  |  F7  |  F8  |  F9  | F10  | F11  | F12  | Del  |
 * |------+------+------+------+------+------++------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      ||      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------++------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      ||      |      |      |      |      |      |             |
 * |------+------+------+------+------+------++------+------+------+------+------+------+------+------|
 * | ---- |      |      |      |      |      ||      |      |      |      |      |      | PgUp | ---- |
 * |-----------------------------------------++-------------------------------------------------------|
 * |     | ----- | ----- | ----- | --------- || -------------- | ------ |        | Home | PgDn | End  |
 * `--------------------------------------------------------------------------------------------------'
*/
  [_FN1] = LAYOUT( \
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,          KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    KC_TRNS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, KC_TRNS, \
    XXXXXXX, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                 KC_TRNS,          KC_TRNS, XXXXXXX,          KC_HOME, KC_PGDN, KC_END \
  ),
/*
 * Fn2
 * ,--------------------------------------------------------------------------------------------------.
 * |      | Mute |VolDwn|VolUp |      |BriDwn||BriUp |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------++------+------+------+------+------+------+------+------|
 * |      |BriDwn|BriUp |      |      |      ||      |      |      |      | Mute |VolDwn|VolUp |      |
 * |------+------+------+------+------+------++------+------+------+------+------+------+------+------|
 * |R_TOG |R_RST |R_HUI |R_SAI |R_VAI |      ||      |      |      |      |      |      |             |
 * |------+------+------+------+------+------++------+------+------+------+------+------+------+------|
 * | ---- |R_MOD |R_HUD |R_SAD |R_VAD |      ||      |      |      |      |      |      |      | ---- |
 * |-----------------------------------------++-------------------------------------------------------|
 * |     | ----- | ----- | ----- | --------- || -------------- | ------ |        |      |      |      |
 * `--------------------------------------------------------------------------------------------------'
*/
[_FN2] = LAYOUT( \
    XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, KC_BRIU,        KC_BRID, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,     XXXXXXX,   XXXXXXX, \
    XXXXXXX, KC_BRMD, KC_BRMU, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC__MUTE, KC__VOLDOWN, KC__VOLUP, XXXXXXX, \
    RGB_TOG, RGBRST,  RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,     XXXXXXX,   \
    KC_TRNS, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,     XXXXXXX,   KC_TRNS, \
    XXXXXXX, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                 KC_TRNS,          KC_TRNS, XXXXXXX,           XXXXXXX,     XXXXXXX,   XXXXXXX \
  )
};

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
