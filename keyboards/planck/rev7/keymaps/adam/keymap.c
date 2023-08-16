#include QMK_KEYBOARD_H

enum planck_layers { _COLEMAK, _LOWER, _RAISE, _ADJUST };

enum planck_keycodes { COLEMAK = SAFE_RANGE };

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

//Tap Dance
enum {
  TD_LEFT_HOME,
  TD_RIGHT_END
};

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

typedef struct {
  bool is_press_action;
  int state;
} tap;


enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};

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

int cur_dance (tap_dance_state_t *state);

void arrow_left_finished (tap_dance_state_t *state, void *user_data);
void arrow_left_reset (tap_dance_state_t *state, void *user_data);

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

void tap_dance_tap_and_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 2
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

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

#define ACTION_TAP_DANCE_TAP_AND_HOLD(tap, hold) \
{ .fn = {NULL, tap_dance_tap_and_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

tap_dance_action_t tap_dance_actions[] = {
  [TD_LEFT_HOME] = ACTION_TAP_DANCE_TAP_AND_HOLD(KC_LEFT, KC_HOME),
  [TD_RIGHT_END] = ACTION_TAP_DANCE_TAP_AND_HOLD(KC_RIGHT, KC_END)
};

/* clang-format off */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Colemak DH
 * ,-------------------------------------------------------------------------------------------------.
 * | Tab    |   Q  |   W  |   F  |   P   |   B  |   J  |      L      |   U   |   Y  |   ;    | Esc   |
 * |--------+------+------+------+-------+------+------+-------------+-------+------+--------+-------|
 * | Bksp   |   A  |   R  |   S  |   T   |   G  |   M  |      N      |   E   |   I  |   O    |  '    |
 * |--------+------+------+------+-------+------+------+-------------+-------+------+--------+-------|
 * | Shift  |   Z  |   X  |   C  |   D   |   V  |   K  |      H      |   ,   |   .  |   /    | Del   |
 * |--------+------+------+------+-------+------+------+-------------+-------+------+--------+-------|
 * |        |      |      | Alt  | Lower | Space/Ctrl  | Enter/Raise |  Win  |      |        |       |
 * `-------------------------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_planck_mit(
    KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,  KC_J,          KC_L,              KC_U,     KC_Y,    KC_SCLN, KC_ESC,
    KC_BSPC, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,  KC_M,          KC_N,              KC_E,     KC_I,    KC_O,    KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,  KC_K,          KC_H,              KC_COMM,  KC_DOT,  KC_SLSH, KC_DEL,
    _______, _______, KC_LGUI, KC_LALT, LOWER,   MT(MOD_LCTL, KC_SPC), LT(RAISE, KC_ENT), KC_LGUI,  _______, _______, _______
),

/* Lower
 * ,-------------------------------------------------------------------------------------.
 * |      |   !  |   @  |   #  |   $   |  %   |   ^  |   &  |   *   |   `  |   ~  |  |   |
 * |------+------+------+------+-------+------+------+------+-------+------+------+------|
 * | Bksp |   =  |   +  |   -  |   _   |      |CapsWd|  [{  |   }]  |   (  |   )  |  \   |
 * |------+------+------+------+------+-------+------+------+-------+------+------+------|
 * |  F5  |  F10 |  F11 |  F12 |CTL-F12|  F8  |      | Left*|  Up  | Down  |Right*| Del  |
 * |------+------+------+------+-------+------+------+------+------+------+-------+------|
 * |      |      |      |      |       |             |      |      |      |       |      |
 * `-------------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_mit(
    _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,       KC_PERC, KC_CIRC, KC_AMPR,          KC_ASTR, KC_GRV,  KC_TILD,          KC_PIPE,
    KC_BSPC, KC_EQL,  KC_PLUS, KC_MINS, KC_UNDS,      _______, CW_TOGG, KC_LBRC,          KC_RBRC, KC_LPRN, KC_RPRN,          KC_BSLS,
    KC_F5,   KC_F10,  KC_F11,  KC_F12,  LCTL(KC_F12), KC_F8,   _______, TD(TD_LEFT_HOME), KC_UP,   KC_DOWN, TD(TD_RIGHT_END), KC_DEL,
    _______, _______, _______, _______, _______,      _______         , _______,          _______, _______, _______,          _______
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |   7  |   8  |   9  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Bksp |      |      |      |      |      |      |      |   4  |   5  |   6  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |   1  |   2  |   3  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |   0  |      |   .  |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_mit(
    _______, _______, _______, _______, _______, _______, _______, _______, KC_7, KC_8,    KC_9,   _______,
    KC_BSPC, _______, _______, _______, _______, _______, _______, _______, KC_4, KC_5,    KC_6,   _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_1, KC_2,    KC_3,   KC_DEL,
    _______, _______, _______, _______, _______, _______         , _______, KC_0, _______, KC_DOT, _______
),

/* Adjust (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * | Flash| Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_mit(
    QK_BOOTLOADER, QK_BOOT, DB_TOGG, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______,
    _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______,       _______, _______, _______, _______, _______         ,  _______, _______, _______, _______, _______
)

};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

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
  else return 8; //magic number. At some point this method will expand to work for more presses
}

//instanalize an instance of 'tap' for the 'x' tap dance.
static tap xtap_state = {
  .is_press_action = true,
  .state = 0
};

void arrow_left_finished (tap_dance_state_t *state, void *user_data) {
  xtap_state.state = cur_dance(state);
  switch (xtap_state.state) {
    case SINGLE_TAP: register_code(KC_LEFT); break;
    case SINGLE_HOLD: layer_on(_RAISE); break;
    case DOUBLE_HOLD: register_code(KC_HOME); break;
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void arrow_left_reset (tap_dance_state_t *state, void *user_data) {
  switch (xtap_state.state) {
    case SINGLE_TAP: unregister_code(KC_LEFT); break;
    case SINGLE_HOLD: layer_off(_RAISE); break;
    case DOUBLE_HOLD: unregister_code(KC_HOME); break;
  }
  xtap_state.state = 0;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;

    switch (keycode) { /* register tap hold actions w/ tap dance*/
        case TD(TD_LEFT_HOME):
        case TD(TD_RIGHT_END):
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
