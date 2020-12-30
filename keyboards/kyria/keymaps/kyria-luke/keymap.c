/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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

enum layers {
    _QWERTY = 0,
    _NUMNAV,
    _SYMBOLS,
    _ADJUST
};

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;
uint16_t copy_paste_timer = 0;

enum custom_keycodes {
  ALT_TAB = SAFE_RANGE,
  KC_CCCV = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* ┌───────┬─────┬─────┬─────┬─────┬─────┐                           ┌─────┬─────┬─────┬─────┬─────┬─────┐
 * │  Tab? │  Q  │  W  │  E  │  R  │  T  │     Base QWERTY Layer     │  Y  │  U  │  I  │  O  │  P  │ - _ │
 * ├───────┼─────┼─────┼─────┼─────┼─────┤                           ├─────┼─────┼─────┼─────┼─────┼─────┤
 * │ ^/Esc │  A  │  S  │  D  │  F  │  G  │                           │  H  │  J  │  K  │  L  │ ; : │ ' " │
 * ├───────┼─────┼─────┼─────┼─────┼─────┼─────┬─────┐   ┌─────┬─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 * │  Alt  │  Z  │  X  │  C  │  V  │  B  │ GUI │     │   │Adjst│     │  N  │  M  │ , < │ . > │ / ? │ = + │
 * └───────┴─────┴┬────┴─┬───┴──┬──┴───┬─┴────┬┴─────┤   ├─────┴┬────┴─┬───┴──┬──┴───┬─┴────┬┴─────┴─────┘
 *                │ Sleep│ Tab  │ Space│ Bksp │ Ctrl │   │ Enter│ Space│ Bksp │ Tab  │      │
 *                │      │ NmNv │ Symb │ Shift│ Del  │   │      │ Shift│ NmNv │ Symb │      │
 *                └──────┴──────┴──────┴──────┴──────┘   └──────┴──────┴──────┴──────┴──────┘
 */

    [_QWERTY] = LAYOUT(
      KC_GRV,         KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                                   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
      LCTL_T(KC_ESC), KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                                   KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
      KC_LALT,        KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,  KC_LGUI, OSL(_ADJUST),   OSL(_ADJUST), KC_LSFT, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_EQL,
        KC_SLEP, LT(_NUMNAV, KC_TAB), LT(_SYMBOLS, KC_SPC), MT(MOD_LSFT, KC_BSPC), MT(MOD_LCTL, KC_DEL), 
                                                        KC_ENT, MT(MOD_RSFT, KC_SPC), LT(_NUMNAV, KC_TAB), LT(_SYMBOLS, KC_BSPC), KC_RGUI
    ),


/* ┌───────┬─────┬─────┬─────┬─────┬─────┐                          ┌─────┬─────┬─────┬─────┬─────┬─────┐
 * │       │     │ PgUp│ Up  │PgDn │     │       NumNav Layer       │  *  │  7  │  8  │  9  │  +  │ -(t)│
 * ├───────┼─────┼─────┼─────┼─────┼─────┤                          ├─────┼─────┼─────┼─────┼─────┼─────┤
 * │       │ Home│ Left│ Dwn │Right│ End │                          │  -  │  4  │  5  │  6  │  0  │ '(t)│
 * ├───────┼─────┼─────┼─────┼─────┼─────┼─────┬─────┐  ┌─────┬─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 * │       │     │     │     │     │     │     │     │  │     │     │  /  │  1  │  2  │  3  │  .  │ =(t)│
 * └───────┴─────┴┬────┴─┬───┴──┬──┴───┬─┴────┬┴─────┤  ├─────┴┬────┴─┬───┴──┬──┴───┬─┴────┬┴─────┴─────┘
 *                │      │      │      │      │      │  │      │      │      │      │      │
 *                │      │      │      │      │      │  │      │      │      │      │      │
 *                └──────┴──────┴──────┴──────┴──────┘  └──────┴──────┴──────┴──────┴──────┘
 */

