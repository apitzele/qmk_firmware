#include QMK_KEYBOARD_H
#include "tapdances.h"

enum layers { _MAIN, _SYMR, _SYML, _NUM, _NAV };
#define SYMR MO(_SYMR)
#define SYML MO(_SYML)
#define NAV MO(_NAV)
#define NUM MO(_NUM)

enum combos { 
  TAB,
  CAPS
};

const uint16_t PROGMEM tab_combo[] = {LT(NUM, KC_SPC), LT(NAV, KC_ENT), COMBO_END};
const uint16_t PROGMEM caps_combo[] = {LT(SYMR, KC_T), LT(SYML, KC_N), COMBO_END};

combo_t key_combos[] = {
    [TAB] = COMBO(tab_combo, KC_TAB),
    [CAPS] = COMBO(caps_combo, KC_CAPS),
};

bool should_process_keypress(void) { return true; }

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

/* clang-format off */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_MAIN] = LAYOUT_planck_grid(
    TD(T_Q),      TD(T_W),      TD(T_F),      KC_P,           KC_B,            XXXXXXX, XXXXXXX,  KC_J,            KC_L,           KC_U,         KC_Y,         KC_SCLN,
 //|-------- ---+-------------+-------------+---------------+---------------+                   +----------------+---------------+-------------+-------------+-------------|
    LCTL_T(KC_A), LSFT_T(KC_R), LALT_T(KC_S), LT(SYMR, KC_T), KC_G,            XXXXXXX, XXXXXXX,  KC_M,            LT(SYML, KC_N), LALT_T(KC_E), RSFT_T(KC_I), RCTL_T(KC_O),
 //|------------+-------------+-------------+---------------+---------------+                   +-----+----------+---------------+-------------+-------------+-------------|
    KC_Z,         TD(T_X),      TD(T_C),      TD(T_D),        TD(T_V),         XXXXXXX, XXXXXXX,  KC_K,            TD(T_H),        KC_COMM,      KC_DOT,       TD(T_SLASH),
 //,------------------------------------------------------------------------+                   +--------------------------------------------------------------------------.
    XXXXXXX,      XXXXXXX,      XXXXXXX,      KC_BSPC,        LT(NUM, KC_SPC), XXXXXXX, XXXXXXX,  LT(NAV, KC_ENT), TD(T_DEL),      XXXXXXX,      XXXXXXX,      XXXXXXX
  ),

  [_SYMR] = LAYOUT_planck_grid(
      _______, _______, _______, _______, _______, XXXXXXX, XXXXXXX,  KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
  //|--------+--------+--------+--------+--------+                   +-------+--------+--------+--------+--------|
      KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI, _______, XXXXXXX, XXXXXXX,  _______, KC_LCBR, KC_RCBR, KC_QUOT, KC_DQT,
  //|--------+--------+--------+--------+--------+                   +-------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, XXXXXXX, XXXXXXX,  _______, KC_LBRC, KC_RBRC, KC_GRV,  KC_BSLS,
  //,--------------------------------------------+                   +-------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX,  KC_ENT,  KC_DEL,  XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [_SYML] = LAYOUT_planck_grid(
      KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, XXXXXXX, XXXXXXX,  _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+                   +-------+--------+--------+--------+--------|
      KC_EQL,  KC_PLUS, KC_MINS, KC_UNDS, _______, XXXXXXX, XXXXXXX,  _______, KC_RGUI, KC_RALT, KC_RSFT, KC_RCTL,
  //|--------+--------+--------+--------+--------+                   +-------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, XXXXXXX, XXXXXXX,  _______, _______, _______, _______, _______,
  //,--------------------------------------------+                   +-------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC, KC_SPC,  XXXXXXX, XXXXXXX,  _______, _______,  XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [_NUM] = LAYOUT_planck_grid(
      _______,    _______,    QK_BOOT, _______, _______, XXXXXXX, XXXXXXX,  KC_PAST, KC_P7,  KC_P8,   KC_P9,   KC_PSLS,
  //|-----------+-----------+--------+--------+--------+                   +-------+--------+--------+--------+--------|
      KC_LCTL,    KC_LSFT,    KC_LALT, KC_LGUI, _______, XXXXXXX, XXXXXXX,  KC_PPLS, KC_P4,  KC_P5,   KC_P6,   KC_PMNS,
  //|-----------+-----------+--------+--------+--------+                   +-------+--------+--------+--------+--------|
      LCTL(KC_Z), LCTL(KC_Y), _______, _______, _______, XXXXXXX, XXXXXXX,  KC_PDOT, KC_P1,  KC_P2,   KC_P3,   KC_PEQL,
  //,--------------------------------------------+                         +-------------------------------------------.
      XXXXXXX,    XXXXXXX,    XXXXXXX, _______, _______, XXXXXXX, XXXXXXX,  KC_P0, _______,  XXXXXXX, XXXXXXX, XXXXXXX
  ),

    [_NAV] = LAYOUT_planck_grid(
      _______, _______, _______, _______, _______, XXXXXXX, XXXXXXX,  _______, _______,     _______, _______, _______,
  //|--------+--------+--------+--------+--------+                  +--------+------------+--------+--------+-------------|
      KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI, _______, XXXXXXX, XXXXXXX,  _______, TD(T_LT_HM), KC_UP,   KC_DOWN, TD(T_RT_ED),
  //|--------+--------+--------+--------+--------+                  +--------+------------+--------+--------+-------------|
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F6,   XXXXXXX, XXXXXXX,  KC_F5,   KC_F10,      KC_F11,  KC_F12,  RCTL(KC_F12),
  //,--------+--------+--------+--------+--------+                  +--------+------------+--------+--------+-------------.
      XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX,  _______, KC_F8,       XXXXXXX, XXXXXXX, XXXXXXX
  )
};
