#include QMK_KEYBOARD_H

enum planck_layers { _COLEMAK, _LOWER, _RAISE, _ADJUST };

enum planck_keycodes { COLEMAK = SAFE_RANGE };

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
/*
enum combos {
  Z_T_MT,
  Z_X_MT,
  A_T_MT,
  X_C_MT,
  D_V_MT,
  R_S_MT,
  W_F_MT,
  S_T_MT,
  T_G_MT,
  M_N_MT,
  COMBO_LENGTH
};

uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM z_t_mt[] = { KC_Z, KC_T, COMBO_END};
const uint16_t PROGMEM z_x_mt[] = { KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM a_t_mt[] = { KC_A, KC_T, COMBO_END};
const uint16_t PROGMEM x_c_mt[] = { KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM d_v_mt[] = { KC_D, KC_V, COMBO_END};
const uint16_t PROGMEM r_s_mt[] = { KC_R, KC_S, COMBO_END};
const uint16_t PROGMEM w_f_mt[] = { KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM s_t_mt[] = { KC_S, KC_T, COMBO_END};
const uint16_t PROGMEM t_g_mt[] = { KC_T, KC_G, COMBO_END};
const uint16_t PROGMEM m_n_mt[] = { KC_M, KC_N, COMBO_END};

combo_t key_combos[] = {
  [Z_T_MT] = COMBO(z_t_mt, LCTL(KC_Z)),
  [Z_X_MT] = COMBO(z_x_mt, LCTL(KC_X)),
  [A_T_MT] = COMBO(a_t_mt, LCTL(KC_A)),
  [X_C_MT] = COMBO(x_c_mt, LCTL(KC_C)),
  [D_V_MT] = COMBO(d_v_mt, LCTL(KC_V)),
  [R_S_MT] = COMBO(r_s_mt, LCTL_T(KC_S)),
  [W_F_MT] = COMBO(w_f_mt, LCTL_T(KC_F)),
  [S_T_MT] = COMBO(s_t_mt, LCTL_T(KC_T)),
  [T_G_MT] = COMBO(t_g_mt, LCTL_T(KC_G)),
  [M_N_MT] = COMBO(m_n_mt, LCTL_T(KC_N))
};
*/
//Tap Dance
enum {
  TD_LEFT_HOME,
  TD_RIGHT_END
 // TD_T_NAV,
//  TD_Z_CTRLZ
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

/*
void t_nav_finished (tap_dance_state_t *state, void *user_data);
void t_nav_reset (tap_dance_state_t *state, void *user_data);


void z_ctlz_finished (tap_dance_state_t *state, void *user_data);
void z_ctlz_reset (tap_dance_state_t *state, void *user_data);
*/

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
  [TD_RIGHT_END] = ACTION_TAP_DANCE_TAP_AND_HOLD(KC_RIGHT, KC_END),
  //[TD_T_NAV]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,t_nav_finished, t_nav_reset),
  //[TD_Z_CTRLZ] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,z_ctlz_finished, z_ctlz_reset)
};

