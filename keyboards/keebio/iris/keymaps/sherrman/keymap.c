#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    ADJUST,
    KC_TMUX_PASTE,
    KC_TMUX_NEXT_WINDOW,
    KC_TMUX_PREV_WINDOW,
    KC_TMUX_NEXT_PANE,
    KC_TMUX_PREV_PANE,
};

#define KX_PST KC_TMUX_PASTE
#define KX_NWIN KC_TMUX_NEXT_WINDOW
#define KX_PWIN KC_TMUX_PREV_WINDOW
#define KX_NPNE KC_TMUX_NEXT_PANE
#define KX_PPNE KC_TMUX_PREV_PANE

#define TMUX_STRING(x) SEND_STRING(SS_LCTRL("]") SS_DELAY(25) x)

#define KC_SCRN_LOCK LGUI(LCTL(KC_PAUSE)) /* Specific to lavastone AwesomeWM setup */

#define SFM_BASE_BACKLIGLHT_LEVEL 1
#define SFM_ELEVATED_BACKLIGHT_LEVEL 3

// RGB timeout feature
#define RGB_TIMEOUT 300                      /* in seconds */
#define _LOCAL_RGBLIGHT_MINIMUM 75           /* see RGBLIGHT_LIMIT_VAL (255) */
#define _LOCAL_RGBLIGHT_TRANSITION_TIME 1750 /* ms */
#define _LOCAL_RGBLIGHT_TRANSITION_INTERVAL _LOCAL_RGBLIGHT_TRANSITION_TIME / ((RGBLIGHT_LIMIT_VAL - _LOCAL_RGBLIGHT_MINIMUM) / RGBLIGHT_VAL_STEP)
static uint32_t idle_timer          = 0;
static bool     idling              = false;
static uint16_t rgblight_transit_ms = 0;

void rgblight_increase_to_val(uint8_t val);
void rgblight_lower_to_val(uint8_t val);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off

  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
  //   ESC   |   1    |   2    |   3    |    4   |    5   |                          |    6   |   7    |   8    |   9    |   0    |   _/-  |
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
  //|  TAB   |   Q    |   W    |   E    |    R   |    T   |                          |    Y   |   U    |   I    |   O    |   P    |  BKSPC |
      KC_TAB,  KC_Q,    KC_W,     KC_E,   KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,   KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
  //|  CTRL  |   A    |   S    |   D    |    F   |    G   |                          |    H   |   J    |   K    |   L    |   :/;  |   "/'  |
     KC_LCTL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
  //|        |   Z    |   X    |   C    |    V   |    B   |  GUI            |        |    N   |   M    |   </,  |  >/.   |  ?-/   | SHIFT  |
      LOWER,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LGUI,          RAISE,   KC_N,    KC_M,  KC_COMM, KC_DOT,   KC_SLSH, KC_RSFT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
  //                               |  ALT   | LSHIFT | BKSPACE|                 | SPACE  |  ENTER |  CTRL  |
                                    KC_LALT, KC_LSFT, KC_BSPC,                   KC_SPC,  KC_ENT,   KC_LCTL
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),
 
  [_RAISE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
  //|  F12   |   F1   |   F2   |   F3   |    F4  |   F5   |                          |   F6   |   F7   |   F8   |   F9   |   F10  |   F11  |
      KC_F12,  KC_F1,    KC_F2,  KC_F3,   KC_F4,   KC_F5,                              KC_F6,    KC_F7,   KC_F8,  KC_F9,   KC_F10,  KC_F11,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
  //|  TAB   |   `/~  |    @   |   {    |   }    |   \-|  |                          |   <|   |  PGUP  |   ↑    |  PGDN  |   |>   |  VOLUP |
     _______,  KC_GRV,   KC_AT,  KC_LCBR, KC_RCBR, KC_BSLS,                           KC_MPRV, KC_PGUP,  KC_UP,  KC_PGDN, KC_MNXT, KC__VOLUP,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
  //|  CTRL  |   +/=  |    $   |   [    |   ]    |   +/=  |                          |   ALT  |    ←   |   ↓    |    →   |  || >  |  VOLDN |
     _______, KC_EQL,   KC_DLR, KC_LBRC, KC_RBRC,  KC_EQL,                            KC_RALT, KC_LEFT,KC_DOWN, KC_RGHT, KC_MPLY,  KC__VOLDOWN,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
  //|        |    %   |    ^   |   (    |   )    |    ~   |        |        |        |   GUI  |   INS  |  HOME  |  END   |  MUTE  |  SHIFT |
     _______, KC_PERC, KC_CIRC, KC_LPRN, KC_RPRN, KC_TILD,  _______,          _______,KC_RGUI, KC_INS, KC_HOME,  KC_END, KC__MUTE, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
  //                               |        |        |   DEL  |                 | SPACE  |        |  CTRL  |
                                    _______, _______,  KC_DEL,                   _______, _______,  KC_RCTL
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  // tmux shortcuts
  // Lower + v   -> C-]
  // Lower + c   -> C-] [
  [_LOWER] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
  //|        |        |        |        |        |        |                          |        |   7    |    8   |    9   |    *   |    /   |
     XXXXXXX, DM_PLY1, DM_PLY2,  XXXXXXX, XXXXXXX, XXXXXXX,                           XXXXXXX,  KC_P7,   KC_P8,   KC_P9,  KC_PAST, KC_PSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
  //|        |        |        |        |        |        |                          |        |    4   |    5   |    6   |    +   |    -   |
     DM_RSTP, DM_REC1, DM_REC2, KX_PWIN, KX_NWIN, XXXXXXX,                            KC_NLCK,  KC_P4,   KC_P5,   KC_P6,  KC_PPLS, KC_PMNS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
  //|        |        |        |        |        |        |                          |        |    1   |    2   |    3   |        |        |
     XXXXXXX, XXXXXXX, XXXXXXX, KX_PPNE, KX_NPNE,  XXXXXXX,                           XXXXXXX,  KC_P1,   KC_P2,   KC_P3,  XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
  //|        |        |        |        |        |        |        |        |        |        |   0    |    .   | ENTER  |   =    |        |
      _______, XXXXXXX, XXXXXXX, XXXXXXX, KX_PST,  XXXXXXX, _______,       _______,  XXXXXXX, KC_P0,   KC_PDOT, KC_PENT, KC_PEQL, XXXXXXX,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
  //                               |        |        | SPACE  |                 | SPACE  |        | RCTRL  |
                                    _______, KC_CAPS,  KC_SPC,                   _______, _______,  KC_RCTL
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_ADJUST] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
  //|        |        |        |        |        |        |                          |        |   7    |    8   |    9   |    *   |    /   |
     XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,                           XXXXXXX,   KC_P7,   KC_P8,   KC_P9,  KC_PAST, KC_PSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
  //|        |        |        |        |        |        |                          |        |    4   |    5   |    6   |    +   |    -   |
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,                           XXXXXXX,   KC_P4,   KC_P5,   KC_P6,  KC_PPLS, KC_PMNS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
  //|        |        |        |        |        |        |                          |        |    1   |    2   |    3   |        |        |
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_SCRN_LOCK,                      XXXXXXX,  KC_P1,   KC_P2,   KC_P3,  XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
  //|        |        |        |        |        |        |        |        |        |        |   0    |    .   | ENTER  |   =    |        |
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,         _______,  XXXXXXX, KC_P0,   KC_PDOT, KC_PENT, KC_PEQL, XXXXXXX,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
  //                               |  ALT   | LSHIFT | BKSPACE|                 | SPACE  | ENTER  | SHIFT  |
                                    _______, _______, _______,                   _______, _______, KC_RSFT
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),
    // clang-format on
};

