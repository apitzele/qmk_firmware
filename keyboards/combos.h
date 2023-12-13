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