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

// Tap Dance keycodes
enum td_keycodes {
  GRV_TILD,
  MINS_UNDS,
  DQUO_QUOT,
  BSLS_PIPE,
  RABK_CIRC,
  SLSH_QUES,
  UNDS_MINS,
  DOT_COMM
};

// Define a type containing as many tapdance states as you need
typedef enum {
    SINGLE_TAP,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_SINGLE_TAP,
    DOUBLE_HOLD,
    TRIPLE_TAP,
    TRIPLE_HOLD
} td_state_t;

// Create a global instance of the tapdance state type
// static td_state_t td_state;

// Function to determine the current tapdance state
uint8_t cur_dance(qk_tap_dance_state_t *state);

// Declare your tapdance functions:
// void grv_tild_finished(qk_tap_dance_state_t *state, void *user_data);
// void grv_tild_reset(qk_tap_dance_state_t *state, void *user_data);


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* ┌────────┬─────┬─────┬─────┬─────┬─────┐                           ┌─────┬─────┬─────┬─────┬─────┬──────┐
 * │  Tab   │  Q  │  W  │  E  │  R  │  T  │     Base QWERTY Layer     │  Y  │  U  │  I  │  O  │  P  │ Bksp │
 * ├────────┼─────┼─────┼─────┼─────┼─────┤                           ├─────┼─────┼─────┼─────┼─────┼──────┤
 * │Bksp/Nav│  A  │  S  │  D  │  F  │  G  │                           │  H  │  J  │  K  │  L  │ ; : │  ' " │
 * ├────────┼─────┼─────┼─────┼─────┼─────┼─────┬─────┐   ┌─────┬─────┼─────┼─────┼─────┼─────┼─────┼──────┤
 * │  Alt   │  Z  │  X  │  C  │  V  │  B  │ GUI │     │   │     │     │  N  │  M  │ , < │ . > │ / ? │  - _ │
 * └────────┴─────┴┬────┴─┬───┴──┬──┴───┬─┴────┬┴─────┤   ├─────┴┬────┴─┬───┴──┬──┴───┬─┴────┬┴─────┴──────┘
 *                 │ A-Tb │ Esc  │   (  │      │      │   │ Enter│ Space│   )  │ Tab  │ Zzz  │
 *                 │      │ Ctrl │ Shift│ Smbl │ NAV  │   │ NAV  │      │ Shift│ FUNC │      │
 *                 └──────┴──────┴──────┴──────┴──────┘   └──────┴──────┴──────┴──────┴──────┘
 */

  [_QWERTY] = LAYOUT(
    KC_TAB,         KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                                   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    LT(_NAV, KC_BSPC), KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                                   KC_H,    KC_J,    KC_K,    KC_L,   LT(_NAV,KC_SCLN), KC_QUOT,
    KC_RALT,        KC_Z,   KC_X,   KC_C,   KC_V,   KC_B, KC_RGUI, KC_RGUI, /**/ KC_NO, KC_LSFT, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
      RALT(KC_TAB), MT(MOD_RCTL, KC_ESC), KC_LSFT, MO(_SYMBOLS), MO(_NAV), /**/ LT(_NAV, KC_TAB), KC_SPC, KC_RSFT, LT(_FUNC, KC_ENT), KC_SLEP
  ),


