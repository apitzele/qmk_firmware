#include QMK_KEYBOARD_H
#include "tapdances.h"

enum planck_layers { _COLEMAK, _LOWER, _RAISE, _NUM, _NAV, _ADJUST };
enum planck_keycodes { COLEMAK = SAFE_RANGE };

#define SYMR MO(_LOWER)
#define SYML MO(_RAISE)
#define NAV MO(_NAV)
#define NUM MO(_NUM)

//Tap dances
enum {
  TD_LEFT_HOME,
  TD_RIGHT_END,
  TD_Z,
  TD_X,
  TD_C,
  TD_V,
  TD_F,
  TD_Y,
  TD_H,
  TD_Q,
  TD_W,
  TD_TAB,
  TD_DEL,
  TD_SLASH
};

void slash_finished (tap_dance_state_t *state, void *user_data);
void slash_reset (tap_dance_state_t *state, void *user_data);

tap_dance_action_t tap_dance_actions[] = {
  [TD_LEFT_HOME] = ACTION_TAP_DANCE_TAP_AND_HOLD(KC_LEFT, KC_HOME),
  [TD_RIGHT_END] = ACTION_TAP_DANCE_TAP_AND_HOLD(KC_RIGHT, KC_END),
  [TD_TAB] = ACTION_TAP_DANCE_TAP_AND_HOLD(KC_TAB, LSFT(KC_TAB)),
  [TD_DEL] = ACTION_TAP_DANCE_TAP_AND_HOLD (KC_DEL, RSFT(KC_DEL)),
  [TD_SLASH] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, slash_finished, slash_reset),
  [TD_Z] = ACTION_TAP_DANCE_TAP_AND_HOLD(KC_Z, LCTL(KC_Z)),
  [TD_Y] = ACTION_TAP_DANCE_TAP_AND_HOLD(KC_Y, RCTL(KC_Y)),
  [TD_X] = ACTION_TAP_DANCE_TAP_HOLD(KC_X, LCTL(KC_X)),
  [TD_C] = ACTION_TAP_DANCE_TAP_HOLD(KC_C, LCTL(KC_C)),
  [TD_V] = ACTION_TAP_DANCE_TAP_HOLD(KC_V, LCTL(KC_V)),
  [TD_F] = ACTION_TAP_DANCE_TAP_HOLD(KC_F, LCTL(KC_F)),
  [TD_W] = ACTION_TAP_DANCE_TAP_HOLD(KC_W, LCTL(KC_A)), // Hold W = Ctrl + A
  [TD_H] = ACTION_TAP_DANCE_TAP_HOLD(KC_H, LCTL(KC_H)),
  [TD_Q] = ACTION_TAP_DANCE_TAP_HOLD(KC_Q, KC_ESC)
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

