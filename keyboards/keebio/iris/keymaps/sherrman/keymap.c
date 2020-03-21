#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum iris_layers { _QWERTY, _LOWER, _RAISE, _ADJUST };

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ADJUST TG(_ADJUST)
/* #define RSFT_BSLS RSFT_T(KC_BSLS) */
#define LCTL_BSLS LCTL_T(KC_BSLS)
/* #define LSFT_ESC LSFT_T(KC_ESC) */

/* #define A_CTL LCTL_T(KC_A) */
/* #define F_SHFT LSFT_T(KC_F) */
/* #define TAB_SHFT LSFT_T(KC_TAB) */

/* #define J_SHFT RSFT_T(KC_J) */

#define KC_SCRN_LOCK LGUI(LCTL(KC_PAUSE))

#define SFM_BASE_BACKLIGLHT_LEVEL 1
#define SFM_ELEVATED_BACKLIGHT_LEVEL 3

typedef struct {
    int state;
} tap;

enum {
    SINGLE_TAP        = 1,
    SINGLE_HOLD       = 2,
    DOUBLE_TAP        = 3,
    DOUBLE_HOLD       = 4,
    DOUBLE_SINGLE_TAP = 5,  // send two single taps
    TRIPLE_TAP        = 6,
    TRIPLE_HOLD       = 7
};

// Tap dance enums
enum { X_SHFT_CAPS = 0 };

int cur_dance(qk_tap_dance_state_t *state);

// for the x tap dance. Put it here so it can be used in any keymap
void x_finished(qk_tap_dance_state_t *state, void *user_data);
void x_reset(qk_tap_dance_state_t *state, void *user_data);

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
  //|  LGUI  |   Z    |   X    |   C    |    V   |    B   |                 |        |    N   |   M    |   </,  |  >/.   |  ?-/   | SHIFT  |
     KC_LGUI,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    LOWER,            RAISE,   KC_N,    KC_M,  KC_COMM, KC_DOT,   KC_SLSH, TD(X_SHFT_CAPS),
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
  //                               |  ALT   | LSHIFT | BKSPACE|                 | SPACE  |  ENTER |   \-|  |
                                    KC_LALT, KC_LSFT, KC_BSPC,                   KC_SPC,  KC_ENT,  LCTL_BSLS
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_RAISE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
  //|  F12   |   F1   |   F2   |   F3   |    F4  |   F5   |                          |   F6   |   F7   |   F8   |   F9   |   F10  |   F11  |
      KC_F12,  KC_F1,    KC_F2,  KC_F3,   KC_F4,   KC_F5,                              KC_F6,    KC_F7,   KC_F8,  KC_F9,   KC_F10,  KC_F11,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
  //|  TAB   |    !   |    @   |   {    |   }    |    |   |                          |   <|   |  PGUP  |   ↑    |  PGDN  |   |>   |  VOLUP |
     _______, KC_EXLM,   KC_AT,  KC_LCBR, KC_RCBR, KC_PIPE,                           KC_MPRV, KC_PGUP,  KC_UP,  KC_PGDN, KC_MNXT, KC__VOLUP,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
  //|  CTRL  |   +/=  |    $   |   (    |   )    |    `   |                          |   ?    |    ←   |   ↓    |    →   |  || >  |  VOLDN |
     _______, KC_EQL,   KC_DLR, KC_LPRN, KC_RPRN,  KC_GRV,                            KC_QUES, KC_LEFT,KC_DOWN, KC_RGHT, KC_MPLY,  KC__VOLDOWN,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
  //|        |    %   |    ^   |   [    |   ]    |    ~   |        |        |        |    &   |   INS  |  HOME  |  END   |  MUTE  |  SHIFT |
     _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD,  _______,          _______, KC_AMPR, KC_INS, KC_HOME,  KC_END, KC__MUTE, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
  //                               |        |        |   DEL  |                 | SPACE  |        |  CTRL  |
                                    _______, _______,  KC_DEL,                   _______, _______,  KC_RCTL
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_LOWER] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
  //|        |        |        |        |        |        |                          |        |   7    |    8   |    9   |    *   |    /   |
     KC_ASUP, KC_ASON, KC_ASRP,  XXXXXXX, XXXXXXX, XXXXXXX,                           XXXXXXX,   KC_P7,   KC_P8,   KC_P9,  KC_PAST, KC_PSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
  //|        |        |        |        |        |        |                          |        |    4   |    5   |    6   |    +   |    -   |
     KC_ASDN, KC_ASOFF, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                           XXXXXXX,  KC_P4,   KC_P5,   KC_P6,  KC_PPLS, KC_PMNS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
  //|        |        |        |        |        |        |                          |        |    1   |    2   |    3   |        |        |
     XXXXXXX, KC_ASTG, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,                           XXXXXXX,  KC_P1,   KC_P2,   KC_P3,  XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
  //|        |        |        |        |        |        |        |        |        |        |   0    |    .   | ENTER  |   =    |        |
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,         _______,  XXXXXXX, KC_P0,   KC_PDOT, KC_PENT, KC_PEQL, XXXXXXX,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
  //                               |        |        | BKSPACE|                 | SPACE  |        |  CTRL  |
                                    _______, _______, _______,                   _______, _______,  KC_RCTL
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_ADJUST] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
  //|        |        |        |        |        |        |                          |        |   7    |    8   |    9   |    *   |    /   |
     KC_ASUP, KC_ASON, KC_ASRP,  XXXXXXX, XXXXXXX, XXXXXXX,                           XXXXXXX,   KC_P7,   KC_P8,   KC_P9,  KC_PAST, KC_PSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
  //|        |        |        |        |        |        |                          |        |    4   |    5   |    6   |    +   |    -   |
     KC_ASDN, KC_ASOFF, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,                           XXXXXXX,  KC_P4,   KC_P5,   KC_P6,  KC_PPLS, KC_PMNS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
  //|        |        |        |        |        |        |                          |        |    1   |    2   |    3   |        |        |
     XXXXXXX, KC_ASTG, XXXXXXX, XXXXXXX, XXXXXXX,  KC_SCRN_LOCK,                       XXXXXXX,  KC_P1,   KC_P2,   KC_P3,  XXXXXXX, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
  //|        |        |        |        |        |        |        |        |        |        |   0    |    .   | ENTER  |   =    |        |
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,         _______,  XXXXXXX, KC_P0,   KC_PDOT, KC_PENT, KC_PEQL, XXXXXXX,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
  //                               |  CTRL  | COMMAND| BKSPACE|                 | SPACE  | ENTER  | SHIFT  |
                                    _______, _______, _______,                   _______, _______, KC_RSFT
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),
    // clang-format on
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        switch (biton32(layer_state)) {
            default:
            case _QWERTY:
                clockwise ? tap_code(KC_MS_WH_UP) : tap_code(KC_MS_WH_DOWN);
                break;
            case _LOWER:
                clockwise ? tap_code(KC_AUDIO_VOL_UP) : tap_code(KC_AUDIO_VOL_DOWN);
                break;
        }
    }
}

