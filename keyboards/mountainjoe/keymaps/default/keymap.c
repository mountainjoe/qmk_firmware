/* Copyright 2020 Joseph Olivier
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
#include <stdint.h>

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE = 0,
    _FN
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    QMKURL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT( RESET, KC_MS_BTN1 ),
    [_FN] = LAYOUT( RESET, KC_ENT )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}


void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

/*
bool led_update_user(led_t led_state) {
    return true;
}
*/
