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

struct KeycodeLayout {
    uint16_t dft[4][10];
    uint16_t num[4][10];
    uint16_t nav[4][10];
    uint16_t symr[4][10];
    uint16_t syml[4][10];
};
 
 // Define an array of keycodes
extern const struct KeycodeLayout layout;
const struct KeycodeLayout layout = {
    { // Default
        {
            TD(T_Q), TD(T_W), TD(T_F), KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_SCLN
        },
        {
            LCTL_T(KC_A), LSFT_T(KC_R), LALT_T(KC_S), LT(SYMR, KC_T), KC_G, KC_M, LT(SYML, KC_N), LALT_T(KC_E), RSFT_T(KC_I), RCTL_T(KC_O)
        },
        {
            KC_Z, TD(T_X), TD(T_C), TD(T_D), TD(T_V),  KC_K, TD(T_H),KC_COMM, KC_DOT,TD(T_SLASH)
        },
        {
            KC_BSPC, LT(NUM, KC_SPC), LT(NAV, KC_ENT), TD(T_DEL)
        }
    },
    { // Num
        {
            QK_BOOT,    _______,    _______, _______, _______, KC_PAST, KC_P7,  KC_P8,   KC_P9,   KC_PSLS
        },
        {
            KC_LCTL,    KC_LSFT,    KC_LALT, KC_LGUI, _______, KC_PPLS, KC_P4,  KC_P5,   KC_P6,   KC_PMNS
        },
        {
            LCTL(KC_Z), LCTL(KC_Y), _______, _______, _______, KC_PDOT, KC_P1,  KC_P2,   KC_P3,   KC_PEQL
        },
        {
            _______,  _______, KC_P0, _______
        }
    },
    { // Nav
        {
            _______, _______, _______, _______, _______, _______, _______,    _______,  _______, _______
        },
        {
            KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI, _______, _______, TD(T_LT_HM), KC_UP,  KC_DOWN, TD(T_RT_ED)
        },
        {
            KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F6, KC_F5,   KC_F10,      KC_F11, KC_F12,  RCTL(KC_F12)
        },
        {
            _______, _______, _______, KC_F8
        }
    },
    { // Symbols Right
        {
            _______, _______, _______, _______, _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN
        },
        {
            KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI, _______, _______, KC_LCBR, KC_RCBR, KC_QUOT, KC_DQT
        },
        {
            _______, _______, _______, _______, _______,  _______, KC_LBRC, KC_RBRC, KC_GRV,  KC_BSLS
        },
        {
            _______, _______, KC_ENT, KC_DEL
        }
    },
    { // Symbols Left
        {
            KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______, _______, _______, _______, _______
        },
        {
            KC_EQL,  KC_PLUS, KC_MINS, KC_UNDS, _______, KC_RGUI, KC_RALT, KC_RSFT, KC_RCTL, _______
        },
        {
            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
        },
        {
            KC_BSPC, KC_SPC, _______, _______
        }
    }
};