/* ┌───────┬─────┬─────┬─────┬─────┬─────┐                           ┌─────┬─────┬─────┬─────┬─────┬─────┐
 * │  ` ~  │  !  │  @  │  {  │  }  │  ^  │      Symbols/Numbers      │  *  │  7  │  8  │  9  │  +  │     │
 * ├───────┼─────┼─────┼─────┼─────┼─────┤ (second symbol when held) ├─────┼─────┼─────┼─────┼─────┼─────┤
 * │       │  #  │  $  │  (  │  )  │  &  │                           │ - _ │  4  │  5  │  6  │  =  │ " ' │
 * ├───────┼─────┼─────┼─────┼─────┼─────┼─────┬─────┐   ┌─────┬─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 * │       │  %  │ \ | │  [  │  ]  │  <  │     │     │   │     │     │ > ^ │  1  │  2  │  3  │ / ? │ _ - │
 * └───────┴─────┴┬────┴─┬───┴──┬──┴───┬─┴────┬┴─────┤   ├─────┴┬────┴─┬───┴──┬──┴───┬─┴────┬┴─────┴─────┘
 *                │      │      │      │      │      │   │      │      │   0  │  . , │      │
 *                │      │      │      │      │      │   │      │      │      │      │      │
 *                └──────┴──────┴──────┴──────┴──────┘   └──────┴──────┴──────┴──────┴──────┘
 */

  [_SYMBOLS] = LAYOUT(
    TD(GRV_TILD), KC_EXLM,  KC_AT,         KC_LCBR, KC_RCBR, KC_CIRC,                                     KC_ASTR,       KC_7, KC_8, KC_9, KC_PLUS,       KC_TRNS,
    KC_TRNS,      KC_HASH,  KC_DLR,        KC_LPRN, KC_RPRN, KC_AMPR,                                     TD(MINS_UNDS), KC_4, KC_5, KC_6, KC_EQL,        TD(DQUO_QUOT),
    KC_TRNS,      KC_PERC,  TD(BSLS_PIPE), KC_LBRC, KC_RBRC, KC_LABK, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TD(RABK_CIRC), KC_1, KC_2, KC_3, TD(SLSH_QUES), TD(UNDS_MINS),
                                           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_0,     TD(DOT_COMM), KC_TRNS
  ),



/* ┌───────┬─────┬─────┬─────┬─────┬─────┐                          ┌─────┬─────┬─────┬─────┬─────┬─────┐
 * │       │     │     │     │     │     │     Navigation Layer     │ ^<- │     │     │ ^-> │ ^<┘ │ ^Bk │
 * ├───────┼─────┼─────┼─────┼─────┼─────┤                          ├─────┼─────┼─────┼─────┼─────┼─────┤
 * │       │     │     │     │     │     │                          │ <-- │  ↓  │  ↑  │ --> │ <─┘ │ Bksp│
 * ├───────┼─────┼─────┼─────┼─────┼─────┼─────┬─────┐  ┌─────┬─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 * │       │     │     │     │     │     │     │     │  │     │     │ Home│ Pg↓ │ Pg↑ │ End │     │ Del │
 * └───────┴─────┴┬────┴─┬───┴──┬──┴───┬─┴────┬┴─────┤  ├─────┴┬────┴─┬───┴──┬──┴───┬─┴────┬┴─────┴─────┘
 *                │      │      │      │      │      │  │      │      │      │      │      │
 *                │      │      │      │      │      │  │      │      │      │      │      │
 *                └──────┴──────┴──────┴──────┴──────┘  └──────┴──────┴──────┴──────┴──────┘
 */

    [_NAV] = LAYOUT( 
      KC_TRNS, KC_1, KC_2, KC_3, KC_4, KC_5,                                               RCTL(KC_LEFT), RCTL(KC_LEFT), KC_NO,  RCTL(KC_RGHT), RCTL(KC_ENT),  RCTL(KC_BSPC),
      KC_TRNS, KC_6, KC_7, KC_8, KC_9, KC_0,                                                   KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT,    KC_ENT,   KC_BSPC,
      KC_TRNS, KC_RALT, KC_RSFT, KC_RCTL, KC_RGUI, OSM(MOD_RGUI), KC_SPC, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP, KC_END,     KC_APP,    KC_DEL,
                                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),


