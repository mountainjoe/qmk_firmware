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
#include <stdint.h>
#include <stdbool.h>
#include "mountainjoe.h"
#include "analog.h"
#include "quantum.h"
#include "keycode.h"
#include "quantum_keycodes.h"
#include "config_common.h"
#include "print.h"
#include "pointing_device.h"

// need a struct for the joystick mouse state, and some busy-loop functions for them.
struct {
    int16_t valX;
    int16_t valY;

    uint16_t oled_state;

#define UP_BIT 0x80
#define DOWN_BIT 0x40
#define LEFT_BIT 0x08
#define RIGHT_BIT 0x04

#define IS_MOVE_UP() (JoystickMouseState.oled_state & UP_BIT)
#define IS_MOVE_DOWN() (JoystickMouseState.oled_state & DOWN_BIT)
#define IS_MOVE_LEFT() (JoystickMouseState.oled_state & LEFT_BIT)
#define IS_MOVE_RIGHT() (JoystickMouseState.oled_state & RIGHT_BIT)

} JoystickMouseState;

void joystick_init_kb(void) {
    JoystickMouseState.oled_state = 0;
}

void joystick_scan_kb(void) {
    JoystickMouseState.valX = analogReadPin(B4);
    JoystickMouseState.valY = analogReadPin(B5);

#define SENSITIVITY 10
    report_mouse_t currentReport = pointing_device_get_report();

// values are 0 - 1023. So 512 is middle.
    JoystickMouseState.oled_state &= ~(LEFT_BIT | RIGHT_BIT);
    if (JoystickMouseState.valX > 750) {
        currentReport.x = SENSITIVITY;
        JoystickMouseState.oled_state |= RIGHT_BIT;
    } else if (JoystickMouseState.valX < 250) {
        currentReport.x = -SENSITIVITY;
        JoystickMouseState.oled_state |= LEFT_BIT;
    }

    JoystickMouseState.oled_state &= ~(UP_BIT | DOWN_BIT);
    if (JoystickMouseState.valY > 750) {
        currentReport.y = SENSITIVITY;
        JoystickMouseState.oled_state |= DOWN_BIT;
    } else if (JoystickMouseState.valY < 250) {
        currentReport.y = -SENSITIVITY;
        JoystickMouseState.oled_state |= UP_BIT;
    }

    pointing_device_set_report(currentReport);
    pointing_device_send();
}

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up
    matrix_init_user();
    joystick_init_kb();
}

// switch is E6

void matrix_scan_kb(void) {
    // put your looping keyboard code here
    // runs every cycle (a lot)
    matrix_scan_user();
    joystick_scan_kb();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    // put your per-action keyboard code here
    // runs for every action, just before processing by the firmware
    print("something happened\n");

    return process_record_user(keycode, record);
}

bool led_update_kb(led_t led_state) {
    // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

    return led_update_user(led_state);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return rotation;
}

static int encoderVar = 0;


void oled_task_user(void) {
    oled_write_P(PSTR("Encod:"), false);
    oled_write_ln_P( encoderVar ? PSTR("clk") : PSTR("cnt"), false);

// values are 0 - 1023. So 512 is middle.
    if (IS_MOVE_RIGHT()) {
        oled_write_P(PSTR(" RT "), true);
    } else if (IS_MOVE_LEFT()) {
        oled_write_P(PSTR(" LT "), true);
    } else {
        oled_write_P(PSTR("----"), false);
    }

    if (IS_MOVE_DOWN()) {
        oled_write_ln_P(PSTR(" DN "), true);
    } else if (IS_MOVE_UP()) {
        oled_write_ln_P(PSTR(" UP "), true);
    } else {
        oled_write_ln_P(PSTR("----"), false);
    }
}
void encoder_update_user(uint8_t index, bool clockwise);

void encoder_update_kb(uint8_t index, bool clockwise) {

    encoder_update_user(index, clockwise);
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            encoderVar = 1;
            tap_code(KC_RIGHT);
        } else {
            encoderVar = 0;
            tap_code(KC_LEFT);
        }
    }
}