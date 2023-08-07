/* Copyright 2015-2023 Jack Humbert
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

enum planck_layers { _COLEMAK, _QWERTY, _LOWER, _RAISE, _ADJUST };

enum planck_keycodes { COLEMAK = SAFE_RANGE, QWERTY };

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

//Tap Dance
enum {
  TD_LEFT_HOME,
  TD_LEFT,
  TD_RIGHT_END,
  TD_Z_CTRL,
  TD_X_WIN,
  TD_C_ALT,
  TD_V_CTRL
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

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

tap_dance_action_t tap_dance_actions[] = {
  [TD_LEFT_HOME] = ACTION_TAP_DANCE_DOUBLE(KC_LEFT, KC_HOME),
  [TD_RIGHT_END] = ACTION_TAP_DANCE_DOUBLE(KC_RIGHT, KC_END),
  [TD_Z_CTRL] = ACTION_TAP_DANCE_TAP_HOLD(LCTL(KC_Z), KC_LCTL),
  [TD_X_WIN] = ACTION_TAP_DANCE_TAP_HOLD(LCTL(KC_X), KC_LGUI),
  [TD_C_ALT] = ACTION_TAP_DANCE_TAP_HOLD(LCTL(KC_C), KC_LALT),
  [TD_V_CTRL] = ACTION_TAP_DANCE_TAP_HOLD(LCTL(KC_V), KC_LCTL),
  [TD_LEFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,arrow_left_finished, arrow_left_reset)
};

/* clang-format off */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Colemak DH
 * ,-------------------------------------------------------------------------------------------.
 * | Tab    |   Q  |   W  |   F  |   P  |   B  |   J  |    L   |   U   |   Y  |   ;    | Esc   |
 * |--------+------+------+------+------+------+------+--------+-------+------+--------+-------|
 * | Bksp   |   A  |   R  |   S  |   T  |   G  |   M  |    N   |   E   |   I  |   O    |  '    |
 * |--------+------+------+------+------+------+------+--------+-------+------+--------+-------|
 * | Shift  |   Z  |   X  |   C  |   D  |   V  |   K  |    H   |   ,   |   .  |   /    | Del   |
 * |--------+------+------+------+------+------+------+--------+-------+------+--------+-------|
 * |        |CtrlZ | Win* | Alt* |Ctrl* |   *Space*   | Raise* |Capswrd|      |        |       |
 * `-------------------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_planck_mit(
    KC_TAB,  KC_Q,       KC_W,         KC_F,         KC_P,          KC_B,     KC_J,    KC_L,              KC_U,    KC_Y,    KC_SCLN, KC_ESC,
    KC_BSPC, KC_A,       KC_R,         KC_S,         KC_T,          KC_G,     KC_M,    KC_N,              KC_E,    KC_I,    KC_O,    KC_QUOT,
    KC_LSFT, KC_Z,       KC_X,         KC_C,         KC_D,          KC_V,     KC_K,    KC_H,              KC_COMM, KC_DOT,  KC_SLSH, KC_DEL,
    _______, LCTL(KC_Z), TD(TD_X_WIN), TD(TD_C_ALT), TD(TD_V_CTRL), LT(LOWER, KC_SPC), LT(RAISE, KC_ENT), CW_TOGG, _______, _______, _______
),

/* Qwerty
 * ,---------------------------------------------------------------------------------------.
 * | Tab      |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Esc  |
 * |------+-------+------+------+------+------+------+------+------+------+------+---------|
 * | Bksp     |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+-------+------+------+------+------+------+------+------+------+------+---------|
 * | Shift    |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Del  |
 * |------+-------+------+------+------+------+------+------+------+------+------+---------|
 * | Capsword |Ctrl* | Win* | Alt* |Ctrl* |   *Space*   |Raise*|Left* |  Up  | Down |Right*|
 * `---------------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_mit(
    KC_TAB,  KC_Q,          KC_W,         KC_E,         KC_R,          KC_T,     KC_Y,    KC_U,              KC_I,             KC_O,   KC_P,    KC_ESC,
    KC_BSPC, KC_A,          KC_S,         KC_D,         KC_F,          KC_G,     KC_H,    KC_J,              KC_K,             KC_L,   KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,          KC_X,         KC_C,         KC_V,          KC_B,     KC_N,    KC_M,              KC_COMM,          KC_DOT, KC_SLSH, KC_DEL,
    CW_TOGG, TD(TD_Z_CTRL), TD(TD_X_WIN), TD(TD_C_ALT), TD(TD_V_CTRL), LT(LOWER, KC_SPC), LT(RAISE, KC_ENT), TD(TD_LEFT_HOME), KC_UP,  KC_DOWN, TD(TD_RIGHT_END)
),

