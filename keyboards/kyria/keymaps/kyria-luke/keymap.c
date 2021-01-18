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
    _NUMBERS,
    _NAV,
    _FUNC,
    _RGB,
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
  DOT_COMM,
};

// Define a type containing as many tapdance states as you need
typedef enum {
    SINGLE_TAP,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_SINGLE_TAP,
    DOUBLE_HOLD,
    TRIPLE_TAP,
    TRIPLE_HOLD,
} td_state_t;

// Create a global instance of the tapdance state type
// static td_state_t td_state;

// Function to determine the current tapdance state
uint8_t cur_dance(qk_tap_dance_state_t *state);

// Declare your tapdance functions:
// void grv_tild_finished(qk_tap_dance_state_t *state, void *user_data);
// void grv_tild_reset(qk_tap_dance_state_t *state, void *user_data);


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* ┌────────┬─────┬─────┬─────┬─────┬─────┐                           ┌─────┬─────┬─────┬─────┬─────┬───────┐
 * │   `    │  Q  │  W  │  E  │  R  │  T  │     Base QWERTY Layer     │  Y  │  U  │  I  │  O  │  P  │  - _  │
 * ├────────┼─────┼─────┼─────┼─────┼─────┤                           ├─────┼─────┼─────┼─────┼─────┼───────┤
 * │Bksp/Nav│  A  │  S  │  D  │  F  │  G  │                           │  H  │  J  │  K  │  L  │ ;Num│  ' "  │
 * ├────────┼─────┼─────┼─────┼─────┼─────┼─────┬─────┐   ┌─────┬─────┼─────┼─────┼─────┼─────┼─────┼───────┤
 * │  Alt   │  Z  │  X  │  C  │  V  │  B  │ Win │ OSW │   │ RGB │     │  N  │  M  │ , < │ . > │ / ? │  - _  │
 * └────────┴─────┴┬────┴─┬───┴──┬──┴───┬─┴────┬┴─────┤   ├─────┴┬────┴─┬───┴──┬──┴───┬─┴────┬┴─────┴───────┘
 *                 │ A-Tb │ Ctrl │ Shft │ Num  │ Func │   │ Nav  │ Space│ Shft │ Ctrl │ Zzz  │
 *                 │      │      │      │      │      │   │      │      │      │      │      │
 *                 └──────┴──────┴──────┴──────┴──────┘   └──────┴──────┴──────┴──────┴──────┘
 */

  [_QWERTY] = LAYOUT(
    KC_GRV,            KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                                                KC_Y,  KC_U,  KC_I,    KC_O,   KC_P,                  KC_MINS,
    LT(_NAV, KC_BSPC), KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                                                KC_H,  KC_J,  KC_K,    KC_L,   LT(_NUMBERS, KC_SCLN), KC_QUOT,
    KC_RALT,           KC_Z,   KC_X,   KC_C,   KC_V,   KC_B, KC_RGUI, OSM(MOD_RGUI), /**/ MO(_RGB), KC_LSFT, KC_N,  KC_M,  KC_COMM, KC_DOT, KC_SLSH,               KC_MINS,
        RALT(KC_TAB), KC_RCTL, KC_LSFT, MO(_NUMBERS), MO(_FUNC), /**/ MO(_NAV), KC_SPC, KC_RSFT, KC_RCTL, KC_SLEP
  ),


/* ┌───────┬─────┬─────┬─────┬─────┬─────┐                           ┌─────┬─────┬─────┬─────┬─────┬─────┐
 * │   ~   │  !  │  @  │  #  │  $  │  %  │          Symbols          │  ^  │  &  │  *  │     │  -  │  _  │
 * ├───────┼─────┼─────┼─────┼─────┼─────┤                           ├─────┼─────┼─────┼─────┼─────┼─────┤
 * │       │  {  │  }  │  (  │  )  │  \  │                           │  -  │  =  │  ;  │  '  │  :  │  "  │
 * ├───────┼─────┼─────┼─────┼─────┼─────┼─────┬─────┐   ┌─────┬─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 * │       │  <  │  >  │  [  │  ]  │  |  │     │     │   │     │     │  /  │  +  │  ,  │  .  │  ?  │  _  │
 * └───────┴─────┴┬────┴─┬───┴──┬──┴───┬─┴────┬┴─────┤   ├─────┴┬────┴─┬───┴──┬──┴───┬─┴────┬┴─────┴─────┘
 *                │      │      │      │      │      │   │      │      │      │  . , │      │
 *                │      │      │      │      │      │   │      │      │      │      │      │
 *                └──────┴──────┴──────┴──────┴──────┘   └──────┴──────┴──────┴──────┴──────┘
 */

  [_SYMBOLS] = LAYOUT(
    KC_TILD,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                                     KC_CIRC, KC_AMPR, KC_ASTR, KC_NO,   KC_MINS, KC_UNDS,
    KC_TRNS,  KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN, KC_BSLS,                                     KC_MINS, KC_EQL,  KC_SCLN, KC_QUOT, KC_COLN, KC_DQUO, 
    KC_TRNS,  KC_LABK, KC_RABK, KC_LCBR, KC_RCBR, KC_PIPE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_SLSH, KC_PLUS, KC_COMM, KC_DOT,  KC_QUES, KC_UNDS,
                                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TD(DOT_COMM), KC_TRNS
  ),

/* ┌───────┬─────┬─────┬─────┬─────┬─────┐                           ┌─────┬─────┬─────┬─────┬─────┬─────┐
 * │  ` ~  │  +  │  7  │  8  │  9  │  +  │          Numbers          │  +  │  7  │  8  │  9  │  +  │     │
 * ├───────┼─────┼─────┼─────┼─────┼─────┤ (second symbol when d.t.) ├─────┼─────┼─────┼─────┼─────┼─────┤
 * │       │  0  │  4  │  5  │  6  │  -  │                           │  -  │  4  │  5  │  6  │ _=_ │ " ' │
 * ├───────┼─────┼─────┼─────┼─────┼─────┼─────┬─────┐   ┌─────┬─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 * │       │  =  │  1  │  2  │  3  │  =  │     │     │   │     │     │  =  │  1  │  2  │  3  │ / ? │ _ - │
 * └───────┴─────┴┬────┴─┬───┴──┬──┴───┬─┴────┬┴─────┤   ├─────┴┬────┴─┬───┴──┬──┴───┬─┴────┬┴─────┴─────┘
 *                │      │  . , │   0  │  __  │      │   │      │      │   0  │  . , │      │
 *                │      │      │      │      │      │   │      │      │      │      │      │
 *                └──────┴──────┴──────┴──────┴──────┘   └──────┴──────┴──────┴──────┴──────┘
 */

  [_NUMBERS] = LAYOUT(
    KC_TRNS, KC_PLUS, KC_7, KC_8, KC_9, KC_PLUS,                                       KC_PLUS,   KC_7, KC_8, KC_9, KC_PLUS, KC_TRNS,
    KC_TRNS, KC_0,    KC_4, KC_5, KC_6, KC_MINS,                                       KC_MINS,   KC_4, KC_5, KC_6, KC_EQL,  KC_EQL,
    KC_TRNS, KC_EQL,  KC_1, KC_2, KC_3, KC_EQL, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_EQL,    KC_1, KC_2, KC_3, KC_SLSH, KC_SLSH,
                   KC_TRNS, TD(DOT_COMM), KC_0, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_0, TD(DOT_COMM), KC_TRNS
  ),



