#include QMK_KEYBOARD_H
#include "tapdances.h"
#include "layout34.h"

// FLASH: qmk flash -kb planck/rev7 -km apitzele

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_MAIN] = LAYOUT_planck_grid(
    layout.dft[0][0], layout.dft[0][1], layout.dft[0][2], layout.dft[0][3], layout.dft[0][4], XXXXXXX, XXXXXXX, layout.dft[0][5], layout.dft[0][6], layout.dft[0][7], layout.dft[0][8], layout.dft[0][9],
    layout.dft[1][0], layout.dft[1][1], layout.dft[1][2], layout.dft[1][3], layout.dft[1][4], XXXXXXX, XXXXXXX, layout.dft[1][5], layout.dft[1][6], layout.dft[1][7], layout.dft[1][8], layout.dft[1][9],
    layout.dft[2][0], layout.dft[2][1], layout.dft[2][2], layout.dft[2][3], layout.dft[2][4], XXXXXXX, XXXXXXX, layout.dft[2][5], layout.dft[2][6], layout.dft[2][7], layout.dft[2][8], layout.dft[2][9],
    XXXXXXX,           XXXXXXX,         XXXXXXX,          layout.dft[3][0], layout.dft[3][1], XXXXXXX, XXXXXXX, layout.dft[3][2], layout.dft[3][3], XXXXXXX,          XXXXXXX,          XXXXXXX
  ),
  [_NUM] = LAYOUT_planck_grid(
    layout.num[0][0], layout.num[0][1], layout.num[0][2], layout.num[0][3], layout.num[0][4], XXXXXXX, XXXXXXX, layout.num[0][5], layout.num[0][6], layout.num[0][7], layout.num[0][8], layout.num[0][9],
    layout.num[1][0], layout.num[1][1], layout.num[1][2], layout.num[1][3], layout.num[1][4], XXXXXXX, XXXXXXX, layout.num[1][5], layout.num[1][6], layout.num[1][7], layout.num[1][8], layout.num[1][9],
    layout.num[2][0], layout.num[2][1], layout.num[2][2], layout.num[2][3], layout.num[2][4], XXXXXXX, XXXXXXX, layout.num[2][5], layout.num[2][6], layout.num[2][7], layout.num[2][8], layout.num[2][9],
    XXXXXXX,           XXXXXXX,         XXXXXXX,          layout.num[3][0], layout.num[3][1], XXXXXXX, XXXXXXX, layout.num[3][2], layout.num[3][3], XXXXXXX,          XXXXXXX,          XXXXXXX
  ),
  [_NAV] = LAYOUT_planck_grid(
    layout.nav[0][0], layout.nav[0][1], layout.nav[0][2], layout.nav[0][3], layout.nav[0][4], XXXXXXX, XXXXXXX, layout.nav[0][5], layout.nav[0][6], layout.nav[0][7], layout.nav[0][8], layout.nav[0][9],
    layout.nav[1][0], layout.nav[1][1], layout.nav[1][2], layout.nav[1][3], layout.nav[1][4], XXXXXXX, XXXXXXX, layout.nav[1][5], layout.nav[1][6], layout.nav[1][7], layout.nav[1][8], layout.nav[1][9],
    layout.nav[2][0], layout.nav[2][1], layout.nav[2][2], layout.nav[2][3], layout.nav[2][4], XXXXXXX, XXXXXXX, layout.nav[2][5], layout.nav[2][6], layout.nav[2][7], layout.nav[2][8], layout.nav[2][9],
    XXXXXXX,           XXXXXXX,         XXXXXXX,          layout.nav[3][0], layout.nav[3][1], XXXXXXX, XXXXXXX, layout.nav[3][2], layout.nav[3][3], XXXXXXX,          XXXXXXX,          XXXXXXX
  ),
  [_SYMR] = LAYOUT_planck_grid(
    layout.symr[0][0], layout.symr[0][1], layout.symr[0][2], layout.symr[0][3], layout.symr[0][4], XXXXXXX, XXXXXXX, layout.symr[0][5], layout.symr[0][6], layout.symr[0][7], layout.symr[0][8], layout.symr[0][9],
    layout.symr[1][0], layout.symr[1][1], layout.symr[1][2], layout.symr[1][3], layout.symr[1][4], XXXXXXX, XXXXXXX, layout.symr[1][5], layout.symr[1][6], layout.symr[1][7], layout.symr[1][8], layout.symr[1][9],
    layout.symr[2][0], layout.symr[2][1], layout.symr[2][2], layout.symr[2][3], layout.symr[2][4], XXXXXXX, XXXXXXX, layout.symr[2][5], layout.symr[2][6], layout.symr[2][7], layout.symr[2][8], layout.symr[2][9],
    XXXXXXX,           XXXXXXX,           XXXXXXX,           layout.symr[3][0], layout.symr[3][1], XXXXXXX, XXXXXXX, layout.symr[3][2], layout.symr[3][3], XXXXXXX,           XXXXXXX,           XXXXXXX
  ),
  [_SYML] = LAYOUT_planck_grid(
    layout.syml[0][0], layout.syml[0][1], layout.syml[0][2], layout.syml[0][3], layout.syml[0][4], XXXXXXX, XXXXXXX, layout.syml[0][5], layout.syml[0][6], layout.syml[0][7], layout.syml[0][8], layout.syml[0][9],
    layout.syml[1][0], layout.syml[1][1], layout.syml[1][2], layout.syml[1][3], layout.syml[1][4], XXXXXXX, XXXXXXX, layout.syml[1][5], layout.syml[1][6], layout.syml[1][7], layout.syml[1][8], layout.syml[1][9],
    layout.syml[2][0], layout.syml[2][1], layout.syml[2][2], layout.syml[2][3], layout.syml[2][4], XXXXXXX, XXXXXXX, layout.syml[2][5], layout.syml[2][6], layout.syml[2][7], layout.syml[2][8], layout.syml[2][9],
    XXXXXXX,           XXXXXXX,           XXXXXXX,           layout.syml[3][0], layout.syml[3][1], XXXXXXX, XXXXXXX, layout.syml[3][2], layout.syml[3][3], XXXXXXX,           XXXXXXX,           XXXXXXX
  )
};