/* Lower
 * ,-------------------------------------------------------------------------------------.
 * |      |   !  |   @  |   #  |   $   |  %   |   ^  |   &  |   *   |   `  |   ~  |  |   |
 * |------+------+------+------+-------+------+------+------+-------+------+------+------|
 * | Bksp |   =  |   +  |   -  |   _   |      |      |  [{  |   }]  |   (  |   )  |  \   |
 * |------+------+------+------+------+-------+------+------+-------+------+------+------|
 * |  F5  |  F10 |  F11 |  F12 |CTL-F12|  F8  |      | Left*|  Up  | Down  |Right*| Del  |
 * |------+------+------+------+-------+------+------+------+------+------+-------+------|
 * |      |      |      |      |       |             |      |      |      |       |      |
 * `-------------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_mit(
    _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,       KC_PERC, KC_CIRC, KC_AMPR,          KC_ASTR, KC_GRV,  KC_TILD,          KC_PIPE,
    KC_BSPC, KC_EQL,  KC_PLUS, KC_MINS, KC_UNDS,      _______, _______, KC_LBRC,          KC_RBRC, KC_LPRN, KC_RPRN,          KC_BSLS,
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
 * |      |      |      |      |      |             |      |      |      |Colemk|Qwerty|
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_mit(
    QK_BOOTLOADER, QK_BOOT, DB_TOGG, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______,
    _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______,       _______, _______, _______, _______, _______         ,  _______, _______, _______, COLEMAK, QWERTY
)

};
/* clang-format on */

#ifdef AUDIO_ENABLE
float plover_song[][2]    = SONG(PLOVER_SOUND);
float plover_gb_song[][2] = SONG(PLOVER_GOODBYE_SOUND);
#endif

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
        case TD(TD_Z_CTRL):
        case TD(TD_X_WIN):
        case TD(TD_C_ALT):
        case TD(TD_V_CTRL):
            action = &tap_dance_actions[TD_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            return true;
            break;
        case QWERTY:
            if (record->event.pressed) {
                print("mode just switched to qwerty and this is a huge string\n");
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
            break;
        case COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
            break;
    }
    return true;
}

/* clang-format off */
float melody[8][2][2] = {
    {{440.0f, 8}, {440.0f, 24}},
    {{440.0f, 8}, {440.0f, 24}},
    {{440.0f, 8}, {440.0f, 24}},
    {{440.0f, 8}, {440.0f, 24}},
    {{440.0f, 8}, {440.0f, 24}},
    {{440.0f, 8}, {440.0f, 24}},
    {{440.0f, 8}, {440.0f, 24}},
    {{440.0f, 8}, {440.0f, 24}},
};
/* clang-format on */

#define JUST_MINOR_THIRD 1.2
#define JUST_MAJOR_THIRD 1.25
#define JUST_PERFECT_FOURTH 1.33333333
#define JUST_TRITONE 1.42222222
#define JUST_PERFECT_FIFTH 1.33333333

#define ET12_MINOR_SECOND 1.059463
#define ET12_MAJOR_SECOND 1.122462
#define ET12_MINOR_THIRD 1.189207
#define ET12_MAJOR_THIRD 1.259921
#define ET12_PERFECT_FOURTH 1.33484
#define ET12_TRITONE 1.414214
#define ET12_PERFECT_FIFTH 1.498307

deferred_token tokens[8];

uint32_t reset_note(uint32_t trigger_time, void *note) {
    *(float*)note = 440.0f;
    return 0;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    cancel_deferred_exec(tokens[index]);
    if (clockwise) {
        melody[index][1][0] = melody[index][1][0] * ET12_MINOR_SECOND;
        melody[index][0][0] = melody[index][1][0] / ET12_PERFECT_FIFTH;
        audio_play_melody(&melody[index], 2, false);
    } else {
        melody[index][1][0] = melody[index][1][0] / ET12_MINOR_SECOND;
        melody[index][0][0] = melody[index][1][0] * ET12_TRITONE;
        audio_play_melody(&melody[index], 2, false);
    }
    tokens[index] = defer_exec(1000, reset_note, &melody[index][1][0]);
    return false;
}

bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
#ifdef AUDIO_ENABLE
            static bool play_sound = false;
#endif
            if (active) {
#ifdef AUDIO_ENABLE
                if (play_sound) {
                    PLAY_SONG(plover_song);
                }
#endif
                layer_on(_ADJUST);
            } else {
#ifdef AUDIO_ENABLE
                if (play_sound) {
                    PLAY_SONG(plover_gb_song);
                }
#endif
                layer_off(_ADJUST);
            }
#ifdef AUDIO_ENABLE
            play_sound = true;
#endif
            break;
        }
    }
    return true;
}