void keyboard_post_init_user(void) {
    backlight_enable();
    backlight_level(SFM_BASE_BACKLIGLHT_LEVEL);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL + 4);

    idle_timer = timer_read32();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        if (idling) {
            idling              = false;
            rgblight_transit_ms = timer_read();
        }
        idle_timer = timer_read32();
    }

    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
            break;
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);

                // Enable numlock
                led_t led_state = host_keyboard_led_state();
                if (!led_state.num_lock) {
                    tap_code(KC_NUMLOCK);
                }
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
            break;

            /* TMUX helpers */
        case KC_TMUX_PASTE:
            if (record->event.pressed) {
                TMUX_STRING("P");
            }
            return false;
        case KC_TMUX_NEXT_WINDOW:
            if (record->event.pressed) {
                TMUX_STRING("n");
            }
            return false;
        case KC_TMUX_PREV_WINDOW:
            if (record->event.pressed) {
                TMUX_STRING("p");
            }
            return false;
        case KC_TMUX_NEXT_PANE:
            if (record->event.pressed) {
                TMUX_STRING("j");
            }
            return false;
        case KC_TMUX_PREV_PANE:
            if (record->event.pressed) {
                TMUX_STRING("l");
            }
            return false;
    }
    return true;
}

uint32_t layer_state_set_user(uint32_t state) {
    switch (get_highest_layer(state)) {
        case _QWERTY:
            rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL + 4);
            break;
        case _LOWER:
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
            rgblight_sethsv_noeeprom(HSV_GREEN);
            break;
        case _RAISE:
            rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_MOOD + 2);
            break;
        case _ADJUST:
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
            rgblight_sethsv_noeeprom(HSV_ORANGE);
            break;
        default:
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_GRADIENT);
            rgblight_sethsv_noeeprom(RGB_TURQUOISE);
            break;
    }
    return state;
}

bool led_update_user(led_t led_state) {
    if (led_state.caps_lock) {
        backlight_level(SFM_ELEVATED_BACKLIGHT_LEVEL);
    } else {
        backlight_level(SFM_BASE_BACKLIGLHT_LEVEL);
    }

    return true;
}

void matrix_scan_user(void) {
    if (idle_timer == 0) {
        idle_timer = timer_read32();
    }

    if (!idling && timer_elapsed32(idle_timer) >= (RGB_TIMEOUT * (uint32_t)1000)) {
        backlight_disable();
        idling              = true;
        rgblight_transit_ms = timer_read();
    }

    if (idling) {
        rgblight_lower_to_val(_LOCAL_RGBLIGHT_MINIMUM);
    } else {
        rgblight_increase_to_val(RGBLIGHT_LIMIT_VAL);

        if (!is_backlight_enabled()) {
            backlight_enable();
        }
    }
}

void rgblight_lower_to_val(uint8_t val) {
    if (rgblight_transit_ms == 0) return;

    if (rgblight_get_val() <= val) {
        rgblight_transit_ms = 0;
        return;
    }
    if (timer_elapsed(rgblight_transit_ms) > _LOCAL_RGBLIGHT_TRANSITION_INTERVAL) {
        rgblight_decrease_val_noeeprom();
        rgblight_transit_ms = timer_read();
    }
}

void rgblight_increase_to_val(uint8_t val) {
    if (rgblight_transit_ms == 0) return;

    if (rgblight_get_val() >= val) {
        rgblight_transit_ms = 0;
        return;
    }

    if (timer_elapsed(rgblight_transit_ms) > _LOCAL_RGBLIGHT_TRANSITION_INTERVAL) {
        rgblight_increase_val_noeeprom();
        rgblight_transit_ms = timer_read();
    }
}

void dynamic_macro_record_start_user(void) {
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_sethsv_noeeprom(HSV_PINK);
}
