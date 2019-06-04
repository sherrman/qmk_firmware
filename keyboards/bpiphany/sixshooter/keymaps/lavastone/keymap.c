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
#include "timer.h"

#define _BL         0
#define _AWM_CLIENT 1
#define _TM         2
#define MOD4 KC_RGUI

#define MAX_KEYPRESS_DIFFERENCE 200 /* In milliseconds */

// Define keyboard specific keycodes for controlling on/off for all LEDs as they
// are all on different pins with this PCB, rather than a single backlight pin
enum custom_keycodes {
  SS_100 = SAFE_RANGE,
  SS_010,
  SS_001,
  SS_TMUX_PASTE,
  SS_TMUX_NEXT_WINDOW,
  SS_TMUX_PREV_WINDOW,
  SS_TMUX_NEXT_PANE,
  SS_TMUX_PREV_PANE,
};

// Declare tap dances
enum tap_dances {
  SSTD_TMUX_PASTE_ENTER = 0,
};

static void tmux_paste_enter(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    SEND_STRING(SS_LCTRL("]") "P");
    reset_tap_dance(state);
  }
  else if (state->count > 1) {
    SEND_STRING(SS_LCTRL("]") "P" SS_TAP(X_ENTER));
    reset_tap_dance(state);
  }
}

// Define tap dances
qk_tap_dance_action_t tap_dance_actions[] = {
  [SSTD_TMUX_PASTE_ENTER] = ACTION_TAP_DANCE_FN(tmux_paste_enter)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Base Layer: AwesomeWM screen controls
   */
  [_BL] = LAYOUT
  ( /* Base */
   RGUI(KC_H), RGUI(KC_L), TO(_AWM_CLIENT),     \
   SS_100,     SS_010,     SS_001
  ),

  /* AwesomeWM Client Layer: Client controls
   */
  [_AWM_CLIENT] = LAYOUT
  (
   RGUI(KC_N), RGUI(KC_ENTER), TO(_TM),         \
   RGUI(KC_K), RGUI(KC_J),     TD(SSTD_TMUX_PASTE_ENTER)
  ),
  /* Tmux: Client controls
   */
  [_TM] = LAYOUT
  (
   SS_TMUX_PREV_WINDOW, SS_TMUX_NEXT_WINDOW, TO(_BL),       \
   SS_TMUX_NEXT_PANE,   SS_TMUX_PREV_PANE,   TD(SSTD_TMUX_PASTE_ENTER)
   ),
};

// There are 3 timers for each 
static uint16_t binary_number_timers[3];

static uint8_t number_from_timers(uint16_t end_time)
{
  uint8_t result = 0x0;
  for (uint8_t i = 0; i < 3; ++i) {
    if (TIMER_DIFF_16(end_time, binary_number_timers[i]) < MAX_KEYPRESS_DIFFERENCE) {
      result |= (1 << i);
    }
  }
  return result;
}

static void reset_binary_number_timers(void) {
  // Initialize timers to 0 (the state that they're off)
  binary_number_timers[0] = 0;
  binary_number_timers[1] = 0;
  binary_number_timers[2] = 0;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	// Put your per-action keyboard code here.
	// Runs for every action, just before processing by the firmware.
  if (record->event.pressed) {

    // Check for custom keycodes for turning on and off LEDs
    switch(keycode) {
    case SS_100:
      binary_number_timers[2] = record->event.time;
      return false;
    case SS_010:
      binary_number_timers[1] = record->event.time;
      return false;
    case SS_001:
      binary_number_timers[0] = record->event.time;
      return false;

    case SS_TMUX_PASTE:
      SEND_STRING(SS_LCTRL("]") "P");
      return false;
    case SS_TMUX_NEXT_WINDOW:
      SEND_STRING(SS_LCTRL("]") "n");
      return false;
    case SS_TMUX_PREV_WINDOW:
      SEND_STRING(SS_LCTRL("]") "p");
      return false;
    case SS_TMUX_NEXT_PANE:
      SEND_STRING(SS_LCTRL("]") "j");
      return false;
    case SS_TMUX_PREV_PANE:
      SEND_STRING(SS_LCTRL("]") "l");
      return false;
    }
  }
  else { // Released
    uint16_t liftoff_time = 0;
    switch(keycode) {
    case SS_100:
    case SS_010:
    case SS_001:
      liftoff_time = record->event.time;
      uint8_t number = number_from_timers(liftoff_time);
      uint16_t kc = KC_1;
      if (number < 1 || number > 7) {
        break;
      }
      kc += number - 1;
      register_code(MOD4);
      register_code(kc);
      unregister_code(kc);
      unregister_code(MOD4);
      reset_binary_number_timers();
      return false;
    }
  }
  return true;
};

void matrix_init_user(void) {
  // Default all LEDs to on
  sixshooter_led_all_on();

  reset_binary_number_timers();
}

uint32_t layer_state_set_user(uint32_t state) {
  switch(biton32(state)) {
  case _BL:
    sixshooter_led_all_on();
    break;
  case _AWM_CLIENT:
    sixshooter_led_0_on();
    sixshooter_led_1_off();
    sixshooter_led_2_on();
    sixshooter_led_3_on();
    sixshooter_led_4_off();
    sixshooter_led_5_on();
    break;
  case _TM:
    sixshooter_led_0_on();
    sixshooter_led_1_on();
    sixshooter_led_2_on();
    sixshooter_led_3_off();
    sixshooter_led_4_on();
    sixshooter_led_5_off();
    break;
  }
  return state;
}
