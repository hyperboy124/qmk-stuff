#include QMK_KEYBOARD_H
// clang-format off
enum layer_names {
    _APT,
    _WORKMAN,
    _QWERTY,
    _COLEMAK,
    _CONVERT,
    _GAMEPAD,
    _TERMVI,
    _NAV,
    _I3WM,
    _LAYERSHIFT,
    _ONESHOTS,
    _ADJUST,
    _SYMB,
    _FUNC
};
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP
} td_state_t;
typedef struct {
    bool       is_press_action;
    td_state_t state;
} td_tap_t;
enum {
    TD_GUI,
    TD_I3,
    TD_COS,
    TD_BSPC,
    TD_SPC,
    TD_VIVI,
    TD_HOME,
    TD_PGUP,
    TD_LEFT,
    TD_DOWN,
    TD_RGHT
};
enum combo_events {
termvicombo,
termvicombo2,
numcombo,
mousecombo,
youcombo,
qucombo,
discombo
};
#include "hyperboy124.h"
const uint16_t PROGMEM wcombo1[]               = {KC_R, KC_S, KC_T, KC_H, COMBO_END};
// const uint16_t PROGMEM vcombo1[]               = {KC_H, KC_J, KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM vcombo1[]               = {KC_J, KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM numcombo9[]               = {KC_8, KC_1,COMBO_END};
const uint16_t PROGMEM numcombo7[]               = {KC_4, KC_1, KC_2,COMBO_END};
// const uint16_t PROGMEM numcombo10[]               = {KC_8, KC_4, KC_2, KC_0,COMBO_END};
const uint16_t PROGMEM numcombo10[]               = {KC_8, KC_4, KC_2,COMBO_END};
const uint16_t PROGMEM numcombo5[]               = {KC_4, KC_1,COMBO_END};
const uint16_t PROGMEM numcombo6[]               = {KC_4, KC_2,COMBO_END};
const uint16_t PROGMEM numcombo3[]               = {KC_1, KC_2,COMBO_END};
// const uint16_t PROGMEM qcombo1[]               = {KC_N, KC_E, KC_A, KC_I, COMBO_END};
const uint16_t PROGMEM qcombo1[]               = {KC_N, KC_E, KC_A, COMBO_END};
const uint16_t PROGMEM discombo1[]               = {KC_DOT, KC_SCLN, COMBO_END};
const uint16_t PROGMEM qcombo2[]               = {KC_N, KC_E,COMBO_END};
const uint16_t PROGMEM ycombo1[]               = {KC_A, KC_E, COMBO_END};
const uint16_t PROGMEM ycombo2[]               = {KC_A, KC_I, COMBO_END};
combo_t                key_combos[COMBO_COUNT] = {
    [termvicombo] = COMBO_ACTION(wcombo1),
    [termvicombo2] = COMBO_ACTION(vcombo1),
    [mousecombo] = COMBO_ACTION(qcombo1),
    [numcombo] = COMBO_ACTION(numcombo10),
    [youcombo] = COMBO_ACTION(ycombo2),
    [qucombo] = COMBO_ACTION(qcombo2),
    [discombo] = COMBO_ACTION(discombo1),
    COMBO(ycombo1, KC_ENT),
    COMBO(numcombo9, KC_9),
    COMBO(numcombo7, KC_7),
    COMBO(numcombo6, KC_6),
    COMBO(numcombo5, KC_5),
    COMBO(numcombo3, KC_3)
};

// clang-format on
void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case termvicombo:
            if (pressed) {
                SEND_STRING("\e");
                layer_on(_TERMVI);
                TermVIState = true;
            }
            break;
        case termvicombo2:
            if (pressed) {
                layer_off(_TERMVI);
                layer_off(_QWERTY);
                TermVIState = false;
            }
            break;
        case mousecombo:
            if (pressed) {
                layer_on(_SYMB);
            }
            break;
        case numcombo:
            if (pressed) {
                layer_off(_SYMB);
            }
            break;
        case youcombo:
            if (pressed) {
                SEND_STRING("you");
            }
            break;
        case qucombo:
            if (pressed) {
                SEND_STRING("qu");
            }
            break;
        case discombo:
            if (pressed) {
                register_code16(KC_LCTL);
                tap_code(KC_K);
                unregister_code16(KC_LCTL);
            }
            break;
    }
}
// clang-format off
//begin fancy layout swapping nonsense
#define LAYOUT_redox_wrapper(...) LAYOUT(__VA_ARGS__)
#define LAYOUT_redox_base(...) LAYOUT_redox_base_wrapper(__VA_ARGS__)
#define LAYOUT_redox_base_wrapper( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
  ) LAYOUT_redox_wrapper( \
     KC_NAGR ,     ________________NUMBER_LEFT________________,                                            ________________NUMBER_RIGHT_______________,  KC_EQL, \
     KC_TAB  , K01   , K02   , K03   , K04   , K05   ,  SYM_L ,                                         SYM_L , K06   , K07   , K08   , K09   , K0A,    KC_MINS, \
     KC_ESC  , K11   , K12   , K13   , K14   , K15   , KC_LBRC,                                       KC_RBRC , K16   , K17   , K18   , K19   , K1A,        K1B, \
     KC_LSPO , K21   , K22   , K23   , K24   , K25   , TD(TD_PGUP), KC_PGDN,                  TD(TD_HOME), KC_ADEN, K26   , K27   , K28   , K29   , K2A,    KC_RSPC, \
   TD(TD_GUI), OSM_SG ,  KC_GRE, KC_ALAS, TD(TD_COS) , TD(TD_BSPC),  KC_NO,                   KC_NO, TD(TD_SPC), TD(TD_I3) ,  TD(TD_LEFT) , TD(TD_DOWN), KC_UP, TD(TD_RGHT) \
)

