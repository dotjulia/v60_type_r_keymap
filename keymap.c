/* Copyright 2017 benlyall, MechMerlin
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

/* This is the default ANSI layout provided by the KBP V60 Type R
* as depicted in their manual and on the stock keycaps.
*/
#include QMK_KEYBOARD_H
#include "raw_hid.h"

enum macros {
  BL_TEST,
  CBL_TOGG,
  CBL_OFF,
};

//const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt);

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch(id) {
    case BL_TEST: {
      if(record->event.pressed) {
        char c[10];
        sprintf(c, "%d", get_backlight_level());
        send_string(c);
        backlight_level(3);
        return false;
      }
    }
    break;
    case CBL_TOGG: {
      if(record->event.pressed) {
        if(get_backlight_level() < 3) {
          backlight_level(3);
        } else {
          backlight_level(0);
        }
        return false;
      }
    }
    break;
  }
  return MACRO_NONE;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap 0: Default Layer (Qwerty)
   * ,-----------------------------------------------------------.
   * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|   Bs  |
   * |-----------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|
   * |-----------------------------------------------------------|
   * |Caps   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |
   * |-----------------------------------------------------------|
   * |LShift  |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /| RShift   |
   * |-----------------------------------------------------------|
   * |Ctrl|Gui |Alt |      Space              |Fn0 |Gui |App|Ctrl|
   * `-----------------------------------------------------------'
   */
  [0] = LAYOUT_60_ansi(
	       KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, \
	       KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, \
	       KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  \
	       KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,   \
	       KC_LCTL, KC_LGUI, KC_LALT,          KC_SPC,                                      MO(1),   KC_RGUI, KC_APP,  KC_RCTL),

  /* Keymap 1: FN Layer
   * ,-----------------------------------------------------------.
   * |`  | F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|  Del  |
   * |-----------------------------------------------------------|
   * |     |   |Up |   |   |   |   |   |Prt|Scl|Pau|Up|   | Ins  |
   * |-----------------------------------------------------------|
   * |      |Prv|Pse|Nxt|   |   |   |   |Hme|PgU|Lef|Rig|        |
   * |-----------------------------------------------------------|
   * |        |   | TM|BOF|BON|VolD|VolU|Mut|End|PgD|Dwn|        |
   * |-----------------------------------------------------------|
   * |    |    |    |                        |    |    |    |    |
   * `-----------------------------------------------------------'
   */
  [1] = LAYOUT_60_ansi(
	       KC_GRV,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,  KC_DEL, \
	       KC_TRNS,   KC_TRNS,  KC_UP,    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS, KC_PSCR, KC_SLCK, KC_PAUS, KC_UP,    KC_TRNS,          KC_INS, \
	       KC_TRNS,   KC_MEDIA_PREV_TRACK,  KC_MEDIA_PLAY_PAUSE,  KC_MEDIA_NEXT_TRACK, KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS, KC_HOME, KC_PGUP, KC_LEFT, KC_RIGHT,          KC_TRNS,          \
	       KC_TRNS,   KC_TRNS,  M(BL_TEST),  RGB_TOG,  M(CBL_TOGG),  KC_VOLD,   KC_VOLU, KC_MUTE, KC_END,  KC_PGDN,  KC_DOWN,           KC_TRNS,  \
	       KC_TRNS,   KC_TRNS,  KC_TRNS,            KC_TRNS,                                                           KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS),

};

// Data:
// e r g b l
/*
 * [0] r - red
 * [1] g - green
 * [2] b - blue
 * [3] l - level (3 = off, 0 = on)
 */
void raw_hid_receive(uint8_t *data, uint8_t length) {
  backlight_level(data[3]);
  rgblight_setrgb(data[0], data[1], data[2]);
  raw_hid_send(1, 1);
}

// void led_set_user(uint8_t usb_led) {

// }