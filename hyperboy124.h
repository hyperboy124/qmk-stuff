// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include QMK_KEYBOARD_H

//#include "eeprom.h"
#include "keyrecords/wrappers.h"
// Shortcut to make keymap more readable

// layer handles
#define SYM_L TG(_NAV)
#define SYM_Q TG(_QWERTY)
#define SYM_M TG(_SYMB)
#define SYM_LS MO(_LAYERSHIFT)
#define SYM_MS MO(_SYMB)
#define SYM_G TG(_GAMEPAD)
#define SYM_D TG(_APT)
#define SYM_C TG(_COLEMAK)
#define SYM_CO TG(_CONVERT)
#define SYM_FUN MO(_FUNC)
#define I3M_MOM MO(_I3WM)
#define I3M_TOG TG(_I3WM)
#define TERMVIM TG(_TERMVI)
#define KC_NAGR LT(_NAV, KC_GRV)
#define KC_NAMI LT(_NAV, KC_MINS)
#define KC_GRE LT(_SYMB, KC_NUBS)
#define KC_ADEN LT(_ADJUST, KC_END)
#define KC_ADPU LT(_ADJUST, KC_PGUP)

// oneshot handles
#define OSM_CAG OSM(MOD_LCTL | MOD_LALT | MOD_LGUI)
#define OSM_LS OSM(MOD_LSFT)
#define OSM_LA OSM(MOD_LALT)
#define OSM_LSA OSM(MOD_LSFT | MOD_LALT)
#define OSM_LCA OSM(MOD_LCTL | MOD_LALT)
#define OSM_AG OSM(MOD_LALT | MOD_LGUI)
#define OSM_SG OSM(MOD_LSFT | MOD_LGUI)
#define OSM_L OSM(MOD_LCTL)
#define OSM_A OSM(MOD_LALT)
#define OSM_G OSM(MOD_LGUI)
#define OSM_S OSM(MOD_LSFT)

#define KC_ALAS LALT_T(KC_PAST)
#define KC_CTPL LCTL_T(KC_BSLS)
#define KC_GES C(G(KC_ESC))

// next workspace previous workspace for i3 window manager
#define KC_NWS G(KC_TAB)
#define KC_PWS LSG(KC_TAB)

// next previous geany tabs
#define OSM_PUP LCTL(KC_PGUP)
#define OSM_PDN LCTL(KC_PGDN)
// unicode characters shortcuts
#define DEGREE UC(0x00b0)
bool     ConfirmedCode     = false;
bool     VimAutoShiftState = true;
bool     TermVIState       = false;
uint16_t VimAutoArray[6]   = {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS};
uint16_t VimIArray[6]      = {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_SPC, KC_I};
uint16_t VIMEDITCODE[6]    = {KC_ENT, KC_N, KC_V, KC_I, KC_M, KC_SPC};
// clang-format off
enum custom_keycodes {
    VIMQUIT = SAFE_RANGE,
    VIMWRIT,
    VIMHELP,
    VIMSPLV,
    VIMSPLI,
    VIMINSE,
    GAMING,
    CLANGER,
    CLANGED,
    IEDITOG,
    VC_GF,
    VC_SC,
    VC_FTT,
    VC_NEXT,
    VC_PREV,
    VC_BUFF,
    VC_COMM,
    VC_INCR,
    VC_FUCK,
    VC_DECR,
    DISCODE,
    FORMCOD,
    SYM_FNK
};
// clang-format on
void ShuffleArrayStack(uint16_t keybit) {
    for (uint8_t vimnumber = 0; vimnumber < 5; vimnumber++) {
        VimAutoArray[vimnumber] = VimAutoArray[vimnumber + 1];
    }
    VimAutoArray[5] = keybit;
}

void CheckArrayStack(void) {
    uint8_t CodeConfirmCounter = 0;
    for (uint8_t vimnumber = 0; vimnumber < 6; vimnumber++) {
        if (VimAutoArray[vimnumber] == VIMEDITCODE[vimnumber]) {
            ConfirmedCode = ++CodeConfirmCounter == 6;
        }
    }
}

void CheckArrayStackI(void) {
    uint8_t CodeConfirmCounter = 0;
    bool ConfirmedCode2 = false;
    for (uint8_t vimnumber = 0; vimnumber < 6; vimnumber++) {
        if (VimAutoArray[vimnumber] == VimIArray[vimnumber]) {
            ConfirmedCode2 = ++CodeConfirmCounter == 2;
        }
        if (ConfirmedCode2) {
            SEND_STRING(SS_TAP(X_BSPC) "I");
            ConfirmedCode2 = false;
        }
    }
}

