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

#pragma once

#ifdef OLED_DRIVER_ENABLE
  #define OLED_DISPLAY_128X64
#endif

#ifdef RGBLIGHT_ENABLE
  #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
  #define RGBLIGHT_EFFECT_TWINKLE
  // #define RGBLIGHT_EFFECT_KNIGHT
  #define RGBLIGHT_HUE_STEP 16
  #define RGBLIGHT_SAT_STEP 16
  #define RGBLIGHT_VAL_STEP 16
  #define RGBLIGHT_LIMIT_VAL 191
  #define RGBLIGHT_LAYERS
  #define RGBLIGHT_SLEEP
  #define RGBLIGHT_SPLIT
  #define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
  // #define RGBLIGHT_LED_MAP { 10, 11, 13, 12, 14, 17, 15, 16, 19, 1, 9, 8, 6, 7, 5, 2, 4, 3, 1, 0 }
  #define RBGLIGHT_LED_MAP {9,8,6,7,5,3,2,4,1,0,10,12,13,11,14,16,17,15,18,19}
#endif

// If you are using an Elite C rev3 on the slave side, uncomment the lines below:
// #define SPLIT_USB_DETECT
// #define NO_USB_STARTUP_CHECK

// EC11K encoders have a different resolution than other EC11 encoders.
// When using the default resolution of 4, if you notice your encoder skipping
// every other tick, lower the resolution to 2.
#define ENCODER_RESOLUTION 2
#define ENCODER_DIRECTION_FLIP

#define TAPPING_TERM 200
#define PERMISSIVE_HOLD_PER_KEY
#define TAPPING_FORCE_HOLD_PER_KEY

#define ONESHOT_TAP_TOGGLE 3  /* Tapping this number of times holds the key until tapped once again. */

#define COMBO_TERM 60
#define COMBO_TERM_PER_COMBO
// #define COMBO_COUNT 52
