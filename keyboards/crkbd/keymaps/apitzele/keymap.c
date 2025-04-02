#include QMK_KEYBOARD_H
#include "tapdances.h"
#include "layout34.h"
#include "oled.h"

// FLASH: qmk flash -kb crkbd -km apitzele -e CONVERT_TO=promicro_rp2040
// COMPILE: qmk compile -kb crkbd -km apitzele -e CONVERT_TO=promicro_rp2040

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_MAIN] = LAYOUT_split_3x6_3(
    _______, layout.dft[0][0], layout.dft[0][1], layout.dft[0][2], layout.dft[0][3], layout.dft[0][4], layout.dft[0][5], layout.dft[0][6], layout.dft[0][7], layout.dft[0][8], layout.dft[0][9], _______,
    _______, layout.dft[1][0], layout.dft[1][1], layout.dft[1][2], layout.dft[1][3], layout.dft[1][4], layout.dft[1][5], layout.dft[1][6], layout.dft[1][7], layout.dft[1][8], layout.dft[1][9], _______,
    _______, layout.dft[2][0], layout.dft[2][1], layout.dft[2][2], layout.dft[2][3], layout.dft[2][4], layout.dft[2][5], layout.dft[2][6], layout.dft[2][7], layout.dft[2][8], layout.dft[2][9], _______,
                                                 _______,          layout.dft[3][0], layout.dft[3][1], layout.dft[3][2], layout.dft[3][3], _______
  ),
  [_NUM] = LAYOUT_split_3x6_3(
    _______, layout.num[0][0], layout.num[0][1], layout.num[0][2], layout.num[0][3], layout.num[0][4], layout.num[0][5], layout.num[0][6], layout.num[0][7], layout.num[0][8], layout.num[0][9], _______,
    _______, layout.num[1][0], layout.num[1][1], layout.num[1][2], layout.num[1][3], layout.num[1][4], layout.num[1][5], layout.num[1][6], layout.num[1][7], layout.num[1][8], layout.num[1][9], _______,
    _______, layout.num[2][0], layout.num[2][1], layout.num[2][2], layout.num[2][3], layout.num[2][4], layout.num[2][5], layout.num[2][6], layout.num[2][7], layout.num[2][8], layout.num[2][9], _______,
                                                 _______,          layout.num[3][0], layout.num[3][1], layout.num[3][2], layout.num[3][3], _______
  ),
  [_NAV] = LAYOUT_split_3x6_3(
    _______, layout.nav[0][0], layout.nav[0][1], layout.nav[0][2], layout.nav[0][3], layout.nav[0][4], layout.nav[0][5], layout.nav[0][6], layout.nav[0][7], layout.nav[0][8], layout.nav[0][9], _______,
    _______, layout.nav[1][0], layout.nav[1][1], layout.nav[1][2], layout.nav[1][3], layout.nav[1][4], layout.nav[1][5], layout.nav[1][6], layout.nav[1][7], layout.nav[1][8], layout.nav[1][9], _______,
    _______, layout.nav[2][0], layout.nav[2][1], layout.nav[2][2], layout.nav[2][3], layout.nav[2][4], layout.nav[2][5], layout.nav[2][6], layout.nav[2][7], layout.nav[2][8], layout.nav[2][9], _______,
                                                 _______,          layout.nav[3][0], layout.nav[3][1], layout.nav[3][2], layout.nav[3][3], _______
  ),
  [_SMBL] = LAYOUT_split_3x6_3(
    _______, layout.smbl[0][0], layout.smbl[0][1], layout.smbl[0][2], layout.smbl[0][3], layout.smbl[0][4], layout.smbl[0][5], layout.smbl[0][6], layout.smbl[0][7], layout.smbl[0][8], layout.smbl[0][9], _______,
    _______, layout.smbl[1][0], layout.smbl[1][1], layout.smbl[1][2], layout.smbl[1][3], layout.smbl[1][4], layout.smbl[1][5], layout.smbl[1][6], layout.smbl[1][7], layout.smbl[1][8], layout.smbl[1][9], _______,
    _______, layout.smbl[2][0], layout.smbl[2][1], layout.smbl[2][2], layout.smbl[2][3], layout.smbl[2][4], layout.smbl[2][5], layout.smbl[2][6], layout.smbl[2][7], layout.smbl[2][8], layout.smbl[2][9], _______,
                                                   _______,           layout.smbl[3][0], layout.smbl[3][1], layout.smbl[3][2], layout.smbl[3][3], _______
  )
};
