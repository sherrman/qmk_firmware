#include "sixshooter.h"

extern inline void sixshooter_led_0_on(void);
extern inline void sixshooter_led_1_on(void);
extern inline void sixshooter_led_2_on(void);
extern inline void sixshooter_led_3_on(void);
extern inline void sixshooter_led_4_on(void);
extern inline void sixshooter_led_5_on(void);

extern inline void sixshooter_led_0_off(void);
extern inline void sixshooter_led_1_off(void);
extern inline void sixshooter_led_2_off(void);
extern inline void sixshooter_led_3_off(void);
extern inline void sixshooter_led_4_off(void);
extern inline void sixshooter_led_5_off(void);

extern inline void sixshooter_led_all_on(void);
extern inline void sixshooter_led_all_off(void);

/* LEADER_EXTERNS(); */


#define _BL 0
#define _AWM_SCREENS 1

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up

	matrix_init_user();
}

void matrix_scan_kb(void) {
	// put your looping keyboard code here
	// runs every cycle (a lot)

	matrix_scan_user();
}

static void awesomewm_change_screen(uint16_t screen_keycode) {
  register_code(KC_LGUI);
  register_code(screen_keycode);
  unregister_code(screen_keycode);
  unregister_code(KC_LGUI);
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
	// put your per-action keyboard code here
	// runs for every action, just before processing by the firmware
  if (record->event.pressed) {

    /* Check for custom keycodes for turning on and off LEDs */
    switch(keycode) {
    case SS_001:
      awesomewm_change_screen(KC_1);
      return false;
    case SS_010:
      awesomewm_change_screen(KC_2);
      return false;
    case SS_011:
      awesomewm_change_screen(KC_3);
      return false;
    case SS_100:
      awesomewm_change_screen(KC_4);
      return false;
    case SS_LON:
      sixshooter_led_all_on();
      return false;
    case SS_LOFF:
      sixshooter_led_all_off();
      return false;
    }
  }

	return process_record_user(keycode, record);
}

uint32_t layer_state_set_user(uint32_t state) {
  switch(biton32(state)) {
  case _BL:
    sixshooter_led_all_on();
    break;
  case _AWM_SCREENS:
    sixshooter_led_0_off();
    break;
  }
  return state;
}

void led_set_kb(uint8_t usb_led) {
	// put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

	led_set_user(usb_led);
}

void matrix_scan_user(void) {
  /* LEADER_DICTIONARY() { */
  /*   leading = false; */
  /*   leader_end(); */

  /*   SEQ_ONE */
  /* } */
}
