#include QMK_KEYBOARD_H

enum planck_layers { _COLEMAK, _LOWER, _RAISE, _NUM, _ADJUST };

enum planck_keycodes { COLEMAK = SAFE_RANGE };

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define NUM MO(_NUM)
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
  TD_RIGHT_END,
  TD_Z,
  TD_X,
  TD_C,
  TD_V,
  TD_G,
  TD_F,
  TD_Y,
  TD_H,
  TD_Q,
  TD_TAB
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
  [TD_Z] = ACTION_TAP_DANCE_TAP_HOLD(KC_Z, LCTL(KC_Z)),
  [TD_X] = ACTION_TAP_DANCE_TAP_HOLD(KC_X, LCTL(KC_X)),
  [TD_C] = ACTION_TAP_DANCE_TAP_HOLD(KC_C, LCTL(KC_C)),
  [TD_V] = ACTION_TAP_DANCE_TAP_HOLD(KC_V, LCTL(KC_V)),
  [TD_F] = ACTION_TAP_DANCE_TAP_HOLD(KC_F, LCTL(KC_F)),
  [TD_G] = ACTION_TAP_DANCE_TAP_HOLD(KC_G, LCTL(KC_G)),
  [TD_Y] = ACTION_TAP_DANCE_TAP_HOLD(KC_Y, LCTL(KC_Y)),
  [TD_H] = ACTION_TAP_DANCE_TAP_HOLD(KC_H, LCTL(KC_H)),
  [TD_Q] = ACTION_TAP_DANCE_TAP_HOLD(KC_Q, KC_ESC),
  [TD_TAB] = ACTION_TAP_DANCE_TAP_AND_HOLD(KC_TAB, LSFT(KC_TAB)),
};

/* clang-format off */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Colemak DH
 * ,-------------------------------------------------------------------------------------.
 * | Q/Esc|  W*  |  F*  |   P  |   B   |      |     |   J   |   L  |   U  |  Y*  |   ;   |
 * |------+------+------+------+-------+------+-----+-------+------+------+------+-------|
 * |   A  |   R  |   S  |   T  |   G*  |      |     |   M   |   N  |   E  |   I  |   O   |
 * | Ctrl |  Alt |  Num |  Nav |       |      |     |       |  Sym |  Win |  Alt | Ctrl  |
 * |------+------+------+------+-------+------+-----+-------+------+------+------+-------|
 * |  Z*  |  X*  |  C*  |   D  |   V*  |      |     |   K   |   H  |   ,  |   .  |   /   |
 * |------+------+------+------+-------+------+-----+-------+------+------+------+-------|
 * |      |      |      |      |  Spc  | Bspc | Tab | Enter |      |      |      |       |
 * |      |      |      |      |  Shft |      |     | Shft  |      |      |      |       |
 * `-------------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_planck_grid(
    TD(TD_Q),     KC_W,         TD(TD_F),      KC_P,            KC_B,           _______, _______,    KC_J,           KC_L,            KC_U,         TD(TD_Y),     KC_SCLN,
    LCTL_T(KC_A), LALT_T(KC_R), LT(NUM, KC_S), LT(LOWER, KC_T), TD(TD_G),       _______, _______,    KC_M,           LT(RAISE, KC_N), RGUI_T(KC_E), RALT_T(KC_I), RCTL_T(KC_O),
    TD(TD_Z),     TD(TD_X),     TD(TD_C),      KC_D,            TD(TD_V),       _______, _______,    KC_K,           KC_H,            KC_COMM,      KC_DOT,       KC_SLSH,
    _______,      _______,      _______,       _______,         LSFT_T(KC_SPC), KC_BSPC, TD(TD_TAB), RSFT_T(KC_ENT), _______,         _______,      _______,      _______
),


/* Raise (Symbols)
 * ,--------------------------------------------------------------------------.
 * |  !  |  @  |  #  |  $  |  %  |     |     |     |       |     |     |      |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-------+-----+-----+------|
 * |  '" | =+  | -_  | [{  | ]}  |     |     |     |       | Win | Alt | Ctrl |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-------+-----+-----+------|
 * |     | `~  | \|  |     |     |     |     |     |       |     |     |      |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-------+-----+-----+------|
 * |     |     |     |     | Spc | Bspc| Tab |Enter|       |     |     |      |
 * |     |     |     |     | Shft|     |     |Shft |       |     |     |      |
 * `--------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,        _______, _______,    _______,        _______, _______, _______, _______,
    KC_QUOT, KC_EQL,  KC_MINS, KC_LBRC, KC_RBRC,        _______, _______,    _______,        _______, KC_RGUI, KC_RALT, KC_RCTL,
    _______, KC_GRV,  KC_BSLS, _______, _______,        _______, _______,    _______,        _______, _______, _______, _______,
    _______, _______, _______, _______, LSFT_T(KC_SPC), KC_BSPC, TD(TD_TAB), RSFT_T(KC_ENT), _______, _______, _______, _______
),
/* Lower (Nav)
 * ,--------------------------------------------------------------------------------------.
 * |      |     |     |       |     |      |        |  ^   |  &   |  *   |  (   |    )    |
 * |------+-----+-----+-------+-----+------+--------+------+------+------+------+---------|
 * | Ctrl | Alt | Win |       |     |      |        |      | Left |  Up  | Down |  Right  |
 * |------+-----+-----+-------+-----+------+--------+------+------+------+------+---------|
 * |      |     |     |       |     |      |        | F5   | F10  |  F11 | F12  | Ctl-F12 |
 * |------+-----+-----+-------+-----+------+--------+------+------+------+------+---------|
 * |      |     |     |       | Spc | Bspc | CapsLk | Del  |      |      |      |         |
 * |      |     |     |       | Shft|      |        | Shft |      |      |      |         |
 * `--------------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______,      _______, _______, KC_CIRC,      KC_AMPR,          KC_ASTR, KC_LPRN, KC_RPRN,
    KC_LCTL, KC_LALT, KC_LGUI, _______, _______,      _______, _______, _______,      TD(TD_LEFT_HOME), KC_UP,   KC_DOWN, TD(TD_RIGHT_END),
    _______, _______, _______, _______, _______,      _______, _______, _______,      _______,          _______, _______, _______,
    _______, _______, _______, _______, LSFT(KC_SPC), KC_BSPC, KC_CAPS, RSFT(KC_DEL), _______,          _______, _______, _______
),