/* ┌───────┬─────┬─────┬─────┬─────┬─────┐                          ┌─────┬─────┬─────┬─────┬─────┬─────┐
 * │       │     │     │     │     │     │     Navigation Layer     │ Home│ Pg↓ │ Pg↑ │ End │ ^Bk │ ^<┘ │
 * ├───────┼─────┼─────┼─────┼─────┼─────┤                          ├─────┼─────┼─────┼─────┼─────┼─────┤
 * │       │     │     │     │     │     │                          │ <-- │  ↓  │  ↑  │ --> │ Bksp│ <─┘ │ 
 * ├───────┼─────┼─────┼─────┼─────┼─────┼─────┬─────┐  ┌─────┬─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 * │       │ Alt │ Sft │ Ctl │ Win │     │     │     │  │     │ Menu│ Menu│ ^Bk │ ^<- │ ^-> │ ^Del│ Del │
 * └───────┴─────┴┬────┴─┬───┴──┬──┴───┬─┴────┬┴─────┤  ├─────┴┬────┴─┬───┴──┬──┴───┬─┴────┬┴─────┴─────┘
 *                │      │      │      │      │      │  │  __  │      │      │      │      │
 *                │      │      │      │      │      │  │      │      │      │      │      │
 *                └──────┴──────┴──────┴──────┴──────┘  └──────┴──────┴──────┴──────┴──────┘
 */

    [_NAV] = LAYOUT( 
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                           KC_HOME, KC_PGDN, KC_PGUP, KC_END,  RCTL(KC_BSPC), RCTL(KC_ENT),
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                           KC_LEFT, KC_DOWN,  KC_UP,  KC_RGHT, KC_BSPC,  KC_ENT,
      KC_TRNS, KC_RALT, KC_RSFT, KC_RCTL, KC_RGUI, OSM(MOD_RGUI), KC_TRNS, KC_SPC,   KC_TRNS, KC_APP, KC_APP, RCTL(KC_BSPC), RCTL(KC_LEFT), RCTL(KC_RGHT), RCTL(KC_DEL), KC_DEL, 
                                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),


