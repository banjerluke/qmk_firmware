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
    _SYMBOLS,
    _NAV,
    _FUNC
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
 * │  Alt  │  Z  │  X  │  C  │  V  │  B  │ GUI │     │   │     │     │  N  │  M  │ , < │ . > │ / ? │ = + │
 * └───────┴─────┴┬────┴─┬───┴──┬──┴───┬─┴────┬┴─────┤   ├─────┴┬────┴─┬───┴──┬──┴───┬─┴────┬┴─────┴─────┘
 *                │ Sleep│ Tab  │ Space│ Bksp │ Del  │   │ Enter│ Space│ Bksp │ Tab  │      │
 *                │      │ Ctrl │ SYMB │ Shift│ NAV  │   │ NAV  │ Shift│ SYMB │ FUNC │      │
 *                └──────┴──────┴──────┴──────┴──────┘   └──────┴──────┴──────┴──────┴──────┘
 */

    [_QWERTY] = LAYOUT(
      KC_GRV,         KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                                   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
      RCTL_T(KC_ESC), KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                                   KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
      KC_RALT,        KC_Z,   KC_X,   KC_C,   KC_V,   KC_B, KC_LGUI, KC_NO,   KC_NO, KC_LSFT, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_EQL,
        KC_SLEP, MT(MOD_RCTL, KC_TAB), LT(_SYMBOLS, KC_SPC), MT(MOD_LSFT, KC_BSPC), LT(_NAV, KC_DEL), 
                                                        LT(_NAV, KC_ENT), MT(MOD_RSFT, KC_SPC), LT(_SYMBOLS, KC_BSPC), LT(_FUNC, KC_TAB), KC_RGUI
    ),


/* ┌───────┬─────┬─────┬─────┬─────┬─────┐                          ┌─────┬─────┬─────┬─────┬─────┬─────┐
 * │  `(t) │  !  │  @  │  #  │  $  │  %  │      Symbols/Numbers     │  ;  │  7  │  8  │  9  │  \  │  |  │
 * ├───────┼─────┼─────┼─────┼─────┼─────┤           Layer          ├─────┼─────┼─────┼─────┼─────┼─────┤
 * │       │  [  │  {  │  }  │  ]  │  ^  │                          │  -  │  4  │  5  │  6  │  +  │ '(t)│
 * ├───────┼─────┼─────┼─────┼─────┼─────┼─────┬─────┐  ┌─────┬─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 * │       │  <  │  >  │  (  │  )  │  &  │     │     │  │     │     │  *  │  1  │  2  │  3  │  /  │ =(t)│
 * └───────┴─────┴┬────┴─┬───┴──┬──┴───┬─┴────┬┴─────┤  ├─────┴┬────┴─┬───┴──┬──┴───┬─┴────┬┴─────┴─────┘
 *                │      │      │      │      │      │  │      │      │   0  │   .  │      │
 *                │      │      │      │      │      │  │      │      │      │      │      │
 *                └──────┴──────┴──────┴──────┴──────┘  └──────┴──────┴──────┴──────┴──────┘
 */

    [_SYMBOLS] = LAYOUT(
      KC_TRNS, KC_EXLM, KC_AT,   KC_HASH, KC_DLR, KC_PERC,                                      KC_SCLN, KC_7, KC_8, KC_9, KC_BSLS, KC_PIPE,
      KC_TRNS, KC_LBRC, KC_LCBR, KC_RCBR, KC_RBRC, KC_CIRC,                                     KC_MINS, KC_4, KC_5, KC_6, KC_PLUS, KC_TRNS,
      KC_TRNS, KC_LABK, KC_RABK, KC_LPRN, KC_RPRN, KC_AMPR, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_ASTR, KC_1, KC_2, KC_3, KC_SLSH, KC_TRNS,
                                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_0,    KC_DOT, KC_TRNS
    ),


/* ┌───────┬─────┬─────┬─────┬─────┬─────┐                          ┌─────┬─────┬─────┬─────┬─────┬─────┐
 * │       │     │ Pg↑ │  ↑  │ Pg↓ │     │     Navigation Layer     │ Home│ Pg↓ │ Pg↑ │ End │     │ -(t)│
 * ├───────┼─────┼─────┼─────┼─────┼─────┤                          ├─────┼─────┼─────┼─────┼─────┼─────┤
 * │       │ Home│ <-- │  ↓  │ --> │ End │                          │ <-- │  ↓  │  ↑  │ --> │ End │ '(t)│
 * ├───────┼─────┼─────┼─────┼─────┼─────┼─────┬─────┐  ┌─────┬─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 * │       │     │     │     │     │     │     │     │  │     │     │ Home│ Pg↓ │ Pg↑ │ Home│     │ =(t)│
 * └───────┴─────┴┬────┴─┬───┴──┬──┴───┬─┴────┬┴─────┤  ├─────┴┬────┴─┬───┴──┬──┴───┬─┴────┬┴─────┴─────┘
 *                │      │      │      │      │      │  │      │      │      │      │      │
 *                │      │      │      │      │      │  │      │      │      │      │      │
 *                └──────┴──────┴──────┴──────┴──────┘  └──────┴──────┴──────┴──────┴──────┘
 */

    [_NAV] = LAYOUT(
      KC_TRNS, KC_TRNS, KC_PGUP, KC_UP,   KC_PGDN, KC_TRNS,                                     KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_NO,  KC_TRNS,
      KC_TRNS, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,                                      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_END, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_NO,  KC_TRNS,
                                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),


