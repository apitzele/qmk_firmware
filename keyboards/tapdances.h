#include QMK_KEYBOARD_H

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
{ .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

#define ACTION_TAP_DANCE_TAP_AND_HOLD(tap, hold) \
{ .fn = {NULL, tap_dance_tap_and_hold_finished, tap_dance_tap_and_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1) {
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

// boilerplate for holds
typedef struct {
  bool is_press_action;
  int state;
} tap;

//instanalize an instance of 'tap' for the 'x' tap dance.
static tap xtap_state = {
  .is_press_action = true,
  .state = 0
};

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
};

int cur_dance (tap_dance_state_t *state);

int cur_dance (tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    /*
     * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
     * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
     * keystrokes of the key, and not the 'double tap' action/macro.
    */
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  return 8; //magic number. At some point this method will expand to work for more presses
}


void tap_dance_tap_and_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
       case SINGLE_TAP:
            register_code16(tap_hold->tap);
            break;
       case SINGLE_HOLD:
            register_code16(tap_hold->tap);
            break;
       case DOUBLE_HOLD:
            register_code16(tap_hold->hold);
	        break;
   }
}

void tap_dance_tap_and_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    switch (xtap_state.state) {
       case SINGLE_TAP:
            unregister_code16(tap_hold->tap);
            break;
       case SINGLE_HOLD:
            unregister_code16(tap_hold->tap);
            break;
       case DOUBLE_HOLD:
            unregister_code16(tap_hold->hold);
		break;
   }
}


//Tap dances
enum {
  T_DEL,
  T_LT_HM,
  T_RT_ED,
  T_Z,
  T_X,
  T_C,
  T_D,
  T_V,
  T_F,
  T_H,
  T_Q,
  T_W,
  T_SLASH
};

void slash_finished (tap_dance_state_t *state, void *user_data);
void slash_reset (tap_dance_state_t *state, void *user_data);

tap_dance_action_t tap_dance_actions[] = {
  [T_DEL] = ACTION_TAP_DANCE_TAP_AND_HOLD (KC_DEL, RSFT(KC_DEL)),
  [T_LT_HM] = ACTION_TAP_DANCE_TAP_AND_HOLD(KC_LEFT, KC_HOME),
  [T_RT_ED] = ACTION_TAP_DANCE_TAP_AND_HOLD(KC_RIGHT, KC_END),
  [T_SLASH] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, slash_finished, slash_reset),
  [T_X] = ACTION_TAP_DANCE_TAP_HOLD(KC_X, LCTL(KC_X)),
  [T_C] = ACTION_TAP_DANCE_TAP_HOLD(KC_C, LCTL(KC_C)),
  [T_D] = ACTION_TAP_DANCE_TAP_HOLD(KC_D, LCTL(KC_S)), // Hold D = Ctrl + S
  [T_V] = ACTION_TAP_DANCE_TAP_HOLD(KC_V, LCTL(KC_V)),
  [T_F] = ACTION_TAP_DANCE_TAP_HOLD(KC_F, LCTL(KC_F)),
  [T_W] = ACTION_TAP_DANCE_TAP_HOLD(KC_W, LCTL(KC_A)), // Hold W = Ctrl + A
  [T_H] = ACTION_TAP_DANCE_TAP_HOLD(KC_H, LCTL(KC_H)),
  [T_Q] = ACTION_TAP_DANCE_TAP_HOLD(KC_Q, KC_ESC)
};

void slash_finished (tap_dance_state_t *state, void *user_data) {
  xtap_state.state = cur_dance(state);
  switch (xtap_state.state) {
    case SINGLE_TAP: register_code(KC_SLSH); break;
    case SINGLE_HOLD:
	    register_code(KC_RSFT);
   		register_code(KC_SLSH);
	    break;
    case DOUBLE_HOLD:
	    register_code(KC_RCTL);
   		register_code(KC_SLSH);
		break;
  }
}

void slash_reset (tap_dance_state_t *state, void *user_data) {
  switch (xtap_state.state) {
    case SINGLE_TAP: unregister_code(KC_SLSH); break;
    case SINGLE_HOLD:
	    unregister_code(KC_RSFT);
   		unregister_code(KC_SLSH);
	    break;
    case DOUBLE_HOLD:
        unregister_code(KC_RCTL);
   		unregister_code(KC_SLSH);
        break;
  }
  xtap_state.state = 0;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;

    switch (keycode) { /* register tap hold actions w/ tap dance*/
        case TD(T_X):
        case TD(T_C):
        case TD(T_V):
        case TD(T_F):
        case TD(T_D):
	    case TD(T_H):
		case TD(T_W):
        case TD(T_Q):
            action = &tap_dance_actions[TD_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            return true;
            break;
    }
    return true;
}