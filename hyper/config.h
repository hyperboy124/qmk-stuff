/*
Copyright 2018-2022 Mattia Dal Ben <matthewdibi@gmail.com>, Ben Williams @rufusw
t
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* Use I2C or Serial, not both */
#define USE_SERIAL

/* Select hand configuration */
//#define MASTER_LEFT
#define MASTER_RIGHT
// #define EE_HANDS
#undef RGBLIGHT_ENABLE
#undef RGBLED_NUM
#undef RGBLIGHT_ANIMATIONS

#ifndef NO_DEBUG
#define NO_DEBUG
#endif
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
//#define NO_ACTION_ONESHOT
#define AUTO_SHIFT_MODIFIERS
#define COMBO_COUNT 9
#define AUTO_SHIFT_TIMEOUT 115
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define PERMISSIVE_HOLD
#define TAPPING_TERM 198
#undef MK_KINETIC_SPEED
#define MOUSEKEY_INERTIA
#define MOUSEKEY_DELAY 10
#define MOUSEKEY_INTERVAL 10
#define MOUSEKEY_MOVE_DELTA 1
#define MOUSEKEY_MAX_SPEED 30
#define MOUSEKEY_TIME_TO_MAX 45
#define MOUSEKEY_FRICTION 6
#define SPLIT_USB_DETECT
#define UNICODE_SELECTED_MODES UNICODE_MODE_LINUX