/* ┌───────┬─────┬─────┬─────┬─────┬─────┐                          ┌─────┬─────┬─────┬─────┬─────┬─────┐
 * │       │     │     │     │     │     │      Function Layer      │     │ F7  │ F8  │ F9  │ F10 │     │
 * ├───────┼─────┼─────┼─────┼─────┼─────┤                          ├─────┼─────┼─────┼─────┼─────┼─────┤
 * │       │ *Tg │ *S+ │ *H+ │ *V+ │ *M+ │                          │     │ F4  │ F5  │ F6  │ F11 │     │
 * ├───────┼─────┼─────┼─────┼─────┼─────┼─────┬─────┐  ┌─────┬─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 * │       │     │ *S- │ *H- │ *V- │ *M- │     │     │  │     │     │     │ F1  │ F2  │ F3  │ F12 │     │
 * └───────┴─────┴┬────┴─┬───┴──┬──┴───┬─┴────┬┴─────┤  ├─────┴┬────┴─┬───┴──┬──┴───┬─┴────┬┴─────┴─────┘
 *                │      │      │      │      │      │  │      │      │      │      │      │
 *                │      │      │      │      │      │  │      │      │      │      │      │
 *                └──────┴──────┴──────┴──────┴──────┘  └──────┴──────┴──────┴──────┴──────┘
 */

    [_FUNC] = LAYOUT(
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                      KC_TRNS, KC_F7, KC_F8, KC_F9, KC_F10, KC_TRNS,
      KC_TRNS, RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD,                                      KC_TRNS, KC_F4, KC_F5, KC_F6, KC_F11, KC_TRNS,
      KC_TRNS, KC_TRNS, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F12, KC_TRNS,
                                 KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),


/* ┌───────┬─────┬─────┬─────┬─────┬─────┐                          ┌─────┬─────┬─────┬─────┬─────┬───────┐
 * │       │     │     │     │     │     │      Layer Template      │     │     │     │     │     │       │
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

// layer_state_t layer_state_set_user(layer_state_t state) {
//     return update_tri_layer_state(state, _NAV, _SYMBOLS, _FUNC);
// }

const rgblight_segment_t PROGMEM symbols_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, HSV_GOLD},
    {3, 1, HSV_GOLD},
    {5, 1, HSV_GOLD},
    {7, 1, HSV_GOLD},
    {9, 1, HSV_GOLD},
    {10, 1, HSV_GOLD},
    {12, 1, HSV_GOLD},
    {14, 1, HSV_GOLD},
    {16, 1, HSV_GOLD},
    {18, 2, HSV_GOLD}
);

const rgblight_segment_t PROGMEM nav_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_MAGENTA},
    {2, 1, HSV_MAGENTA},
    {4, 1, HSV_MAGENTA},
    {6, 1, HSV_MAGENTA},
    {8, 2, HSV_MAGENTA},
    {10, 2, HSV_MAGENTA},
    {13, 1, HSV_MAGENTA},
    {15, 1, HSV_MAGENTA},
    {17, 1, HSV_MAGENTA},
    {19, 1, HSV_MAGENTA}
);

const rgblight_segment_t PROGMEM func_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {8, 2, HSV_RED}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    symbols_layer,
    nav_layer,
    func_layer
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // Both layers will light up if both kb layers are active
    rgblight_set_layer_state(0, layer_state_cmp(state, 1));
    rgblight_set_layer_state(1, layer_state_cmp(state, 2));
    rgblight_set_layer_state(2, layer_state_cmp(state, 3));
    return state;
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
        case _SYMBOLS:
            oled_write_P(PSTR("Layer:  "), false);
            oled_write_P(PSTR("SYMBOLS\n"), false);
            break;
        case _NAV:
            oled_write_P(PSTR("Layer:  "), false);
            oled_write_P(PSTR("NAVIGATION\n"), false);
            break;
        case _FUNC:
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