/* blank layout to copy
 [_blank] = LAYOUT_redox_wrapper(
      _______, _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______ ,_______ ,     _______ ,    _______, _______,         _______, _______,     _______,      _______, _______, _______, _______
  ),
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_WORKMAN] = LAYOUT_redox_base(
        _________________WORKMAN_L1________________, _________________WORKMAN_R1________________,
        _________________WORKMAN_L2________________, _________________WORKMAN_R2________________,
        _________________WORKMAN_L3________________, _________________WORKMAN_R3________________
    ),
    [_QWERTY] = LAYOUT_redox_base(
        _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
        _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
        _________________QWERTY_L3_________________, _________________QWERTY_R3_________________
    ),
    [_COLEMAK] = LAYOUT_redox_base(
        _________________KLINGON_L1________________, _________________KLINGON_R1________________,
        _________________KLINGON_L2________________, _________________KLINGON_R2________________,
        _________________KLINGON_L3________________, _________________KLINGON_R3________________
    ),
    [_APT] = LAYOUT_redox_base(
        ___________________APT_L1__________________, ___________________APT_R1__________________,
        ___________________APT_L2__________________, ___________________APT_R2__________________,
        ___________________APT_L3__________________, ___________________APT_R3__________________
    ),
    [_CONVERT] = LAYOUT_redox_wrapper(
       KC_ESC, ________________NUMBER_LEFT_1______________,                                             ________________NUMBER_RIGHT_1_____________, _______,
       KC_TAB, _______, _______, _______, _______, _______, KC_VOLD,                           KC_VOLU, _______, _______, _______, _______, _______, _______,
      CAPSWRD, _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______, _______,
      KC_LSFT, _______, _______, _______, _______, _______, KC_PGUP, KC_PGDN,         KC_HOME,  KC_END, _______, _______, _______, _______, _______, KC_RSFT,
      KC_LCTL, KC_LALT, _______, KC_LGUI,      _______,     KC_BSPC,  KC_DEL,          KC_ENT,  KC_SPC,     _______,      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT
    ),
    [_GAMEPAD] = LAYOUT_redox_wrapper(
      _______, ________________NUMBER_LEFT_1______________,                                             ________________NUMBER_RIGHT_1_____________, _______,
      _______, _______,    KC_F, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______, _______,
      _______, _______,    KC_C,    KC_W,    KC_D, _______, _______,                           _______, _______, _______, _______, _______, _______, _______,
      _______, _______,    KC_S,    KC_X, _______, _______, KC_BSPC,  KC_DEL,          KC_ENT, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______,      _______,      KC_SPC, KC_LSFT,         _______, _______,       SYM_L,      KC_LEFT, KC_DOWN, _______, KC_RGHT
    ),
    [_TERMVI] = LAYOUT_redox_wrapper(
      _______, ________________NUMBER_LEFT_1______________,                                             ________________NUMBER_RIGHT_1_____________, _______,
      _______, _______, _______, _______, S(KC_4), VC_COMM, _______,                           _______, _______, _______, _______, _______, _______, _______,
      _______, __________________VIM_3____________________, VC_BUFF,                              KC_B, _________________VIM_NAV___________________,    KC_W,
      _______, _______, _______, _______, _______, TD(TD_VIVI), _______, _______,     _______, _______, VIMSPLI, VIMSPLV, IEDITOG,S(KC_COMM),S(KC_DOT), KC_U,
      _______, _______, _______, _______,     _______,      _______, _______,         _______, _______,     _______,      _______, _______, _______, _______
    ),
    [_NAV] = LAYOUT_redox_wrapper(
      _______, _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______,                           _______, KC_BTN2, ________________MOUSE_WHEEL________________,
      _______, _______, _______, _______, _______, _______, _______,                           _______, KC_BTN1, _________________MOUSE_MOVE________________,
      _______, _______, _______, _______, _______, _______, _______, _______,         KC_BTN2, _______, KC_BTN3, _________________VIM_NAV___________________,
      _______, _______, _______, _______,      _______,     _______, _______,         KC_BTN1, _______,       SYM_L,      _______, _______, _______, _______
    ),
    [_SYMB] = LAYOUT_redox_wrapper(
     OSM_CAG , ___________________BLANK___________________,                                             OSM_SG , _______, _______, _______, _______, _______,
     KC_VOLU , ___________________BLANK___________________, _______,                          _______ , KC_PSLS, KC_PAST, _______, _______, KC_PMNS, _______,
     KC_VOLD , _______, _______, _______, _______, _______,  KC_GES,                          C(KC_K) , _______,    KC_8,    KC_4,    KC_2,    KC_0, _______,
     OSM_AG  , _______, _______, _______,  KC_EQL, _______, _______, _______,         _______, _______, KC_PSCR, _______, _______, _______, _______, _______,
     OSM_G   , _______, _______, _______,      _______,     _______, _______,         _______,   KC_1,       KC_SPC,      _______, _______, _______, _______
    ),
    [_ADJUST] = LAYOUT_redox_wrapper(
     _______, _______, _______, _______, _______, _______,                                              _______, _______, _______, _______, _______, _______,
     _______, QK_BOOT   , _______, _______, _______, _______, _______ ,                        _______, _______, _______, _______,_______ ,_______ , _______,
     _______, ________________AUTO_SHIFT_________________, _______ ,  SYM_Q ,                  _______, _______, _______, _______, _______, _______, _______,
     _______, DT_PRNT, DT_DOWN,  DT_UP , CAPSWRD, _______ ,_______ ,_______ ,         _______, _______, _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______,     _______,    CAPSWRD, _______,            _______, _______,     _______,      _______, _______, _______, _______
    ),
    [_I3WM] = LAYOUT_redox_wrapper(
      _______, _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
      _______, ________________NUMBER_RIGHT_______________, _______,                           _______, _______, G(KC_ENT), G(KC_SPC), C(KC_K), C(S(KC_A)), _______,
      _______, ________________NUMBER_LEFT________________, _______,                           _______, OSM_LSA, ________________I3WM_ADJUST________________,
      _______, G(KC_T), _______, G(KC_D), OSM_LCA, _______, _______, _______,         _______, _______, _______, _________________I3WM_MOVE_________________,
      _______, _______, _______, _______,      _______,      OSM_LS,  OSM_LA,         _______, _______,     _______,      _______, _______, _______, _______
    ),
    [_FUNC] = LAYOUT_redox_wrapper(
      _______, _________________FUNC_4____________________,                                             _______, _______, _______, _______, _______, _______,
      _______, _________________FUNC_2____________________, _______,                           _______, _________________UNICODE_1_________________         ,
      _______, _________________FUNC_1____________________, _______,                           _______, _________________UNICODE_2_________________         ,
       OSM_LS, _________________FUNC_3____________________, _______, _______,         _______, _______,  KC_GRV, KC_BSLS,  DEGREE,  KC_EQL, KC_MINS, _______,
      _______, _______, _______, _______,      _______,     _______, _______,         _______, _______,     _______,      _______, _______, _______, _______
    ),
    [_LAYERSHIFT] = LAYOUT_redox_wrapper(
      _______, _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
      KC_VOLU, DISCODE, OSM_LSA, OSM_PUP, OSM_PDN, _______, _______,                           _______, _______, _______, _______, _______, _______, _______,
      KC_VOLD, _______________LAYER_SHIFT_1_______________, _______,                           _______, ______________LAYOUT_SHIFT_1_______________, _______,
      _______, _______, I3M_TOG, CAPSWRD,   OSM_L,  SYM_CO, _______, _______,         _______, KC_WH_U, KC_VOLD, _______, _______, OSM_LCA, _______, _______,
      _______, _______, _______, _______,      _______,     _______, _______,         _______, KC_WH_D,      SYM_FNK,     _______, _______, _______, _______
    ),
    [_ONESHOTS] = LAYOUT_redox_wrapper(
      _______, _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______,                           _______, CLANGER, VC_INCR,  VC_FTT, _______, _______, _______,
      _______,   OSM_S,   OSM_L,   OSM_A,   OSM_G, C(KC_W), C(KC_T),                           _______, FORMCOD,   VC_GF, VC_PREV, VC_NEXT,   VC_SC, _______,
      _______, _______, _______, _______, C(KC_C), C(KC_V), _______, _______,         _______, _______, CLANGED, VC_DECR, _______, _______, _______, _______,
      _______, _______, _______ ,_______ ,     _______ ,    _______, _______,         _______, _______,     _______,      _______, _______, _______, _______
  ),
};
// clang-format on