/* ┌───────┬─────┬─────┬─────┬─────┬─────┐                          ┌─────┬─────┬─────┬─────┬─────┬─────┐
 * │       │ F1  │ F2  │ F3  │ F4  │ F5  │      Function Layer      │ F6  │ F7  │ F8  │ F9  │ F10 │     │
 * ├───────┼─────┼─────┼─────┼─────┼─────┤                          ├─────┼─────┼─────┼─────┼─────┼─────┤
 * │       │ *Tg │ *S+ │ *H+ │ *V+ │ *M+ │                          │     │ F4  │ F5  │ F6  │ F11 │     │
 * ├───────┼─────┼─────┼─────┼─────┼─────┼─────┬─────┐  ┌─────┬─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 * │       │     │ *S- │ *H- │ *V- │ *M- │     │     │  │     │     │     │ F1  │ F2  │ F3  │ F12 │     │
 * └───────┴─────┴┬────┴─┬───┴──┬──┴───┬─┴────┬┴─────┤  ├─────┴┬────┴─┬───┴──┬──┴───┬─┴────┬┴─────┴─────┘
 *                │      │      │      │      │  __  │  │      │      │      │      │      │
 *                │      │      │      │      │      │  │      │      │      │      │      │
 *                └──────┴──────┴──────┴──────┴──────┘  └──────┴──────┴──────┴──────┴──────┘
 */

    [_FUNC] = LAYOUT(
           KC_F11,         KC_F1,         KC_F2,         KC_F3,         KC_F4,         KC_F5,                               
           KC_F6,          KC_F7,         KC_F8,         KC_F9,         KC_F10,        KC_F12,
      RALT(KC_F11),   RALT(KC_F1),   RALT(KC_F2),   RALT(KC_F3),   RALT(KC_F4),   RALT(KC_F5),
        RALT(KC_F6),    RALT(KC_F7),   RALT(KC_F8),   RALT(KC_F9),   RALT(KC_F10),  RALT(KC_F12),
      RCTL(KC_F11),   RCTL(KC_F1),   RCTL(KC_F2),   RCTL(KC_F3),   RCTL(KC_F4),   RCTL(KC_F5),  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
        RCTL(KC_F6),    RCTL(KC_F7),   RCTL(KC_F8),   RCTL(KC_F9),   RCTL(KC_F10),  RCTL(KC_F12),
             KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),