    [_NUMNAV] = LAYOUT(
      KC_TRNS, KC_TRNS, KC_PGUP, KC_UP,   KC_PGDN, KC_TRNS,                                     KC_ASTR, KC_7, KC_8, KC_9, KC_PLUS, KC_TRNS,
      KC_TRNS, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,                                      KC_MINS, KC_4, KC_5, KC_6, KC_0,    KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_SLSH, KC_1, KC_2, KC_3, KC_DOT,  KC_TRNS,
                                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),


/* ┌───────┬─────┬─────┬─────┬─────┬─────┐                          ┌─────┬─────┬─────┬─────┬─────┬───────┐
 * │       │  "  │  '  │  ;  │  :  │  ~  │       Symbols Layer      │  |  │  &  │  *  │  \  │  +  │  -(t) │
 * ├───────┼─────┼─────┼─────┼─────┼─────┤                          ├─────┼─────┼─────┼─────┼─────┼───────┤
 * │       │  [  │  {  │  }  │  ]  │  ?  │                          │  -  │  $  │  %  │  ^  │  ;  │  '(t) │
 * ├───────┼─────┼─────┼─────┼─────┼─────┼─────┬─────┐  ┌─────┬─────┼─────┼─────┼─────┼─────┼─────┼───────┤
 * │       │  <  │  >  │  (  │  )  │  `  │     │     │  │     │     │  _  │  !  │  @  │  #  │  /  │  =(t) │
 * └───────┴─────┴┬────┴─┬───┴──┬──┴───┬─┴────┬┴─────┤  ├─────┴┬────┴─┬───┴──┬──┴───┬─┴────┬┴─────┴───────┘
 *                │      │      │      │      │      │  │      │      │      │      │      │
 *                │      │      │      │      │      │  │      │      │      │      │      │
 *                └──────┴──────┴──────┴──────┴──────┘  └──────┴──────┴──────┴──────┴──────┘
 */

    [_SYMBOLS] = LAYOUT(
      _______, KC_DQUO, KC_QUOT, KC_SCLN, KC_COLN, KC_TILD,                                     KC_PIPE, KC_AMPR, KC_ASTR, KC_BSLS, KC_PLUS, KC_TRNS,
      _______, KC_LBRC, KC_LCBR, KC_RCBR, KC_RBRC, KC_QUES,                                     KC_MINS, KC_DLR,  KC_PERC, KC_CIRC, KC_SCLN, KC_TRNS,
      _______, KC_LABK, KC_RABK, KC_LPRN, KC_RPRN, KC_GRV,  _______, _______, _______, _______, KC_UNDS, KC_EXLM, KC_AT,   KC_HASH, KC_SLSH, KC_TRNS,
                                 _______, _______, _______, _______, _______, _______, _______, _______, KC_DOT, _______
    ),


/* ┌───────┬─────┬─────┬─────┬─────┬─────┐                          ┌─────┬─────┬─────┬─────┬─────┬─────┐
 * │       │     │     │     │     │     │      Function Layer      │     │ F7  │ F8  │ F9  │ F10 │     │
 * ├───────┼─────┼─────┼─────┼─────┼─────┤                          ├─────┼─────┼─────┼─────┼─────┼─────┤
 * │       │     │     │     │     │     │                          │     │ F4  │ F5  │ F6  │ F11 │     │
 * ├───────┼─────┼─────┼─────┼─────┼─────┼─────┬─────┐  ┌─────┬─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 * │       │     │     │     │     │     │     │     │  │     │     │     │ F1  │ F2  │ F3  │ F12 │     │
 * └───────┴─────┴┬────┴─┬───┴──┬──┴───┬─┴────┬┴─────┤  ├─────┴┬────┴─┬───┴──┬──┴───┬─┴────┬┴─────┴─────┘
 *                │      │      │      │      │      │  │      │      │      │      │      │
 *                │      │      │      │      │      │  │      │      │      │      │      │
 *                └──────┴──────┴──────┴──────┴──────┘  └──────┴──────┴──────┴──────┴──────┘
 */