/* clang-format off */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Colemak DH
 * ,----------------------------------------------------------------------------------------.
 * |   Q  |   W  |   F  |   P  |   B   |      |      |   J    |   L   |   U  |   Y  |   ;   |
 * |------+------+------+------+-------+------+------+--------+-------+------+------+-------|
 * |   A  |   R  |   S  |   T  |   G   |      |      |   M    |   N   |   E  |   I  |   O   |
 * |      |      |      |  Nav |       |      |      |        |       |      |      |       |
 * |------+------+------+------+-------+------+------+--------+-------+------+------+-------|
 * |   Z  |   X  |   C  |   D  |   V   |      |      |   K    |   H   |   ,  |   .  |   /   |
 * | Ctrl |      |      |      |       |      |      |        |       |      |      |       |
 * |------+------+------+------+-------+------+------+--------+-------+------+------+-------|
 * |      |      |      | Bksp |  Spc  | Tab  | Esc  |  Enter |  Del  |      |      |       |
 * |      |      |      |      | Lower | Shft | Win  |  Lower |  Alt  |      |      |       |
 * `----------------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_planck_grid(
    KC_Q,               KC_W,    KC_F,    KC_P,            KC_B,              _______,              _______,              KC_J,              KC_L,                 KC_U,    KC_Y,    KC_SCLN,
    KC_A,               KC_R,    KC_S,    LT(RAISE, KC_T), KC_G,              _______,              _______,              KC_M,              KC_N,                 KC_E,    KC_I,    KC_O,
    MT(MOD_LCTL, KC_Z), KC_X,    KC_C,    KC_D,            KC_V,              _______,              _______,              KC_K,              KC_H,                 KC_COMM, KC_DOT,  KC_SLSH,
    _______,            _______, _______, KC_BSPC,         LT(LOWER, KC_SPC), MT(MOD_RSFT, KC_TAB), MT(MOD_LGUI, KC_ESC), LT(LOWER, KC_ENT), MT(MOD_RALT, KC_DEL), _______, _______, _______
),

/* Lower
 * ,-----------------------------------------------------------------------.
 * |  1  |  2  |  3  |  4  |  5  |     |     |  6  |  7  |  8  |  9  |  0  |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * |  =  |  +  |  -  |  _  |     |     |     |  \  |  [{ | }]  |  `  |  '  |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * |  !  |  @  |  #  |  $  |  %  |     |     |  ^  |  &  |  *  |  (  |  )  |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * |     |     |     |     |     |     |     |     |     |     |     |     |
 * `-----------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______, _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    KC_EQL,  KC_PLUS, KC_MINS, KC_UNDS, _______, _______, _______, KC_BSLS, KC_LBRC, KC_RBRC, KC_GRV,  KC_QUOT,
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______, _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),
/* Raise
z * ,--------------------------------------------------------------------------------------.
 * |  F5  |  F8  | Ctl-F12 |     |     |         |     |     |      |      |      |       |
 * |------+------+---------+-----+-----+---------+-----+-----+------+------+------+-------|
 * |  F10 |  F12 |   F12   |     |     |         |     |     | Left |  Up  | Down | Right |
 * |------+------+---------+-----+-----+---------+-----+-----+------+------+------+-------|
 * |      |      |         |     |     |         |     |     |      |      |      |       |
 * |------+------+---------+-----+-----+---------+-----+-----+------+------+------+-------|
 * |      |      |         |     |     | CapsWrd |     |     |      |      |      |       |
 * `---------------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    KC_F5,   KC_F8,   LCTL(KC_F12), _______, _______, _______, _______, _______, _______,          _______, _______, _______,
    KC_F10,  KC_F11,  KC_F12,       _______, _______, _______, _______, _______, TD(TD_LEFT_HOME), KC_UP,   KC_DOWN, TD(TD_RIGHT_END),
    _______, _______, _______,      _______, _______, _______, _______, _______, _______,          _______, _______, _______,
    _______, _______, _______,      _______, _______, CW_TOGG, _______, _______, _______,          _______, _______, _______
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
[_ADJUST] = LAYOUT_planck_grid(
    QK_BOOTLOADER, QK_BOOT, DB_TOGG, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______,
    _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
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
/*
static tap xtap_state = {
  .is_press_action = true,
  .state = 0
};


void t_nav_finished (tap_dance_state_t *state, void *user_data) {
  xtap_state.state = cur_dance(state);
  switch (xtap_state.state) {
    case SINGLE_TAP: register_code(KC_T); break;
    case SINGLE_HOLD: layer_on(_RAISE); break;
    case DOUBLE_HOLD: register_code(MT(MOD_LCTL, KC_T)); break;
  }
}

void t_nav_reset (tap_dance_state_t *state, void *user_data) {
  switch (xtap_state.state) {
    case SINGLE_TAP: unregister_code(KC_T); break;
    case SINGLE_HOLD: layer_off(_RAISE); break;
    case DOUBLE_HOLD: unregister_code(MT(MOD_LCTL, KC_T)); break;
  }
  xtap_state.state = 0;
}


void z_ctlz_finished (tap_dance_state_t *state, void *user_data) {
  xtap_state.state = cur_dance(state);
  switch (xtap_state.state) {
    case SINGLE_TAP: register_code(KC_Z); break;
    case SINGLE_HOLD: register_code(KC_LCTL); break;
    case DOUBLE_HOLD: register_code(MT(MOD_LCTL, KC_Z)); break;
  }
}

void z_ctlz_reset (tap_dance_state_t *state, void *user_data) {
  switch (xtap_state.state) {
    case SINGLE_TAP: unregister_code(KC_Z); break;
    case SINGLE_HOLD: unregister_code(KC_LCTL); break;
    case DOUBLE_HOLD: unregister_code(MT(MOD_LCTL, KC_Z)); break;
  }
  xtap_state.state = 0;
}
*/
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
