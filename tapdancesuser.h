td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed)
            return TD_SINGLE_TAP;
        else
            return TD_SINGLE_HOLD;
    } else if (state->count == 2)
        return TD_DOUBLE_TAP;
    else
        return TD_UNKNOWN;
}
static td_tap_t ql_tap_state = {.is_press_action = true, .state = TD_NONE};

void i3_finished(qk_tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            layer_invert(_SYMB);
            break;
        case TD_SINGLE_HOLD:
            layer_on(_I3WM);
            break;
        case TD_DOUBLE_TAP:
            if (layer_state_is(_QWERTY)) {
                layer_off(_QWERTY);
            } else {
                layer_on(_QWERTY);
            }
            break;
        default:
            break;
    }
}
void i3_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (ql_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(_I3WM);
    }
    ql_tap_state.state = TD_NONE;
}
void ql_finished(qk_tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            add_oneshot_mods(MOD_LCTL);
            break;
        case TD_SINGLE_HOLD:
            layer_on(_LAYERSHIFT);
            break;
        case TD_DOUBLE_TAP:
            if (layer_state_is(_NAV)) {
                layer_off(_NAV);
            } else {
                layer_on(_NAV);
            }
            break;
        default:
            break;
    }
}

void ql_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (ql_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(_LAYERSHIFT);
    }
    ql_tap_state.state = TD_NONE;
}

void bspc_finished(qk_tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            register_code16(KC_BSPC);
            break;
        case TD_SINGLE_HOLD:
            register_code16(KC_LCTL);
            register_code16(KC_BSPC);
            break;
        case TD_DOUBLE_TAP:
            register_code16(KC_DEL);
            break;
        default:
            break;
    }
}

void bspc_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_BSPC);
            break;
        case TD_SINGLE_HOLD:
            unregister_code16(KC_LCTL);
            unregister_code16(KC_BSPC);
            break;
        case TD_DOUBLE_TAP:
            unregister_code16(KC_DEL);
            break;
        case TD_UNKNOWN:
        case TD_NONE:
            break;
    }
    ql_tap_state.state = TD_NONE;
}

void spc_finished(qk_tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            if (layer_state_is(!_TERMVI)) {
                CheckArrayStackI();
            }
            ShuffleArrayStack(KC_SPC);
            register_code16(KC_SPC);
            break;
        case TD_SINGLE_HOLD:
            layer_on(_ONESHOTS);
            break;
        case TD_DOUBLE_TAP:
            register_code16(KC_ENT);
            ShuffleArrayStack(KC_ENT);
            CheckArrayStack();
            if (ConfirmedCode) {
                ConfirmedCode = false;
                layer_on(_TERMVI);
            }
            if (TermVIState) {
                TermVIState = false;
                layer_on(_TERMVI);
            }
            break;
        default:
            break;
    }
}

void spc_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_SPC);
            break;
        case TD_SINGLE_HOLD:
            layer_off(_ONESHOTS);
            break;
        case TD_DOUBLE_TAP:
            unregister_code16(KC_ENT);
            break;
        case TD_UNKNOWN:
        case TD_NONE:
            break;
    }
    ql_tap_state.state = TD_NONE;
}

void pgup_finished(qk_tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            register_code16(KC_PGDN);
            break;
        case TD_SINGLE_HOLD:
            layer_on(_ADJUST);
            break;
        case TD_DOUBLE_TAP:
            register_code16(KC_PGUP);
            break;
        default:
            break;
    }
}

void pgup_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_PGDN);
            break;
        case TD_SINGLE_HOLD:
            layer_off(_ADJUST);
            break;
        case TD_DOUBLE_TAP:
            unregister_code16(KC_PGUP);
            break;
        case TD_UNKNOWN:
        case TD_NONE:
            break;
    }
    ql_tap_state.state = TD_NONE;
}

qk_tap_dance_action_t tap_dance_actions[] = {[TD_I3] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, i3_finished, i3_reset), [TD_COS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ql_finished, ql_reset), [TD_BSPC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, bspc_finished, bspc_reset), [TD_SPC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, spc_finished, spc_reset), [TD_PGUP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, pgup_finished, pgup_reset), [TD_GUI] = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, SGUI(KC_Q)), [TD_VIVI] = ACTION_TAP_DANCE_DOUBLE(KC_V, LCTL(KC_V)), [TD_HOME] = ACTION_TAP_DANCE_DOUBLE(KC_HOME, KC_END), [TD_LEFT] = ACTION_TAP_DANCE_DOUBLE(KC_LEFT, LCTL(KC_LEFT)), [TD_DOWN] = ACTION_TAP_DANCE_DOUBLE(KC_DOWN, LCTL(KC_DOWN)), [TD_RGHT] = ACTION_TAP_DANCE_DOUBLE(KC_RGHT, LCTL(KC_RGHT))};
uint16_t              get_tapping_term(uint16_t keycode, keyrecord_t *record) {
                 switch (keycode) {
                     case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
            return 178;
                     default:
            return TAPPING_TERM;
    }
}