/* Numbers
 * ,----------------------------------------------------------------------------.
 * |      |     |     |       |     |     |       |  *  |  7  |  8  |  9  |  /  |
 * |------+-----+-----+-------+-----+-----+-------+-----+-----+-----+-----+-----|
 * | Ctrl | Alt | Win | Shift |     |     |       |  +  |  4  |  5  |  6  |  -  |
 * |------+-----+-----+-------+-----+-----+-------+-----+-----+-----+-----+-----|
 * |      |     |     |       |     |     |       |  .  |  1  |  2  |  3  |  =  |
 * |------+-----+-----+-------+-----+-----+-------+-----+-----+-----+-----+-----|
 * |      |     |     |       |     |     | Bkspc |  0  |     |     |     |     |
 * `----------------------------------------------------------------------------'
 */
[_NUM] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______,        _______, _______,    KC_PAST, KC_P7,   KC_P8,   KC_P9,   KC_PSLS,
    KC_LCTL, KC_LALT, KC_LGUI, _______, _______,        _______, _______,    KC_PPLS, KC_P4,   KC_P5,   KC_P6,   KC_PMNS,
    _______, _______, _______, _______, _______,        _______, _______,    KC_PDOT, KC_P1,   KC_P2,   KC_P3,   KC_PEQL,
    _______, _______, _______, _______, LSFT_T(KC_SPC), KC_BSPC, TD(TD_TAB), KC_P0,   _______, _______, _______, _______
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
    QK_BOOTLOADER, QK_BOOT, DB_TOGG, RGB_TOG, RGB_MOD,        RGB_HUI, RGB_HUD,    RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______,
    _______,       _______, _______, _______, _______,        _______, _______,    _______, _______, _______, _______, _______,
    _______,       _______, _______, _______, _______,        _______, _______,    _______, _______, _______, _______, _______,
    _______,       _______, _______, _______, LSFT_T(KC_SPC), KC_BSPC, TD(TD_TAB), KC_P0,   _______, _______, _______, _______
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

wwwqqqqqqqqqqqqqqqqqqqqvoid t_nav_finished (tap_dance_state_t *state, void *user_data) {
  xtap_state.state = cur_dance(state);
  switch (xtap_state.state) {
    case SINGLE_TAP: register_code(KC_T); break;
    case SINGLE_HOLD: layer_on(_RAISE); break;
    case DOUBLE_HOLD: register_code(LCTL(KC_T)); break;
  }
}11

void t_nav_reset (tap_dance_state_t *state, void *user_data) {
  switch (xtap_state.state) {
    case SINGLE_TAP: unregister_code(KC_T); break;
    case SINGLE_HOLD: layer_off(_RAISE); break;
    case DOUBLE_HOLD: unregister_code(LCTL(KC_T)); break;
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
        case TD(TD_Z):
        case TD(TD_X):
        case TD(TD_C):
        case TD(TD_V):
        case TD(TD_G):
        case TD(TD_F):
        case TD(TD_Y):
	    case TD(TD_H):
        case TD(TD_Q):
	    case TD(TD_TAB):
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
