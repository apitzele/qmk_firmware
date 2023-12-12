#include QMK_KEYBOARD_H
#include "layers.h"
#include "tapdances.h"
#include "combos.h"

/*
qmk flash -kb planck/rev7 -km apitzele
*/

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
      _______,    _______,    _______, QK_BOOT, _______, XXXXXXX, XXXXXXX,  KC_PAST, KC_P7,  KC_P8,   KC_P9,   KC_PSLS,
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