/* ┌───────┬─────┬─────┬─────┬─────┬─────┐                          ┌─────┬─────┬─────┬─────┬─────┬─────┐
 * │       │ F1  │ F2  │ F3  │ F4  │ F5  │      Function Layer      │ F6  │ F7  │ F8  │ F9  │ F10 │     │
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
      KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                        KC_F6,   KC_F7, KC_F8, KC_F9, KC_F10, KC_TRNS,
      KC_TRNS, KC_TRNS, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD,                                     KC_TRNS, KC_F4, KC_F5, KC_F6, KC_F11, KC_TRNS,
      KC_TRNS, KC_RALT, KC_RSFT, KC_RCTL, KC_RWIN, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F12, KC_TRNS,
                                 KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
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

    [_RGB] = LAYOUT(
      KC_TRNS, RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD,                                      KC_TRNS, KC_F7, KC_F8, KC_F9, KC_F10, KC_TRNS,
      KC_TRNS, KC_TRNS, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD,                                     KC_TRNS, KC_F4, KC_F5, KC_F6, KC_F11, KC_TRNS,
      KC_TRNS, KC_RALT, KC_RSFT, KC_RCTL, KC_RWIN, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F12, KC_TRNS,
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

enum combo_events {
   DOUBLE_SHIFT
};

const uint16_t PROGMEM double_shift_combo[] = {KC_LSFT, KC_RSFT, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [DOUBLE_SHIFT] = COMBO_ACTION(double_shift_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case DOUBLE_SHIFT:
      if (pressed) {
        layer_on(_NAV);
      } else {
          layer_off(_NAV);
      }
      break;
  }
}

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(_NAV, KC_BSPC):
            return true;
        default:
            return false;
    }
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(_NAV, KC_BSPC):
            return true;
        default:
            return false;
    }
}

// Determine the tapdance state to return
uint8_t cur_dance(qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) return SINGLE_TAP;
    else return SINGLE_HOLD;
  }

  if (state->count == 2) {
    if (state->interrupted) return DOUBLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  if (state->count == 3) {
      if (state->interrupted || !state->pressed) return TRIPLE_TAP;
      else return TRIPLE_HOLD;
  } else return 8; // Magic number. At some point this method will expand to work for more presses
}

// Handle the possible states for each tapdance keycode you define:

// void grv_tild_finished(qk_tap_dance_state_t *state, void *user_data) {
//   td_state = cur_dance(state);
//   switch (td_state) {
//     case SINGLE_TAP:
//       register_code16(KC_GRV);
//       break;
//     case SINGLE_HOLD:
//       tap_code16(KC_TILD);
//       break;
//     case DOUBLE_SINGLE_TAP:
//       tap_code16(KC_GRV);
//       register_code16(KC_GRV);
//   }
// }

// void grv_tild_reset(qk_tap_dance_state_t *state, void *user_data) {
//   switch (td_state) {
//     case SINGLE_TAP:
//       unregister_code16(KC_GRV);
//       break;
//     case DOUBLE_SINGLE_TAP:
//       unregister_code16(KC_GRV);
//   }
// }

// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
qk_tap_dance_action_t tap_dance_actions[] = {
    // [GRV_TILD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, grv_tild_finished, grv_tild_reset)
  [GRV_TILD] = ACTION_TAP_DANCE_DOUBLE(KC_GRV, KC_TILD),
  [MINS_UNDS] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_UNDS),
  [DQUO_QUOT] = ACTION_TAP_DANCE_DOUBLE(KC_DQUO, KC_QUOT),
  [BSLS_PIPE] = ACTION_TAP_DANCE_DOUBLE(KC_BSLS, KC_PIPE),
  [RABK_CIRC] = ACTION_TAP_DANCE_DOUBLE(KC_RABK, KC_CIRC),
  [SLSH_QUES] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_QUES),
  [UNDS_MINS] = ACTION_TAP_DANCE_DOUBLE(KC_UNDS, KC_MINS),
  [DOT_COMM] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_COMM),
};


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


#ifdef ENCODER_ENABLE

void encoder_update_user(uint8_t index, bool clockwise) {
    // clockwise is reversed for some reason; keep that in mind
    if (index == 0) {
        if (clockwise) {
            tap_code16(KC_TAB);
        } else {
            tap_code16(S(KC_TAB));
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