/* clang-format off */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Colemak DH
 * ,-------------------------------------------------------------------------------------.
 * | Q/Esc|  W*  |  F*  |   P  |   B    |     |     |   J   |  L   |   U  |  Y*  |   ;   |
 * |------+------+------+------+--------+-----+-----+-------+------+------+------+-------|
 * |   A  |   R  |   S  |   T  |   G    |     |     |   M   |  N   |   E  |   I  |   O   |
 * | Ctrl |  Alt |  Nav | Shft |        |     |     |       | Shft |  Win |  Alt | Ctrl  |
 * |------+------+------+------+--------+-----+-----+-------+------+------+------+-------|
 * |  Z*  |  X*  |  C*  |   D  |   V*   |     |     |   K   |  H   |   ,  |   .  |   /   |
 * |------+------+------+------+--------+-----+-----+-------+------+------+------+-------|
 * |      |      |      | Bspc |  Spc   |     |     | Enter | Del  |      |      |       |
 * |      |      |      | Num  |  Sym R |     |     | Sym L |      |      |      |       |
 * `-------------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_planck_grid(
    TD(TD_Q),     TD(TD_W),     TD(TD_F),      KC_P,             KC_B,             _______, _______,    KC_J,             KC_L,         KC_U,         TD(TD_Y),     KC_SCLN,
    LCTL_T(KC_A), LALT_T(KC_R), LT(NAV, KC_S), LSFT_T(KC_T),     KC_G,             _______, _______,    KC_M,             RSFT_T(KC_N), RGUI_T(KC_E), RALT_T(KC_I), RCTL_T(KC_O),
    TD(TD_Z),     TD(TD_X),     TD(TD_C),      KC_D,             TD(TD_V),         _______, _______,    KC_K,             KC_H,         KC_COMM,      KC_DOT,       TD(TD_SLASH),
    _______,      _______,      _______,       LT(NUM, KC_BSPC), LT(SYMR, KC_SPC), _______, _______,    LT(SYML, KC_ENT), TD(TD_DEL),   _______,      _______,      _______
),
/* Raise (Sym L)
 * ,--------------------------------------------------------------------------.
 * |  !  |  @  |  #  |  $   |  %  |     |     |     |      |     |     |      |
 * |-----+-----+-----+------+-----+-----+-----+-----+------+-----+-----+------|
 * |  =  |  +  |  -  |  _   |     |     |     |     | Shft | Win | Alt | Ctrl |
 * |-----+-----+-----+------+-----+-----+-----+-----+------+-----+-----+------|
 * |     |     |     |      |     |     |     |     |      |     |     |      |
 * |-----+-----+-----+------+-----+-----+-----+-----+------+-----+-----+------|
 * |     |     |     | Bspc | Spc |     |     |     |      |     |     |      |
 * `--------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______, _______, _______,  _______, _______, _______, _______,
    KC_EQL,  KC_PLUS, KC_MINS, KC_UNDS, KC_QUOT, _______, _______, _______,  KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL,
    _______, KC_GRV,  KC_BSLS, KC_LBRC, KC_RBRC, _______, _______, _______,  _______, _______, _______, _______,
    _______, _______, _______, _______, _______,  _______, _______, _______,  _______, _______, _______, _______
),
/* Lower (Sym R)
 * ,-----------------------------------------------------------------------------.
 * |      |     |     |      |     |     |     |  ^  |    &    |  *  |  (  |  )  |
 * |------+-----+-----+------+-----+-----+-----+-----+---------+-----+-----+-----|
 * | Ctrl | Alt | Win | Shft |     |     |     |     |    {    |  }  |  |  |  '  |
 * |------+-----+-----+------+-----+-----+-----+-----+---------+-----+-----+-----|
 * |      |     |     |      |     |     |     |     |    [    |  ]  |  `  |  \  |
 * |------+-----+-----+------+-----+-----+-----+-----+---------+-----+-----+-----|
 * |      |     |     |      |     |     |     | Tab | CapsLck |     |     |     |
 * `-----------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______, _______, KC_CIRC,    KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
    KC_EQL,  KC_PLUS, KC_MINS, KC_UNDS, KC_QUOT, _______, _______, _______,    KC_LBRC, KC_RBRC, KC_PIPE, KC_QUOT,
    _______, KC_GRV,  KC_BSLS, KC_LBRC, KC_RBRC, _______, _______, _______,    KC_LBRC, KC_RBRC, KC_GRV, KC_BSLS,
    _______, _______, _______, _______, _______, _______, _______, TD(TD_TAB), KC_CAPS, _______, _______, _______
),
/* Nav
 * ,----------------------------------------------------------------------------------.
 * |      |     |     |      |      |     |     |      |      |      |      |         |
 * |------+-----+-----+------+------+-----+-----+------+------+------+------+---------|
 * | Ctrl | Alt | Win | Shft |      |     |     |      | Left |  Up  | Down |  Right  |
 * |------+-----+-----+------+------+-----+-----+------+------+------+------+---------|
 * |      |     |     |      |      |     |     | F5   | F10  |  F11 | F12  | Ctl-F12 |
 * |------+-----+-----+------+------+-----+-----+------+------+------+------+---------|
 * |      |     |     |      |      |     |     |      |      |      |      |         |
 * `----------------------------------------------------------------------------------'
 */
[_NAV] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, _______,  _______,         _______, _______, _______,
    KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, _______, _______, _______, _______, TD(TD_LEFT_HOME), KC_UP,   KC_DOWN, TD(TD_RIGHT_END),
    _______, _______, _______, _______, _______, _______, _______, KC_F5,   KC_F10,           KC_F11,  KC_F12,  RCTL(KC_F12),
    _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______
),

/* Numbers
 * ,--------------------------------------------------------------------------.
 * |      |     |     |       |     |     |    |  *  |  7  |  8  |  9  |  /  |
 * |------+-----+-----+-------+-----+-----+----+-----+-----+-----+-----+-----|
 * | Ctrl | Alt | Win | Shift |     |     |    |  +  |  4  |  5  |  6  |  -  |
 * |------+-----+-----+-------+-----+-----+----+-----+-----+-----+-----+-----|
 * |      |     |     |       |     |     |    |  .  |  1  |  2  |  3  |  =  |
 * |------+-----+-----+-------+-----+-----+----+-----+-----+-----+-----+-----|
 * |      |     |     |       |     |     |    |  0  |     |     |     |     |
 * `--------------------------------------------------------------------------'
 */
[_NUM] = LAYOUT_planck_grid(
    _______, _______,       _______, _______, _______, _______, _______, KC_PAST, KC_P7,  KC_P8,   KC_P9,   KC_PSLS,
    KC_LCTL, KC_LALT,       KC_LGUI, KC_LSFT, _______, _______, _______, KC_PPLS, KC_P4,  KC_P5,   KC_P6,   KC_PMNS,
    _______, _______,       _______, _______, _______, _______, _______, KC_PDOT, KC_P1,  KC_P2,   KC_P3,   KC_PEQL,
    _______, QK_BOOTLOADER, _______, _______, _______, _______, _______, KC_P0,   _______, _______, _______, _______
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;

    switch (keycode) { /* register tap hold actions w/ tap dance*/
        case TD(TD_Z):
        case TD(TD_X):
        case TD(TD_C):
        case TD(TD_V):
        case TD(TD_F):
        case TD(TD_Y):
	    case TD(TD_H):
        case TD(TD_Q):
		case TD(TD_W):
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

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