/* void encoder_update_user(uint8_t index, bool clockwise) { */
/*     if (index == 0) { */
/*         switch (biton32(layer_state)) { */
/*             default: */
/*             case _QWERTY: */
/*                 clockwise ? tap_code(KC_MS_WH_UP) : tap_code(KC_MS_WH_DOWN); */
/*                 break; */
/*             case _LOWER: */
/*                 clockwise ? tap_code(KC_AUDIO_VOL_UP) : tap_code(KC_AUDIO_VOL_DOWN); */
/*                 break; */
/*         } */
/*     } */
/* } */

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    /* if (!process_record_dynamic_macro(keycode, record)) { */
    /*     return false; */
    /* } */

    switch (keycode) {
        /* case COLEMAK: */
        /*   if (record->event.pressed) { */
        /*     set_single_persistent_default_layer(_COLEMAK); */
        /*   } */
        /*   return false; */
        /*   break; */
        /* case QWERTY: */
        /*   if (record->event.pressed) { */
        /*     set_single_persistent_default_layer(_QWERTY); */
        /*   } */
        /*   return false; */
        /*   break; */
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
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
    }
    return true;
}

uint32_t layer_state_set_user(uint32_t state) {
    switch (get_highest_layer(state)) {
        case _QWERTY:
            backlight_enable();
            backlight_level(SFM_BASE_BACKLIGLHT_LEVEL);
            rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL + 4);
            break;
        case _LOWER:
            /* rgblight_mode_noeeprom(RGBLIGHT_MODE_SNAKE + 3); */
            rgblight_sethsv_noeeprom(HSV_BLUE);
            break;
        case _RAISE:
            /* rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_GRADIENT); */
            rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_MOOD + 2);
            break;
        case _ADJUST:
            rgblight_sethsv_noeeprom(HSV_ORANGE);
            break;
        default:
            rgblight_sethsv_noeeprom(RGB_TURQUOISE);
            break;
    }
    return state;
}
/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
int cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        // key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
        else
            return SINGLE_HOLD;
    } else if (state->count == 2) {
        /*
         * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
         * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
         * keystrokes of the key, and not the 'double tap' action/macro.
         */
        if (state->interrupted)
            return DOUBLE_SINGLE_TAP;
        else if (state->pressed)
            return DOUBLE_HOLD;
        else
            return DOUBLE_TAP;
    }
    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed)
            return TRIPLE_TAP;
        else
            return TRIPLE_HOLD;
    } else
        return 8;  // magic number. At some point this method will expand to work for more presses
}

// instanalize an instance of 'tap' for the 'x' tap dance.
// clang-format off
static tap xtap_state = {
    .state = 0
};
// clang-format on

void x_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP:
            register_code(KC_LSHIFT);
            break;
        case SINGLE_HOLD:
            register_code(KC_LSHIFT);
            break;
        case DOUBLE_TAP:
            register_code(KC_CAPSLOCK);
            break;
        case DOUBLE_HOLD:
            register_code(KC_RCTRL);
            break;
            /* case DOUBLE_SINGLE_TAP: */
            /* register_code(KC_X); */
            /* unregister_code(KC_X); */
            /* register_code(KC_X); */
            // Last case is for fast typing. Assuming your key is `f`:
            // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
            // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
    }
}

void x_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_LSHIFT);
            break;
        case SINGLE_HOLD:
            unregister_code(KC_LSHIFT);
            break;
        case DOUBLE_TAP:
            unregister_code(KC_CAPSLOCK);
            // These are inverted because the state lags. This is controlled on the host.
            if ((host_keyboard_leds() & (1 << USB_LED_CAPS_LOCK))) {
                backlight_level(SFM_BASE_BACKLIGLHT_LEVEL);
            } else {
                backlight_level(SFM_ELEVATED_BACKLIGHT_LEVEL);
            }
            break;
        case DOUBLE_HOLD:
            unregister_code(KC_RCTRL);
            /* case DOUBLE_SINGLE_TAP: */
            /* unregister_code(KC_X); */
    }
    xtap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {[X_SHFT_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished, x_reset)};