void checkautoshift(void) {
    if (get_autoshift_state()) {
        autoshift_disable();
        VimAutoShiftState = true;
    } else {
        VimAutoShiftState = false;
    }
}
void setautoshift(void) {
    if (VimAutoShiftState) {
        autoshift_enable();
    } else {
        VimAutoShiftState = false;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_A ... KC_Z:
            if (!record->event.pressed) {
                ShuffleArrayStack(keycode);
            }
            return true;
        case DISCODE:
            if (record->event.pressed) {
                SEND_STRING("```" SS_LCTL("v") "```");
            }
            return true;
        case FORMCOD:
            if (record->event.pressed) {
                SEND_STRING("\e bf\e");
            }
            return true;
        case VC_FUCK:
            if (record->event.pressed) {
                SEND_STRING("fuck you get off my pc");
            }
            return true;
        case CLANGER:
            if (record->event.pressed) {
                SEND_STRING("\ei// clang-format on\e");
            }
            return true;
        case VC_INCR:
            if (record->event.pressed) {
                SEND_STRING("\e n+\e");
            }
            return true;
        case VC_BUFF:
            if (record->event.pressed) {
                SEND_STRING("\e bn\e");
            }
            return true;
        case VC_DECR:
            if (record->event.pressed) {
                SEND_STRING("\e n-\e");
            }
            return true;
        case VC_COMM:
            if (record->event.pressed) {
                SEND_STRING("\e cl\e");
            }
            return true;
        case CLANGED:
            if (record->event.pressed) {
                SEND_STRING("\ei// clang-format off\e");
            }
            return true;
        case IEDITOG:
            if (record->event.pressed) {
                SEND_STRING("\e se");
            }
            return true;
        case GAMING:
            if (record->event.pressed) {
                if (layer_state_is(_GAMEPAD)) {
                    layer_off(_GAMEPAD);
                    layer_off(_QWERTY);
                    layer_off(_NAV);
                } else {
                    layer_on(_GAMEPAD);
                    layer_on(_NAV);
                    layer_on(_QWERTY);
                }
            }
            return true;
        case KC_ENT:
            if (record->event.pressed) {
                if (ConfirmedCode) {
                    ConfirmedCode = false;
                    layer_on(_TERMVI);
                }
                ShuffleArrayStack(keycode);
                if (TermVIState) {
                    TermVIState = false;
                    layer_on(_TERMVI);
                }
            }
            return true;
        case VC_PREV:
            if (record->event.pressed) {
                SEND_STRING("[[");
            }
            return true;
        case VC_NEXT:
            if (record->event.pressed) {
                SEND_STRING("]]");
            }
            return true;
        case VC_SC:
            if (record->event.pressed) {
                SEND_STRING("\e sc");
            }
            return true;
        case VC_FTT:
            if (record->event.pressed) {
                SEND_STRING("f");
                SEND_STRING("tt");
            }
            return true;
        case VC_GF:
            if (record->event.pressed) {
                SEND_STRING("\egf");
            }
            return true;
        case KC_QUOT:
            if (record->event.pressed) {
                CheckArrayStackI();
            }
            return true;
        case KC_SPC:
            if (record->event.pressed) {
                ShuffleArrayStack(keycode);
                CheckArrayStack();
            }
            return true;
        case VIMINSE:
            if (record->event.pressed) {
                SEND_STRING("i");
                TermVIState = true;
            } else {
                layer_off(_TERMVI);
                return false;
            }
            break;
        case VIMSPLV:
            if (record->event.pressed) {
                SEND_STRING(":vsplit ~/");
            } else {
                layer_off(_TERMVI);
                TermVIState = true;
            }
            break;
        case VIMSPLI:
            if (record->event.pressed) {
                SEND_STRING(":split ~/");
            } else {
                layer_off(_TERMVI);
                TermVIState = true;
            }
            break;
        case KC_ESC:
            if (TermVIState) {
                if (record->event.pressed) {
                    register_code(KC_ESC);
                } else {
                    unregister_code(KC_ESC);
                    layer_on(_TERMVI);
                    TermVIState = false;
                }
                return false;
            }
            return true;
        case VIMQUIT:
            if (record->event.pressed) {
                SEND_STRING(":q!\n");
            } else {
                TermVIState = false;
                layer_off(_TERMVI);
                VimAutoArray[5] = KC_ENT;
            }
            break;
        case VIMWRIT:
            if (record->event.pressed) {
                SEND_STRING(":w\n");
            }
            break;
        case VIMHELP:
            if (record->event.pressed) {
                if (layer_state_is(_TERMVI)) {
                    layer_off(_TERMVI);
                } else {
                    layer_on(_TERMVI);
                    SEND_STRING(SS_TAP(X_ESC));
                    TermVIState = true;
                }
            }
            break;
        case SYM_FNK:
            if (record->event.pressed) {
                layer_on(_FUNC);
            } else {
                layer_off(_FUNC);
            }
            return true;
        case KC_ASTG:
            if (record->event.pressed) {
                if (VimAutoShiftState) {
                    VimAutoShiftState = false;
                } else {
                    VimAutoShiftState = true;
                }
                return true;
            }
    }
    return true;
}
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _WORKMAN:
        case _SYMB:
        case _APT:
            setautoshift();
            break;
        default:
            if (get_autoshift_state()) {
                checkautoshift();
            }
            break;
    }
    return state;
}

#include "tapdancesuser.h"