/* ┌───────┬─────┬─────┬─────┬─────┬─────┐                          ┌─────┬─────┬─────┬─────┬─────┬─────┐
 * │       │     │     │     │     │     │         RGB Layer        │     │ F7  │ F8  │ F9  │ F10 │     │
 * ├───────┼─────┼─────┼─────┼─────┼─────┤                          ├─────┼─────┼─────┼─────┼─────┼─────┤
 * │       │ *Tg │ *S+ │ *H+ │ *V+ │ *M+ │                          │     │ F4  │ F5  │ F6  │ F11 │     │
 * ├───────┼─────┼─────┼─────┼─────┼─────┼─────┬─────┐  ┌─────┬─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 * │       │     │ *S- │ *H- │ *V- │ *M- │     │     │  │ --- │     │     │ F1  │ F2  │ F3  │ F12 │     │
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

const uint16_t PROGMEM double_shift_combo[] = {KC_LSFT, KC_RSFT, COMBO_END};
const uint16_t PROGMEM coma_dot_1_combo[] = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM coma_dot_2_combo[] = {KC_2, KC_3, COMBO_END};
const uint16_t PROGMEM d_f_1_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM d_f_2_combo[] = {KC_LPRN, KC_RPRN, COMBO_END};
const uint16_t PROGMEM d_v_1_combo[] = {KC_D, KC_V, COMBO_END};
const uint16_t PROGMEM d_v_a_1_combo[] = {KC_D, KC_V, KC_A, COMBO_END};
const uint16_t PROGMEM d_v_s_1_combo[] = {KC_D, KC_V, KC_S, COMBO_END};
const uint16_t PROGMEM e_i_1_combo[] = {KC_E, KC_I, COMBO_END};
const uint16_t PROGMEM f_c_1_combo[] = {KC_F, KC_C, COMBO_END};
const uint16_t PROGMEM f_c_2_combo[] = {KC_RPRN, KC_RBRC, COMBO_END};
const uint16_t PROGMEM f_c_a_1_combo[] = {KC_F, KC_C, KC_A, COMBO_END};
const uint16_t PROGMEM f_c_a_2_combo[] = {KC_RPRN, KC_RBRC, KC_LBRC, COMBO_END};
const uint16_t PROGMEM f_g_1_combo[] = {KC_F, KC_G, COMBO_END};
const uint16_t PROGMEM f_g_2_combo[] = {KC_RPRN, KC_TILD, COMBO_END};
const uint16_t PROGMEM j_k_1_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM j_k_2_combo[] = {KC_4, KC_5, COMBO_END};
const uint16_t PROGMEM j_k_l_1_combo[] = {KC_J, KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM j_k_l_2_combo[] = {KC_4, KC_5, KC_6, COMBO_END};
const uint16_t PROGMEM j_l_1_combo[] = {KC_J, KC_L, COMBO_END};
const uint16_t PROGMEM j_l_2_combo[] = {KC_4, KC_6, COMBO_END};
const uint16_t PROGMEM k_dot_1_combo[] = {KC_K, KC_DOT, COMBO_END};
const uint16_t PROGMEM k_dot_2_combo[] = {KC_5, KC_3, COMBO_END};
const uint16_t PROGMEM k_l_1_combo[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM k_l_2_combo[] = {KC_5, KC_6, COMBO_END};
const uint16_t PROGMEM m_coma_1_combo[] = {KC_M, KC_COMM, COMBO_END};
const uint16_t PROGMEM m_coma_2_combo[] = {KC_1, KC_2, COMBO_END};
const uint16_t PROGMEM m_dot_1_combo[] = {KC_M, KC_DOT, COMBO_END};
const uint16_t PROGMEM m_dot_2_combo[] = {KC_1, KC_3, COMBO_END};
const uint16_t PROGMEM m_k_1_combo[] = {KC_M, KC_K, COMBO_END};
const uint16_t PROGMEM m_k_2_combo[] = {KC_1, KC_5, COMBO_END};
const uint16_t PROGMEM q_r_1_combo[] = {KC_Q, KC_R, COMBO_END};
const uint16_t PROGMEM q_s_1_combo[] = {KC_Q, KC_S, COMBO_END};
const uint16_t PROGMEM q_w_1_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM s_d_1_combo[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM s_d_2_combo[] = {KC_LPRN, KC_LPRN, COMBO_END};
const uint16_t PROGMEM s_d_f_1_combo[] = {KC_S, KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM s_d_f_2_combo[] = {KC_LPRN, KC_LPRN, KC_RPRN, COMBO_END};
const uint16_t PROGMEM s_f_1_combo[] = {KC_S, KC_F, COMBO_END};
const uint16_t PROGMEM s_f_2_combo[] = {KC_LPRN, KC_RPRN, COMBO_END};
const uint16_t PROGMEM s_g_1_combo[] = {KC_S, KC_G, COMBO_END};
const uint16_t PROGMEM s_g_2_combo[] = {KC_LPRN, KC_TILD, COMBO_END};
const uint16_t PROGMEM s_v_1_combo[] = {KC_S, KC_V, COMBO_END};
const uint16_t PROGMEM u_i_o_1_combo[] = {KC_U, KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM u_i_o_2_combo[] = {KC_7, KC_8, KC_9, COMBO_END};
const uint16_t PROGMEM w_e_r_1_combo[] = {KC_W, KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM x_d_1_combo[] = {KC_X, KC_D, COMBO_END};
const uint16_t PROGMEM x_d_a_1_combo[] = {KC_X, KC_D, KC_A, COMBO_END};
const uint16_t PROGMEM x_d_f_1_combo[] = {KC_X, KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM x_f_1_combo[] = {KC_X, KC_F, COMBO_END};
const uint16_t PROGMEM x_f_a_1_combo[] = {KC_X, KC_F, KC_A, COMBO_END};
const uint16_t PROGMEM z_s_1_combo[] = {KC_Z, KC_S, COMBO_END};


enum combo_events {
  DOUBLE_SHIFT,
  COMBO_coma_dot_1,
  COMBO_coma_dot_2,
  COMBO_d_f_1,
  COMBO_d_f_2,
  COMBO_d_v_1,
  COMBO_d_v_a_1,
  COMBO_d_v_s_1,
  COMBO_e_i_1,
  COMBO_f_c_1,
  COMBO_f_c_2,
  COMBO_f_c_a_1,
  COMBO_f_c_a_2,
  COMBO_f_g_1,
  COMBO_f_g_2,
  COMBO_j_k_1,
  COMBO_j_k_2,
  COMBO_j_k_l_1,
  COMBO_j_k_l_2,
  COMBO_j_l_1,
  COMBO_j_l_2,
  COMBO_k_dot_1,
  COMBO_k_dot_2,
  COMBO_k_l_1,
  COMBO_k_l_2,
  COMBO_m_coma_1,
  COMBO_m_coma_2,
  COMBO_m_dot_1,
  COMBO_m_dot_2,
  COMBO_m_k_1,
  COMBO_m_k_2,
  COMBO_q_r_1,
  COMBO_q_s_1,
  COMBO_q_w_1,
  COMBO_s_d_1,
  COMBO_s_d_2,
  COMBO_s_d_f_1,
  COMBO_s_d_f_2,
  COMBO_s_f_1,
  COMBO_s_f_2,
  COMBO_s_g_1,
  COMBO_s_g_2,
  COMBO_s_v_1,
  COMBO_u_i_o_1,
  COMBO_u_i_o_2,
  COMBO_w_e_r_1,
  COMBO_x_d_1,
  COMBO_x_d_a_1,
  COMBO_x_d_f_1,
  COMBO_x_f_1,
  COMBO_x_f_a_1,
  COMBO_z_s_1,
  COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

combo_t key_combos[] = {
  [DOUBLE_SHIFT] = COMBO_ACTION(double_shift_combo),
  [COMBO_coma_dot_1] = COMBO_ACTION(coma_dot_1_combo),
  [COMBO_coma_dot_2] = COMBO_ACTION(coma_dot_2_combo),
  [COMBO_d_f_1] = COMBO(d_f_1_combo, KC_TAB),
  [COMBO_d_f_2] = COMBO(d_f_2_combo, KC_TAB),
  [COMBO_d_v_1] = COMBO_ACTION(d_v_1_combo),
  [COMBO_d_v_a_1] = COMBO_ACTION(d_v_a_1_combo),
  [COMBO_d_v_s_1] = COMBO_ACTION(d_v_s_1_combo),
  [COMBO_e_i_1] = COMBO(e_i_1_combo, KC_MINS),
  [COMBO_f_c_1] = COMBO_ACTION(f_c_1_combo),
  [COMBO_f_c_2] = COMBO_ACTION(f_c_2_combo),
  [COMBO_f_c_a_1] = COMBO_ACTION(f_c_a_1_combo),
  [COMBO_f_c_a_2] = COMBO_ACTION(f_c_a_2_combo),
  [COMBO_f_g_1] = COMBO(f_g_1_combo, KC_SPC),
  [COMBO_f_g_2] = COMBO(f_g_2_combo, KC_SPC),
  [COMBO_j_k_1] = COMBO(j_k_1_combo, KC_ESC),
  [COMBO_j_k_2] = COMBO(j_k_2_combo, KC_ESC),
  [COMBO_j_k_l_1] = COMBO_ACTION(j_k_l_1_combo),
  [COMBO_j_k_l_2] = COMBO_ACTION(j_k_l_2_combo),
  [COMBO_j_l_1] = COMBO(j_l_1_combo, KC_BSPC),
  [COMBO_j_l_2] = COMBO(j_l_2_combo, KC_BSPC),
  [COMBO_k_dot_1] = COMBO(k_dot_1_combo, KC_RGHT),
  [COMBO_k_dot_2] = COMBO(k_dot_2_combo, KC_RGHT),
  [COMBO_k_l_1] = COMBO(k_l_1_combo, KC_ENT),
  [COMBO_k_l_2] = COMBO(k_l_2_combo, KC_ENT),
  [COMBO_m_coma_1] = COMBO_ACTION(m_coma_1_combo),
  [COMBO_m_coma_2] = COMBO_ACTION(m_coma_2_combo),
  [COMBO_m_dot_1] = COMBO(m_dot_1_combo, KC_APP),
  [COMBO_m_dot_2] = COMBO(m_dot_2_combo, KC_APP),
  [COMBO_m_k_1] = COMBO(m_k_1_combo, KC_LEFT),
  [COMBO_m_k_2] = COMBO(m_k_2_combo, KC_LEFT),
  [COMBO_q_r_1] = COMBO(q_r_1_combo, DYN_REC_START1),
  [COMBO_q_s_1] = COMBO(q_s_1_combo, DYN_REC_STOP),
  [COMBO_q_w_1] = COMBO(q_w_1_combo, DYN_MACRO_PLAY1),
  [COMBO_s_d_1] = COMBO(s_d_1_combo, KC_ENT),
  [COMBO_s_d_2] = COMBO(s_d_2_combo, KC_ENT),
  [COMBO_s_d_f_1] = COMBO_ACTION(s_d_f_1_combo),
  [COMBO_s_d_f_2] = COMBO_ACTION(s_d_f_2_combo),
  [COMBO_s_f_1] = COMBO(s_f_1_combo, KC_BSPC),
  [COMBO_s_f_2] = COMBO(s_f_2_combo, KC_BSPC),
  [COMBO_s_g_1] = COMBO(s_g_1_combo, KC_SPC),
  [COMBO_s_g_2] = COMBO(s_g_2_combo, KC_SPC),
  [COMBO_s_v_1] = COMBO_ACTION(s_v_1_combo),
  [COMBO_u_i_o_1] = COMBO(u_i_o_1_combo, KC_ESC),
  [COMBO_u_i_o_2] = COMBO(u_i_o_2_combo, KC_ESC),
  [COMBO_w_e_r_1] = COMBO(w_e_r_1_combo, KC_ESC),
  [COMBO_x_d_1] = COMBO_ACTION(x_d_1_combo),
  [COMBO_x_d_a_1] = COMBO_ACTION(x_d_a_1_combo),
  [COMBO_x_d_f_1] = COMBO_ACTION(x_d_f_1_combo),
  [COMBO_x_f_1] = COMBO(x_f_1_combo, KC_DEL),
  [COMBO_x_f_a_1] = COMBO_ACTION(x_f_a_1_combo),
  [COMBO_z_s_1] = COMBO_ACTION(z_s_1_combo),
};

void process_combo_event(uint16_t combo_index, bool p) {
  switch(combo_index) {
    case DOUBLE_SHIFT:
      if (p) {
        layer_on(_SYMBOLS);
      } else {
        layer_off(_SYMBOLS);
      }
      break;
    case COMBO_coma_dot_1: if (p) {SEND_STRING(SS_DOWN(X_RCTL)SS_DOWN(X_RGHT));} else {SEND_STRING(SS_UP(X_RGHT)SS_UP(X_RCTL));} break;
    case COMBO_coma_dot_2: if (p) {SEND_STRING(SS_DOWN(X_RCTL)SS_DOWN(X_RGHT));} else {SEND_STRING(SS_UP(X_RGHT)SS_UP(X_RCTL));} break;
    case COMBO_d_v_1: if (p) {tap_code16(RSFT(KC_INS));}  break;
    case COMBO_d_v_a_1: if (p) {SEND_STRING(SS_RCTL("av"));}  break;
    case COMBO_d_v_s_1: if (p) {SEND_STRING(SS_RGUI("`"));}  break;
    case COMBO_f_c_1: if (p) {tap_code16(RCTL(KC_INS));}  break;
    case COMBO_f_c_2: if (p) {tap_code16(RCTL(KC_INS));}  break;
    case COMBO_f_c_a_1: if (p) {SEND_STRING(SS_RCTL("ac"));}  break;
    case COMBO_f_c_a_2: if (p) {SEND_STRING(SS_RCTL("ac"));}  break;
    case COMBO_j_k_l_1: if (p) {SEND_STRING(SS_DOWN(X_RCTL)SS_DOWN(X_DEL));} else {SEND_STRING(SS_UP(X_DEL)SS_UP(X_RCTL));} break;
    case COMBO_j_k_l_2: if (p) {SEND_STRING(SS_DOWN(X_RCTL)SS_DOWN(X_DEL));} else {SEND_STRING(SS_UP(X_DEL)SS_UP(X_RCTL));} break;
    case COMBO_m_coma_1: if (p) {SEND_STRING(SS_DOWN(X_RCTL)SS_DOWN(X_LEFT));} else {SEND_STRING(SS_UP(X_LEFT)SS_UP(X_RCTL));} break;
    case COMBO_m_coma_2: if (p) {SEND_STRING(SS_DOWN(X_RCTL)SS_DOWN(X_LEFT));} else {SEND_STRING(SS_UP(X_LEFT)SS_UP(X_RCTL));} break;
    case COMBO_s_d_f_1: if (p) {SEND_STRING(SS_DOWN(X_RCTL)SS_DOWN(X_DEL));} else {SEND_STRING(SS_UP(X_DEL)SS_UP(X_RCTL));} break;
    case COMBO_s_d_f_2: if (p) {SEND_STRING(SS_DOWN(X_RCTL)SS_DOWN(X_DEL));} else {SEND_STRING(SS_UP(X_DEL)SS_UP(X_RCTL));} break;
    case COMBO_s_v_1: if (p) {SEND_STRING(SS_RCTL("s"));}  break;
    case COMBO_x_d_1: if (p) {tap_code16(RSFT(KC_DEL));}  break;
    case COMBO_x_d_a_1: if (p) {SEND_STRING(SS_RCTL("ax"));}  break;
    case COMBO_x_d_f_1: if (p) {SEND_STRING(SS_DOWN(X_RCTL)SS_DOWN(X_BSPC));} else {SEND_STRING(SS_UP(X_BSPC)SS_UP(X_RCTL));} break;
    case COMBO_x_f_a_1: if (p) {SEND_STRING(SS_RCTL("a")SS_TAP(X_DEL));}  break;
    case COMBO_z_s_1: if (p) {SEND_STRING(SS_RCTL("z"));}  break;
  }
}

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    switch (index) {
        case DOUBLE_SHIFT:
            return 2000;
    }
    return COMBO_TERM;
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
    {0, 19, HSV_GOLD}
);

const rgblight_segment_t PROGMEM nav_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 19, HSV_MAGENTA}
);

const rgblight_segment_t PROGMEM numbers_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 19, HSV_GREEN}
);

const rgblight_segment_t PROGMEM func_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 19, HSV_RED}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    symbols_layer,
    nav_layer,
    numbers_layer,
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
    rgblight_set_layer_state(3, layer_state_cmp(state, 4));
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
            tap_code16(KC_WH_D);
        } else {
            tap_code16(KC_WH_U);
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