    [_ADJUST] = LAYOUT(
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                      KC_TRNS, KC_F7, KC_F8, KC_F9, KC_F10, KC_TRNS,
      KC_TRNS, RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD,                                      KC_TRNS, KC_F4, KC_F5, KC_F6, KC_F11, KC_TRNS,
      KC_TRNS, KC_TRNS, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F12, KC_TRNS,
                                 KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),


/* ┌───────┬─────┬─────┬─────┬─────┬─────┐                          ┌─────┬─────┬─────┬─────┬─────┬───────┐
 * │       │     │     │     │     │     │       Layer Temlate      │     │     │     │     │     │       │
 * ├───────┼─────┼─────┼─────┼─────┼─────┤                          ├─────┼─────┼─────┼─────┼─────┼───────┤
 * │       │     │     │     │     │     │                          │     │     │     │     │     │       │
 * ├───────┼─────┼─────┼─────┼─────┼─────┼─────┬─────┐  ┌─────┬─────┼─────┼─────┼─────┼─────┼─────┼───────┤
 * │       │     │     │     │     │     │     │     │  │     │     │     │     │     │     │     │       │
 * └───────┴─────┴┬────┴─┬───┴──┬──┴───┬─┴────┬┴─────┤  ├─────┴┬────┴─┬───┴──┬──┴───┬─┴────┬┴─────┴───────┘
 *                │      │      │      │      │      │  │      │      │      │      │      │
 *                │      │      │      │      │      │  │      │      │      │      │      │
 *                └──────┴──────┴──────┴──────┴──────┘  └──────┴──────┴──────┴──────┴──────┘
 */


// /* ┌────────┬──────┬──────┬──────┬──────┬──────┐                              ┌──────┬──────┬──────┬──────┬──────┬────────┐
//  * │        │      │      │      │      │      │         Layer Template       │      │      │      │      │      │        │
//  * ├────────┼──────┼──────┼──────┼──────┼──────┤                              ├──────┼──────┼──────┼──────┼──────┼────────┤
//  * │        │      │      │      │      │      │                              │      │      │      │      │      │        │
//  * ├────────┼──────┼──────┼──────┼──────┼──────┼──────┬──────┐  ┌──────┬──────┼──────┼──────┼──────┼──────┼──────┼────────┤
//  * │        │      │      │      │      │      │      │      │  │      │      │      │      │      │      │      │        │
//  * └────────┴──────┴──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┴──────┴────────┘
//  *                        │      │      │      │      │      │  │      │      │      │      │      │
//  *                        │      │      │      │      │      │  │      │      │      │      │      │
//  *                        └──────┴──────┴──────┴──────┴──────┘  └──────┴──────┴──────┴──────┴──────┘
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _NUMNAV, _SYMBOLS, _ADJUST);
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

static void render_status(void) {
    // QMK Logo and version information
    //render_qmk_logo();
    oled_write_P(PSTR("\n\n"), false);

    // Host Keyboard Layer Status
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("-                \n"), false);
            break;
        case _NUMNAV:
            oled_write_P(PSTR("Layer:  "), false);
            oled_write_P(PSTR("NUM-NAV\n"), false);
            break;
        case _SYMBOLS:
            oled_write_P(PSTR("Layer:  "), false);
            oled_write_P(PSTR("SYMBOLS\n"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Layer:  "), false);
            oled_write_P(PSTR("Function\n"), false);
            break;
        default:
            oled_write_P(PSTR("Layer:  "), false);
            oled_write_P(PSTR("Undefined\n"), false);
    }

    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK) ? PSTR("            ") : PSTR("NumLock OFF "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK) ? PSTR("CAPS LOCK ") : PSTR("          "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("\nScrLk") : PSTR("\n      "), false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
       // render_kyria_logo();
    }
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_CCCV:  // One key copy/paste
            if (record->event.pressed) {
                copy_paste_timer = timer_read();
            } else {
                if (timer_elapsed(copy_paste_timer) > TAPPING_TERM) {  // Hold, copy
                    tap_code16(LCTL(KC_C));
                } else { // Tap, paste
                    tap_code16(LCTL(KC_V));
                }
            }
            break;
    }
    return true;
}

#ifdef ENCODER_ENABLE

void encoder_update_user(uint8_t index, bool clockwise) {
    // clockwise is reversed for some reason; keep that in mind
    if (index == 0) {
        if (clockwise) {
            tap_code16(S(KC_TAB));
        } else {
            tap_code16(KC_TAB);
        }
    }
    else if (index == 1) {
        // // Switch between windows on Windows with alt tab.
        // if (clockwise) {
        //     if (!is_alt_tab_active) {
        //         is_alt_tab_active = true;
        //         register_code(KC_LALT);
        //     } 
        //     alt_tab_timer = timer_read();
        //     tap_code16(KC_TAB);
        // } else {
        //     tap_code16(S(KC_TAB));
        // }
        // Switch between windows on Windows with alt tab.
        if (clockwise) {
            tap_code16(KC_WH_U);
        } else {
            tap_code16(KC_WH_D);
        }
    }
}

// void matrix_scan_user(void) {
//   if (is_alt_tab_active) {
//     if (timer_elapsed(alt_tab_timer) > 1000) {
//       unregister_code(KC_LALT);
//       is_alt_tab_active = false;
//     }
//   }
// }
#endif
