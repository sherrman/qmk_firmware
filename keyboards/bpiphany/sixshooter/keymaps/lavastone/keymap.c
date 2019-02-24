/* Copyright 2018 QMK Community
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
#include "quantum.h"

#define _BL 0
#define _AWM_SCREENS 1

enum screen_binary {
  SCREEN3,
  OH010,
  OH100,
  OH101,
};

const uint16_t PROGMEM screen3_combo[] = { SS_010, SS_001, COMBO_END };

combo_t key_combos[COMBO_COUNT] = {
  [SCREEN3] = COMBO_ACTION(screen3_combo),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap 0: 
     * ,-----------.
     * |Mut| V-| V+|
     * |---+---+---|
     * |Prv|Ply|Nxt|
     * `-----------'
     */
  [_BL] = LAYOUT
  ( /* Base */
   LGUI(KC_LEFT), LGUI(KC_RIGHT), TO(_AWM_SCREENS),
   SS_100, SS_010, SS_001
  ),
  [_AWM_SCREENS] = LAYOUT
  (
   SS_LON, SS_LOFF, TO(_BL),
   SS_100, SS_010, SS_001
  ),
};

static void awesomewm_change_screen(uint16_t screen_keycode) {
  register_code(KC_LGUI);
  register_code(screen_keycode);
  unregister_code(screen_keycode);
  unregister_code(KC_LGUI);
}

void process_combo_event(uint8_t combo_index, bool pressed) {
  if (!pressed) {
    return;
  }

  switch (combo_index) {
  case SCREEN3:
    awesomewm_change_screen(KC_3);
    break;
  }
}

void matrix_init_user(void) {
  /* Default all LEDs to on */
  sixshooter_led_all_on();
}
