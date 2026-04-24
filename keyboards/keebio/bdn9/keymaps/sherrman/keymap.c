/* Copyright 2019 Danny Nguyen <danny@keeb.io>
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
#include "qmk_midi.h"

#include "quantum/process_keycode/process_midi.h"

#include "print.h"

enum encoder_names {
    _LEFT,
    _RIGHT,
    _MIDDLE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        |  Knob 1: Vol Dn/Up |       |  Knob 2: Page Dn/Up |
        |  Press: Mute       |  TAB  |  Press: Play/Pause  |
        |  CMD               |  Up   |  '['                |
        |  Left              |  Down |  Right              |
     */
    // clang-format off
    [0] = LAYOUT(
        MO(1),     KC_TAB,    MI_C4,
        KC_LCMD,   KC_UP,     KC_LEFT_BRACKET,
        KC_LEFT,   KC_DOWN,   KC_RGHT
    ),
    /*
        | QK_BOOT        | N/A  | Media Stop |
        | Held: Layer 2  | Home | RGB Mode   |
        | Media Previous | End  | Media Next |
     */
    [1] = LAYOUT(
        _______,  _______,  QK_MIDI_CHANNEL_UP,
        _______,  KC_HOME,  RM_NEXT,
        KC_MPRV,  KC_END,   KC_MNXT
    ),
    // clang-format on
};

void keyboard_post_init_user(void) {
    uprintf("setting midi_config.channel old=%d ", midi_config.channel);
    midi_config.channel = 13;
    uprintf("new=%d\n", midi_config.channel);
}

#define LEFT_ENCODER_CC 16
#define RIGHT_ENCODER_CC 17
bool encoder_update_user(uint8_t index, bool clockwise) {
    /* My BDN9 doesn't have a middle encoder */
    if (index == _LEFT) {
        uprintf("encoder_update_user LEFT chan=%d %d %d\n", midi_config.channel, index, clockwise);
        /* Send MIDI control to incrememnt integer values.
         *
         * This is going to be mapped to tempo control in Live.
         */
        if (clockwise) {
            midi_send_cc(&midi_device, midi_config.channel, LEFT_ENCODER_CC, 1);
        } else {
            midi_send_cc(&midi_device, midi_config.channel, LEFT_ENCODER_CC, 65);
        }
    } else if (index == _RIGHT) {
        uprintf("encoder_update_user RIGHT %d %d\n", index, clockwise);
        if (clockwise) {
            midi_send_cc(&midi_device, midi_config.channel, RIGHT_ENCODER_CC, 1);
        } else {
            midi_send_cc(&midi_device, midi_config.channel, RIGHT_ENCODER_CC, 65);
        }
    }
    return false;
}
