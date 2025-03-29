#include QMK_KEYBOARD_H

enum custom_keycodes {
  MAC_PRFX
};

typedef struct {
  uint16_t tap;
  uint16_t hold;
  uint16_t held;
} tap_dance_tap_hold_t;
tap_dance_action_t *action;

enum tap_dance_codes {
  T_Q,
  T_W,
  T_F,
  T_Z,
  T_X,
  T_C,
  T_D,
  T_V,
  T_H,
  T_QUOT,
  T_LBRC,
  T_RBRC,
  T_GRV,
  T_BSLS,
  T_SLASH
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MAC_PRFX:
    if (record->event.pressed) {
      SEND_STRING(SS_LSFT(SS_TAP(X_P)) SS_DELAY(100) SS_LSFT(SS_TAP(X_2)));
    }
    break;

    case TD(T_Q):
    case TD(T_W):
    case TD(T_F):
    case TD(T_Z):
    case TD(T_X):
    case TD(T_C):
    case TD(T_D):
    case TD(T_V):
    case TD(T_H):
    case TD(T_QUOT):
    case TD(T_LBRC):
    case TD(T_RBRC):
    case TD(T_GRV):
    case TD(T_BSLS):
        action = &tap_dance_actions[TD_INDEX(keycode)];
        if (!record->event.pressed && action->state.count && !action->state.finished) {
            tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
            tap_code16(tap_hold->tap);
        }
        break;
  }
  return true;
}

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}


#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

typedef struct {
    bool is_press_action;
    uint8_t step;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP,
    MORE_TAPS
};

static tap dance_state[3];

uint8_t dance_step(tap_dance_state_t *state);

uint8_t dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}


void on_T_SLASH(tap_dance_state_t *state, void *user_data);
void T_SLASH_finished(tap_dance_state_t *state, void *user_data);
void T_SLASH_reset(tap_dance_state_t *state, void *user_data);

void on_T_SLASH(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_SLASH);
        tap_code16(KC_SLASH);
        tap_code16(KC_SLASH);
    }
    if(state->count > 3) {
        tap_code16(KC_SLASH);
    }
}

void T_SLASH_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[0].step = dance_step(state);
    switch (dance_state[0].step) {
        case SINGLE_TAP: register_code16(KC_SLASH); break;
        case SINGLE_HOLD: register_code16(KC_QUES); break;
        case DOUBLE_TAP: register_code16(KC_SLASH); register_code16(KC_SLASH); break;
        case DOUBLE_HOLD: register_code16(RCTL(KC_SLASH)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_SLASH); register_code16(KC_SLASH);
    }
}

void T_SLASH_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[0].step) {
        case SINGLE_TAP: unregister_code16(KC_SLASH); break;
        case SINGLE_HOLD: unregister_code16(KC_QUES); break;
        case DOUBLE_TAP: unregister_code16(KC_SLASH); break;
        case DOUBLE_HOLD: unregister_code16(RCTL(KC_SLASH)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_SLASH); break;
    }
    dance_state[0].step = 0;
}

tap_dance_action_t tap_dance_actions[] = {
        [T_Q] = ACTION_TAP_DANCE_TAP_HOLD(KC_Q, KC_ESCAPE),
        [T_W] = ACTION_TAP_DANCE_TAP_HOLD(KC_W, LCTL(KC_A)),
        [T_F] = ACTION_TAP_DANCE_TAP_HOLD(KC_F, LCTL(KC_F)),
        [T_Z] = ACTION_TAP_DANCE_TAP_HOLD(KC_Z, KC_TAB),
        [T_X] = ACTION_TAP_DANCE_TAP_HOLD(KC_X, LCTL(KC_X)),
        [T_C] = ACTION_TAP_DANCE_TAP_HOLD(KC_C, LCTL(KC_C)),
        [T_D] = ACTION_TAP_DANCE_TAP_HOLD(KC_D, LCTL(KC_S)),
        [T_V] = ACTION_TAP_DANCE_TAP_HOLD(KC_V, LCTL(KC_V)),
        [T_H] = ACTION_TAP_DANCE_TAP_HOLD(KC_H, LCTL(KC_H)),
        [T_QUOT] = ACTION_TAP_DANCE_TAP_HOLD(KC_QUOTE, KC_QUOTE),
        [T_LBRC] = ACTION_TAP_DANCE_TAP_HOLD(KC_LBRC, KC_LBRC),
        [T_RBRC] = ACTION_TAP_DANCE_TAP_HOLD(KC_RBRC, KC_RBRC),
        [T_GRV] = ACTION_TAP_DANCE_TAP_HOLD(KC_GRAVE, KC_GRAVE),
        [T_BSLS] = ACTION_TAP_DANCE_TAP_HOLD(KC_BSLS, KC_BSLS),
        [T_SLASH] = ACTION_TAP_DANCE_FN_ADVANCED(on_T_SLASH, T_SLASH_finished, T_SLASH_reset)
};