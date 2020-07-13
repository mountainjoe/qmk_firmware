#include QMK_KEYBOARD_H

#include <keycode.h>
#include <keymap_dvorak.h>
#include <send_string_keycodes.h>
#include <sendstring_dvorak.h>

#define _HOME 0
#define _NUMS 1
#define _NAVI 2
#define _SPEC 3


enum custom_keycodes {
    _2COLON = SAFE_RANGE,
    _SSHXIT,
};

#define CTL_TICK LCTL_T(KC_GRAVE)
#define CMD_ESC LGUI_T(KC_ESCAPE)
#define CMD_BSPC LGUI_T(KC_BSPC)
#define SFT_DEL LSFT_T(KC_DEL)
#define CTL_ESC LCTL_T(KC_ESCAPE)
#define SCNSHOT LGUI(LSFT(KC_4))

#define G_NAVI OSL(_NAVI)
#define G_NUMS OSL(_NUMS)
#define GSP_ESC LT(_SPEC,KC_ESC)

#define VSC_BCK LCTL(DV_MINS)
#define VSC_FWD LCTL(DV_UNDS)

#define MUTE KC_AUDIO_MUTE
#define VOL_UP KC_AUDIO_VOL_UP
#define VOL_DN KC_AUDIO_VOL_DOWN


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_HOME] = LAYOUT( \
    GSP_ESC,  DV_QUOT, DV_COMM, DV_DOT,  DV_P,    DV_Y,   XXXXXXX,                      XXXXXXX,  DV_F,    DV_G,    DV_C,    DV_R,    DV_L,  DV_SLSH, \
    CTL_TICK, DV_A,    DV_O,    DV_E,    DV_U,    DV_I,   VSC_BCK,                      XXXXXXX,  DV_D,    DV_H,    DV_T,    DV_N,    DV_S,  DV_MINS, \
    KC_LSPO,  DV_SCLN, DV_Q,    DV_J,    DV_K,    DV_X,           SFT_DEL ,    KC_TAB ,           DV_B,    DV_M,    DV_W,    DV_V,    DV_Z,  KC_RSPC, \
    XXXXXXX,  XXXXXXX, XXXXXXX,        G_NAVI,  G_NUMS,   KC_SPC, CMD_BSPC,    CTL_ESC,  KC_ENT, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, \
  ),

 [_NUMS] = LAYOUT(
    _______,  DV_EXLM,  DV_AT,  DV_LCBR, DV_RCBR,   DV_PIPE, _______,                        _______, DV_CIRC,    KC_7,    KC_8,    KC_9,  KC_KP_PLUS,  _______, \
    _______,  DV_HASH,  DV_DLR, KC_LPRN, KC_RPRN, KC_BSLASH, _______,                        _______, DV_PERC,    KC_4,    KC_5,    KC_6,  KC_KP_MINUS, _______, \
    _______,  _2COLON, XXXXXXX, DV_LBRC, DV_RBRC,   DV_TILD,           _______,     _______,          DV_AMPR,    KC_1,    KC_2,    KC_3,  KC_KP_EQUAL, _______, \
    _______,  _______, _______,          _______,   _______, _______,  _______,     _______, _______, KC_KP_0,   KC_KP_DOT,       _______, KC_BSLASH,   _______  \
 ),

  [_NAVI] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______,                      _______, _______,   KC_UP,   KC_DOWN, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______,                      _______, _______, KC_LEFT,  KC_RIGHT, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______,          _______,    _______,          _______, KC_PGUP, KC_PGDOWN, _______, _______, _______, \
    _______, _______, _______,          _______, _______, _______, _______,    _______, _______, _______, _______,            _______, _______, _______  \
  ),

  [_SPEC] = LAYOUT(
    _______, _SSHXIT, SCNSHOT, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______,                      _______, _______, VOL_UP , VOL_DN , _______, _______, _______, \
    _______, _______, _______, _______, _______, _______,          _______,    _______,          _______, _______, _______, _______, _______, _______, \
    _______, _______, _______,          _______, _______, _______, _______,    _______, MUTE, _______, _______,          _______, _______, _______  \
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case _2COLON:
            if (record->event.pressed) {
                SEND_STRING("::");
            }
            break;
        case _SSHXIT:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_ENTER) "~.");
            }
            break;
    }
    return true;
}
